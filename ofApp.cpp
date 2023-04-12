#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	auto radius = 250;
	ofColor color;
	for (int i = 0; i < 8; i++) {

		color.setHsb(ofMap(i, 0, 8, 0, 255), 255, 255);
		ofSetColor(color);

		auto noise_seed = ofRandom(1000);
		vector<glm::vec3> vertices;
		for (int deg = 0; deg < 360; deg += 1) {

			auto vertex = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
			auto rotate_deg = ofMap(ofNoise(i * 0.05 + vertex.x * 0.001 + ofGetFrameNum() * 0.004), 0, 1, -720, 720);
			auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));

			vertex = glm::vec4(vertex, 0) * rotation;
			vertices.push_back(vertex);
		}

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}