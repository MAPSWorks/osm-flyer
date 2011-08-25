#include <iostream>
#include <SFML/Graphics.hpp>
#include "FlyerWindow.hpp"
#include "FlyerMap.hpp"
#include "FlyerConverter.hpp"

FlyerWindow::FlyerWindow():zoom(5),map(zoom)
{
    init();
}

FlyerWindow::FlyerWindow(int z):zoom(z),map(zoom)
{
    init();
}

FlyerWindow::FlyerWindow(int z,float const& lat,float const& lon):zoom(z),map(zoom)
{
    init(lat,lon);
}

FlyerWindow::~FlyerWindow()
{
    if(App.IsOpened())
    {
        App.Close();
    }
}

void FlyerWindow::init(float const& lat, float const& lon)
{
    App.Create(sf::VideoMode(800,600,32),"Open Street Map Flyer");
    App.SetFramerateLimit(60);

    glClearDepth(10.0f);
    glClearColor(0.7f,0.8f,1.0f,0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f,1.0f,1.0f,500.0f);

    float startingTileX = long2tilex(lon,zoom);
    float startingTileY = lat2tiley(lat,zoom);
    cam.setPosition(tile2pos(startingTileX),5.0,tile2pos(startingTileY));
    cam.look();
}

void FlyerWindow::run()
{
    while(App.IsOpened())
    {
        sf::Event Event;
        while(App.GetEvent(Event))
        {
            processEvent(Event);
        }

        cam.look();
        App.SetActive();
        map.setCenter(cam.getX(),cam.getZ());
        paint();
        App.Display();
    }
}

void FlyerWindow::paint()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    map.paint();
}

void FlyerWindow::processEvent(sf::Event const& Event)
{
    if(Event.Type == sf::Event::Closed)
    {
        App.Close();
    }
    else if(Event.Type == sf::Event::KeyPressed)
    {
        float elapsedTime = App.GetFrameTime();
        if(Event.Key.Code == sf::Key::Escape)
        {
            App.Close();
        }
        else if(Event.Key.Code == sf::Key::Right)
        {
            cam.rotate(-1.0 * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::Left)
        {
            cam.rotate(1.0 * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::Up)
        {
            cam.moveForward(10.0 * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::Down)
        {
            cam.moveBackward(10.0 * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::W)
        {
            cam.moveUp(10.0 * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::S)
        {
            cam.moveDown(10.0 * elapsedTime);
        }
    }
    else if(Event.Type == sf::Event::Resized)
    {
        glViewport(0,0,Event.Size.Width,Event.Size.Height);
    }
}
