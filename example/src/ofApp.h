#pragma once

#include "ofMain.h"
#include "ofxRadonTransform.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    ofImage inputImage;      // 입력 이미지
    ofImage outputImage;     // 라돈 변환 결과 이미지
    
    ofxRadonTransform radonTransform;  // 라돈 변환 객체
    
    ofxPanel gui;
    ofxIntSlider angleResolution;  // 각도 해상도 슬라이더
    ofxButton computeButton;       // 계산 버튼
    ofxToggle autoUpdate;         // 자동 업데이트 토글
    
    void onComputeButtonPressed(); // 계산 버튼 이벤트 핸들러
};
