#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	_wheatTex.enableMipmap(); 
	ofLoadImage(_wheatTex, "wheat_b&w.png");
	
	load_shader();

	std::vector<Wheat> wheats(50*1000);

	for (auto& wheat : wheats)
	{
		wheat.pos.x = range*(ofRandom(1.f) - 0.5f);
		wheat.pos.y = 0.f;
		wheat.pos.z = range*(ofRandom(1.f) - 0.5f);
		wheat.pos.w = 1.f;
		
	}
	wheat_buf_obj.allocate(wheats, GL_DYNAMIC_DRAW);
	wheat_vbo.setVertexBuffer(wheat_buf_obj, 3, sizeof(Wheat));
	
	
	cam.setupPerspective(false, 45, 0.1, 50);
	cam.setPosition({ 5,1,5 });
	cam.lookAt({ 0,0,0 }, { 0,1,0 });
	ofBackground(0);

	_wheat_root_of_tex.x = 66;
	_wheat_root_of_tex.y = 986;
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDisableDepthTest();
	ofEnableBlendMode(OF_BLENDMODE_SCREEN);

	cam.begin();
	{
		glPointSize(10);
		shader.begin();
		shader.setUniformTexture("_wheat_tex", _wheatTex, 0);
		shader.setUniform2f("_tu", _wheatTex.getTextureData().tex_t, _wheatTex.getTextureData().tex_u);
		shader.setUniform1i("_seg_num", _wheat_data.seg_num);
		shader.setUniform2f("_wheat_root_of_tex", _wheat_root_of_tex.x*_wheat_data.wheat_scale, _wheat_root_of_tex.y*_wheat_data.wheat_scale);
		shader.setUniform2f("_tex_size", _wheatTex.getWidth()*_wheat_data.wheat_scale, _wheatTex.getHeight()*_wheat_data.wheat_scale);
		shader.setUniform1f("_fade_out_range", _wheat_data.fade_out_range);
		shader.setUniform1f("_fade_in_range", _wheat_data.fade_in_range);
		shader.setUniform3f("_lightDir", sin(ofGetElapsedTimef()), cos(ofGetElapsedTimef()), 0);


		wheat_buf_obj.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
		if(wheat_vbo.getNumVertices()>0)
			wheat_vbo.draw(GL_POINTS, 0, wheat_vbo.getNumVertices());
		wheat_buf_obj.unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
		shader.end();

		
		ofPushMatrix();
		ofRotate(90, 0, 0, 1);
		ofDrawGridPlane(1, range*0.5f, true);
		ofPopMatrix();

		ofDrawAxis(5);
	}
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_F5)
		load_shader();
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