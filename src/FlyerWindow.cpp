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

FlyerWindow::~FlyerWindow()
{
    if(App.IsOpened())
    {
        App.Close();
    }
}

void FlyerWindow::init()
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

    float startingTileX = 282.0;
    float startingTileY = 404.0;
    cam.setPosition(tile2pos(startingTileX),5.0,tile2pos(startingTileY));
}

void FlyerWindow::run()
{
    cam.look();
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

void FlyerWindow::drawDiscoFloor()
{
    int colorNumber = 1;
    for(int startX=-50;startX<50;startX+=25)
    {
        for(int startZ=-50;startZ<50;startZ+=25)
        {
            glPushMatrix();
            glTranslatef(startX,0.0f,startZ);
        
            sf::Randomizer::SetSeed(colorNumber);
            float red = sf::Randomizer::Random(0.0f,1.0f);
            float green = sf::Randomizer::Random(0.0f,1.0f);
            float blue = sf::Randomizer::Random(0.0f,1.0f);
            glColor3f(red,green,blue);
            ++colorNumber;

            glBegin(GL_QUADS);
                glVertex3f(0.0f,0.0f,0.0f);
                glVertex3f(25.0f,0.0f,0.0f);
                glVertex3f(25.0f,0.0f,25.0f);
                glVertex3f(0.0f,0.0f,25.0f);
            glEnd();

            glPopMatrix();
        }
    }
}

void FlyerWindow::paint()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glTranslatef(cam.getX(),0.0f,cam.getZ());
    map.paint();
}

void FlyerWindow::drawCube()
{
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-200.0f);
    glBegin(GL_QUADS);
        glVertex3f(-50.0f,-50.0f,-50.0f); 
        glVertex3f(-50.0f,50.0f,-50.0f); 
        glVertex3f(50.0f,50.0f,-50.0f); 
        glVertex3f(50.0f,-50.0f,-50.0f); 

        glVertex3f(-50.0f,-50.0f,50.0f); 
        glVertex3f(-50.0f,50.0f,50.0f); 
        glVertex3f(50.0f,50.0f,50.0f); 
        glVertex3f(50.0f,-50.0f,50.0f); 

        glVertex3f(-50.0f,-50.0f,-50.0f); 
        glVertex3f(-50.0f,50.0f,-50.0f); 
        glVertex3f(-50.0f,50.0f,50.0f); 
        glVertex3f(-50.0f,-50.0f,50.0f); 

        glVertex3f(50.0f,-50.0f,-50.0f); 
        glVertex3f(50.0f,50.0f,-50.0f); 
        glVertex3f(50.0f,50.0f,50.0f); 
        glVertex3f(50.0f,-50.0f,50.0f); 

        glVertex3f(-50.0f,-50.0f,50.0f); 
        glVertex3f(-50.0f,-50.0f,-50.0f); 
        glVertex3f(50.0f,-50.0f,-50.0f); 
        glVertex3f(50.0f,-50.0f,50.0f); 

        glVertex3f(-50.0f,50.0f,50.0f); 
        glVertex3f(-50.0f,50.0f,-50.0f); 
        glVertex3f(50.0f,50.0f,-50.0f); 
        glVertex3f(50.0f,50.0f,50.0f); 
    glEnd();
    glPopMatrix();
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
