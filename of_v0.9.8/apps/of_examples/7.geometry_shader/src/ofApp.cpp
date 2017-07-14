#include "ofApp.h"
namespace
{
	ofVec3f _getUpDir(float x_rate, float z_rate, float max_degree)
	{
		float max_radius = ofDegToRad(max_degree);
		float h = 1.0 / tan(max_radius);
		return ofVec3f(x_rate, h, z_rate).normalize();
	}
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	ofDisableArbTex();
	_wheatTex.enableMipmap(); 
	ofLoadImage(_wheatTex, "wheat_b&w.png");
	
	load_shader();

	std::vector<Wheat> wheats(1000*1000);

	for (auto& wheat : wheats)
	{
		wheat.pos.x = range*(ofRandom(1.f) - 0.5f);
		wheat.pos.y = 0.f;
		wheat.pos.z = range*(ofRandom(1.f) - 0.5f);
		wheat.pos.w = 1.f;

		wheat.color.x = ofRandom(0.5f, 1.0f);
		wheat.color.y = ofRandom(0.5f, 1.0f);
		wheat.color.z = ofRandom(0.5f, 1.0f);


		ofVec3f up(0, 1, 0);
		//ofVec3f new_up = _getUpDir(ofRandom(-1.f, 1.f), ofRandom(-1.f, 1.f), max_root_angle);
		ofVec3f new_up = _getUpDir(ofRandom(-1.f, 1.f), ofRandom(-1.f, 1.f), 1);
		wheat.angle = up.crossed(new_up);
		
	}
	wheat_buf_obj.allocate(wheats, GL_DYNAMIC_DRAW);
	wheat_vbo.setVertexBuffer(wheat_buf_obj, 3, sizeof(Wheat));
	
	
	cam.setupPerspective(false, 45, 0.1, 2*range);
	cam.setPosition({ 4,2,4 });
	cam.lookAt({ 0,0,0 }, { 0,1,0 });
	ofBackground(0);

	_wheat_root_of_tex.x = 66;
	_wheat_root_of_tex.y = 986;
		
	group.add(seg_num.set("Segment",seg_num,1,6));
	group.add(wheat_num.set("Number", wheat_num, 1000, 1000000));
	group.add(wheat_scale.set("Scale", wheat_scale, 0.0001, 0.001));
	group.add(max_swing_angle.set("Max Swing Angle", max_swing_angle, 0,75));
	group.add(max_root_angle.set("Max Root Angle", max_root_angle, 0, 60));
	group.add(swing_pos_freq.set("Swing Pos. Freq.", swing_pos_freq, 0.01, 1.0));
	group.add(swing_time_freq.set("Swing Time Freq.", swing_time_freq, 0.01, 1.0));
	group.add(fade_out_range.set("Fade Out Range", fade_out_range, 0,200));
	group.add(fade_in_range.set("Fade In Range", fade_in_range, 0,200));
	panel.setup(group);
	panel.loadFromFile("settings.xml");
	
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle("FPS: "+ofToString(ofGetFrameRate(), 1));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDisableDepthTest();
	ofEnableBlendMode(OF_BLENDMODE_SCREEN);

	cam.begin();
	{
		shader.begin();
		shader.setUniformTexture("_wheat_tex", _wheatTex, 0);
		shader.setUniform1i("_seg_num", seg_num);
		shader.setUniform2f("_wheat_root_of_tex", _wheat_root_of_tex.x*wheat_scale, _wheat_root_of_tex.y*wheat_scale);
		shader.setUniform2f("_tex_size", _wheatTex.getWidth()*wheat_scale, _wheatTex.getHeight()*wheat_scale);
		
		shader.setUniform1f("_max_root_angle", max_root_angle);
		shader.setUniform1f("_max_swing_angle", max_swing_angle);
		shader.setUniform1f("_swing_pos_freq", swing_pos_freq);
		shader.setUniform1f("_swing_time_freq", swing_time_freq);
		shader.setUniform1f("_fade_out_range", fade_out_range);
		shader.setUniform1f("_fade_in_range", fade_in_range);
		shader.setUniform1f("_elapsed_time", ofGetElapsedTimef());

		wheat_buf_obj.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
		if(wheat_vbo.getNumVertices()>0)
			wheat_vbo.draw(GL_POINTS, 0, wheat_num);
		wheat_buf_obj.unbindBase(GL_SHADER_STORAGE_BUFFER, 0);
		shader.end();

		/*
		ofPushMatrix();
		ofRotate(90, 0, 0, 1);
		ofDrawGridPlane(1, range*0.5f, true);
		ofPopMatrix();
		*/
		ofDrawAxis(5);
	}
	cam.end();
	ofDisableBlendMode();
	panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_F5)
		load_shader();
	float step = 0.1f;
	switch (key)
	{
	case 'A':case 'a':
		cam.move(cam.getXAxis()* -step);
		break;
	case 'D':case 'd':
		cam.move(cam.getXAxis()*  step);
		break;
	case 'W':case 'w':
		cam.move(cam.getZAxis()*  -step);
		break;
	case 'S':case 's':
		cam.move(cam.getZAxis()*   step);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofVec2f pre_mouse(ofGetPreviousMouseX(), ofGetPreviousMouseY());
	ofVec2f mouse(x, y);
	ofVec2f diff = mouse - pre_mouse;
	float theta = diff.length()*0.1f;
	ofVec2f axis(diff.y, diff.x);
	axis.normalize();
	ofMatrix4x4 rot;
	rot.makeRotationMatrix(theta, axis);
	ofMatrix4x4 view_mat = cam.getLocalTransformMatrix().getInverse();
	view_mat = view_mat*rot;	
	ofQuaternion qq;
	ofVec3f wy = view_mat._mat[1];
	wy.z = 0;
	wy.normalize();
	qq.makeRotate(wy, ofVec3f(0, 1, 0));
	rot.makeRotationMatrix(qq);
	view_mat = view_mat*rot;
	cam.setTransformMatrix(view_mat.getInverse());
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