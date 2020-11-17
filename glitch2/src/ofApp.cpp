#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup() {
  img.load("cat2.jpg");
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSaveImage(img.getPixels(), "in.png");

    string cmd = "pnglitch data/in.png --filter=" + to_string(mode) + " data/out.png";
    cout << ofSystem(cmd.c_str()) << endl;
    mode++;
    if (mode > 4) {
      mode = 1;
    }

    img.load("out.png");
}

//--------------------------------------------------------------
void ofApp::draw() {

  img.draw(0, 0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == ' ') {
    img.load("cat2.jpg");
    mode = 0;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
