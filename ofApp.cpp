#include "ofApp.h"
#include <stdlib.h>
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(10);
    ofSetBackgroundColor(0,0,0);
    ofSetWindowShape(800, 800);
    
    for (int i = 0; i < theNumberOfAgent; i++) {
        for (int k = 0; k < theNumberOfComponents; k++) {
            pos[i][k] = ofRandom(-2.084,2.084);
            vel[i][k] = ofRandom(-0.5,0.5);
            pbs[i][k] = 2.084;
        }
        
        
        pbvalue[i] = 10000;
    }
    gbvalue = 10000;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //調節が必要なパラメータ
    
    double w = 0.3; // 慣性の強度
    double c1 = 0.8; //pbsの強度
    double c2 = 1.0; //gbsの強度
    double r1 = ofRandom(0,1);
    double r2 = ofRandom(0,1);
    
    
    for (int i = 0; i < theNumberOfAgent; i++) {
        
        //x(t+1)の位置をx(t)+v(i)で更新
        for (int k = 0; k < theNumberOfComponents; k++) {
            
            pos[i][k] = pos[i][k] + vel[i][k];
            
            if (pos[i][k] > 2.084) {
                pos[i][k] = 2.084;
                vel[i][k] = 0;
            }
            else if (pos[i][k] < -2.084) {
                pos[i][k] = -2.084;
                vel[i][k] = 0;
            }
            
            
        }
        
        double pbsvec[6] = {pbs[i][0], pbs[i][1], pbs[i][2], pbs[i][3], pbs[i][4], pbs[i][5]};
        pbvalue[i] = evaluation(pbsvec);
        gbvalue = evaluation(gbs);
            //personel best solutionの更新
        
        if (canvalue[i] < pbvalue[i]) {
            for (int k = 0; k < theNumberOfComponents; k++) {
                pbs[i][k] = pos[i][k];
            }
        } 
            //global best solutionの更新
        else if (canvalue[i] < gbvalue){
            for (int k = 0; k < theNumberOfComponents; k++) {
                gbs[k] = pos[i][k];
            }
        }
            
        for (int k = 0; k < 6; k++) {
            vel[i][k] = (w * vel[i][k]) + (r1 * c1 * (pbs[i][k] - pos[i][k])) + (r2 * c2 * (gbs[k] - pos[i][k])); 
        }
    }
    
    t++;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofTranslate(400, 400);
    ofScale(1, -1);
    
    ofSetColor(0, 255, 0);
    ofDrawBitmapString("trial : " + ofToString(t), 200, 380);
    ofDrawBitmapString("gbs : " + ofToString(gbs[0]) + " " + ofToString(gbs[1]) + " " + ofToString(gbs[2]) + " " +
                       ofToString(gbs[3]) + " " + ofToString(gbs[4]) + " " + ofToString(gbs[5]), 0, 360);
    ofDrawBitmapString("value : " + ofToString(gbvalue), 200, 340);

        
    ofSetColor(255, 255, 255);

    for (int i = 0; i < 10; i++) {
        ofDrawBitmapString("No" +ofToString(i)+ "  : " +ofToString(pos[i][0]) + " " + ofToString(pos[i][1]) + " " + ofToString(pos[i][2]) + " " + ofToString(pos[i][3]) + " " + ofToString(pos[i][4]) + " " + ofToString(pos[i][5]), -380, 380 + (-i*20));
    }
    
    for (int i = 10; i < theNumberOfAgent; i++) {
        ofDrawBitmapString("No" +ofToString(i)+ " : " +ofToString(pos[i][0]) + " " + ofToString(pos[i][1]) + " " + ofToString(pos[i][2]) + " " + ofToString(pos[i][3]) + " " + ofToString(pos[i][4]) + " " + ofToString(pos[i][5]), -380, 380 + (-i*20));
    }
    
//    for (int i = 0; i < theNumberOfAgent; i++) {
//        ofDrawBitmapString("Value :" + ofToString(canvalue[i]), -200, 380 + (-i*20));
//    }
//        
//    ofSetColor(255, 0, 0);
//    
//    for (int i = 0; i < 10; i++) {
//        ofDrawBitmapString("No" +ofToString(i)+ "  : " +ofToString(pbs[i][0]) + " " + ofToString(pbs[i][1]) + " " + ofToString(pbs[i][2]) + " " + ofToString(pbs[i][3]) + " " + ofToString(pbs[i][4]) + " " + ofToString(pbs[i][5]), -100, 380 + (-i*20));
//    }
//    
//    for (int i = 10; i < theNumberOfAgent; i++) {
//        ofDrawBitmapString("No" +ofToString(i)+ " : " +ofToString(pbs[i][0]) + " " + ofToString(pbs[i][1]) + " " + ofToString(pbs[i][2]) + " " + ofToString(pbs[i][3]) + " " + ofToString(pbs[i][4]) + " " + ofToString(pbs[i][5]), -100, 380 + (-i*20));
//    }
//    
//    for (int i = 0; i < theNumberOfAgent; i++) {
//        ofDrawBitmapString("Value :" + ofToString(pbvalue[i]), 80, 380 + (-i*20));
//    }
    
    
    
}

//--------------------------------------------------------------
//評価関数
double ofApp::evaluation(double vec[6]){
    for (int i = 0; i < theNumberOfAgent; i++) {
        double sum = 0;
        for (int k = 0; k < theNumberOfComponents-1; k++) {
            sum += (100 * (vec[k+1] - (vec[k]*vec[k])) + ((1 - vec[k])*(1 - vec[k])));
        }
        canvalue[i] = sum;
        return canvalue[i];
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

