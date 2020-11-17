#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup() {
  grabber.setup(640, 480);
  tracker.setup();

  img.allocate(640, 480, OF_IMAGE_COLOR);

  buffer.reserve(640*480);
  buffer2.reserve(640*480);
}

//--------------------------------------------------------------
void ofApp::update() {

  grabber.update();

  if(grabber.isFrameNew()) {
    tracker.update(toCv(grabber));

    if(tracker.size() > 0){

      ofPolyline leftEyePoly = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
      ofPolyline rightEyePoly = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
      ofPolyline jawPoly = tracker.getImageFeature(ofxFaceTracker::JAW);

      if (leftEyePoly.size() > 0 && jawPoly.size() > 0) {
        leftEye.set(0,0);
        for(int i = 0; i < leftEyePoly.size(); i++){
          leftEye += leftEyePoly[i];
        }
        leftEye /= (float)leftEyePoly.size();

        rightEye.set(0,0);
        for(int i = 0; i < rightEyePoly.size(); i++){
          rightEye += rightEyePoly[i];
        }
        rightEye /= (float)rightEyePoly.size();

        jaw.set(0,0);
        for(int i = 0; i < jawPoly.size(); i++){
          jaw += jawPoly[i];
        }
        jaw /= (float)jawPoly.size();


        leftEyeSmoothed = 0.75 * leftEyeSmoothed + 0.25 * leftEye;
        rightEyeSmoothed = 0.75 * rightEyeSmoothed + 0.25 * rightEye;
        jawSmoothed = 0.75 * jawSmoothed + 0.25 * jaw;

        ofSaveImage(grabber.getPixels(), buffer, OF_IMAGE_FORMAT_JPEG, OF_IMAGE_QUALITY_BEST);

        int idx1 = leftEyeSmoothed.x + leftEyeSmoothed.y * 640;
        int i = ofMap(idx1, 0, 640 * 480, 0, buffer.size() - 1);
        int idx2 = jawSmoothed.x + jawSmoothed.y * 640;
        int j = ofMap(idx2, 0, 640 * 480, 0, buffer.size() - 1);
        int idx3 = rightEyeSmoothed.x + rightEyeSmoothed.y * 640;
        int k = ofMap(idx3, 0, 640 * 480, 0, 255);

        //cout << buffer.size() << " , " << i << " , " << j << " : " << (j - i) << endl;

        if (j > i) {
          buffer2.clear();

          char* data = new char[1];
          data[0] = k;
          buffer2.append(buffer.getData(), i);
          buffer2.append(data, 1);
          buffer2.append(buffer.getData() + i + 1, j - i - 1);
          buffer2.append(data, 1);
          buffer2.append(buffer.getData() + j + 2, buffer.size() - j - 2);

          img.load(buffer2);
        }

      }
    }
  }

}

//--------------------------------------------------------------
void ofApp::draw() {

  img.draw(0, 0);

  if (tracker.size() > 0) {
    // ofDrawCircle(rightEyeSmoothed.x, rightEyeSmoothed.y, 2);
    //
    // ofDrawCircle(leftEyeSmoothed.x, leftEyeSmoothed.y, 4);
    //
    // ofDrawCircle(jawSmoothed.x, jawSmoothed.y, 6);
  }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
