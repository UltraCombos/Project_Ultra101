#include "ofCameraApp.h"
ofFbo fbo;
//--------------------------------------------------------------
void ofCameraApp::setup(){	
	ofDisableArbTex();
	ofLoadImage(_tex, "lena_color.gif");	
	
	ofSetFrameRate(60);
	ofBackground(0);

	camera.setupPerspective(false, 60, 0.1, 100);
	camera.setPosition({ 3,1,3 });
	camera.lookAt({ 0,1,0 }, { 0,1,0 });

	_model.makeTranslationMatrix(0, 1, 0);
	ofSetWindowTitle(string(typeid(*this).name()).substr(6));
	fbo.allocate(800, 600, GL_RGBA8);
}

//--------------------------------------------------------------
void ofCameraApp::update(){
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
void ofCameraApp::draw(){
	ofEnableDepthTest();
	
	camera.begin();
	{
		//////////////////////////////////////////////////////////////////////////
		//world space
		ofPushMatrix();
		ofDrawAxis(10);
		ofRotate(90, 0, 0, 1);
		ofDrawGridPlane(1, 10, true);
		ofPopMatrix();
		//////////////////////////////////////////////////////////////////////////
		ofMultMatrix(_model);
		//////////////////////////////////////////////////////////////////////////
		//model space
		ofDrawAxis(1);
		ofFill();
		_tex.bind();
		ofDrawBox(1);
		_tex.unbind();
	}
	camera.end();
}

//--------------------------------------------------------------
void ofCameraApp::keyPressed(int key){
#if 1
	float step = 0.1;
	switch (key)
	{
	case 'a':case 'A':
		camera.move(-camera.getXAxis()*step);
		break;
	case 'd':case 'D':
		camera.move(camera.getXAxis()*step);
		break;
	case 's':case 'S':
		camera.move(camera.getZAxis()*step);
		break;
	case 'w':case 'W':
		camera.move(-camera.getZAxis()*step);
		break;	
	}
#endif
}

//--------------------------------------------------------------
void ofCameraApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofCameraApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofCameraApp::mouseDragged(int x, int y, int button){
#if 1
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
		ofMatrix4x4 view = camera.getLocalTransformMatrix().getInverse();
		view = view*rot;
		camera.setTransformMatrix(view.getInverse());
		break;
	}
	case OF_MOUSE_BUTTON_1:
		ofMatrix4x4 t;
		diff *= 0.01f;
		camera.move(-camera.getXAxis()*diff.x);
		camera.move(camera.getYAxis()*diff.y);
		break;
	}
#endif
}

//--------------------------------------------------------------
void ofCameraApp::mousePressed(int x, int y, int button){
	
	
}

//--------------------------------------------------------------
void ofCameraApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofCameraApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofCameraApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofCameraApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofCameraApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofCameraApp::dragEvent(ofDragInfo dragInfo){ 

}


