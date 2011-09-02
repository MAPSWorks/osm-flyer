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

void FlyerMap::paint(float const& centerX, float const& centerZ)
{
    glPushMatrix();
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

size_t curl_to_string(void* ptr, size_t size, size_t nmemb, void* data)
{
    std::string* str = (std::string*) data;
    char* cPtr = (char*) ptr;
    for(size_t i=0; i<size*nmemb;++i)
    {
        (*str) += cPtr[i];
    }
    return size * nmemb;
}

float FlyerMap::getAltitude(float const& x, float const& z)
{
    srand(x+z);
    float const factor = (double) rand() / RAND_MAX + 1;
    float const maxAltitude = 40;
    return factor * maxAltitude;
    /*
    float const lat = xpos2lat(z,zoom);
    float const lon = zpos2long(x,zoom);
    float altitude = 0.0;

    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl)
    {
        std::stringstream url;
        url << "http://api.geonames.org/srtm3?";
        url << "lat=" << lat << "&";
        url << "lng=" << lon << "&";
        url << "username=forestmb";
        std::string altData;
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,curl_to_string);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&altData);
        curl_easy_setopt(curl,CURLOPT_URL,url.str().c_str());
        res = curl_easy_perform(curl);
        if(res)
        {
            std::cerr << "Unable to retrieve data from " << url.str() << std::endl;
            return 0.0;
        }
        curl_easy_cleanup(curl);
        altitude = atof(altData.c_str());
    }

    return altitude;
    */
}

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
