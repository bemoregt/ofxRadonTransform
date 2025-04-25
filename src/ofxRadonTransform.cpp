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

cv::Mat ofxRadonTransform::computeRadonTransform(const cv::Mat& srcImage, int angleResolution) {
    // srcImage를 부동소수점 형태로 변환
    Mat dst;
    srcImage.convertTo(dst, CV_32FC1);
    
    // 결과 이미지 메모리 할당 
    Mat radon_image = Mat(dst.rows, angleResolution, CV_32FC1, Scalar(0));
    float center = (dst.rows / 2.0f);
    
    // 이미지 회전에 필요한 시프트 행렬 정의
    float shift0[] = {1, 0, -center,
                      0, 1, -center,
                      0, 0, 1};
    float shift1[] = {1, 0, center,
                      0, 1, center,
                      0, 0, 1};
    Mat m0 = Mat(3, 3, CV_32FC1, shift0);
    Mat m1 = Mat(3, 3, CV_32FC1, shift1);
    
    // 각도별 라돈 변환 계산
    for (int t = 0; t < angleResolution; t++) {
        float theta = t * CV_PI / angleResolution;
        
        // 회전 행렬 계산
        float R[] = {cos(theta), sin(theta), 0,
                    -sin(theta), cos(theta), 0,
                     0, 0, 1};
        Mat mR = Mat(3, 3, CV_32FC1, R);
        Mat rotation = m1 * mR * m0;
        
        // 이미지 회전
        Mat rotated;
        warpPerspective(dst, rotated, rotation, cv::Size(dst.rows, dst.cols), WARP_INVERSE_MAP);
        
        // 각 열별로 픽셀 값 합산
        for (int j = 0; j < rotated.cols; j++) {
            float *p1 = radon_image.ptr<float>(j);
            for (int i = 0; i < rotated.rows; i++) {
                float *p2 = rotated.ptr<float>(i);
                p1[t] += p2[j];
            }
        }
    }
    
    // 결과 정규화
    Mat normalized;
    normalize(radon_image, normalized, 255, 0, NORM_MINMAX, CV_8U);
    
    return normalized;
}

ofImage ofxRadonTransform::getRadonImage() {
    return radonImage;
}

float ofxRadonTransform::getElapsedTime() {
    return elapsedTime;
}
