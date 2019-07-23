#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto len = 150; len < ofGetWidth(); len += 100) {

		vector<glm::vec3> top, bottom;
		for (auto param = 0; param <= 100; param++) {

			auto noise_location = this->make_point(len, param);
			auto noise_value = ofNoise(noise_location.x * 0.005, noise_location.y * 0.005, ofGetFrameNum() * 0.005);
			auto height = 0;
			if (noise_value > 0.35) {

				height = ofMap(noise_value, 0.35, 1, 0, 300);
			}

			ofSetColor(239);
			ofFill();
			ofBeginShape();
			ofVertex(glm::vec3(this->make_point(len, param), 0));
			ofVertex(glm::vec3(this->make_point(len, param + 1), 0));
			ofVertex(glm::vec3(this->make_point(len, param + 1), height));
			ofVertex(glm::vec3(this->make_point(len, param), height));
			ofEndShape(true);

			ofSetColor(39);
			ofNoFill();
			ofBeginShape();
			ofVertex(glm::vec3(this->make_point(len + 1, param), 0));
			ofVertex(glm::vec3(this->make_point(len + 1, param + 1), 0));
			ofVertex(glm::vec3(this->make_point(len + 1, param + 1), height));
			ofVertex(glm::vec3(this->make_point(len + 1, param), height));
			ofEndShape(true);

			ofBeginShape();
			ofVertex(glm::vec3(this->make_point(len - 1, param), 0));
			ofVertex(glm::vec3(this->make_point(len - 1, param + 1), 0));
			ofVertex(glm::vec3(this->make_point(len - 1, param + 1), height));
			ofVertex(glm::vec3(this->make_point(len - 1, param), height));
			ofEndShape(true);

		}
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}