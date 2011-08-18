#ifndef FLYERMAPBUILDER_H
#define FLYERMAPBUILDER_H
#include<deque>
#include<map>
#include<utility>
#include<stdio.h>
#include<string>
#include<SFML/System.hpp>
#include"OSMConnection.hpp"
typedef std::map<int,GLuint> TextureMap;
typedef std::map<int,TextureMap > OSMTextureMap;
typedef std::deque<std::pair<int,int> > OSMTextureQueue;
class FlyerMapBuilder : public sf::Thread
{
    public:
        FlyerMapBuilder();
        FlyerMapBuilder(int z);
        ~FlyerMapBuilder();
        GLuint getTile(int x, int y); 
        virtual void Run();
    private:
        OSMTextureQueue tileQueue;
        OSMTextureMap downloadedTiles;
        sf::Mutex DownloadedMutex;
        sf::Mutex QueueMutex;
        bool building;
        GLuint defaultTexture;
        GLuint loadTextureRAW(std::string const& filename);
        OSMConnection osmConnection;
        unsigned int zoom;
};
#endif
