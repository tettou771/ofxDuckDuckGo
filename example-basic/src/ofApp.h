#pragma once

#include "ofMain.h"
#include "ofxDuckDuckGo.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void onSearchResult(const ofJson& result, ofxDuckDuckGo::ErrorCode errorCode);

    ofxDuckDuckGo duckDuckGo;
    ofJson result;
};
