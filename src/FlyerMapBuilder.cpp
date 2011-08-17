#include<deque>
#include<map>
#include<utility>
#include<iostream>
#include<stdio.h>
#include<string>
#include<SFML/Graphics.hpp>
#include"FlyerMapBuilder.hpp"

FlyerMapBuilder::FlyerMapBuilder():building(true),defaultTexture(0)
{
}

FlyerMapBuilder::~FlyerMapBuilder()
{
}

GLuint FlyerMapBuilder::getTile(int x,int y)
{
    if(0 == defaultTexture)
    {
        defaultTexture = loadTextureRAW("default.bmp");
    }
    {
        sf::Lock DownloadLock(DownloadedMutex);
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
                    (*secondKey).second = loadTextureRAW("thread-test.bmp");
                }

                return (*secondKey).second;
            }
        }
    }

    std::pair<int,int> newTile(x,y);
    {
        sf::Lock QueueLock(QueueMutex);
        tileQueue.push_back(newTile);
    }

    return defaultTexture;
}
;
void FlyerMapBuilder::Run()
{
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
            }
            int x = nextTile.first;
            int y = nextTile.second;

            {
                sf::Lock DownloadLock(DownloadedMutex);
                downloadedTiles[x][y] = 0;
            }

            {
                sf::Lock QueueLock(QueueMutex);
                tileQueue.pop_front();
            }

            sf::Sleep(0.5f);
        }
    }
}

GLuint FlyerMapBuilder::loadTextureRAW(std::string const& filename)
{
    sf::Image TextureImage;
    if (!TextureImage.LoadFromFile(filename))
    {
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
