#include "ofApp.h"


int main() {
    ofSetupOpenGL(600, 300, OF_WINDOW);
    return ofRunApp(std::make_shared<ofApp>());
}
