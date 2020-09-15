#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetRectMode(OF_RECTMODE_CENTER);
  ofBackground(65, 112, 0);

  running = false;
  startTime = ofGetElapsedTimef();

}

void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
  //
  // float delta = mouseY / 300.0;
  // cout << delta << endl;

  //trail.clear();


    for (int i = 0; i < 20; i++) {
      float speed = 0.1 + 0.005 * i;
      float offset = 1;
      float delta = 1.82666;
      if (i >= 10) {
        offset += 0;
        //speed *= -1;
        delta = 1.6;
        speed = 0.11 + 0.0055 * (i - 10);
      }
      float t = offset + (ofGetElapsedTimef() - startTime) * speed;
      //float t = offset + (60 - (ofGetElapsedTimef() - startTime)) * speed;  // reverse
      if (!running) {
        t = offset;
      }

      // float t = 0;
      // while (t < 2 * PI) {
        float xorig = 400;
        float yorig = 500;
        float r = 250;

        // Lissajous curve
        float a = 3;
        float b = 4;
        float c = 2;
        //float delta = 1.82666;
        float delta2 = 2.33333;
        float x = xorig + r * sin(a * t + delta);
        float y = yorig + r * sin(b * t);
        float size = 5 + 250 * pow(sin(c * t + delta2), 4);
        float angle = 90 * sin(0.05 * (t - offset));

        //trail.addVertex(x, y);

        ofNoFill();
        ofSetColor(0);
        ofSetLineWidth(4);
        if (i > 10) {
          ofPushMatrix();
          ofTranslate(x, y);
          ofRotateZDeg(angle);
          ofDrawRectangle(0, 0, size, size);
          ofPopMatrix();
        } else {
          ofDrawRectangle(x, y, size, size);
        }

    //     t+= 0.02;
    // }
    // trail.draw();

  }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

  if (key == 's') {
    running = !running;
    startTime = ofGetElapsedTimef();
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
