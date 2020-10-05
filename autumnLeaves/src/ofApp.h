#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void drawTreeRec(ofVec3f origin, ofVec3f end, int depth, float winter, bool treeType, float treeBrightness);

    vector<tuple<ofPolyline, float, bool, float>> trees;
    vector<tuple<ofVec3f, float, bool, float>> leaves;


    int treeRows, treeColumns;
    float mountainRadius, mountainCenterX, mountainCenterY;

    float bushiness;

    int mode;

    ofColor green, red, orange;
};
