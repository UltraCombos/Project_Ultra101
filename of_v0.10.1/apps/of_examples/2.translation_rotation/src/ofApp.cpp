#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLoadImage(_tex, "lena_color.gif");
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	{		
		ofTranslate(100, 100);
		_tex.draw(0, 0, 250, 250);
		
		ofTranslate(350, 0);
		_tex.draw(0, 0, 250, 250);
	}
	ofPopMatrix();

	ofPushMatrix();
	{
		ofTranslate(100, 450);
		ofTranslate(250 / 2, 250 / 2);		
		ofRotate(ofGetElapsedTimef() * 200+45);
		ofTranslate(-250 / 2, -250 / 2);
		_tex.draw(0, 0, 250, 250);
	}
	ofPopMatrix();

	ofMatrix4x4 mat;
	mat.translate(-250 / 2, -250 / 2, 0.0);
	mat.rotate(ofGetElapsedTimef() * 200, 0, 0, 1);
	mat.translate(250 / 2, 250 / 2, 0.0);
	mat.translate(100, 450, 0.0);
	ofPushMatrix();
	{
		ofMultMatrix(mat);
		_tex.draw(0, 0, 250, 250);
	}
	ofPopMatrix();
	
	ofRotate(ofGetElapsedTimef() * -200);
	_tex.draw(450,450, 250, 250);
	
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