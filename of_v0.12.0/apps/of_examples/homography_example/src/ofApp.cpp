#include "ofApp.h"
namespace
{
    ofMatrix4x4 homo_mat;
}
//--------------------------------------------------------------
void ofApp::setup(){
    ofLoadImage(tex, "koala.jpg");
    //cout << tex.getHeight() << endl;
    src_pnt.push_back(ofVec2f(0,0));
    src_pnt.push_back(ofVec2f(tex.getWidth(),0));
    src_pnt.push_back(ofVec2f(tex.getWidth(),tex.getHeight()));
    src_pnt.push_back(ofVec2f(0,tex.getHeight()));
    
    
    dst_pnt.push_back(ofVec2f(0,0));
    dst_pnt.push_back(ofVec2f(ofGetWidth(),0));
    dst_pnt.push_back(ofVec2f(ofGetWidth(),ofGetHeight()));
    dst_pnt.push_back(ofVec2f(0,ofGetHeight()));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    cv::Mat src(src_pnt.size(),2,CV_32FC1,&src_pnt[0]);
    cv::Mat dst(dst_pnt.size(),2,CV_32FC1,&dst_pnt[0]);
    cv::Mat H = cv::findHomography(src,dst);
    //H.type()==CV_64F
	if (H.empty())
		return;
    homo_mat._mat[0] = ofVec4f(H.at<double>(0,0),H.at<double>(1,0),0,H.at<double>(2,0));
    homo_mat._mat[1] = ofVec4f(H.at<double>(0,1),H.at<double>(1,1),0,H.at<double>(2,1));
    homo_mat._mat[2] = {0,0,1,0};
    homo_mat._mat[3] = ofVec4f(H.at<double>(0,2),H.at<double>(1,2),0,H.at<double>(2,2));
    std::cout<<homo_mat<<std::endl<<std::endl;
    
    ofSetWindowTitle(ofToString(current_pnt));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    //tex.draw(0,0);
    ofPushMatrix();

    ofMultMatrix(homo_mat);
    tex.draw(0,0);
    ofPopMatrix();
    
    ofSetColor(0,255,0);
    ofNoFill();
    for(int i = 0; i < dst_pnt.size(); ++i){
        ofDrawCircle(dst_pnt[i],20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (current_pnt == -1)
		return;
    dst_pnt[current_pnt] = ofVec2f(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for(int i = 0; i < dst_pnt.size(); ++i){
        if(dst_pnt[i].distance(ofVec2f(x,y)) < 20){
            current_pnt = i;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    current_pnt = -1;
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
