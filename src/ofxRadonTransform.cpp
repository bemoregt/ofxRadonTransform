#include "ofxRadonTransform.h"

using namespace cv;
using namespace ofxCv;

ofxRadonTransform::ofxRadonTransform() {
    elapsedTime = 0.0f;
}

ofxRadonTransform::~ofxRadonTransform() {
    // 소멸자 내용
}

void ofxRadonTransform::compute(const ofImage& inputImage, ofImage& outputImage, int angleResolution) {
    // 입력 이미지를 OpenCV Mat으로 변환
    Mat src = toCv(inputImage);
    Mat src_gray;

    // 이미지가 컬러인 경우 그레이스케일로 변환
    if (src.channels() == 3) {
        cvtColor(src, src_gray, CV_BGR2GRAY);
    } else {
        src_gray = src.clone();
    }

    // 라돈 변환 계산
    double t = cv::getTickCount();
    Mat radonMat = computeRadonTransform(src_gray, angleResolution);
    elapsedTime = (cv::getTickCount() - t) / cv::getTickFrequency();

    // 결과를 ofImage로 변환
    toOf(radonMat, outputImage);
    radonImage = outputImage;
}