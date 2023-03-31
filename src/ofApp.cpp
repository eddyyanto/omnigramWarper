#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Omnigram Warper");

	first_fbo.allocate(1920, 1080);

	bezManager.setup(10); //WarpResolution
	bezManager.addFbo(&first_fbo);

	bezManager.loadSettings();

	moviePlayer.load("movies/pexels-tripaway-day-7031954-1080p.mp4");
	moviePlayer.setLoopState(OF_LOOP_NORMAL);
	moviePlayer.play();

	// Load a movie file
	//load("movies/pexels-tripaway-day-7031954.mov");
	//player.setLoopState(OF_LOOP_NORMAL);

	//inScrub = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	moviePlayer.update();

		// Show or hide the cursor and position bar
	//if (ofGetSystemTimeMillis() - lastMovement < 3000)
	//{
	//	drawBar = true;
	//}
	//else
	//{
	//	drawBar = false;
	//}
	//ofRectangle window = ofGetWindowRect();
	//if (!drawBar && window.inside(ofGetMouseX(), ofGetMouseY()))
	//{
	//	ofHideCursor();
	//}
	//else
	//{
	//	ofShowCursor();
	//}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(0);
	ofBackground(ofColor::black);

	// update fbo //////////////////////
	first_fbo.begin();
	moviePlayer.draw(0, 0);


	//if (player.isLoaded())
	//{
	//	// Draw the video frame
	//	//ofSetColor(255, 255, 255);
	//	ofRectangle videoRect(0, 0, player.getWidth(), player.getHeight());
	//	videoRect.scaleTo(ofGetWindowRect());
	//	player.draw(videoRect.x, videoRect.y, videoRect.width, videoRect.height);

	//	// Draw the position bar if appropriate
	//	//if (drawBar)
	//	//{
	//	//	ofNoFill();
	//	//	ofRectangle bar = getBarRectangle();
	//	//	ofSetColor(244, 66, 234);
	//	//	ofDrawRectangle(bar);
	//	//	ofFill();
	//	//	ofSetColor(244, 66, 234, 180);
	//	//	bar.width *= player.getPosition();
	//	//	ofDrawRectangle(bar);
	//	//}
	//}
	//else
	//{
	//	if (player.getError().length())
	//	{
	//		ofDrawBitmapStringHighlight(player.getError(), 20, 20);
	//	}
	//	else
	//	{
	//		ofDrawBitmapStringHighlight("Movie is loading...", 20, 20);
	//	}
	//}


	first_fbo.end();

	// draw bezier
	bezManager.draw();

	//string _help = "[ENTER] key : Toggle guide visible.\n";
	//_help += "[S] key : Save settings.\n";
	//_help += "[L] key : Load settings.\n";
	//_help += "Left drag the control point : Move Corners/Anchors.\n";
	//_help += "Right click the control point : Toggle bezier/homoglaphy mode.\n";
	//_help += "Arrow key : Move Corners/Anchors. (selected control point)\n";
	//ofDrawBitmapString(_help, 10, 20);
}

//void ofApp::load(std::string movie)
//{
//	//ofSetWindowTitle(ofFilePath::getBaseName(movie));
//	ofSetWindowTitle("OMNIGRAM WARPER");
//	player.load(movie);
//	player.play();
//	//lastMovement = ofGetSystemTimeMillis();
//}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// send key event
	bezManager.keyPressed(key);

	// show / hide guide
	if (key == OF_KEY_RETURN) {
		bezManager.toggleGuideVisible();
	}
	// save settings
	if (key == 's') {
		bezManager.saveSettings();
	}
	// load settings
	if (key == 'l') {
		bezManager.loadSettings();
	}

	//if (key == ' ')
	//{
	//	player.setPaused(!player.isPaused());
	//}
	//else if (key == OF_KEY_UP)
	//{
	//	player.setVolume(player.getVolume() + 0.1);
	//}
	//else if (key == OF_KEY_DOWN)
	//{
	//	player.setVolume(player.getVolume() - 0.1);
	//}

	if (key == 'f') {
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	    if (ofGetWindowRect().inside(x, y))
    {
        //lastMovement = ofGetSystemTimeMillis();
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	// send drag event
	bezManager.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	// send press event
	bezManager.mousePressed(x, y, button);
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
