#ifndef FLYERWINDOW_H
#define FLYERWINDOW_H
#include <SFML/Graphics.hpp>
#include "FlyerCamera.hpp"
#include "FlyerMap.hpp"

class FlyerWindow
{
    public:
        FlyerWindow();
        ~FlyerWindow();
        void run();
        void paint();
        void processEvent(sf::Event const& Event);

    private:
        sf::Window App;
        FlyerCamera cam;
        FlyerMap map;
        void drawCube();
        void drawDiscoFloor();
};
#endif
