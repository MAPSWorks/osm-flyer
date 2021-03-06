#ifndef FLYERCAMERA_H
#define FLYERCAMERA_H
#include <SFML/Graphics.hpp>

class FlyerCamera
{
    public:
        FlyerCamera():xpos(0.0),ypos(0.0),zpos(0.0),
                    xup(0.0),yup(1.0),zup(0.0),
                    angle(0.0),lensAngle(0.0){}
        FlyerCamera(float const& x, float const& y, float const& z):
                    xpos(x),ypos(y),zpos(z),
                    xup(0.0),yup(1.0),zup(0.0),
                    angle(0.0){}
        ~FlyerCamera(){}
        void rotate(float const& angleDiff);
        void tilt(float const& angleDiff);
        void setTilt(float const& tiltAngle);
        float const& getTilt();
        void setPosition(float const& x, float const& y, float const& z);
        void look();
        void moveForward(float const& step=1.0f);
        void moveBackward(float const& step=1.0f);
        void moveUp(float const& step=1.0);
        void moveDown(float const& step=1.0);
        float const& getX(){ return xpos; }
        float const& getY(){ return ypos; }
        float const& getZ(){ return zpos; }
    private:
        float xpos, ypos, zpos;
        float xup, yup, zup;
        float angle;
        float lensAngle;
};
#endif
