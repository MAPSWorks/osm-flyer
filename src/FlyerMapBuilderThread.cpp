#include <deque>
#include <map>
#include <utility>
#include <iostream>
#include <SFML/System.hpp>
#include "FlyerMapBuilderThread.hpp"
#include "OSMConnection.hpp"

FlyerMapBuilderThread::FlyerMapBuilderThread(int z,OSMTextureQueue& tq, sf::Mutex& qm,
        OSMTextureMap& dt, sf::Mutex& dm):osmConn(),tileQueue(tq),
    QueueMutex(qm),downloadedTiles(dt),DownloadMutex(dm),building(false),zoom(z)
{
}

FlyerMapBuilderThread::~FlyerMapBuilderThread()
{
    building = false;
}

void FlyerMapBuilderThread::Run()
{
    building = true;
    while(building)
    {
        bool hasTiles;
        {
            sf::Lock QueueLock(QueueMutex);
            hasTiles = !tileQueue.empty();
        }

        if(hasTiles)
        {
            std::pair<int,int> nextTile;
            {
                sf::Lock QueueLock(QueueMutex);
                nextTile = tileQueue.front();
                tileQueue.pop_front();
            }

            int x = nextTile.first;
            int y = nextTile.second;

            {
                sf::Lock DownloadLock(DownloadMutex);
                downloadedTiles[x][y] = -1;
            }
            osmConn.getImage(zoom,x,y);
            {
                sf::Lock DownloadLock(DownloadMutex);
                downloadedTiles[x][y] = 0;
            }
        }else
        {
            sf::Sleep(1.5f);
        }
    }
}

std::string FlyerMapBuilderThread::getFilenameString(int zoom,int x,int y)
{
    return osmConn.getFilenameString(zoom,x,y);
}

void FlyerMapBuilderThread::stopBuilding()
{
    building = false;
}
