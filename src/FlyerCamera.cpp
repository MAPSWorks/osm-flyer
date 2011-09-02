#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FlyerCamera.hpp"

void FlyerCamera::setPosition(float const& x, float const& y, float const& z)
{
    xpos = x;
    ypos = y;
    zpos = z;
}

void FlyerCamera::rotate(float const& angleDiff)
{
    angle += angleDiff;
    if(angle > 2*M_PI)
    {
        angle = angle - 2*M_PI;
    }
    else if(angle < 0.0)
    {
        angle = 2*M_PI - angle;
    }
}

void FlyerCamera::tilt(float const& angleDiff)
{
    float const tiltLimit = M_PI / 4.0;

    lensAngle += angleDiff;
    if(lensAngle > tiltLimit)
    {
        lensAngle = tiltLimit;
    }else if (lensAngle < -tiltLimit)
    {
        lensAngle = -tiltLimit;
    }

    if(lensAngle > 2*M_PI)
    {
        lensAngle = lensAngle - 2*M_PI;
    }
    else if(lensAngle < -2*M_PI)
    {
        lensAngle = 2*M_PI - lensAngle;
    }
}

void FlyerCamera::setTilt(float const& tiltAngle)
{
    lensAngle = tiltAngle;
}

float const& FlyerCamera::getTilt()
{
    return lensAngle;
}

void FlyerCamera::look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float const xoff = sin(angle);
    float const yoff = 0.0;
    float const zoff = cos(angle);

    float const rotatedAngle = angle + (M_PI / 2.0);
    float const xrot = cos(lensAngle) * sin(rotatedAngle);
    float const yrot = sin(lensAngle);
    float const zrot = cos(lensAngle) * cos(rotatedAngle);

    xup = yoff * zrot - zoff * yrot;
    yup = zoff * xrot - xoff * zrot;
    zup = xoff * yrot - yoff * xrot;

    glMatrixMode(GL_MODELVIEW);
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

void FlyerCamera::moveUp(float const& step)
{
    ypos += step;
}

void FlyerCamera::moveDown(float const& step)
{
    ypos -= step;
}
