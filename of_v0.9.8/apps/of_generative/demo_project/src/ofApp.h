#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
	// setup > update > draw > update > draw > .......(loop)
	void setup();
	void update();
	void draw();
	
	// only happened when the event is triggered
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
#if 0
	// define mouse_position as a vector of ofVec2f to store mouse position history
	vector<ofVec2f> mouse_position;
#endif

	// this is for storing the line we are dragging
	ofPolyline current_line;
	// history lines we have drawn
	vector<ofPolyline> history_lines;
	// minor lines
	vector<ofPolyline> minor_lines;

};
