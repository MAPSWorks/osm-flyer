#ifndef OSMCONNECTION_H
#define OSMCONNECTION_H
#include<SFML/System.hpp>
#include<string>
class OSMConnection
{
    public:
        OSMConnection();
        ~OSMConnection(){}
        bool getImage(int zoom, int x, int y);
        std::string getFilenameString(int zoom, int x, int y);
    private:
        std::string cacheDir;
        std::string uri;
};
#endif
