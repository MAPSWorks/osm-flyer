#ifndef FLYERMAPBUILDER_H
#define FLYERMAPBUILDER_H
#include <deque>
#include <map>
#include <utility>
#include <string>
#include <SFML/System.hpp>
#include "FlyerMapBuilderThread.hpp"

class FlyerMapBuilder 
{
    public:
        FlyerMapBuilder();
        FlyerMapBuilder(int z);
        ~FlyerMapBuilder();
        int getTile(int x, int y); 
    private:
        OSMTextureQueue tileQueue;
        OSMTextureMap downloadedTiles;
        sf::Mutex DownloadMutex;
        sf::Mutex QueueMutex;
        GLuint defaultTexture;
        GLuint loadTextureRAW(std::string const& filename);
        unsigned int zoom;
        int numTiles;
        FlyerMapBuilderThread builderThreadA;
        FlyerMapBuilderThread builderThreadB;
};
#endif
