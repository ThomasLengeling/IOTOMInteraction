//
//  Block.cpp
//  IOTOMInteraction
//
//  Created by tom on 1/12/16.
//
//


#include "Blocks.h"

namespace iotom{
    
    //Face
    Face::Face()
    {
        mHover = ofColor(255, 255, 255);
        mSelect = ofColor(255, 255, 0);
    }
    
    
    void Face::addVertex(ofVec3f vert)
    {
        mVertices.push_back(vert);
    }
    
    void Face::setColor(ofColor col)
    {
        mCurrent = col;
    }
    
    void Face::drawFace()
    {
        ofSetColor(mCurrent);
        ofFill();
        
        ofBeginShape();
        for(auto & vert : mVertices){
            ofVertex(vert.x, vert.y, vert.z);
        }
        ofEndShape(true);
  
        ofDrawSphere(mCenter.x, mCenter.y, mCenter.z, 5);
    }
    
    void Face::setCenter(ofVec3f center)
    {
        mCenter = center;
    }
    
    ofVec3f Face::getCenter()
    {
        return mCenter;
    }
    
    //---Block
    Block::Block()
    {
        
    }
    
    void Block::setTranslation(ofVec3f pos)
    {
        mTrans = pos;
    }
    
    void Block::setSize(ofVec3f size)
    {
        mSize = size;
        
        float x = mSize.x;
        float y = mSize.y;
        float z = mSize.z;
        
        //blue 0
        //red  1
        //green 2
        //yellow 3
        //purple 4
        //aqua 5
        
        mFaces.clear();
        FaceRef backFace = Face::create();
        backFace->addVertex(ofVec3f(x, -y, -z));
        backFace->addVertex(ofVec3f(-x, -y, -z));
        backFace->addVertex(ofVec3f(-x, y, -z));
        backFace->addVertex(ofVec3f(x, y, -z));
        backFace->setColor(ofColor(0, 0, 255));
        backFace->setCenter(ofVec3f(0, 0, -z));
        mFaces.push_back(backFace);
        
        //Right
        FaceRef rightFace = Face::create();
        rightFace->addVertex(ofVec3f(x, y, -z));
        rightFace->addVertex(ofVec3f(x, y, z));
        rightFace->addVertex(ofVec3f(x, -y, z));
        rightFace->addVertex(ofVec3f(x, -y, -z));
        rightFace->setColor(ofColor(255, 0, 0));
        rightFace->setCenter(ofVec3f(x, 0, 0));
        mFaces.push_back(rightFace);
        
        //Left
        FaceRef leftFace = Face::create();
        leftFace->addVertex(ofVec3f(-x, y, z));
        leftFace->addVertex(ofVec3f(-x, y, -z));
        leftFace->addVertex(ofVec3f(-x, -y, -z));
        leftFace->addVertex(ofVec3f(-x, -y, z));
        leftFace->setColor(ofColor(0, 255, 0));
        leftFace->setCenter(ofVec3f(-x, 0, 0));
        mFaces.push_back(leftFace);
        
        //bottom
        FaceRef bottomFace = Face::create();
        bottomFace->addVertex(ofVec3f(x, -y, z));
        bottomFace->addVertex(ofVec3f(-x, -y, z));
        bottomFace->addVertex(ofVec3f(-x, -y, -z));
        bottomFace->addVertex(ofVec3f(x, -y, -z));
        bottomFace->setColor(ofColor(255, 255, 0));
        bottomFace->setCenter(ofVec3f(0, -y, 0));
        mFaces.push_back(bottomFace);
        
        //Top
        FaceRef topFace = Face::create();
        topFace->addVertex(ofVec3f(x, y, -z));
        topFace->addVertex(ofVec3f(-x, y, -z));
        topFace->addVertex(ofVec3f(-x, y, z));
        topFace->addVertex(ofVec3f(x, y, z));
        topFace->setColor(ofColor(255, 0, 255));
        topFace->setCenter(ofVec3f(0, y, 0));
        mFaces.push_back(topFace);
        
        //Front
        FaceRef frontFace = Face::create();
        frontFace->addVertex(ofVec3f(x, y, z));
        frontFace->addVertex(ofVec3f(-x, y, z));
        frontFace->addVertex(ofVec3f(-x, -y, z));
        frontFace->addVertex(ofVec3f(x, -y, z));
        frontFace->setColor(ofColor(0, 255, 255));
        frontFace->setCenter(ofVec3f(0, 0, z));
        mFaces.push_back(frontFace);
    }
    
    void Block::draw()
    {

        for(auto & face : mFaces){
            ofPushMatrix();
        
            ofTranslate(mTrans.x, mTrans.y, mTrans.z);

            face->drawFace();
            ofPopMatrix();
            
            ofGetCurrentViewMatrix();
        }
        
    }
    
    
    std::vector<FaceRef> Block::getFaces()
    {
        return mFaces;
    }
    
    //Block Manger
    BlockManager::BlockManager()
    {
        
    }
    
    
    void BlockManager::addBlock(BlockRef block)
    {
        mBlocks.push_back(block);
    }
    
    void BlockManager::draw()
    {
        for(auto & blocks : mBlocks){
            blocks->draw();
        }
    }
    
    BlockPair BlockManager::getPickedBlock(ofVec2f mousePos, ofEasyCam cam)
    {
        float nearestDistance = 10;
        ofVec2f nearestVertex;
        
        int nearestFaceId = -1;
        int nearestBlockId = -1;
    
        int fi = 0;
        int bj = 0;
        for(auto & blocks : mBlocks){
            for(auto & face : blocks->getFaces()){
                ofVec3f translate  = face->getCenter() + blocks->getTranslation();
              
                ofVec3f cur = cam.worldToScreen(translate );
                
                float distance = cur.distance(mousePos);
                if( distance < nearestDistance) {
                    nearestDistance = distance;
                    nearestVertex = cur;
                    
                    
                    nearestBlockId = bj;
                    nearestFaceId = fi % 6;
                }
                fi++;
            }
            bj++;
        }
        return std::make_pair(nearestBlockId, nearestFaceId);
    }
    
}
