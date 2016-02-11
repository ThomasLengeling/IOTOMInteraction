#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableSmoothing();
    ofEnableDepthTest();
    
    camEasyCam.setDistance(1000);

    mBlockManager = iotom::BlockManager::create();
    
    iotom::BlockRef block = iotom::Block::create();
    block->setSize(ofVec3f(30, 30, 30));
    block->setTranslation(ofVec3f(50, 0, 0));
    mBlockManager->addBlock(block);
    
    iotom::BlockRef block2 = iotom::Block::create();
    block2->setSize(ofVec3f(30, 30, 30));
    block2->setTranslation(ofVec3f(150, 0, 50));
    mBlockManager->addBlock(block2);
    
    iotom::BlockRef block3 = iotom::Block::create();
    block3->setSize(ofVec3f(30, 30, 30));
    block3->setTranslation(ofVec3f(300, 0, 150));
    mBlockManager->addBlock(block3);
    
    iotom::BlockRef block4 = iotom::Block::create();
    block4->setSize(ofVec3f(30, 30, 30));
    block4->setTranslation(ofVec3f(350, 0, 250));
    mBlockManager->addBlock(block4);
    
    std::cout<<"Hello"<<std::endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    ofEnableDepthTest();
    
    camEasyCam.begin();
    ofPushMatrix();
    //ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0);
    mBlockManager->draw();
    ofPopMatrix();
    
    ofSetColor(255);
    ofDrawGrid(200, 10, false, false, true, false);
    
    camEasyCam.end();
    
    ofDisableDepthTest();
    
    iotom::BlockPair bk =  mBlockManager->getPickedBlock(ofVec2f(mouseX, mouseY), camEasyCam);
    
    std::cout<<bk.first<<" "<<bk.second<<std::endl;
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
