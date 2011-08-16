#ifndef FLYERTILE_H
#define FLYERTILE_H
#include <SFML/Graphics.hpp>
class FlyerTile
{
    public:
        FlyerTile():tileLat(35.0),tileLong(-80.0){}
        FlyerTile(float const& lat, float const& lng):tileLat(lat),tileLong(lng){}
        ~FlyerTile(){}
        void setPosition(float const& lat, float const& lng);
        void paint();
    private:
        float xpos;
        float ypos;
        float tileLat;
        float tileLong;
        sf::Image Image;
};
#endif
