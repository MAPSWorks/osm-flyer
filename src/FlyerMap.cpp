#include <iostream>
#include <SFML/Graphics.hpp>
#include "FlyerMap.hpp"
#include "FlyerConverter.hpp"

FlyerMap::FlyerMap():centerX(0.0),centerZ(0.0),zoom(5),mapBuilder(zoom)
{
}

FlyerMap::FlyerMap(int z):centerX(0.0),centerZ(0.0),zoom(z),mapBuilder(zoom)
{
}

FlyerMap::~FlyerMap()
{
}

void FlyerMap::paint()
{
    glPushMatrix();
    unsigned int const width = 64;
    unsigned int const radius = width*3;
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

            GLuint tile = (GLuint) mapBuilder.getTile(currentTileX,currentTileY);
            printTile(tile,i,j,width);
        }
    }
    glPopMatrix();
}

void FlyerMap::printTile(GLuint tile,int x, int z, int w)
{
    glBindTexture(GL_TEXTURE_2D,tile);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0); 
        glVertex3f(x,0.0,z);
        glTexCoord2f(0.0,1.0); 
        glVertex3f(x,0.0,z+w);
        glTexCoord2f(1.0,1.0); 
        glVertex3f(x+w,0.0,z+w);
        glTexCoord2f(1.0,0.0); 
        glVertex3f(x+w,0.0,z);
    glEnd();
}

void FlyerMap::setCenter(float const& x, float const& z)
{
    centerX = x;
    centerZ = z;
}
