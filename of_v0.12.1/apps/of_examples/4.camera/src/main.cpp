#include "ofMain.h"
#include "ofApp.h"
#include "ofCameraApp.h"
//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.setSize(800, 600);
	settings.setGLVersion(4, 0);
	settings.windowMode = OF_WINDOW;
	
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	shared_ptr<ofApp> mainApp(new ofApp);

	auto camWindow = ofCreateWindow(settings);
	auto camApp = std::make_shared<ofCameraApp>();

	ofRunApp(mainWindow, mainApp);
	ofRunApp(camWindow, camApp);
	ofRunMainLoop();

}
