#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //grabber.listDevices();
    //grabber.setDeviceID(1);
    grabber.initGrabber(640, 480);

    cam.allocate(grabber.getWidth(),
                grabber.getHeight(),
                OF_IMAGE_COLOR);

    bg.allocate(grabber.getWidth(),
                grabber.getHeight(),
                OF_IMAGE_COLOR);

    diffImg.allocate(grabber.getWidth(),
                    grabber.getHeight(),
                    OF_IMAGE_COLOR);


    threshImg.allocate(grabber.getWidth(),
                      grabber.getHeight(),
                      OF_IMAGE_GRAYSCALE);

    bRecordBg = true;
}

//--------------------------------------------------------------
void ofApp::update(){


    grabber.update();
    if (grabber.isFrameNew()){
        cam.setFromPixels(grabber.getPixels());
        cam.update();

        if (bRecordBg){
            bg.setFromPixels(cam.getPixels());
            bg.update();
            bRecordBg = false;
        }

        absdiff(cam, bg, diffImg);
        diffImg.update();

        convertColor(diffImg, threshImg, CV_RGB2GRAY);
        threshold(threshImg, mouseX / 10);
        erode(threshImg, 8);
        dilate(threshImg, 8);
        cout << (mouseX / 10) << endl;
        threshImg.update();

        finder.setSortBySize(true);
        //finder.setMinArea(10);
        finder.findContours(threshImg);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(33);

  float t = ofGetElapsedTimef();

    if (debug) {
      ofScale(0.5, 0.5);
      ofSetColor(255);
      grabber.draw(0,0);
      ofSetColor(255);
      cam.draw(grabber.getWidth(), 0);
      // bg.draw(0, grabber.getHeight());
      // diffImg.draw(grabber.getWidth(), grabber.getHeight());
      threshImg.draw(grabber.getWidth()*2, 0);
    } else {
      ofScale(2, 2);
    }

    if (finder.size() > 0){
        ofPushMatrix();
          if (debug) {
            ofTranslate(grabber.getWidth(), grabber.getHeight() * 1.2);
          }
          ofSetColor(160, 80, 80);
          auto poly = finder.getPolyline(0).getSmoothed(2);

          int rightmostX = 0;
          int rightmostY = 0;
          int topmostX = 0;
          int topmostY = ofGetHeight();
          ofBeginShape();
              for( int i = 0; i < poly.getVertices().size(); i++) {
                  int x = poly.getVertices().at(i).x;
                  int y = poly.getVertices().at(i).y;
                  ofVertex(x, y);

                  if (x > rightmostX && y < grabber.getHeight() * 0.75) {
                      rightmostX = x;
                      rightmostY = y;
                  }
                  if (y < topmostY) {
                      topmostX = x;
                      topmostY = y;
                  }
              }
          ofEndShape();

          smoothX = 0.75 * smoothX + 0.25 * rightmostX;
          smoothY = 0.75 * smoothY + 0.25 * rightmostY;

          ofSetColor(80, 90, 10);
          ofSetLineWidth(2);
          float pendulumX = smoothX + 40 * cos(t * 3.741);
          float pendulumY = smoothY + 120;
          ofDrawLine(smoothX, smoothY, pendulumX, pendulumY);

          ofPushMatrix();

            float scale = 4;
            ofTranslate(pendulumX - ((grabber.getWidth() - topmostX) / scale), pendulumY - (topmostY / scale));
            //ofSetColor(0, 90, 80);
            ofBeginShape();
                for( int i = 0; i < poly.getVertices().size(); i++) {
                    float x = grabber.getWidth() - poly.getVertices().at(i).x;
                    float y = poly.getVertices().at(i).y;
                    ofVertex(x / scale, y / scale);
                }
            ofEndShape();
          ofPopMatrix();

        ofPopMatrix();

    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' ' ){
        bRecordBg = true;
    } else if (key == 'd') {
      debug = !debug;
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
