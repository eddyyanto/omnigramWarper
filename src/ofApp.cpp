#include "ofApp.h"

#define BarInset 20
#define BarHeight 40

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetFullscreen(true);

	first_fbo.allocate(1920, 1080);

	bezManager.setup(10);
	bezManager.addFbo(&first_fbo);
	bezManager.loadSettings();
	bezManager.toggleGuideVisible(); 

	load("movies/pexels-tripaway-day-7031954-1080p[Hap (Default) PCM 24bit (Default)].mov");
	player.setLoopState(OF_LOOP_NORMAL);

	inScrub = true;
	drawBar = true;
	showHelp = false;
}

//--------------------------------------------------------------
void ofApp::update(){

	if (ofGetSystemTimeMillis() - lastMovement < 3000){
		drawBar = true;
	}else{
		drawBar = false;
	}

	ofRectangle window = ofGetWindowRect();
	if (!drawBar && window.inside(ofGetMouseX(), ofGetMouseY())){
		ofHideCursor();
	}else{
		ofShowCursor();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	first_fbo.begin();

	ofClear(0);
	ofSetBackgroundColor(0, 0, 0);
	if (player.isLoaded()){
		ofRectangle videoRect(0, 0, player.getWidth(), player.getHeight());
		videoRect.scaleTo(ofGetWindowRect());
		player.draw(videoRect.x, videoRect.y, videoRect.width, videoRect.height);

		//if (drawBar){
		//	ofNoFill();
		//	ofRectangle bar = getBarRectangle();
		//	ofSetColor(244, 66, 234);
		//	ofDrawRectangle(bar);
		//	ofFill();
		//	ofSetColor(244, 66, 234, 180);
		//	bar.width *= player.getPosition();
		//	ofLog() << player.getPosition();
		//	ofDrawRectangle(bar);
		//}

	}else{
		if (player.getError().length()){
			ofDrawBitmapStringHighlight(player.getError(), 20, 20);
		}else{
			ofDrawBitmapStringHighlight("Movie is loading...", 20, 20);
		}
	}

	first_fbo.end();
	bezManager.draw();

	if (showHelp){
		string _help = "[ENTER] key : Toggle guide visible.\n";
		_help += "[S] key : Save settings.\n";
		_help += "[L] key : Load settings.\n";
		_help += "Left drag the control point : Move Corners/Anchors.\n";
		_help += "Right click the control point : Toggle bezier/homoglaphy mode.\n";
		_help += "Arrow key : Move Corners/Anchors. (selected control point)\n";
		_help += "[H] key : Show/hide help text\n";

		ofDrawBitmapString(_help, 10, 20);
	}
}

void ofApp::load(std::string movie)
{
	ofSetWindowTitle("OMNIGRAM WARPER");
	player.load(movie);
	player.play();
	lastMovement = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// send key event
	bezManager.keyPressed(key);

	// show / hide guide
	if (key == OF_KEY_RETURN){
		bezManager.toggleGuideVisible();
	}
	// save settings
	if (key == 's'){
		bezManager.saveSettings();
	}
	// load settings
	if (key == 'l') {
		bezManager.loadSettings();
	}
	// play/pause
	if (key == ' '){
		player.setPaused(!player.isPaused());
	}
	if (key == OF_KEY_UP){
		player.setVolume(player.getVolume() + 0.1);
	}
	if (key == OF_KEY_DOWN){
		player.setVolume(player.getVolume() - 0.1);
	}
	// toggle fullscreen
	if (key == 'f'){
		ofToggleFullscreen();
	}
	if (key == 'h') {
		showHelp = !showHelp;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	    if (ofGetWindowRect().inside(x, y))
    {
        lastMovement = ofGetSystemTimeMillis();
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	// send drag event
	bezManager.mouseDragged(x, y, button);

	if (inScrub){
		float position = static_cast<float>(x - BarInset) / getBarRectangle().width;
		position = std::max(0.0f, std::min(position, 1.0f));
		player.setPosition(position);
		lastMovement = ofGetSystemTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	// send press event
	bezManager.mousePressed(x, y, button);

	ofRectangle bar = getBarRectangle();
	if (bar.inside(x, y)){
		inScrub = true;
		wasPaused = player.isPaused() || player.getIsMovieDone();
		player.setPaused(true);
		mouseDragged(x, y, button);
	}
	lastMovement = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (inScrub){
		inScrub = false;
		player.setPaused(wasPaused);
	}
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
void ofApp::dragEvent(ofDragInfo dragInfo) {
	vector< string > fileList = dragInfo.files;
	load(fileList[0]);
}

ofRectangle ofApp::getBarRectangle() const{
	return ofRectangle(BarInset, ofGetWindowHeight() - BarInset - BarHeight, ofGetWindowWidth() - (2 * BarInset), BarHeight);
}