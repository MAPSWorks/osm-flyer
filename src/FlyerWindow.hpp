#ifndef FLYERWINDOW_H
#define FLYERWINDOW_H
#include <SFML/Graphics.hpp>
#include "FlyerCamera.hpp"
#include "FlyerMap.hpp"

class FlyerWindow
{
    public:
        FlyerWindow();
        FlyerWindow(int z);
        FlyerWindow(int z,float const& lat, float const& lon);
        ~FlyerWindow();
        void run();
        void paint();
        void processEvent(sf::Event const& Event);

    private:
        unsigned int zoom;
        FlyerMap map;
        FlyerCamera cam;
        sf::RenderWindow App;
        void init(float const& lat=-80.27, float const& lon=36.0);
        void drawCube();
        void drawDiscoFloor();
};
#endif
