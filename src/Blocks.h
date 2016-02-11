//
//  Block.h
//  IOTOMInteraction
//
//  Created by tom on 1/12/16.
//
//

#pragma once


#include "ofMain.h"
#include <memory>
#include <vector>
#include <iostream>

namespace iotom {
    
    //Face class
    class Face;
    class Block;
    class BlockManager;
    
    typedef std::shared_ptr<Face>         FaceRef;
    typedef std::shared_ptr<BlockManager> BlockManagerRef;
    typedef std::shared_ptr<Block>        BlockRef;
    
    typedef std::pair<int, int>           BlockPair;
    
    class Face{
    public:
        Face();
        
        static FaceRef create(){return std::make_shared<Face>();}
        
        void addVertex(ofVec3f vert);
        void setColor(ofColor col);
        void drawFace();
        
        void setCenter(ofVec3f center);
        ofVec3f getCenter();
        
    private:
        std::vector< ofVec3f > mVertices;
        ofVec3f                mCenter;
        
        
        ofColor                mCurrent;
        ofColor                mHover;
        ofColor                mSelect;
        
    };
    
    
    //class Block
    
    class Block{
    public:
        Block();
        
        void setSize(ofVec3f size);
        
        void setTranslation(ofVec3f pos);
        ofVec3f getTranslation(){return mTrans;}
        
        static BlockRef create(){return std::make_shared<Block>();}
        
        void draw();
        
        std::vector<FaceRef> getFaces();
        
        
        
    private:
        
        std::vector<FaceRef> mFaces;
        ofVec3f              mSize;
        ofVec3f              mTrans;
    };
    
    
    
    //BlockManager
    class BlockManager{
    public:
        BlockManager();
        static BlockManagerRef create(){return std::make_shared<BlockManager>();}
        
        
        void addBlock(BlockRef block);
        void draw();
        
        BlockPair getPickedBlock(ofVec2f mousePos, ofEasyCam cam);
        
        
    private:
        std::vector<BlockRef> mBlocks;
    };
}