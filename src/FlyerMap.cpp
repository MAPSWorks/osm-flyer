#include <SFML/Graphics.hpp>
#include "FlyerMap.hpp"
#include <iostream>

FlyerMap::FlyerMap():centerLat(0.0),centerLong(0.0),zoom(5)
{
    mapBuilder.Launch();
}

FlyerMap::~FlyerMap()
{
    mapBuilder.Terminate();
}

void FlyerMap::paint()
{
    glPushMatrix();
    for(int i=-512; i<512;i+=128)
    {
        for(int j=-512; j<512; j+=128)
        {
            GLuint tile = mapBuilder.getTile(i,j);
            glBindTexture(GL_TEXTURE_2D,tile);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0,0.0); 
                glVertex3f(i,0.0,j);
                glTexCoord2f(0.0,1.0); 
                glVertex3f(i,0.0,j+128);
                glTexCoord2f(1.0,1.0); 
                glVertex3f(i+128,0.0,j+128);
                glTexCoord2f(1.0,0.0); 
                glVertex3f(i+128,0.0,j);
            glEnd();
        }
    }
    glPopMatrix();
}

