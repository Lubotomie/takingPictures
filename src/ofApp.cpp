#include "ofApp.h"
#include "artnet.h"

//--------------------------------------------------------------


void ofApp::setup(){

    ofSetWindowShape(2*HALF,2*HALF);
    
    anNode.setup("10.0.0.4", 0xFD);
    
    for(int i = 0; i<512; i++) {
        dmxData[i] = 50;
    }
    this->anSendDMX();
    
    for(int i=0;i<NB_STRIPS;i++){
        strips.push_back(LightStrip(1+i*3));
    }

    
	ofSetCircleResolution(80);
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    setMode();
    ofPopMatrix();
    
    ofTranslate(30,2*HALF-30);
    for(int i=0;i<NB_MODES;i++){
        if(i==cMode) ofSetColor(200);
        else ofSetColor(100);
        ofFill();
        ofCircle(0,0,5);
        ofTranslate(20,0);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
        case 356: // left
            cMode--;
            if(cMode<0) cMode=NB_MODES-1;
            break;
        case 358: // right
            cMode++;
            if(cMode==NB_MODES) cMode=0;
            break;
    }
    setMode();
    this->anSendDMX();

}

void ofApp::setMode(){
    float temp=0;
    float step=360/NB_STRIPS;
    
    ofBackground(20);
    ofTranslate(HALF,HALF);
    
    switch(cMode){
        case 0:
            for(int i=0;i<NB_STRIPS;i++){
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,0);
                ofPopMatrix();
            }
            break;
        case 1:
            for(int i=0;i<NB_STRIPS;i++){
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,255);
                ofPopMatrix();
            }
            break;
        case 2:
            for(int i=0;i<NB_STRIPS;i++){
                int intensity;
                if(i) intensity=0;
                else intensity=255;
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,intensity);
                ofPopMatrix();
            }
            break;
        case 3:
            for(int i=0;i<NB_STRIPS;i++){
                int intensity;
                if(i!=NB_STRIPS/2) intensity=0;
                else intensity=255;
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,intensity);
                ofPopMatrix();
            }
            break;
        case 4:
            for(int i=0;i<NB_STRIPS;i++){
                int intensity;
                if(i) intensity=255;
                else intensity=0;
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,intensity);
                ofPopMatrix();
            }
            break;
        case 5:
            for(int i=0;i<NB_STRIPS;i++){
                int intensity;
                if(i!=NB_STRIPS/2) intensity=255;
                else intensity=0;
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,intensity);
                ofPopMatrix();
            }
            break;
        /*case 3:
            for(int i=0;i<NB_STRIPS;i++){
                int intensity;
                if(i) intensity=255;
                else intensity=0;
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,intensity);
                ofPopMatrix();
            }
            break;
        case 4:
            for(int i=0;i<NB_STRIPS;i++){
                int intensity=255*(NB_STRIPS-i)/NB_STRIPS;
                ofPushMatrix();
                ofRotate(step*(i+1/2));
                strips.at(NB_STRIPS-i-1).setLight(dmxData,temp,intensity);
                ofPopMatrix();
            }
            break;*/
    }
    
}