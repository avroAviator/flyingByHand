#include "ofApp.h"
#include "spaceObject.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);

	for (int i = 0; i < numAsteroids; i++) {
		objects.push_back(spaceFactory::createObject(objectTypes::Asteroid));
	}
	for (int i = 0; i < numStars; i++) {
		objects.push_back(spaceFactory::createObject(objectTypes::Star));
	}

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->setup();
	}

	initialDraw = true;
	numDrawn = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	//if (numDrawn < objects.size()) {

	//}
	//else {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->draw();
		}
	//}

	

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
