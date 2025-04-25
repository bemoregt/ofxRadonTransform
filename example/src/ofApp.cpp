#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // Setup GUI
    gui.setup("Radon Transform");
    gui.add(loadImageButton.setup("Load Image"));
    gui.add(angleSlider.setup("Angles", 360, 10, 720));
    
    // Setup button listener
    loadImageButton.addListener(this, &ofApp::loadImageButtonPressed);
    angleSlider.addListener(this, &ofApp::angleSliderChanged);
    
    // Set window title
    ofSetWindowTitle("ofxRadonTransform Example");
    
    // Load default test image (if available)
    originalImage.load("test.png");
    if (originalImage.isAllocated()) {
        radonTransform.setup(originalImage);
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    // Nothing to update continuously
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(50);
    ofSetColor(255);
    
    // Draw original image on the left
    if (originalImage.isAllocated()) {
        originalImage.draw(10, 50, 480, 480);
        ofDrawBitmapString("Original Image", 10, 40);
    }
    
    // Draw sinogram on the right
    if (radonTransform.getSinogram().isAllocated()) {
        radonTransform.getSinogram().draw(500, 50, 480, 480);
        ofDrawBitmapString("Radon Transform (Sinogram)", 500, 40);
        ofDrawBitmapString("Processing Time: " + ofToString(radonTransform.getProcessingTime(), 3) + " seconds", 500, 540);
    }
    
    // Draw GUI
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::loadImageButtonPressed() {
    ofFileDialogResult result = ofSystemLoadDialog("Load image");
    if (result.bSuccess) {
        originalImage.load(result.getPath());
        if (originalImage.isAllocated()) {
            radonTransform.setup(originalImage, angleSlider);
        }
    }
}

//--------------------------------------------------------------
void ofApp::angleSliderChanged(int &value) {
    if (originalImage.isAllocated()) {
        radonTransform.setup(originalImage, value);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // Press 's' to save the sinogram
    if (key == 's' || key == 'S') {
        if (radonTransform.getSinogram().isAllocated()) {
            ofFileDialogResult result = ofSystemSaveDialog("sinogram.png", "Save Sinogram");
            if (result.bSuccess) {
                radonTransform.getSinogram().save(result.getPath());
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    if (dragInfo.files.size() > 0) {
        originalImage.load(dragInfo.files[0]);
        if (originalImage.isAllocated()) {
            radonTransform.setup(originalImage, angleSlider);
        }
    }
}