#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// data type
	char c = 'a'; // (character) ex: ‘A’, ‘e’, ‘$’
	int i = 13579; // (integer) ex: 5, 68, 126, -687, 1235484
	float f = 3.14159f; // (floating-point) ex: 3.14f, -6.387f, 15687.354984f
	bool b = true; // (boolean) ex: true, false
	string s = "This is a string"; // ex: “first line\n\tsecond line with tab\n”



	// output to console, begin with "cout", end with "endl"
	cout << i << endl; // 13579
	cout << s << endl; // This is a string
	cout << "x: " << i << ", y: " << f << endl; // x: 13579, y: 3.14159



	// container
	vector<float> seeds; // define "seeds" as a vector of float
	cout << "define a vector of float named seeds" << endl;
	seeds.push_back(3.14159f); // add element at the end of vector
	seeds.push_back(1.414f);
	seeds.size(); // size of vector
	cout << "seeds has " << seeds.size() << " elements" << endl;
	seeds[0]; // get value at position 0
	seeds.at(1); // get value at position 1
	cout << "seeds has float " << seeds.at(0) << " at position 0" << endl;
	cout << "seeds has float " << seeds[1] << " at position 1" << endl;
	seeds.pop_back(); // remove the last element
	cout << "seeds has " << seeds.size() << " elements after pop_back()" << endl;
	seeds.clear(); // clear vector
	cout << "seeds has " << seeds.size() << " elements after clear()" << endl;


	// loop
	int x = 0;
	cout << "x is " << x << endl;
	while (x < 10)
	{
		x = x + 1;
	}
	cout << "x become " << x << " after while loop" << endl;
	for (int i = 0; i < 10; i++)
	{
		x = x + i;
	}
	cout << "x become " << x << " after for loop" << endl;



	// statement (if else)
	x = -53;
	if (x > 0)
		cout << x << " is positive" << endl;
	else if (x < 0)
		cout << x << " is negative" << endl;
	else
		cout << x << " is 0" << endl;



	// statement (switch case)
	int key = OF_KEY_F1;
	switch (key)
	{
	case OF_KEY_F1: // if key == OF_KEY_F1
		cout << "key F1 pressed" << endl;
		break;
	case OF_KEY_F11: // if key == OF_KEY_F11
		cout << "key F11 pressed" << endl;
		break;
	case 's': // if key == 's'
		cout << "key s pressed" << endl;
		break;
	}



	// oF common classes for data storing
	ofColor color = ofColor(255, 0, 128, 255); // {r, g, b, a} (0~255)
	color.set(128, 128); // brightness: 128, alpha: 128
	color = ofColor::fromHex(0x323F1B); // use hex as color
	ofFloatColor float_color = ofFloatColor(1.0f, 0.0f, 0.5f); //{r, g, b, a} (0.0f ~ 1.0f)
	float_color = ofFloatColor::fromHsb(0.35, 0.8, 0.3); // hue: 0.35, saturation: 0.8, brightness: 0.3

	ofVec2f point_2d = ofVec2f(1, -1); // {x, y}
	ofVec3f point_3d = ofVec3f(1, -1, 3); // {x, y, z} same as ofPoint
	point_3d.set(-1, -1, 3); // set x: -1, y: -1, z: 3
	ofVec4f point_4d = ofVec4f(1, -1, 3, 1); // {x, y, z, w}
	point_4d.w = 1.0f; // assign 1.0f to w



	// oF common math function
	cout << "ofRandom(5.0f) get value "			<< ofRandom(5.0f)			<< " between 0.0f and 5.0f"		<< endl; // [0, max]
	cout << "ofRandom(1.4f, 3.2f) get value "	<< ofRandom(1.4f, 3.2f)		<< " between 1.4f and 3.2f"		<< endl; // [min, max]
	cout << "ofRandomf() get value "			<< ofRandomf()				<< " between -1.0f and 1.0f"	<< endl; // [-1, 1]
	cout << "ofRandomuf() get value "			<< ofRandomuf()				<< " between 0.0f and 1.0f"		<< endl; // [0, 1]
	cout << "ofNoise(1.57f) get value "			<< ofNoise(1.57f)			<< " between 0.0f and 1.0f"		<< endl; // [0, 1]
	cout << "ofSignedNoise(1.57f) get value "	<< ofSignedNoise(1.57f)		<< " between -1.0f and 1.0f"	<< endl; // [-1, 1]



	// oF common function
	ofSetBackgroundAuto(false); // disable auto background
	ofSetFrameRate(60); // set fps to 60
	//ofToggleFullscreen(); // switch between window mode and fullscreen
	ofSetFullscreen(false); // set fullscreen or not

	ofSetColor(ofColor(128)); // set color to ofColor(128)
	ofClear(0); // clear canvas
	ofBackground(0); // draw background with ofColor(0)
	ofBackgroundGradient(ofColor(128), ofColor(0), ofGradientMode::OF_GRADIENT_CIRCULAR); // draw gradient background from ofColor(128) to ofColor(0) with circular mode
	
	ofGetWidth(); // get canvas width
	ofGetHeight(); // get canvas height
	ofGetElapsedTimef(); // get elapsed time of application in seconds
	ofGetMousePressed(); // get mouse is pressed or not
	ofGetMouseX(); // get mouse x
	ofGetMouseY(); // get mouse y
	ofGetPreviousMouseX(); // get previous mouse x
	ofGetPreviousMouseY(); // get previous mouse y

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofVAArgsToString("fps: %f", ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// if there is no background, we could draw line by current mouse position and previouse mouse position
	if (ofGetMousePressed())
	{
		ofDrawLine(ofGetMouseX(), ofGetMouseY(), ofGetPreviousMouseX(), ofGetPreviousMouseY());
	}

	// we can set background with various style
	ofBackground(2);
	ofBackgroundGradient(ofColor(64), ofColor(0), ofGradientMode::OF_GRADIENT_CIRCULAR);
	ofBackgroundGradient(ofColor(64), ofColor(0), ofGradientMode::OF_GRADIENT_LINEAR);
	ofBackgroundGradient(ofColor::fromHex(0xF82C30), ofColor::fromHex(0x092743), ofGradientMode::OF_GRADIENT_CIRCULAR);
#if 0
	// draw line only if we have more than 1 position
	if (mouse_position.size() > 1) 
	{
		for (int i = 0; i < mouse_position.size() - 1; i++)
		{
			//ofVec2f this_position = mouse_position[i + 0];
			//ofVec2f next_position = mouse_position[i + 1];
			//ofDrawLine(this_position, next_position);
			int hue = ofWrap(i, 0, 255); // warp i between 0 and 255 as hue
			ofColor c = ofColor::fromHsb(hue, 200, 200);
			ofSetColor(c);
			ofDrawLine(mouse_position[i + 0], mouse_position[i + 1]);
		}
	}
#endif
	
	// draw current line
	ofSetColor(ofColor::fromHex(0x105B63));
	ofSetLineWidth(1);
	current_line.draw();

	// draw history lines
	ofSetColor(ofColor::fromHex(0xDB9E36));
	ofSetLineWidth(2);
	for (int i = 0; i < history_lines.size(); i++)
	{
		history_lines[i].draw();
	}

	// draw lines nearby
	ofSetColor(ofColor::fromHex(0xBD4932));
	ofSetLineWidth(1);
	for (int i = 0; i < minor_lines.size(); i++)
	{
		minor_lines[i].draw();
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
#if 0
	//ofVec2f pos = ofVec2f(x, y);
	//mouse_position.push_back(pos);
	mouse_position.push_back(ofVec2f(x, y)); // add mouse position (x, y) to vector
#endif
	// add mouse pos (x, y) to current polyline
	current_line.addVertex(x, y);

	// we check every vertex of history lines to add any lines nearby
	// you can change min and max distance
	float min_distance = 10.0f;
	float max_distance = 30.0f;
	// for loop to check every history lines
	for (int i = 0; i < history_lines.size(); i++)
	{
		// for loop to check every vertex on line
		// ofPolyLine::getVertices() will get vector of vertices it stores
		// we can check every point in vector
		for (int j = 0; j < history_lines[i].getVertices().size(); j++)
		{
			// assign vertex in potision 'j' to history_point
			ofVec2f history_point = history_lines[i].getVertices()[j];
			// for getting distance between mouse posiiton (x, y) and history_point,
			// we can use ofDist(float x1, float y1, float x2, float y2)
			// it will return distance between 2 points in float
			float dist = ofDist(x, y, history_point.x, history_point.y);
			// so we could check distance is in min-max range or not
			// use ofInRange(float t, float min, float max)
			// it will return bool (true, false) 
			if (ofInRange(dist, min_distance, max_distance))
			{
				// if distance is in range
				// create new ofPolyLine and add mouse position and history point to it
				// and push_back to minor_lines
				ofPolyline line;
				line.addVertex(x, y);
				line.addVertex(history_point);
				minor_lines.push_back(line);
			}
		}
		
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// if mouse released, add current line to history and clear it
	history_lines.push_back(current_line);
	current_line.clear();
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