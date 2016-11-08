#pragma once
#include "ofMain.h" 

#define KINECT_DATA_WITH_COLOR

class ofxKinectData {
public:

	struct Body {
		vector<ofVec3f> vertices;
		vector<ofColor> colors;
		vector<ofVec3f> joints;
	} bodies[6];
#ifdef KINECT_DATA_WITH_COLOR
	struct Color {
		ofPixels pixels;
	} color;
#endif

	void addVert(int id, const ofVec3f& vert) {
		bodies[id].vertices.push_back(vert);
	}

	void addColor(int id, const ofColor& col) {
		bodies[id].colors.push_back(col);
	}

	void addJoint(int id, const ofVec3f& joint) {
		bodies[id].joints.push_back(joint);
	}

	void clear() {
		for (int i=0; i<6; i++) {
			bodies[i].vertices.clear();
			bodies[i].colors.clear();
			bodies[i].joints.clear();
		}
	}
};