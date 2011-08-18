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
        ~FlyerWindow();
        void run();
        void paint();
        void processEvent(sf::Event const& Event);

    private:
        unsigned int zoom;
        FlyerMap map;
        FlyerCamera cam;
        sf::Window App;
        void init();
        void drawCube();
        void drawDiscoFloor();
};
#endif
