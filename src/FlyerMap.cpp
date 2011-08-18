#include <SFML/Graphics.hpp>
#include "FlyerMap.hpp"
#include <iostream>
#include <math.h>

FlyerMap::FlyerMap():centerX(0.0),centerZ(0.0),zoom(5)
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
    unsigned int const width = 128;
    unsigned int const radius = width*4;
    int centerTileX = long2tilex(zpos2long(centerZ,zoom),zoom);
    int centerTileY = lat2tiley(xpos2lat(centerX,zoom),zoom);
    float drawX = lat2xpos(tiley2lat(centerTileY,zoom),zoom);
    float drawZ = long2zpos(tilex2long(centerTileX,zoom),zoom);
    
    for(float i = drawX - radius;
            i < drawX + radius + 1;
            i += width)
    {
        for(float j = drawZ - radius;
                j < drawZ + radius + 1;
                j += width)
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

void FlyerMap::setCenter(float const& x, float const& z)
{
    centerX = x;
    centerZ = z;
}

float FlyerMap::xpos2lat(float const& xpos,int zoom)
{
    return tiley2lat(xpos/2,zoom);
}

float FlyerMap::zpos2long(float const& zpos,int zoom)
{
    return tilex2long(zpos/2,zoom);
}

float FlyerMap::lat2xpos(float const& lat, int zoom)
{
    return lat2tiley(lat,zoom) * 2;
}

float FlyerMap::long2zpos(float const& lng, int zoom)
{
    return long2tilex(lng,zoom) * 2;
}

int FlyerMap::long2tilex(float const& lng, int z)
{
    return (int)(floor((lng + 180.0) / 360.0 * pow(2.0,z)));
}

int FlyerMap::lat2tiley(float const& lat, int z)
{
    return (int)(floor((1.0 - log(tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0,z)));
}

float FlyerMap::tilex2long(int tilex, int z)
{
    return tilex / pow(2.0,z) * 360.0 - 180.0;
}

float FlyerMap::tiley2lat(int tiley, int z)
{
    float n = M_PI - 2.0 * M_PI * tiley / pow(2.0,z);
    return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}
