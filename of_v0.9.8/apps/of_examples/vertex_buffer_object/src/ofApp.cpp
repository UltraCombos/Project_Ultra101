#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLoadImage(_tex, "lena_color.gif");
	ofBackground(0);

	float verts[] = { 150,350,350,350,350,550,150,550 };
	float coords[] = { 0,0,_tex.getWidth() ,0,_tex.getWidth() ,_tex.getHeight(),0,_tex.getHeight() };
	vbo.setVertexData((ofVec2f*)verts, 4, GL_STATIC_DRAW);
	vbo.setTexCoordData((ofVec2f*)coords, 4, GL_STATIC_DRAW);
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
	//////////////////////////////////////////////////////////////////////////
	//Top Left
	ofSetColor(255, 255, 255);
	_tex.bind();
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0, 0);
	glVertex2f(150, 50);
	glTexCoord2f(_tex.getWidth(), 0);
	glVertex2f(350, 50);
	glTexCoord2f(_tex.getWidth(), _tex.getHeight());
	glVertex2f(350, 250);
	glTexCoord2f(0, _tex.getHeight());
	glVertex2f(150, 250);
	glEnd();
	_tex.unbind();

	ofSetColor(0, 255, 0);
	ofDrawBitmapString("glVertex()", 150 + 5, 50 + 10);
	//////////////////////////////////////////////////////////////////////////
	//Top Right

	ofSetColor(255, 255, 255);
	float verts[] = {450,50,650,50,650,250,450,250};
	float coords[] = {0,0,_tex.getWidth() ,0,_tex.getWidth() ,_tex.getHeight(),0,_tex.getHeight()};
	_tex.bind();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 2 * sizeof(float), verts);
	glTexCoordPointer(2, GL_FLOAT, 2 * sizeof(float), coords);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);;
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	_tex.unbind();

	ofSetColor(0, 255, 0);
	ofDrawBitmapString("glVertexPointer()", 450 + 5, 50 + 10);
	//////////////////////////////////////////////////////////////////////////
	//Bottom Left	

	ofSetColor(255, 255, 255);

	_tex.bind(); 
	vbo.draw(GL_TRIANGLE_FAN, 0, vbo.getNumVertices());
	_tex.unbind();

	ofSetColor(0, 255, 0);
	ofDrawBitmapString("Vertex Buffer Object", 150 + 5, 350 + 10);

	//////////////////////////////////////////////////////////////////////////
	//Bottom Right
	ofSetColor(255, 255, 255);
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