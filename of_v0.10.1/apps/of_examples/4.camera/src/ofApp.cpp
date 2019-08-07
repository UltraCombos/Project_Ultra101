#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){	
	ofDisableArbTex();
	ofLoadImage(_tex, "lena_color.gif");	
	
	ofSetFrameRate(60);
	ofBackground(0);

	_proj.makePerspectiveMatrix(60, (float)ofGetWidth() / ofGetHeight(), 0.1, 100);
	_view.makeLookAtViewMatrix({ 3,1,3 }, { 0,1,0 }, { 0,1,0 });
	_model.makeTranslationMatrix(0, 1, 0);
	ofSetWindowTitle(string(typeid(*this).name()).substr(6));
}

//--------------------------------------------------------------
void ofApp::update(){
	float tmp = ofGetElapsedTimef();
	float delta = tmp - _time_stamp;
	_time_stamp = tmp;

	ofMatrix4x4 rot;
	rot.makeRotationMatrix(delta * 100, 1, 1, 1);
	ofVec3f pos = _model.getTranslation();
	_model.setTranslation(ofVec3f::zero());
	_model = _model*rot;
	_model.setTranslation(pos);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();

	ofSetMatrixMode(OF_MATRIX_PROJECTION);
	ofLoadMatrix(_proj);
	ofScale(1, -1, 1);
	ofSetMatrixMode(OF_MATRIX_MODELVIEW);
	//////////////////////////////////////////////////////////////////////////
	//camera space

	//////////////////////////////////////////////////////////////////////////
	ofLoadMatrix(_model*_view);
	//////////////////////////////////////////////////////////////////////////
	//model space
	ofDrawAxis(1);
	ofFill();
	_tex.bind();
	ofDrawBox(1);
	_tex.unbind();
	//////////////////////////////////////////////////////////////////////////
	ofLoadMatrix(_view);
	//////////////////////////////////////////////////////////////////////////
	//world space
	ofDrawAxis(10);
	ofRotate(90, 0, 0, 1);
	ofDrawGridPlane(1,10, true);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	ofMatrix4x4 camMat = _view.getInverse();
	float step = 0.1;
	switch (key)
	{
	case 'a':case 'A':
		camMat.preMultTranslate(ofVec3f(-step, 0, 0));
		break;
	case 'd':case 'D':
		camMat.preMultTranslate(ofVec3f(step, 0, 0));
		break;
	case 's':case 'S':
		camMat.preMultTranslate(ofVec3f(0, 0,  step));
		break;
	case 'w':case 'W':
		camMat.preMultTranslate(ofVec3f(0, 0, -step));
		break;	
	}
	_view = camMat.getInverse();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofVec2f premouse(ofGetPreviousMouseX(), ofGetPreviousMouseY());
	ofVec2f mouse(x, y);
	ofVec2f diff = mouse - premouse;

	switch (button)
	{
	case OF_MOUSE_BUTTON_3:
	{
		float theta = 0.1f*diff.length();
		ofVec2f axis = diff.normalize();
		ofMatrix4x4 rot;
		rot.makeRotationMatrix(theta, axis.y, axis.x, 0);
		_view = _view*rot;
		break;
	}
	case OF_MOUSE_BUTTON_1:
		ofMatrix4x4 t;
		diff *= 0.01f;
		t.makeTranslationMatrix(diff.x, -diff.y, 0);
		_view = _view*t;
		break;
	}

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


