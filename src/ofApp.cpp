#include "ofApp.h"

ofPoint p0, p1;		// for line drawing
ofPoint t;		// for translating
float rX, rY, rZ;	// for rotation

float rX1, rY1, rZ1;
ofPoint p2, p3;
ofPoint t2;

ofFbo fbo;

ofColor black(0,0,0);

//--------------------------------------------------------------
void ofApp::setup(){
    
    song.load("horizon.mp3");
    while(!song.isLoaded()); //spin wheels till loaded
    song.play();
    nBandsToGet = 360; // up to 512
    
    //-------------------
    
    p0 = ofPoint(-30, 0);
    p1 = ofPoint(30, 0);
    
    p2 = ofPoint(-5.0);
    p3 = ofPoint(5,0);
    
    t = ofPoint(ofGetWidth()/3, ofGetHeight()/3, 0);
    
    //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
     //backIamge.load("image/1.jpg");
    ofSetBackgroundColor(black);
}
    
float *val;
//--------------------------------------------------------------
void ofApp::update(){
   // ofBackground(0,82,165);
    
    //update the sound playing system
    ofSoundUpdate();
    
    val = ofSoundGetSpectrum(nBandsToGet);
    //get array of floats(1 for each band)
    
    //---------------------
    
    float time = ofGetElapsedTimef();
    
    rX = ofSignedNoise(time * 0.5 + nBandsToGet/8 * 5) * (150.0 + nBandsToGet/8 * 5);  // rotate +- 400deg 0.5
    rY = ofSignedNoise(time * 0.3 + nBandsToGet/8 * 5) * (150.0 + nBandsToGet/8 * 5);
    rZ = ofSignedNoise(time * 0.9 + nBandsToGet/8 * 5) * (150.0 + nBandsToGet/8 * 5); //0.9
    
    //ofPoint dT = ofPoint(ofSignedNoise(time * 0.2) * 3, ofSignedNoise(time * 0.4) * 3, ofSignedNoise(time * 0.6) * 20);
    //t += dT;  // add the delta to our current
    
    float x = ofMap(ofSignedNoise(time * 0.2), -1, 1, 0, ofGetWidth());
    float y = ofMap(ofSignedNoise(time * 0.4), -1, 1, 0, ofGetHeight());
    float z = ofMap(ofSignedNoise(time * 0.2), -1, 1, -500, 500);
    
    t = ofPoint(x, y, z);

    //float time = ofGetElapsedTimef();
    rX1 = ofSignedNoise((time * 0.5 + nBandsToGet/8 * 5) * 150.0 );  // rotate +- 400deg 0.5
    rY1 = ofSignedNoise((time * 0.3 + nBandsToGet/8 * 5) * 150.0);
    rZ1 = ofSignedNoise((time * 0.9 + nBandsToGet/8 * 5) * 150.0); //0.9
    
    float x1 = ofMap(ofSignedNoise(time * 0.5), -1, 1, 0, ofGetWidth());
    float y1 = ofMap(ofSignedNoise(time * 0.4), -1, 1, 0, ofGetHeight());
    float z1 = ofMap(ofSignedNoise(time * 0.9), -1, 1, -1000, 1000);

    t2 = ofPoint(x1,y1,z1);
}

//--------------------------------------------------------------
void ofApp::draw(){
     // draw the fft
    ofSetColor(255,255,255,80);
    ofNoFill();
    for(int i = 0; i < nBandsToGet/60; i++){
        //ofDrawCircle(100 +i*2, ofGetHeight()-300,2,(-1*val[i])*200);
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2,2,(-1*val[i])*200);
    }

//    for(int i = 0; i < nBandsToGet/4; i++){
//        ofDrawLine(ofGetWidth()/2, ofGetHeight()/2, i*4, (-1*val[i])*3000);
//    
//    }
    
   
    
    fbo.begin();
    ofPushStyle();
//    ofSetColor(0,0,0,100);  // alpha fade it
//    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    ofPopStyle();
 
    
    ofPushMatrix();
    ofSetColor(0,0,0,100);  // alpha fade it
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    ofTranslate(t);
    //ofTranslate(t2);
    
    ofRotateX(rX);
    ofRotateY(rY);
    ofRotateZ(rZ);
    
//    ofRotateX(rX1);
//    ofRotateY(rY1);
//    ofRotateZ(rZ1);
    
    ofPushStyle();

//    for(int i = 0; i< nBandsToGet/30;i++){
//        ofSetColor(0, 0, 255);
//        ofDrawLine(p2,p3);
//    }

       for(int i = 0; i< 20;i++){
        ofSetColor(0, 0, 255);
        ofDrawLine(p0,p1);
    }
    ofPopStyle();
    ofPopMatrix();
    fbo.end();

    fbo.draw(0,0);
     //backIamge.draw(0,0);
   // string msg = ofToString((int) ofGetFrameRate()) + " fps";

     ofTranslate(t2);
    
     ofRotateX(rX1);
     ofRotateY(rY1);
     ofRotateZ(rZ1);
    
    for(int i = 0; i< nBandsToGet/3;i++){
              ofSetColor(255, 0, 0);
              ofDrawLine(p2*nBandsToGet/30,p3*nBandsToGet/30);
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
