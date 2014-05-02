/*
 *  SharedData.h
 */

#pragma once

class SharedData
{
public:
    
    //put shared data here
    ofFbo wallOne;
    ofFbo wallTwo;
	ofFbo syphonOut;
    
    ofShader maskShader;
    int xPos, yPos;
    int inc;
    
    void maskFrames( ofImage topLayer, ofImage mask, bool vidPlayerLoaded ){
        if(vidPlayerLoaded) {
            
            maskShader.begin();
            
            maskShader.setUniformTexture("Tex0", topLayer.getTextureReference(), 0);
            maskShader.setUniformTexture("Tex1", mask.getTextureReference(), 1);
            
            //our shader uses two textures, the top layer and the alpha
            //we can load two textures into a shader using the multi texture coordinate extensions
            glActiveTexture(GL_TEXTURE0_ARB);
            topLayer.getTextureReference().bind();
            
            glActiveTexture(GL_TEXTURE1_ARB);
            mask.getTextureReference().bind();
            
            //draw a quad the size of the frame
            glBegin(GL_QUADS);
            
            //move the mask around with the mouse by modifying the texture coordinates
            glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
            glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);
            glVertex2f( 0, 0);
            
            glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), 0);
            glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth(), 0);
            glVertex2f( 935, 0);
            
            glMultiTexCoord2d(GL_TEXTURE0_ARB, topLayer.getWidth(), topLayer.getHeight());
            glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth(), mask.getHeight());
            glVertex2f( 935, ofGetHeight());
            
            glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, topLayer.getHeight());
            glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, mask.getHeight());
            glVertex2f( 0, ofGetHeight() );
            
            glEnd();
            
            //deactive and clean up
            glActiveTexture(GL_TEXTURE1_ARB);
            mask.getTextureReference().unbind();
            
            glActiveTexture(GL_TEXTURE0_ARB);
            topLayer.getTextureReference().unbind();
            
            maskShader.end();
        }
    }

    
    
};
