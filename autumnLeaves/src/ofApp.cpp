#include "ofApp.h"

void ofApp::drawTreeRec(ofVec3f origin, ofVec3f end, int depth, float winter, bool treeType, float treeBrightness) {
  cout << "Origin: " << origin << " end " << end << " depth " << depth << endl;

  ofVec3f v = end - origin;
  v.normalize();
  float length = origin.distance(end);

  float newWinter = winter;
  if (ofRandom(1) < 0.25) {
    newWinter = ofRandom(winter, 1);
  }

  if (ofDist(end.x / 1.5, end.y, mountainCenterX / 1.5, mountainCenterY) < mountainRadius) {
  //
  // if (ofDist(v.x, v.y, 0, -1) > 0) {
    // skip the first leaf
    ofPolyline tree;
    tree.addVertex(origin);
    tree.lineTo(end);

    leaves.push_back(make_tuple(end, newWinter, treeType, treeBrightness));

    trees.push_back(make_tuple(tree, newWinter, treeType, treeBrightness));
  }
  // } else {
  //   ofPolyline tree;
  //   tree.addVertex(origin);
  //   tree.lineTo(origin + v * length / 2);
  //
  //   //leaves.push_back(make_tuple(end, newWinter, treeType, treeBrightness));
  //
  //   trees.push_back(make_tuple(tree, newWinter, treeType, treeBrightness));
  // }




  if (depth > 0) {



    float distLeft = 0.75 * length; //1.618; // golden ratio

    while (distLeft > 6) {
      float branchDist = length - distLeft;
      ofVec3f newOrigin = origin + branchDist * v;
      float newLength = 0.75 * distLeft; // / 1.618;

      //cout << "distLeft " << distLeft << " branchDist " << branchDist << " newOrigin " << newOrigin << endl;

      float newAngle = ofRandom(30, 60);
      for (int j = 0; j < 2; j++) { // run twice for each angle (-45, 45)
        if (ofRandom(1) < bushiness) {
          cout << "v " << v << " getRotated " << v.getRotated(newAngle, ofVec3f(0, 0, 1)) << endl;
          ofVec3f newEnd = newOrigin + v.getRotated(newAngle, ofVec3f(0, 0, 1)) * newLength;

          if (ofDist(newEnd.x / 1.5, newEnd.y, mountainCenterX / 1.5, mountainCenterY) < mountainRadius) {
            drawTreeRec(newOrigin, newEnd, depth - 1, newWinter, treeType, treeBrightness);
          }
        }

        newAngle *= -1;
      }

      //distLeft /= 1.618;
      distLeft *= 0.75;
    }
  }
}
//--------------------------------------------------------------
void ofApp::setup(){

  mountainCenterX = ofGetWidth() / 2;
  mountainCenterY = 755;
  mountainRadius = 555;

  treeRows = 12; //12;
  treeColumns = 16; //22;


  bushiness = 1;

  mode = 0;

  green = ofColor(1, 68, 33);
  red = ofColor(156, 39, 6);
  orange = ofColor(198, 119, 39);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  //ofBackground(135, 206, 235);
  ofBackground(0);

  ofSetLineWidth(1);


  // moon
  ofSetColor(255);
  float radius = 60;
  ofPath moon;

  float rad1 = ofMap(mouseX, ofGetWidth() / 2, ofGetWidth(), radius, -radius, true);
  float rad2 = ofMap(mouseX, 0, ofGetWidth() / 2, radius, -radius, true);

  ofPushMatrix();
  moon.setCircleResolution(360);
  moon.arc( 0, 0, rad1, radius, 90, 270);
  moon.arcNegative( 0, 0, rad2, radius, 270, 90);

  ofTranslate(100, 100);
  if (mouseX < ofGetWidth() / 2) {
    ofRotateDeg(-22.5);
  } else {
    ofRotateDeg(22.5);
  }
  moon.draw();
  ofPopMatrix();

  float stdev = ofMap(mouseX, 0, ofGetWidth(), 0, 0.66);

  for (auto& tree : trees) {
    ofColor newColor = green;
    float brightness = newColor.getBrightness();
    brightness += get<3>(tree);
    newColor.setBrightness(brightness);

    float winter = get<1>(tree);
    // gaussian
    float x = exp(- pow(winter - 1, 2) / (2 * pow(stdev, 2)));
    ofColor endColor;
    if (get<2>(tree)){
      endColor = orange;
    } else {
      endColor = red;
    }
    brightness = endColor.getBrightness();
    brightness += get<3>(tree);
    endColor.setBrightness(brightness);
    newColor.lerp(endColor, x);

    ofSetColor(newColor);
    get<0>(tree).draw();
  }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  //bushiness = ofMap(mouseY, 0, ofGetHeight(), 0, 1);
  cout << "bushiness: " << bushiness << endl;

  ofSeedRandom(mouseX * 100);

  cout << "######## START #############" << endl;

  trees.clear();
  leaves.clear();
  for (int i = 0; i < treeRows; i++) {
    // run the loop once for even numbers
    for (int j = 0; j < treeColumns; j += 2) {
      float y = ofMap(i, 0, treeRows, 250, ofGetHeight() + 200) + 5 * ofSignedNoise(j * 0.1, i * 100);
      float x = ofMap(j, 0, treeColumns, 10 * (treeRows - i), ofGetWidth() - 10 * (treeRows - i)); // ofMap(i, 0, treeRows, 150, 0) +
      float treeLen = ofMap(i, 0, treeRows, 60, 300);

      if (ofRandom(1) < 0.999) {
        float brightness = ofRandom(-11, 11); // this number will determine how bright is the tree
        float treeType = ofRandom(1); // this number will determine whether the tree will become red or orange

        drawTreeRec(ofVec2f(x, y), ofVec2f(x, y - treeLen), 3, 0, treeType, brightness);
      }
    }

    // same thing for odd numbers (code replication = :( )
    for (int j = 1; j < treeColumns; j += 2) {
      float y = ofMap(i, 0, treeRows, 250, ofGetHeight() + 200) + 5 * ofSignedNoise(j * 0.1, i * 100);
      float x = ofMap(j, 0, treeColumns, 10 * (treeRows - i), ofGetWidth() - 10 * (treeRows - i)); // ofMap(i, 0, treeRows, 150, 0) +
      float treeLen = ofMap(i, 0, treeRows, 60, 300);

      if (ofRandom(1) < 0.95) {
        float brightness = ofRandom(-11, 11); // this number will determine how bright is the tree
        bool treeType = ofRandom(1) > 0.33; // this number will determine whether the tree will become red or orange

        drawTreeRec(ofVec2f(x, y), ofVec2f(x, y - treeLen), 3, 0, treeType, brightness);
      }
    }
  }



  cout << "########## END #############" << endl;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

  if (key >= '1' && key <= '9') {
    mode = key - '1';
  }

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
