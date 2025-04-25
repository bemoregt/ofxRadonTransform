#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // GUI 설정
    gui.setup("Radon Transform");
    gui.add(angleResolution.setup("Angle Resolution", 360, 90, 720));
    gui.add(computeButton.setup("Compute"));
    gui.add(autoUpdate.setup("Auto Update", false));
    
    // 버튼 이벤트 리스너 설정
    computeButton.addListener(this, &ofApp::onComputeButtonPressed);
    
    // 기본 이미지 로드 시도
    if (!inputImage.load("test.png")) {
        ofLogNotice() << "Example image not found, please drag and drop an image onto the window.";
    } else {
        // 이미지가 로드되면 바로 라돈 변환 계산
        radonTransform.compute(inputImage, outputImage, angleResolution);
    }
    
    ofSetWindowTitle("ofxRadonTransform Example");
}

//--------------------------------------------------------------
void ofApp::update(){
    // 자동 업데이트가 활성화되어 있고 이미지가 로드된 경우에만 계산
    if(autoUpdate && inputImage.isAllocated() && angleResolution.getParameter().isReadOnly() == false) {
        radonTransform.compute(inputImage, outputImage, angleResolution);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50);
    
    // 이미지가 로드된 경우에만 표시
    if(inputImage.isAllocated()) {
        // 입력 이미지 표시
        ofSetColor(255);
        inputImage.draw(20, 70, 400, 400);
        ofDrawBitmapStringHighlight("Input Image", 20, 60);
        
        // 라돈 변환 결과 표시
        ofSetColor(255);
        if(outputImage.isAllocated()) {
            outputImage.draw(440, 70, 400, 400);
            ofDrawBitmapStringHighlight("Radon Transform (Sinogram)", 440, 60);
            
            // 계산 시간 표시
            string timeInfo = "Computation Time: " + ofToString(radonTransform.getElapsedTime(), 3) + " seconds";
            ofDrawBitmapStringHighlight(timeInfo, 440, 490);
        }
    } else {
        ofDrawBitmapStringHighlight("Drag and drop an image file to process", ofGetWidth()/2 - 150, ofGetHeight()/2);
    }
    
    // GUI 표시
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::onComputeButtonPressed(){
    if(inputImage.isAllocated()) {
        radonTransform.compute(inputImage, outputImage, angleResolution);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's') {
        // 결과 이미지 저장
        if(outputImage.isAllocated()) {
            outputImage.save("radon_result.png");
            ofLogNotice() << "Saved result as 'radon_result.png'";
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    if(dragInfo.files.size() > 0) {
        // 첫 번째 드롭된 파일만 처리
        inputImage.load(dragInfo.files[0]);
        
        // 이미지가 로드되면 바로 라돈 변환 계산
        if(inputImage.isAllocated()) {
            radonTransform.compute(inputImage, outputImage, angleResolution);
        }
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
