#include "ofApp.h"
#include <stdlib.h>
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(10);
    ofSetBackgroundColor(0,0,0);
    ofSetWindowShape(800, 800);
    
    for (int i = 0; i < theNumberOfCandidate; i++) {
        pos[i][0] = ofRandom(6);
        pos[i][1] = ofRandom(5);
        pos[i][2] = ofRandom(9);
        pos[i][3] = ofRandom(7);
        pos[i][4] = ofRandom(3);
        pos[i][5] = ofRandom(4);
        vel[i][0] = ofRandom(-4,4);
        vel[i][1] = ofRandom(-3,3);
        vel[i][2] = ofRandom(-5,5);
        vel[i][3] = ofRandom(-4,4);
        vel[i][4] = ofRandom(-2,2);
        vel[i][5] = ofRandom(-3,3);
        for (int k = 0; k < 6; k++){
            pbs[i][k] = 0;
        }
        pbvalue[i] = 0;
    }
    gbvalue = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //調節が必要なパラメータ
    
    double w = 0.3; // 慣性の強度
    double c1 = 0.3; //pbsの強度
    double c2 = 1.0; //gbsの強度
    double r1 = ofRandom(0,1);
    double r2 = ofRandom(0,1);
    
    
    for (int i = 0; i < theNumberOfCandidate; i++) {
        
        //x(t+1)の位置をx(t)+v(i)で更新、重さ65以下の価値を取得
        
        pos[i][0] = pos[i][0] + vel[i][0];
        pos[i][1] = pos[i][1] + vel[i][1];
        pos[i][2] = pos[i][2] + vel[i][2];
        pos[i][3] = pos[i][3] + vel[i][3];
        pos[i][4] = pos[i][4] + vel[i][4];
        pos[i][5] = pos[i][5] + vel[i][5];
        
        //境界条件
        if(pos[i][0] > 6 || pos[i][0] < 0) pos[i][0] = 0;
        if(pos[i][1] > 5 || pos[i][1] < 0) pos[i][1] = 0;
        if(pos[i][2] > 9 || pos[i][2] < 0) pos[i][2] = 0;
        if(pos[i][3] > 7 || pos[i][3] < 0) pos[i][3] = 0;
        if(pos[i][4] > 3 || pos[i][4] < 0) pos[i][4] = 0;
        if(pos[i][5] > 4 || pos[i][5] < 0) pos[i][5] = 0;
        
        if(vel[i][0] > 6 || vel[i][0] < -6) vel[i][0] = ofRandom(-2,2);
        if(vel[i][1] > 5 || vel[i][1] < -5) vel[i][1] = ofRandom(-2,2);
        if(vel[i][2] > 9 || vel[i][2] < -9) vel[i][2] = ofRandom(-2,2);
        if(vel[i][3] > 7 || vel[i][3] < -7) vel[i][3] = ofRandom(-2,2);
        if(vel[i][4] > 3 || vel[i][4] < -3) vel[i][4] = ofRandom(-2,2);
        if(vel[i][5] > 4 || vel[i][5] < -4) vel[i][5] = ofRandom(-2,2);
        
       
        int weight = (pos[i][0]*10)+(pos[i][1]*12)+(pos[i][2]*7)+(pos[i][3]*9)+(pos[i][4]*21)+(pos[i][5]*16);
        
        if (weight <= 65) {
            canvalue[i] = evaluation(pos[i][0], pos[i][1], pos[i][2], pos[i][3], pos[i][4], pos[i][5]);
            pbvalue[i] = evaluation(pbs[i][0], pbs[i][1], pbs[i][2], pbs[i][3], pbs[i][4], pbs[i][5]);
            gbvalue = evaluation(gbs[0], gbs[1], gbs[2], gbs[3], gbs[4], gbs[5]);
            //personel best solutionの更新
        
            if (canvalue[i] > pbvalue[i]) {
                pbs[i][0] = pos[i][0];
                pbs[i][1] = pos[i][1];
                pbs[i][2] = pos[i][2];
                pbs[i][3] = pos[i][3];
                pbs[i][4] = pos[i][4];
                pbs[i][5] = pos[i][5];
                
            } 
            
            //global best solutionの更新
            else if (canvalue[i] > gbvalue){
                gbs[0] = pbs[i][0];
                gbs[1] = pbs[i][1];
                gbs[2] = pbs[i][2];
                gbs[3] = pbs[i][3];
                gbs[4] = pbs[i][4];
                gbs[5] = pbs[i][5];
                
                
            }
            
            for (int k = 0; k < 6; k++) {
                newvel[i][k] = (w * vel[i][k]) + (r1 * c1 * (pbs[i][k] - pos[i][k])) + (r2 * c2 * (gbs[k] - pos[i][k])); 
            }
        
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
                       ofToString(gbs[3]) + " " + ofToString(gbs[4]) + " " + ofToString(gbs[5]), 200, 360);
    ofDrawBitmapString("value : " + ofToString(gbvalue), 200, 340);

        
    ofSetColor(255, 255, 255);

    for (int i = 0; i < 10; i++) {
        ofDrawBitmapString("No" +ofToString(i)+ "  : " +ofToString(pos[i][0]) + " " + ofToString(pos[i][1]) + " " + ofToString(pos[i][2]) + " " + ofToString(pos[i][3]) + " " + ofToString(pos[i][4]) + " " + ofToString(pos[i][5]), -380, 380 + (-i*20));
    }
    
    for (int i = 10; i < theNumberOfCandidate; i++) {
        ofDrawBitmapString("No" +ofToString(i)+ " : " +ofToString(pos[i][0]) + " " + ofToString(pos[i][1]) + " " + ofToString(pos[i][2]) + " " + ofToString(pos[i][3]) + " " + ofToString(pos[i][4]) + " " + ofToString(pos[i][5]), -380, 380 + (-i*20));
    }
    
    for (int i = 0; i < theNumberOfCandidate; i++) {
        ofDrawBitmapString("Value :" + ofToString(canvalue[i]), -200, 380 + (-i*20));
    }
        
    ofSetColor(255, 0, 0);
    
    for (int i = 0; i < 10; i++) {
        ofDrawBitmapString("No" +ofToString(i)+ "  : " +ofToString(pbs[i][0]) + " " + ofToString(pbs[i][1]) + " " + ofToString(pbs[i][2]) + " " + ofToString(pbs[i][3]) + " " + ofToString(pbs[i][4]) + " " + ofToString(pbs[i][5]), -100, 380 + (-i*20));
    }
    
    for (int i = 10; i < theNumberOfCandidate; i++) {
        ofDrawBitmapString("No" +ofToString(i)+ " : " +ofToString(pbs[i][0]) + " " + ofToString(pbs[i][1]) + " " + ofToString(pbs[i][2]) + " " + ofToString(pbs[i][3]) + " " + ofToString(pbs[i][4]) + " " + ofToString(pbs[i][5]), -100, 380 + (-i*20));
    }
    
    for (int i = 0; i < theNumberOfCandidate; i++) {
        ofDrawBitmapString("Value :" + ofToString(pbvalue[i]), 80, 380 + (-i*20));
    }
    
    
    
}

//--------------------------------------------------------------
//評価関数
int ofApp::evaluation(int x1, int x2, int x3, int x4, int x5, int x6){
    
    return (x1*120) + (x2*130) + (x3*80) + (x4*100) + (x5*250 ) + (x6*185);  
    
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

