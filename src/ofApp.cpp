#include "ofApp.h"


ofSoundPlayer sound;
ofFbo fbo;
const int numBands = 512;
float spectrum[numBands];

void ofApp::setup() {
    ofBackgroundGradient(ofColor(128), ofColor(0));

    sound.load("sound.mp3");
    sound.setLoop(true);
    sound.play();

    fbo.allocate(ofGetWidth(), ofGetHeight());

    for (int i = 0; i < numBands; i++) {
        spectrum[i] = 0.0f;
    }
}

void ofApp::update() {
    float *val = ofSoundGetSpectrum(numBands);

    for (int i = 0; i < numBands; i++) {
        spectrum[i] *= ofRandom(0.75, 0.95);
        spectrum[i] = max(spectrum[i] * ofRandom(0.02, 0.05), val[i]);
    }
}

void ofApp::draw() {
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();

    fbo.begin();
    ofBackgroundGradient(ofColor(128), ofColor(0));

    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    float radius = ofRandom(150, 250);
    for (int i = 0; i < numBands; i++) {
        float x = radius * cos(i);
        float y = radius * sin(i);
        float size = spectrum[i] * ofRandom(100, 200);
        size *= ofRandom(-1, 1);

        int c = ofRandom(255);
        ofSetColor(c, 0, 0);
        ofDrawCircle(x, y, size);
    }

    fbo.end();
    ofPopMatrix();
    fbo.draw(0, 0);
}
