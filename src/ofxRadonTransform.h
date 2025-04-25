#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class ofxRadonTransform {
public:
    ofxRadonTransform();
    ~ofxRadonTransform();
    
    // 라돈 변환 계산 함수
    void compute(const ofImage& inputImage, ofImage& outputImage, int angleResolution = 360);
    
    // 라돈 변환 결과 가져오기
    ofImage getRadonImage();
    
    // 계산 시간 가져오기
    float getElapsedTime();
    
private:
    // 라돈 변환 내부 구현
    cv::Mat computeRadonTransform(const cv::Mat& srcImage, int angleResolution);
    
    ofImage radonImage;
    float elapsedTime;
};
