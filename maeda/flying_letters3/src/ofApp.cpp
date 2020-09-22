#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  font.load("Roboto-Regular.ttf", 50);

  ofHideCursor();

  ofSetFrameRate(30);

  running = false;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  ofBackground(0);

  if (running) {
    for (int i = 0; i < 2; i++) {
      xs.push_back(ofRandom(-100, 800));
      ys.push_back(ofRandom(850));
      bw.push_back(false);
    }

    // insert black
    xs.push_back(mouseX);
    ys.push_back(mouseY);
    bw.push_back(true);

    if (bw.size() > 10000) {
      cout << "hit limit" << endl;
      xs.erase(xs.begin());
      ys.erase(ys.begin());
      bw.erase(bw.begin());
    }

    for(int i=0; i < xs.size(); i++){
      if (bw[i]){
        ofSetColor(0);
        font.drawString("black", xs[i], ys[i]);
      } else {
        ofSetColor(255);
        font.drawString("white", xs[i], ys[i]);
      }

    }
  }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if (key == 's') {
    running = !running;
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
