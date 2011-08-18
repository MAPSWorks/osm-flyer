#include <iostream>
#include <SFML/Graphics.hpp>
#include "FlyerMap.hpp"
#include "FlyerConverter.hpp"

FlyerMap::FlyerMap():centerX(0.0),centerZ(0.0),zoom(5),mapBuilder(zoom)
{
    mapBuilder.Launch();
}

FlyerMap::FlyerMap(int z):centerX(0.0),centerZ(0.0),zoom(z),mapBuilder(zoom)
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
    unsigned int const width = 64;
    unsigned int const radius = width*4;
    int centerTileX = pos2tile(centerX);
    int centerTileY = pos2tile(centerZ);

    float drawX = tile2pos(centerTileX);
    float drawZ = tile2pos(centerTileY);
    
    for(float i = drawX - radius;
            i < drawX + radius + 1;
            i += width)
    {
        for(float j = drawZ - radius;
                j < drawZ + radius + 1;
                j += width)
        {
            int currentTileX = pos2tile(i);
            int currentTileY = pos2tile(j);

            GLuint tile = mapBuilder.getTile(currentTileX,currentTileY);
            glBindTexture(GL_TEXTURE_2D,tile);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0,0.0); 
                glVertex3f(i,0.0,j);
                glTexCoord2f(0.0,1.0); 
                glVertex3f(i,0.0,j+width);
                glTexCoord2f(1.0,1.0); 
                glVertex3f(i+width,0.0,j+width);
                glTexCoord2f(1.0,0.0); 
                glVertex3f(i+width,0.0,j);
            glEnd();
        }
    }
    glPopMatrix();
}

void FlyerMap::setCenter(float const& x, float const& z)
{
    centerX = x;
    centerZ = z;
}
