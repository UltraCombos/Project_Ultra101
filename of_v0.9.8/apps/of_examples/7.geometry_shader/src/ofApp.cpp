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

		ofVec3f up(0, 1, 0);
		ofVec3f new_up = _getUpDir(ofRandom(-1.f, 1.f), ofRandom(-1.f, 1.f), _wheat_data.max_root_angle);
		wheat.angle = up.crossed(new_up);
		
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
	_swing_wheats();
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
void ofApp::_swing_wheats()
{
#if 0
	_emitor_list.clear();
	TouchInfoList   touch_info_list;
	vector<ofVec3f> ray_x_pre_ray_list;
	vector<ofVec3f> ori_ray_list;
	vector<float>   ray_theta_per_sec_list;
	if (_touch_rays.size())
	{
		touch_info_list.assign(_touch_rays.size(), TouchInfo());

		ofMatrix4x4 view_rotate_mat = _cam_mat.getInverse();
		view_rotate_mat.setTranslation(ofVec3f(0, 0, 0));

		for (int j = 0; j < _touch_rays.size(); j++)
		{
			ofVec3f ray_crossd = _touch_rays[j].pre_ray.crossed(_touch_rays[j].ray);
			if (fabs(ray_crossd.y) > 0.0001)
			{
				float sign = ray_crossd.y / fabs(ray_crossd.y);
				float ray_theta = asin(sign*ray_crossd.length());

				float   ray_theta_per_sec = ray_theta / (_deltaMillis / 1000.f);
				ofVec3f ori_ray = _touch_rays[j].ray * view_rotate_mat;

				touch_info_list[j] = TouchInfo(ofRadToDeg(fabs(ray_theta_per_sec)), FLT_MAX, ori_ray);
			}
			else
			{
				touch_info_list[j] = TouchInfo(0.f, FLT_MAX, ofVec3f(0, 0, 0));
			}
		}
	}

	for (int i = 0; i < _wheat_list.size(); i++)
	{
		ofVec3f pos = _wheat_list[i].pos * _wheat_data.swing_noise_scale;
		long long millis = ofGetElapsedTimeMillis();
		float x_off = _noise(pos.x, pos.y, millis*_wheat_data.swing_noise_millis_scale, 0);
		float z_off = _noise(pos.x, pos.y, 0, millis*_wheat_data.swing_noise_millis_scale);

		ofVec3f up(0, 1, 0);
		ofVec3f dir = _getUpDir(x_off, z_off, _wheat_data.max_swing_angle);
		_wheat_list[i].swing = up.crossed(dir);


		ofVec3f eye_to_wheat = _wheat_list[i].pos - _smooth_eye;
		float eye_to_wheat_dist = eye_to_wheat.length();
		eye_to_wheat.normalize();

		ofVec3f touch_axis = -eye_to_wheat;
		float touch_theta = 0;
		for (int j = 0; j < _touch_rays.size(); j++)
		{
			ofVec3f v = _touch_rays[j].ray;
			float theta = acos(v.dot(eye_to_wheat));
			if (theta < PI / 48 && touch_info_list[j].delta_angle_per_second != 0)
			{
				touch_theta += ofDegToRad(touch_info_list[j].delta_angle_per_second) * 2;//ray_theta*50;
				float dist_in_meter = eye_to_wheat_dist / 1000.f;
				float min_dist = std::min(dist_in_meter, touch_info_list[j].touch_distance_in_meter);

				touch_info_list[j].touch_distance_in_meter = min_dist;
			}
		}
		float spring = 0.01f;
		float friction = 0.92f;
		float diff = _get_offset(touch_theta - _wheat_list[i].touch_theta);

		_wheat_list[i].touch_theta_v *= _get_keep_rate(friction);
		_wheat_list[i].touch_theta_v += _get_offset(diff*spring);
		_wheat_list[i].touch_theta += _wheat_list[i].touch_theta_v;

		if (fabs(_wheat_list[i].touch_theta) < 0.0001)
			_wheat_list[i].touch_theta = 0;

		_wheat_list[i].touch_swing = sin(_wheat_list[i].touch_theta) * touch_axis;
	}


	ofMatrix4x4 view_mat = _cam_mat.getInverse();
	ofMatrix4x4 model_view_outter;
	glGetFloatv(GL_MODELVIEW_MATRIX, model_view_outter.getPtr());
	ofVec3f real_eye = (model_view_outter.getInverse()*_cam_mat).getTranslation();

	ofMatrix4x4 cam_rotate = _cam_mat;
	cam_rotate.setTranslation(ofVec3f(0, 0, 0));
	_touch_info_list.clear();
	for (int i = 0; i < touch_info_list.size(); i++)
	{
		if (touch_info_list[i].touch_distance_in_meter < FLT_MAX)
		{
			_touch_info_list.push_back(touch_info_list[i]);
			if (_emitor_list.size() < MAX_EMITOR_NUM)
			{
				ofVec3f ray = touch_info_list[i].touch_ray_dir*cam_rotate;
				float height = _wheatTex.getHeight()*_wheat_data.wheat_scale*0.8;
				_emitor_list.push_back(real_eye + ray*touch_info_list[i].touch_distance_in_meter * 1000);
			}
		}
	}
	if (_touch_info_list.size())
	{
		TouchEventArgs args(_touch_info_list);
		ofNotifyEvent(touch_event, args, this);
	}
#endif
}