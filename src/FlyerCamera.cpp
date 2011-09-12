#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FlyerCamera.hpp"

/**
 * Set the grid coordinates for the camear
 */
void FlyerCamera::setPosition(float const& x, float const& y, float const& z)
{
    xpos = x;
    ypos = y;
    zpos = z;
}

/**
 * Rotate camera an angle delta given in radians
 */
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

/**
 * Tilt camera an angle delta given in radians
 */
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

/**
 * Set the tile of the camera to angle in radians
 */
void FlyerCamera::setTilt(float const& tiltAngle)
{
    lensAngle = tiltAngle;
}

/**
 * Get tilt of camera
 */
float const& FlyerCamera::getTilt()
{
    return lensAngle;
}

/**
 * Calculate direction of camera and up vector for camera, then
 * performs opengl gluLookAt call
 */
void FlyerCamera::look()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Caculate direction vector
    float const xoff = sin(angle);
    float const yoff = 0.0;
    float const zoff = cos(angle);

    // Calculate rotated vector. The dot product of this and the direction
    // vector results in the up vector
    float const rotatedAngle = angle + (M_PI / 2.0);
    float const xrot = cos(lensAngle) * sin(rotatedAngle);
    float const yrot = sin(lensAngle);
    float const zrot = cos(lensAngle) * cos(rotatedAngle);

    // Find the up vector
    xup = yoff * zrot - zoff * yrot;
    yup = zoff * xrot - xoff * zrot;
    zup = xoff * yrot - yoff * xrot;

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(xpos,ypos,zpos,
            xpos+xoff,ypos+yoff,zpos+zoff,
            xup,yup,zup);
}

/**
 * Move the camera forward a step in the direction vector
 */
void FlyerCamera::moveForward(float const& step)
{
    xpos += sin(angle) * step;
    zpos += cos(angle) * step;
}

/**
 * Move the camera backward a step in the direction vector
 */
void FlyerCamera::moveBackward(float const& step)
{
    xpos -= sin(angle) * step;
    zpos -= cos(angle) * step;
}

/**
 * Move the camera a step up in altitude
 */
void FlyerCamera::moveUp(float const& step)
{
    ypos += step;
}

/**
 * Move the camera a step down in altitude
 */
void FlyerCamera::moveDown(float const& step)
{
    ypos -= step;
}
