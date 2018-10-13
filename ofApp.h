#pragma once

#include "ofMain.h"
#include "vector"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    
    static const int theNumberOfMaxTrial = 30;
    static const int theNumberOfCandidate = 30;
    int pos[theNumberOfCandidate][6];
    int vel[theNumberOfCandidate][6];
    int gbs[6] = {0,0,0,0,0,0}; // global best solution
    int pbs[theNumberOfCandidate][6]; // local best solution
    int newvel[theNumberOfCandidate][6];
    int canvalue[theNumberOfCandidate]; //candidate distance
    int pbvalue[theNumberOfCandidate]; //personel best distanse
    int gbvalue; // whole best distance
    int t;
    int evaluation(int x1, int x2, int x3, int x4, int x5, int x6); // evaluation function
    
    
};
