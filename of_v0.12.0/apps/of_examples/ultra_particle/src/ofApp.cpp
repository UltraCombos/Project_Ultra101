#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
    pos_updater.load("pos_updater_shader.vert","pos_updater_shader.frag");
    vel_updater.load("vel_updater_shader.vert","vel_updater_shader.frag");

    ofFbo::Settings settings;
    
    int width = std::max(ceil(sqrt(RECOMMENDED_MAX_PARTICLE_NUM)), 1.0);
    int height = std::max(ceil((float)RECOMMENDED_MAX_PARTICLE_NUM / width), 1.0f);
    max_num = width*height;
    
    settings.width = width;
    settings.height = height;
    settings.colorFormats = { GL_RGBA32F };
    settings.useDepth = settings.useStencil = false;
    settings.maxFilter = settings.minFilter = GL_NEAREST;
    
   
    vel_fbo.allocate(settings);
    pos_fbo.allocate(settings);
    vel_fbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    pos_fbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ofFloatPixels pos_pxl;
    ofFloatPixels vel_pxl;
    pos_fbo.getTexture().readToPixels(pos_pxl);
    vel_fbo.getTexture().readToPixels(vel_pxl);
    
    ofVec4f* p_vel = (ofVec4f*)vel_pxl.getData();
    ofVec4f* p_pos = (ofVec4f*)pos_pxl.getData();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x, ++p_vel, ++p_pos)
        {
            *p_vel = 0.0*ofVec4f(ofRandom(-1, 1),ofRandom(-1, 1),ofRandom(-1, 1),0);
            *p_pos = 10*ofVec4f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1),0);
        }
    }
    pos_fbo.getTexture().loadData(pos_pxl);
    vel_fbo.getTexture().loadData(vel_pxl);
    
    pos_bufobj.allocate(pos_pxl, GL_DYNAMIC_DRAW);
    vbo.setVertexBuffer(pos_bufobj,4,sizeof(ofVec4f));
    display_num.set("num", display_num, 100, max_num);
    
    cam.setupPerspective(false, 60, 0.1, 1000);
    ofVec3f eye = {10,5,10};
    cam.setDistance(eye.length());
    cam.setPosition(eye);
    cam.lookAt(ofVec3f(0, 0, 0),ofVec3f(0,1,0));
    
    //ofBackground(155);
    
    group.add(force.set("force",force,0.01,1.0));
    group.add(max_vel.set("max_vel",max_vel,0.1,1.0));
    panel.setup(group);
    panel.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle("FPS: " + ofToString(ofGetFrameRate(), 1));
    ofDisableBlendMode();
    ofDisableDepthTest();
#if 1
    vel_fbo.begin();
    {
        vel_updater.begin();
        vel_updater.setUniformTexture("pos_tex", pos_fbo.getTexture(), 0);
        vel_updater.setUniformTexture("vel_tex", vel_fbo.getTexture(), 1);
        vel_updater.setUniform1f("force",force);
        vel_updater.setUniform1f("max_vel",max_vel);
        pos_fbo.getTexture().draw(0, 0);
        vel_updater.end();
    }
    vel_fbo.end();
#endif


    pos_fbo.begin();
    pos_updater.begin();
    {
        pos_updater.setUniformTexture("pos_tex", pos_fbo.getTexture(), 1);
        pos_updater.setUniformTexture("vel_tex", vel_fbo.getTexture(), 0);
        vel_fbo.getTexture().draw(0, 0);
    }
    pos_updater.end();
    pos_fbo.end();
   
    pos_fbo.getTexture().copyTo(pos_bufobj);

//#endif
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    glPointSize(1);
    cam.begin();
    ofDrawAxis(100);
    
    vbo.draw(GL_POINTS, 0, display_num);
    
    cam.end();
    ofDisableBlendMode();
    pos_fbo.getTexture().draw(0,0,100,100);
    vel_fbo.getTexture().draw(100,0,100,100);
    
    panel.draw();
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
