#pragma once
#include "ofMain.h" 

class ofxKinectData {
public:
	vector<ofVec3f> vertices0;
	vector<ofColor> colors0;
	vector<ofVec3f> joints0;

	vector<ofVec3f> vertices1;
	vector<ofColor> colors1;
	vector<ofVec3f> joints1;

	vector<ofVec3f> vertices2;
	vector<ofColor> colors2;
	vector<ofVec3f> joints2;

	vector<ofVec3f> vertices3;
	vector<ofColor> colors3;
	vector<ofVec3f> joints3;

	vector<ofVec3f> vertices4;
	vector<ofColor> colors4;
	vector<ofVec3f> joints4;

	vector<ofVec3f> vertices5;
	vector<ofColor> colors5;
	vector<ofVec3f> joints5;

	void addVert(int id, ofVec3f vert) {
		switch (id)
		{
		case 0:
			vertices0.push_back(vert);
			break;
		case 1:
			vertices1.push_back(vert);
			break;
		case 2:
			vertices2.push_back(vert);
			break;
		case 3:
			vertices3.push_back(vert);
			break;
		case 4:
			vertices4.push_back(vert);
			break;
		case 5:
			vertices5.push_back(vert);
			break;

		default:
			break;
		}
	}

	void addColor(int id, ofColor col) {
		switch (id)
		{
		case 0:
			colors0.push_back(col);
			break;
		case 1:
			colors1.push_back(col);
			break;
		case 2:
			colors2.push_back(col);
			break;
		case 3:
			colors3.push_back(col);
			break;
		case 4:
			colors4.push_back(col);
			break;
		case 5:
			colors5.push_back(col);
			break;

		default:
			break;
		}
	}

	void addJoint(int id, ofVec3f joint) {
		switch (id)
		{
		case 0:
			joints0.push_back(joint);
			break;
		case 1:
			joints1.push_back(joint);
			break;
		case 2:
			joints2.push_back(joint);
			break;
		case 3:
			joints3.push_back(joint);
			break;
		case 4:
			joints4.push_back(joint);
			break;
		case 5:
			joints5.push_back(joint);
			break;

		default:
			break;
		}
	}

	void clear() {
		vertices0.clear();
		colors0.clear();
		joints0.clear();
		
		vertices1.clear();
		colors1.clear();
		joints1.clear();
		
		vertices2.clear();
		colors2.clear();
		joints2.clear();

		vertices3.clear();
		colors3.clear();
		joints3.clear();

		vertices4.clear();
		colors4.clear();
		joints4.clear();

		vertices5.clear();
		colors5.clear();
		joints5.clear();
	}


	ofVec3f* getVertices0() { return vertices0.data(); }
};