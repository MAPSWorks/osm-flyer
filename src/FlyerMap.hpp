#ifndef FLYERMAP_H
#define FLYERMAP_H
#include <map>
#include <SFML/Graphics.hpp>
#include "FlyerMapBuilder.hpp"
class FlyerMap
{
    public:
        FlyerMap();
        FlyerMap(int z);
        ~FlyerMap();
        void paint(float const& centerX, float const& centerZ);
    private:
        unsigned int zoom;
        FlyerMapBuilder mapBuilder;
        void printTile(GLuint tile,float x,float z,int w);
        float getAltitude(float const& x,float const& z);
        std::map<int,std::map<int,float> > altitudes;
};
#endif
