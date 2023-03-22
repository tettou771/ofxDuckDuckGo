#include "ofApp.h"

void ofApp::setup() {
    // To show verbose
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofLogToConsole();
    
    ofSetWindowTitle("ofxDuckDuckGo Example");

    duckDuckGo.search("openFrameworks", [&](const ofJson& result, ofxDuckDuckGo::ErrorCode errorCode) {
        onSearchResult(result, errorCode);
    });
}

void ofApp::update() {
}

void ofApp::draw() {
    ofDrawBitmapString(result, 20, 20);
}

void ofApp::onSearchResult(const ofJson& result, ofxDuckDuckGo::ErrorCode errorCode) {
    if (errorCode == ofxDuckDuckGo::Success) {
        this->result = result;
    } else {
        ofLogError() << "Error: " << duckDuckGo.getErrorMessage(errorCode);
    }
}
