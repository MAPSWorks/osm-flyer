#include <iostream>
#include <SFML/Graphics.hpp>
#include "FlyerWindow.hpp"
#include "FlyerMap.hpp"

FlyerWindow::FlyerWindow()
{
    App.Create(sf::VideoMode(800,600,32),"Open Street Map Flyer");
    App.SetFramerateLimit(60);

    glClearDepth(10.0f);
    glClearColor(0.7f,0.8f,1.0f,0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f,1.0f,1.0f,500.0f);

    cam.setPosition(0.0,5.0,0.0);
}

FlyerWindow::~FlyerWindow()
{
    if(App.IsOpened())
    {
        App.Close();
    }
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

    glColor3f(1.0f,1.0f,1.0f);
    glTranslatef(cam.getX(),0.0f,cam.getZ());

    glBegin(GL_QUADS);
        glVertex3f(-500.0,0.0,-500.0);
        glVertex3f(-500.0,0.0,500.0);
        glVertex3f(500.0,0.0,500.0);
        glVertex3f(500.0,0.0,-500.0);
    glEnd();

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
        if(Event.Key.Code == sf::Key::Escape)
        {
            App.Close();
        }
        else if(Event.Key.Code == sf::Key::Right)
        {
            cam.rotate(-0.1);
        }
        else if(Event.Key.Code == sf::Key::Left)
        {
            cam.rotate(0.1);
        }
        else if(Event.Key.Code == sf::Key::Up)
        {
            cam.moveForward(2.0);
        }
        else if(Event.Key.Code == sf::Key::Down)
        {
            cam.moveBackward(2.0);
        }
    }
    else if(Event.Type == sf::Event::Resized)
    {
        glViewport(0,0,Event.Size.Width,Event.Size.Height);
    }
}