#include <deque>
#include <map>
#include <utility>
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "FlyerMapBuilder.hpp"
#include "FlyerMapBuilderThread.hpp"

FlyerMapBuilder::FlyerMapBuilder():defaultTexture(0),zoom(5),
    numTiles(pow(2.0,zoom)),
    builderThreadA(zoom,tileQueue,QueueMutex,downloadedTiles,DownloadMutex),
    builderThreadB(zoom,tileQueue,QueueMutex,downloadedTiles,DownloadMutex)
{
    builderThreadA.Launch();
    builderThreadB.Launch();
}

FlyerMapBuilder::FlyerMapBuilder(int z):defaultTexture(0),
    zoom(z),numTiles(pow(2.0,zoom)),
    builderThreadA(zoom,tileQueue,QueueMutex,downloadedTiles,DownloadMutex),
    builderThreadB(zoom,tileQueue,QueueMutex,downloadedTiles,DownloadMutex)
{

    builderThreadA.Launch();
    builderThreadB.Launch();
}

FlyerMapBuilder::~FlyerMapBuilder()
{
    builderThreadA.stopBuilding();
    builderThreadB.stopBuilding();
    builderThreadA.Wait();
    builderThreadB.Wait();
}

int FlyerMapBuilder::getTile(int x,int y)
{
    if(0 == defaultTexture)
    {
        defaultTexture = loadTextureRAW("default.bmp");
    }

    // Outside bounds of map
    if(x < 0 || y < 0 || x > numTiles - 1 
            || y > numTiles - 1)
    {
        return defaultTexture;
    }

    {
        sf::Lock DownloadLock(DownloadMutex);
        // Find Row
        OSMTextureMap::iterator firstKey = downloadedTiles.find(x);
        if(downloadedTiles.end() != firstKey)
        {
            // Find Column
            TextureMap::iterator secondKey = (*firstKey).second.find(y);
            if((*firstKey).second.end() != secondKey)
            {
                // Texture hasn't been loaded yet 
                if(0 == (*secondKey).second)
                {
                    GLuint result = loadTextureRAW(builderThreadA.getFilenameString(zoom,x,y));
                    if(result != 0)
                    {
                        (*secondKey).second = result;
                        return (*secondKey).second;
                    }
                }
                // Texture is downloading
                else if(-1 == (*secondKey).second)
                {
                    return defaultTexture;
                }
                // Texture is loaded
                else
                { 
                    return (*secondKey).second;
                }
            }
        }
    }
    
    std::pair<int,int> newTile(x,y);
    {
        sf::Lock DownloadLock(DownloadMutex);
        downloadedTiles[x][y] = -1;
    }
    {
        sf::Lock QueueLock(QueueMutex);
        tileQueue.push_back(newTile);
    }

    return defaultTexture;
}

GLuint FlyerMapBuilder::loadTextureRAW(std::string const& filename)
{
    sf::Image TextureImage;
    if (!TextureImage.LoadFromFile(filename))
    {
        if(remove(filename.c_str()) != 0)
        {
            std::cerr << "Error deleting file " << filename << std::endl;
        }
        return 0;
    }
    GLuint texture = 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TextureImage.GetWidth(), TextureImage.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, TextureImage.GetPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    return texture;
}
