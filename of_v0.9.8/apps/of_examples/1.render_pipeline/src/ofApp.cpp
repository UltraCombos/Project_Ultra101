#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLoadImage(_tex, "lena_color.gif");
	ofBackground(0);
	glPointSize(10);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(_is_fill ? "Fill" : "No Fill");
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	if (_is_fill)
		ofFill();
	else
		ofNoFill(); 
	
	glBegin(_primative_type);	
	glVertex2f(150,  50);
	glVertex2f(350,  50);
	glVertex2f(350, 250);
	glVertex2f(150, 250);
	glEnd();
	
	ofSetColor(0, 255, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(450, 50);
	glVertex2f(650, 50);
	glVertex2f(650, 250);
	glVertex2f(450, 250);
	glEnd();
	
	ofSetColor(255, 255, 255);
	_tex.bind();
	glBegin(GL_TRIANGLE_FAN);
	
	glTexCoord2f(0, 0);
	glVertex2f(150, 350);

	glTexCoord2f(_tex.getWidth(), 0);
	glVertex2f(350, 350);
	
	glTexCoord2f(_tex.getWidth(), _tex.getHeight());
	glVertex2f(350, 550);
	
	glTexCoord2f(0, _tex.getHeight());
	glVertex2f(150, 550);
	
	glEnd();
	_tex.unbind();

	
	_tex.draw(450, 350, 200, 200);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key)
	{
	case '1':
		_primative_type = GL_POINTS;
		break;
	case '2':
		_primative_type = GL_LINE_LOOP;
		break;
	case '3':
		_primative_type = GL_TRIANGLE_FAN;
		break;
	case 'f':case'F':
		_is_fill = !_is_fill;
		break;
	}
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