#include <iostream>
#include <SFML/Graphics.hpp>
#include "FlyerWindow.hpp"
#include "FlyerMap.hpp"
#include "FlyerConverter.hpp"

FlyerWindow::FlyerWindow():zoom(5),speed(10.0),map(zoom)
{
    init();
}

FlyerWindow::FlyerWindow(int z):zoom(z),speed(10.0),map(zoom)
{
    init();
}

FlyerWindow::FlyerWindow(int z,float const& lat,float const& lon):zoom(z),speed(10.0),map(zoom)
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
    App.Create(sf::VideoMode(800,600,32),"OpenStreetMap Flyer");
    App.SetFramerateLimit(60);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glClearColor(0.7f,0.8f,1.0f,0.0f);
    glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f,1.0f,1.0f,1000.0f);

    float startingTileX = long2tilex(lon,zoom);
    float startingTileY = lat2tiley(lat,zoom);
    cam.setPosition(tile2pos(startingTileX),100.0,tile2pos(startingTileY));
    cam.look();
}

void FlyerWindow::run()
{
    App.SetActive();
    while(App.IsOpened())
    {
        float const elapsedTime = App.GetFrameTime();
        cam.moveForward(speed * elapsedTime);
        bool isTurning = false;
        sf::Event Event;
        while(App.GetEvent(Event))
        {
            processEvent(Event);
        }

        cam.look();
        paint();
        App.Display();
        //std::cerr << (1.0 / App.GetFrameTime()) << std::endl;
    }
}

void FlyerWindow::paint()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    map.paint(cam.getX(),cam.getZ());
}

void FlyerWindow::processEvent(sf::Event const& Event)
{
    if(Event.Type == sf::Event::Closed)
    {
        App.Close();
    }
    else if(Event.Type == sf::Event::KeyPressed)
    {
        float const moveSpeed = 20.0;
        float const rotateSpeed = 2.0;
        float const tiltSpeed = 0.5;
        float const elapsedTime = App.GetFrameTime();

        if(Event.Key.Code == sf::Key::Escape)
        {
            App.Close();
        }
        else if(Event.Key.Code == sf::Key::Right)
        {
            cam.rotate(-rotateSpeed * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::Left)
        {
            cam.rotate(rotateSpeed * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::Up)
        {
            //cam.moveForward(moveSpeed * elapsedTime);
            speed += 5.0;
            if(speed > 110)
            {
                speed = 110;
            }
        }
        else if(Event.Key.Code == sf::Key::Down)
        {
            //cam.moveBackward(moveSpeed * elapsedTime);
            speed -= 5.0;
            if(speed < 0)
            {
                speed = 0;
            }
        }
        else if(Event.Key.Code == sf::Key::W)
        {
            cam.moveUp(moveSpeed * elapsedTime);
        }
        else if(Event.Key.Code == sf::Key::S)
        {
            cam.moveDown(moveSpeed * elapsedTime);
        }
    }
    else if(Event.Type == sf::Event::Resized)
    {
        glViewport(0,0,Event.Size.Width,Event.Size.Height);
    }
}
