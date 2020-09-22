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

  string horiz = "HORIZ";
  for (int i = 0; i < horiz.length(); i++) {
    string s(1, horiz.at(i));
    if (s != "I") {
      font.drawString(s, ofMap(i, 0, horiz.length() - 1, 5, mouseX - 35), mouseY);
    } else {
      // hack the I
      font.drawString(s, ofMap(i, 0, horiz.length() - 1, 18, mouseX - 22), mouseY);
    }
  }

  string ontal = "ONTAL";
  for (int i = 0; i < ontal.length(); i++) {
    string s(1, ontal.at(i));
    font.drawString(s, ofMap(i, 0, ontal.length() - 1, mouseX + 30, 755), mouseY);
  }

  string vert = "VERT";
  for (int i = 0; i < vert.length(); i++) {
    string s(1, vert.at(i));
    font.drawString(s, mouseX, ofMap(i, 0, vert.length() - 1, 55, mouseY - 50));
  }

  string ical = "ICAL";
  for (int i = 0; i < ical.length(); i++) {
    string s(1, ical.at(i));
    if (i > 0) {
      font.drawString(s, mouseX, ofMap(i, 0, ical.length() - 1, mouseY + 50, 795));
    } else {
      // hack the I
      font.drawString(s, mouseX + 13, ofMap(i, 0, ical.length() - 1, mouseY + 50, 795));
    }
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
