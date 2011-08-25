#ifndef FLYERMAPBUILDERTHREAD_H
#define FLYERMAPBUILDERTHREAD_H
#include <deque>
#include <map>
#include <utility>
#include <string>
#include <SFML/System.hpp>
#include "OSMConnection.hpp"

typedef std::map<int,int> TextureMap;
typedef std::map<int,TextureMap > OSMTextureMap;
typedef std::deque<std::pair<int,int> > OSMTextureQueue;

class FlyerMapBuilderThread : public sf::Thread
{
    public:
        FlyerMapBuilderThread(int z,OSMTextureQueue& tq, sf::Mutex& qm, 
                OSMTextureMap& dt, sf::Mutex& dm);
        ~FlyerMapBuilderThread();
        virtual void Run();
        std::string getFilenameString(int zoom, int x, int y);
    private:
        OSMConnection osmConn;
        OSMTextureQueue& tileQueue;
        sf::Mutex& QueueMutex;
        OSMTextureMap& downloadedTiles;
        sf::Mutex& DownloadMutex;
        bool building;
        int zoom;
};
#endif
