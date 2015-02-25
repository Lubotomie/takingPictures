#pragma once

#include "ofMain.h"
#include "ofxArtnet.h"

#define NB_STRIPS 10
#define NB_MODES 6
#define HALF 300


float adist(float a1, float a2, bool rad=false);

class LightStrip{
public:
    
    int id_cold;
    int id_warm;
    
    LightStrip(int start_id){
        id_warm=start_id;
        id_cold=start_id+1;
    }
    
    void setLight(unsigned char dmxData[512],float temp,float intensity){
        dmxData[id_warm-1]=intensity*(temp+50)/100;
        dmxData[id_cold-1]=intensity*(50-temp)/100;
        
        ofSetColor(20+(205+3*temp/5)*intensity/255,20+205*intensity/255,20+(205-3*temp/5)*intensity/255);
        ofFill();
        ofRect(-50,NB_STRIPS*100/(2*PI),100,10);
    }
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    void keyPressed(int key);
    void setMode();
    
    ofxArtnet anNode;
    vector<LightStrip> strips;
    unsigned char dmxData[512];
    int cMode=0;
    
    void anSendDMX(){
        anNode.sendDmx("10.29.0.71", dmxData, 512);
    }
};