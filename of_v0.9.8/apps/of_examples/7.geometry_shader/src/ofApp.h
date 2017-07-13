#pragma once

#include "ofMain.h"
class Wheat
{
public:
	ofVec4f pos;
	ofVec4f angle;
	ofVec4f color = { 1,1,1,1};

	ofVec4f swing;
	ofVec4f touch_swing;
	float touch_theta = 0;
	float touch_theta_v = 0;
	float a;
	float b;
};
class WheatData
{
public:

	bool visible;
	int   seg_num;
	int   wheat_num;
	float wheat_scale;
	float max_swing_angle;
	float max_root_angle;

	float swing_noise_scale;
	float swing_noise_millis_scale;
	float fade_out_range;
	float fade_in_range;
	ofVec3f hsv_key1;
	ofVec3f hsv_key2;
	bool inner_hsv;
	WheatData()
	{
		visible = true;
		seg_num = 5;
		wheat_num = 12000;
		wheat_scale = 0.0005;
		max_swing_angle = 30;
		max_root_angle = 6;
		swing_noise_scale = 0.0005;
		swing_noise_millis_scale = 0.0002;
		fade_in_range = 1000.f;
		fade_out_range = 1500.f;

//		hsv_key1 = uc::rgb_to_hsv(ofVec3f(0.844444, 0.565309, 0.286173));
//		hsv_key2 = uc::rgb_to_hsv(ofVec3f(0.888889, 0.801317, 0.232099));
		inner_hsv = true;
	}
};
class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
		
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
private:
	void load_shader()
	{
		printf("load shader.\n");
		shader.load("wheat_bill_borad.vert", "wheat_bill_borad.frag", "wheat_bill_borad.geom");
	}
	void _swing_wheats();
	ofShader shader;
	ofBufferObject wheat_buf_obj;
	ofVbo wheat_vbo;

	ofCamera cam;
	float range = 40.f;
	WheatData  _wheat_data;
	ofTexture _wheatTex;
	ofVec2f _wheat_root_of_tex;
};
