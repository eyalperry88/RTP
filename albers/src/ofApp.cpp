#include "ofApp.h"

// checks if two lines (u and v) intersect
bool intersects(ofVec3f u1, ofVec3f u2, ofVec3f v1, ofVec3f v2) {
    // taken from https://forum.openframeworks.cc/t/segment-polyline-intersection/24830/3

    ofVec2f originA(u1.x, u1.y);
    ofVec2f vecA(u2.x - u1.x, u2.y - u1.y);
    ofVec2f originB(v1.x, v1.y);
    ofVec2f vecB(v2.x - v1.x, v2.y - v1.y);

    float s, t;
    s = -vecA.y * (originA.x - originB.x);
    s += vecA.x * (originA.y - originB.y);
    s /= (-vecB.x * vecA.y + vecA.x * vecB.y);

    t = vecB.x * (originA.y - originB.y);
    t -= vecB.y * (originA.x - originB.x);
    t /= (-vecB.x * vecA.y + vecA.x * vecB.y);

    return (s >= 0 && s <= 1 && t >= 0 && t <= 1);
}

// given a point and a direction - returns a new point with a random angle (-pi to pi) and random step size (30 to 60)
ofVec3f newPoint(ofVec3f oldPoint, ofVec3f direction) {
  float randomAngle = ofRandom(-PI, PI);
  ofVec3f newDirection;
  newDirection.x = cos(randomAngle) * direction.x - sin(randomAngle) * direction.y;
  newDirection.y = sin(randomAngle) * direction.x + cos(randomAngle) * direction.y;
  ofVec3f newP = oldPoint + newDirection * ofRandom(30, 60);

  return newP;
}

// --------------------------------------------------------------
void ofApp::setup(){

  ofBackground(47);

  ofSetCurveResolution(100);

  ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){

  cam.begin();


  for (int i=0; i < line.size(); i++) {
    ofSetColor(255);
    ofDrawCircle(line[i].x, line[i].y, line[i].z, 8);
  }

  for (int i=0; i < line.size(); i++) {
    ofSetColor(47);
    ofDrawCircle(line[i].x, line[i].y, line[i].z+2, 6);
  }

  // uncomment this to see the nodes
  // for (int i = 0; i < NODE_NUM; i++) {
  //
  //
  //   ofSetColor(255);
  //   ofDrawCircle(nodes[i].x, nodes[i].y, 8);
  //
  //   if (updown[i] == 0) {
  //     ofSetColor(0, 255, 0);
  //   } else if (updown[i] == 1) {
  //     ofSetColor(255, 0, 0);
  //   } else {
  //     ofSetColor(0);
  //   }
  //   ofDrawBitmapString(std::to_string(i), nodes[i].x, nodes[i].y);
  //
  // }

  cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  ofSeedRandom(mouseX * mouseY);

  line.clear();
  cout << "------------------------" << endl;

  vector<pair<int, int>> existingEdges;
  int degree[NODE_NUM]; // node degree

  // disperse the nodes on a grid, with some random pertubations
  int idx = 0;
  for (int i = 0; i < SQRT_NODE_NUM; i++) {
    float shift = ofRandom(0, PI);
    for (int j = 0; j < SQRT_NODE_NUM; j++) {
      nodes[idx].x = ofMap(i, 0, SQRT_NODE_NUM, 50, 750) + ofRandom(-25, 25);
      nodes[idx].y = ofMap(j, 0, SQRT_NODE_NUM, 50, 750) + ofRandom(-25, 25);

      degree[idx] = 0;
      updown[idx] = -1;
      idx++;
    }
  }

  // initialize starting node (middle), starting direction etc
  ofVec3f direction(1, 0, 0);
  int startNode = 45;
  int currentNode = startNode;
  line.addVertex(ofPoint(nodes[currentNode].x, nodes[currentNode].y, 0));
  updown[currentNode] = 1;

  // as long as we don't get stuck
  while (true) {
    degree[currentNode]++;

    // take a random step "forward"
    ofVec3f oneStepForward = newPoint(nodes[currentNode], direction);

    // now sort all of the nodes by the distance from that point
    vector<pair<float, int>> dists;
    for (int j = 0; j < NODE_NUM; j++) {
      if (j == currentNode) {
        continue;
      }
      float distFromCenter = ofDist(400, 400, nodes[j].x, nodes[j].y);
      if (distFromCenter > 350) {
        continue;
      }
      float dist = ofDist(oneStepForward.x, oneStepForward.y, nodes[j].x, nodes[j].y);
      dists.push_back(make_pair(dist, j));
    }
    sort(dists.begin(), dists.end());


    // now, go over the node list by order and find another *suitable* node to connect to
    int toNode;
    bool foundIt = false;
    for (int i = 0; i < dists.size(); i++) {
      toNode = dists[i].second;
      cout << "trying toNode " << toNode << " ... ";

      if (updown[currentNode] == updown[toNode]) {
        // nodes are already assigned with up/down, and have the same assignment (not weaving!)
        cout << "Bad Up/Down combination" << endl;
        continue;
      }

      if (degree[toNode] >= 3) {
        // the node we aim for needs to have degree of less than 3, otherwise it has been visited too much
        cout << "Nodes degree is too high " << degree[toNode] << endl;
        continue;
      }

      auto newDirection = nodes[toNode] - nodes[currentNode];
      newDirection.normalize();
      if ((newDirection.x * direction.x + newDirection.y * direction.y) < -0.75) {
        // the next node must be in the same direction
        cout << "The direction is too negative :( " << (newDirection.x * direction.x + newDirection.y * direction.y) << endl;
        continue;
      }

      // and most importantly, try not to intersect ny existing edges....
      bool doesIntersects = false;
      for (auto edge : existingEdges) {
        if (currentNode != edge.first && currentNode != edge.second && toNode != edge.first && toNode != edge.second) {
          if (intersects(nodes[edge.first], nodes[edge.second], nodes[currentNode], nodes[toNode])) {
            doesIntersects = true;
            cout << "intersects with " << edge.first << "-->" <<  edge.second << endl;
            break;
          }
        }
      }
      if (doesIntersects) {
        // can't go to this node because it is NOT reachable.. try another
        continue;
      }

      // we are good!
      foundIt = true;
      break;
    }

    if (!foundIt) {
      cout << "Stuck!";
      break;
    }

    existingEdges.push_back(make_pair(currentNode, toNode));
    updown[toNode] = 1 - updown[currentNode];
    degree[toNode]++;

    float z = 0;
    if (degree[toNode] > 2) {
      // this is the second time we hit the node - change the z to create the weave
      if (updown[toNode]) {
        z += 10;
      } else {
        z -= 10;
      }
    }
    line.curveTo(ofPoint(nodes[toNode].x, nodes[toNode].y, z));
    direction = nodes[toNode] - nodes[currentNode];
    direction.normalize();
    cout << currentNode << "(" << updown[currentNode] << ", " << degree[currentNode] << ") --> " << toNode << "(" << updown[toNode] << ", " << degree[toNode] << ")" << endl;

    currentNode = toNode;
  }

  line= line.getResampledBySpacing(1);
  //line= line.getSmoothed(4);

  // print degrees
  for (int i = 0; i < NODE_NUM; i++) {
    cout << i << ":" << degree[i] << "   ";
  }
  cout << endl;


  cout << "------------------------" << endl;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){




}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
