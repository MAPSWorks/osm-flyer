#include <SFML/Graphics.hpp>
#include "FlyerCamera.hpp"
#include <iostream>

#define PI 3.1459

void FlyerCamera::setPosition(float const& x, float const& y, float const& z)
{
    xpos = x;
    ypos = y;
    zpos = z;
}

void FlyerCamera::rotate(float const& angleDiff)
{
    angle += angleDiff;
    if(angle > 2*PI)
    {
        angle = angle - 2*PI;
    }
    else if(angle < 0.0)
    {
        angle = 2*PI + angle;
    }
}

void FlyerCamera::look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float xoff = sin(angle);
    float zoff = cos(angle);
    float yoff = 0.0;
    gluLookAt(xpos,ypos,zpos,
            xpos+xoff,ypos+yoff,zpos+zoff,
            xup,yup,zup);
}

void FlyerCamera::moveForward(float const& step)
{
    xpos += sin(angle) * step;
    zpos += cos(angle) * step;
}

void FlyerCamera::moveBackward(float const& step)
{
    xpos -= sin(angle) * step;
    zpos -= cos(angle) * step;
}
