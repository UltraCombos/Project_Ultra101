#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);
	float w = ofGetWidth() / 100;
	float h = ofGetHeight() / 100;
	proj.makeOrthoMatrix(-w / 2, w / 2, -h / 2, h / 2,-10,10);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(proj.getPtr());
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//////////////////////////////////////////////////////////////////////////
	{
		drawGrid();

		glGetFloatv(GL_MODELVIEW_MATRIX, cur.getPtr());

		glTranslatef(1, 1, 0);	printCurrentModelMat();

		glRotatef(30, 0, 0, 1);	printCurrentModelMat();

		//////////////////////////////////////////////////////////////////////////
		//Draw a rectangle
		ofSetColor(128);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0);
		glVertex2f(2, 0);
		glVertex2f(2, 1);
		glVertex2f(0, 1);
		glEnd();

		//Draw one point
		ofSetColor(255, 255, 0);
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(2, 0);
		glEnd();

	}
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


void ofApp::drawGrid()
{
	ofSetColor(96);
	glPushMatrix();
	//ofDrawGrid(1,8,true,true,true,false);
	glRotatef(90, 0, 1, 0);
	ofDrawGridPlane(1, 8, true);
	glPopMatrix();
}

void ofApp::printCurrentModelMat()
{
	pre = cur;
	glGetFloatv(GL_MODELVIEW_MATRIX, cur.getPtr());
	cout << "R1=" << cur * pre.getInverse() << endl << endl;
}

