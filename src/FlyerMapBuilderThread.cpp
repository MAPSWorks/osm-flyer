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

/**
 * Thread worker loop. Downloads tiles as they appear in download queue
 */
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
            // Get tile from queue
            std::pair<int,int> nextTile;
            {
                sf::Lock QueueLock(QueueMutex);
                nextTile = tileQueue.front();
                tileQueue.pop_front();
            }

            int x = nextTile.first;
            int y = nextTile.second;

            // Download image  
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

/**
 * Get filename string from connection for the given parameters
 */
std::string FlyerMapBuilderThread::getFilenameString(int zoom,int x,int y)
{
    return osmConn.getFilenameString(zoom,x,y);
}

/**
 * Stops the worker loop if it is running
 */
void FlyerMapBuilderThread::stopBuilding()
{
    building = false;
}
