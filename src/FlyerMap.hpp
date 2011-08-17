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
    private:
        float centerLat;
        float centerLong;
        unsigned int zoom;
        FlyerMapBuilder mapBuilder;
        float xpos2lat(float const& xpos);
        float ypos2long(float const& ypos);
        float lat2xpos(float const& lat);
        float long2ypos(float const& lng);
        int long2tilex(float const& lng, int zoom);
        int lat2tiley(float const& lng, int zoom);
        float tilex2long(int tilex, int zoom);
        float tiley2lat(int tiley, int zoom);
};
#endif
