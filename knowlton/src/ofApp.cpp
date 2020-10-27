#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  img.load("conure.jpg");
  //img.load("bix.jpg");

  diceSize = 15;

  ofSetCircleResolution(100);
}

//--------------------------------------------------------------
void ofApp::update(){

}

ofColor ofApp::getAverageColor(int x, int y) {
  float r = 0;
  float g = 0;
  float b = 0;
  float count = 0;
  for (int i = x-diceSize/2; i < x + diceSize/2; i++) {
    for (int j = y-diceSize/2; j < y + diceSize/2; j++) {
      ofColor color = img.getColor(ofClamp(i, 0, img.getWidth()-1), ofClamp(j, 0, img.getHeight()-1));
      r += color.r;
      g += color.g;
      b += color.b;
      count += 1;
    }
  }

  return ofColor(r/count, g/count, b/count);
}

//--------------------------------------------------------------
void ofApp::draw(){
  //ofScale(2);
  ofBackground(0);

  ofSeedRandom(mouseX);


  for (int i = 0; i < img.getWidth(); i += diceSize) {
    for (int j = 0; j < img.getHeight(); j += diceSize) {
      ofColor color = img.getColor(i+diceSize/2, j+diceSize/2); //getAverageColor(i+diceSize/2, j+diceSize/2);
      ofColor diceColor;
      float hue = color.getHue();
      float brightness = color.getBrightness();

      if (ofRandom(1) < 0.005) {
        brightness = ofRandom(255);
        hue = ofRandom(100);
      }



      int dice = round(ofMap(brightness, 0, 255, 1, 6));
      //cout << dice << endl;

      ofFill();
      //ofSetColor(color);
      if (brightness < 80) {
        ofSetColor(240, 240, 240); // white
        diceColor = ofColor(0);
        //ofSetColor(25, 25, 25); // black
        //diceColor = ofColor(255);
      } else if (hue < 25) {
        ofSetColor(180, 60, 60); // red
        diceColor = ofColor(255);
      } else if (hue >= 25 && hue < 50) {
        ofSetColor(205, 180, 70); // yellow
        diceColor = ofColor(0);
      } else if (hue >= 50 && hue < 75) {
        ofSetColor(70, 140, 70); // green
        diceColor = ofColor(255);
      } else {
        ofSetColor(50, 100, 200); // blue
        diceColor = ofColor(255);
      }
      ofDrawRectangle(i, j, diceSize-1, diceSize-1);

      ofSetColor(diceColor);
      if (dice == 1 || dice == 3 || dice == 5) {
        //cout << (i+diceSize/2+1) << " " << (j+diceSize/2 + 1) << " " << diceSize/10 << endl;
        ofDrawCircle(i+diceSize/2, j+diceSize/2, diceSize/10);
      }
      if (dice > 1) {
        ofDrawCircle(i+3, j+3, diceSize/10);
        ofDrawCircle(i+diceSize-4, j+diceSize-4, diceSize/10);
      }
      if (dice > 3) {
        ofDrawCircle(i+3, j+diceSize-4, diceSize/10);
        ofDrawCircle(i+diceSize-4, j+3, diceSize/10);
      }
      if (dice == 6) {
        ofDrawCircle(i+3, j+diceSize/2, diceSize/10);
        ofDrawCircle(i+diceSize-4, j+diceSize/2, diceSize/10);
      }

    }
  }

  ofSetColor(255);
  int tmp = floor(img.getWidth() / diceSize) + 1;
  img.draw(tmp*diceSize, 0);
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
