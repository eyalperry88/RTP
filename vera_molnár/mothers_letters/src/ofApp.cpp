#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(0);

  // lines
  ofSeedRandom(mouseX);
  ofPolyline line;
  for (int i = 0; i < 29; i++) {

    int x = 950;
    int y = 50 + i * 23;
    int direction = 1;

    while (x > 50) {
      ofPoint pt;

      // chaotic to the right, order to the left
      //float randomIntensity = ofMap(x, 50, 1000, 0, 1.5);
      //float scale = 2 + randomIntensity * randomIntensity * 24;

      // chaos in the middle
      float randomIntensity = 1 - ofMap(abs(x - 500), 0, 450, 0, 1);
      float scale = 2 + randomIntensity * randomIntensity * randomIntensity * randomIntensity * 24;



      if (ofRandom(1) < 0.95) {
        pt.set(x + ofSignedNoise(x * 0.033 + i * 1000, mouseX * 0.01) * scale, y + ofSignedNoise(x * 0.03 + i * 1000, mouseY * 0.01));
      } else {
        // once in a while, add a lot of noise on the Y for letters that exit the row
        pt.set(x + ofSignedNoise(x * 0.033 + i * 1000, mouseX * 0.01) * scale, y + ofRandom(-scale, scale));
      }
      line.addVertex(pt);

      if (direction) {
        x -= 12;
        y += 20;
      } else {
        x += 6;
        y -= 20;
      }

      direction = 1 - direction;

      if (i == 0 && x < 80) {
        break;
      }
    }

  }
  line.draw();

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
