#pragma once

#include "ofMain.h"
#include "ofxPanel.h"
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
    ofFbo pos_fbo;
    ofFbo vel_fbo;
    
    ofShader pos_updater;
    ofShader vel_updater;
    
    ofBufferObject pos_bufobj;
    ofVbo vbo;
    const int RECOMMENDED_MAX_PARTICLE_NUM = 1024 * 1024;
    ofParameter<int> max_num ;
    ofParameter<int> display_num = RECOMMENDED_MAX_PARTICLE_NUM;
    ofEasyCam cam;
    
    ofxPanel panel;
    ofParameterGroup group;
    ofParameter<float> force = 0.01;
    ofParameter<float> max_vel = 0.3;
};
