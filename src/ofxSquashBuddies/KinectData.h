#pragma once

#include "ofMain.h" 


struct skeleton {
	int bodyId;
	vector<ofVec3f> joints;
};

class ofxKinectData {
public:
	vector<skeleton> skeletons;
};