#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  font.load("Roboto-Regular.ttf", 50);

  ofHideCursor();

  ofSetFrameRate(30);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  ofBackground(17);

  float p = ofRandom(100);
  // pick letters by frequency table: http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
  string c = "X";
  if (p < 12) {
    c = 'E';
  } else if (p < 21) {
    c = 'T';
  } else if (p < 29) {
    c = 'A';
  } else if (p < 37) {
    c = 'O';
  } else if (p < 44) {
    c = 'I';
  } else if (p < 51) {
    c = 'N';
  } else if (p < 57) {
    c = 'S';
  } else if (p < 63) {
    c = 'R';
  } else if (p < 69) {
    c = 'H';
  } else if (p < 73) {
    c = 'D';
  } else if (p < 77) {
    c = 'L';
  } else if (p < 80) {
    c = 'U';
  } else if (p < 83) {
    c = 'C';
  } else if (p < 86) {
    c = 'M';
  } else if (p < 88) {
    c = 'F';
  } else if (p < 90) {
    c = 'Y';
  } else if (p < 92) {
    c = 'W';
  } else if (p < 94) {
    c = 'G';
  } else if (p < 96) {
    c = 'P';
  } else if (p < 97) {
    c = 'B';
  } else if (p < 98) {
    c = 'V';
  } else if (p < 99) {
    c = 'K';
  } else if (p < 99.25) {
    c = 'X';
  } else if (p < 99.5) {
    c = 'Q';
  } else if (p < 99.75) {
    c = 'J';
  } else if (p < 100) {
    c = 'Z';
  }

  chars.push_back(c);
  xs.push_back(mouseX);
  ys.push_back(mouseY);
  if (chars.size() > 13) {
    chars.erase(chars.begin());
    xs.erase(xs.begin());
    ys.erase(ys.begin());
  }

  for(int i=0; i < chars.size(); i++){
     ofSetColor(255, 255, 255, ofMap(i, 0, chars.size(), 18, 255));
     font.drawString(chars[i], xs[i], ys[i]);
  }





}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
