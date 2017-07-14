#pragma once

#include "ofMain.h"
#include "ofxPanel.h"
class Wheat
{
public:
	ofVec4f pos;
	ofVec4f angle;
	ofVec4f color = { 1,1,1,1};
	ofVec4f touch_swing;
	float touch_theta = 0;
	float touch_theta_v = 0;
	float a;
	float b;
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
	ofShader shader;
	ofBufferObject wheat_buf_obj;
	ofVbo wheat_vbo;

	ofCamera cam;
	float range = 200;

	ofTexture _wheatTex;
	ofVec2f _wheat_root_of_tex;


	ofParameter<int>   seg_num = 5;
	ofParameter<int>   wheat_num = 100000;
	ofParameter<float> wheat_scale = 0.0005;
	ofParameter<float> max_swing_angle = 30;
	ofParameter<float> max_root_angle = 6;
	ofParameter<float> swing_pos_freq = 0.1;
	ofParameter<float> swing_time_freq = 0.3;
	ofParameter<float> fade_out_range = 50;
	ofParameter<float> fade_in_range = 100;
	ofParameterGroup group;

	ofxPanel panel;
};
