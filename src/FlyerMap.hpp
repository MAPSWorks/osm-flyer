#ifndef FLYERMAP_H
#define FLYERMAP_H
#include<SFML/Graphics.hpp>
#include "FlyerMapBuilder.hpp"
class FlyerMap
{
    public:
        FlyerMap();
        ~FlyerMap();
        void paint();
        void setCenter(float const& x, float const& z);
    private:
        float centerX;
        float centerZ;
        unsigned int zoom;
        FlyerMapBuilder mapBuilder;
        float xpos2lat(float const& xpos,int zoom);
        float zpos2long(float const& zpos, int zoom);
        float lat2xpos(float const& lat,int zoom);
        float long2zpos(float const& lng,int zoom);
        int long2tilex(float const& lng, int zoom);
        int lat2tiley(float const& lng, int zoom);
        float tilex2long(int tilex, int zoom);
        float tiley2lat(int tiley, int zoom);
};
#endif
