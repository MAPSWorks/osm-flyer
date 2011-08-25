#include <math.h>
#include "FlyerConverter.hpp"

int pos2tile(float const& pos)
{
    return floor(pos / 64.0);
}

float tile2pos(int tile)
{
    return tile * 64.0;
}

float xpos2lat(float const& xpos,int zoom)
{
    return tiley2lat(xpos / 128.0,zoom);
}

float zpos2long(float const& zpos,int zoom)
{
    return tilex2long(zpos / 128.0,zoom);
}

float lat2xpos(float const& lat, int zoom)
{
    return lat2tiley(lat,zoom) * 128.0;
}

float long2zpos(float const& lng, int zoom)
{
    return long2tilex(lng,zoom) * 128.0;
}

int long2tilex(float const& lon, int z) 
{ 
        return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
}
 
int lat2tiley(float const& lat, int z)
{ 
        return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
}
 
float tilex2long(int x, int z) 
{
        return x / pow(2.0, z) * 360.0 - 180;
}
 
float tiley2lat(int y, int z) 
{
        float n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
            return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}
