#pragma once
#include "ofMain.h" 

class ofxKinectData {
public:

	struct Body {
		vector<ofVec3f> vertices;
		vector<ofColor> colors;
		vector<ofVec3f> joints;
		vector<ofVec2f> uvs;
	} bodies[6];

	struct Color {
		ofPixels pixels;
	} color;

	void addVert(int id, const ofVec3f& vert) {
		bodies[id].vertices.push_back(vert);
	}

	void addColor(int id, const ofColor& col) {
		bodies[id].colors.push_back(col);
	}

	void addUv(int id, const ofVec2f& uv) {
		bodies[id].uvs.push_back(uv);
	}

	void addJoint(int id, const ofVec3f& joint) {
		bodies[id].joints.push_back(joint);
	}

	void clear() {
		for (int i=0; i<6; i++) {
			bodies[i].vertices.clear();
			bodies[i].colors.clear();
			bodies[i].joints.clear();
			bodies[i].uvs.clear();
		}
		color.pixels.clear();
	}
};