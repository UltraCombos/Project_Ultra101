#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	for (int i = 0; i < 200; ++i)
	{
		ofVec2f pos(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));		
		ofVec2f vel (ofRandom(-1, 1), ofRandom(-1, 1));
		Cell * cell = nullptr;
		if (ofRandom(1.f) < 0.8f)
			cell = new DotCell(pos, vel);   //polymorphism
		else
			cell = new SquareCell(pos, vel);//polymorphism
		cells.push_back(cell);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for (Cell* cell : cells)
		cell->move(); // dynamic binding
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (Cell* cell : cells)
		cell->draw(); // dynamic binding
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