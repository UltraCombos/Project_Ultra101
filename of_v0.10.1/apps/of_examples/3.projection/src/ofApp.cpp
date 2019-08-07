#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	
	ofDisableArbTex();
	ofLoadImage(_tex, "lena_color.gif");	
	
	update_projection_matrix();

	ofSetFrameRate(60);
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle("FOV Y: " + ofToString(_fovy, 1));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();

	ofSetMatrixMode(OF_MATRIX_PROJECTION);
	ofLoadMatrix(_proj);

	ofSetMatrixMode(OF_MATRIX_MODELVIEW);
	ofLoadIdentityMatrix();
		
	ofScale(1, -1, 1);
	ofTranslate(0, 0, -3);
		
	ofDrawAxis(2);	
	ofRotate(ofGetElapsedTimef() * 100, 1, 1, 1);
	
	ofFill();
	_tex.bind();
	ofDrawBox(0.1);
	_tex.unbind();

	ofNoFill();
	for(int i=0;i<50;++i)
		ofDrawBox(i*0.1);
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
	update_projection_matrix();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	_fovy += scrollY;
	_fovy = ofClamp(_fovy, 10, 120);
	update_projection_matrix();
}

void ofApp::update_projection_matrix()
{
	_proj.makePerspectiveMatrix(_fovy, (float)ofGetWidth() / ofGetHeight(), 0.1, 10);
}

