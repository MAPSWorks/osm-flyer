#ifndef FLYERMAP_H
#define FLYERMAP_H
class FlyerMap
{
    public:
        FlyerMap():centerLat(0.0),centerLong(0.0),zoom(5){}
        ~FlyerMap(){}
        void paint();
        void update(float const& newLat, float const& newLong);
    private:
        float centerLat;
        float centerLong;
        unsigned int zoom;
};
#endif
