#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <SFML/Graphics.hpp>
#include "FlyerMap.hpp"
#include "FlyerConverter.hpp"

FlyerMap::FlyerMap():zoom(5),mapBuilder(zoom)
{
}

FlyerMap::FlyerMap(int z):zoom(z),mapBuilder(zoom)
{
}

FlyerMap::~FlyerMap()
{
}

/**
 * paint a tile at the given opengl coordinates
 */
void FlyerMap::paint(float const& centerX, float const& centerZ)
{
    glPushMatrix();
    
    // Only print tiles within a certain radius
    unsigned int const width = TILE_WIDTH;
    unsigned int const radius = width*5;

    int const centerTileX = pos2tile(centerX);
    int const centerTileY = pos2tile(centerZ);

    float const drawX = tile2pos(centerTileX);
    float const drawZ = tile2pos(centerTileY);
    
    for(float i = drawX - radius;
            i < drawX + radius + 1;
            i += width)
    {
        for(float j = drawZ - radius;
                j < drawZ + radius + 1;
                j += width)
        {
            int const currentTileX = pos2tile(i);
            int const currentTileY = pos2tile(j);

            GLuint const tile = (GLuint) mapBuilder.getTile(currentTileX,currentTileY);
            printTile(tile,i,j,width);
        }
    }
    glPopMatrix();
}

/**
 * Returns random altitude for given opengl coordinates
 */
float FlyerMap::getAltitude(float const& x, float const& z)
{
    srand(x+z);
    float const factor = (double) rand() / RAND_MAX + 1;
    float const maxAltitude = 40;
    return factor * maxAltitude;
}

/**
 * Use opengl to print a texture to a grid coordinate of the specified width
 */
void FlyerMap::printTile(GLuint tile,float x, float z, int w)
{
    glBindTexture(GL_TEXTURE_2D,tile);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0); 
        glVertex3f(x,getAltitude(x,z),z);
        glTexCoord2f(0.0,1.0); 
        glVertex3f(x,getAltitude(x,z+w),z+w);
        glTexCoord2f(1.0,1.0); 
        glVertex3f(x+w,getAltitude(x+w,z+w),z+w);
        glTexCoord2f(1.0,0.0); 
        glVertex3f(x+w,getAltitude(x+w,z),z);
    glEnd();
}
