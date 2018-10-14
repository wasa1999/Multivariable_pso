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
    static const int theNumberOfAgent = 30;
    static const int theNumberOfComponents = 6;
    double pos[theNumberOfAgent][theNumberOfComponents];
    double vel[theNumberOfAgent][theNumberOfComponents];
    double gbs[6] = {0,0,0,0,0,0}; // global best solution
    double pbs[theNumberOfAgent][theNumberOfComponents]; // local best solution
    double newvel[theNumberOfAgent][theNumberOfComponents];
    double canvalue[theNumberOfAgent]; //candidate distance
    double pbvalue[theNumberOfAgent]; //personel best distanse
    double gbvalue; // whole best distance
    int t;
    double evaluation(double vec[6]); // evaluation function
    
    
};
