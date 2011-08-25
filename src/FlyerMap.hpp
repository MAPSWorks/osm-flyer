#ifndef FLYERMAP_H
#define FLYERMAP_H
#include<SFML/Graphics.hpp>
#include "FlyerMapBuilder.hpp"
class FlyerMap
{
    public:
        FlyerMap();
        FlyerMap(int z);
        ~FlyerMap();
        void paint();
        void setCenter(float const& x, float const& z);
    private:
        float centerX;
        float centerZ;
        unsigned int zoom;
        FlyerMapBuilder mapBuilder;
        void printTile(GLuint tile,int x,int z,int w);
};
#endif
