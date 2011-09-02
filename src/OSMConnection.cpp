#include <curl/curl.h>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "OSMConnection.hpp"

OSMConnection::OSMConnection():cacheDir("/tmp/osmflyer/tiles/"),uri("http://a.tile.openstreetmap.org/")
{
    char command[PATH_MAX];
    sprintf(command,"mkdir -p %s",cacheDir.c_str());
    system(command);
}

bool OSMConnection::getImage(int zoom, int x, int y)
{
    std::string filename = getFilenameString(zoom,x,y);
    FILE* fp = NULL;
    fp = fopen(filename.c_str(),"rb");
    if(fp != NULL)
    {
        fseek(fp,0L,SEEK_END);
        size_t const size = ftell(fp);
        fclose(fp);
        if(size > 0)
        {
            return true;
        }
    }
    sf::Clock clock;
    clock.Reset();

    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl)
    {
        std::stringstream url;
        url << uri;
        url << zoom << "/" << x << "/" << y;
        url << ".png";
        std::string filename = getFilenameString(zoom,x,y);
        FILE* fp;
        fp = fopen(filename.c_str(),"w");
        if(fp == NULL)
        {
            std::cerr << "Unable to open " << filename << std::endl;
            return false;
        }

        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,NULL);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
        curl_easy_setopt(curl,CURLOPT_URL,url.str().c_str());
        res = curl_easy_perform(curl);
        if(res)
        {
            std::cerr << "Unable to retrieve data from " << url.str() << std::endl;
            return false;
        }

        curl_easy_cleanup(curl);
        fclose(fp);
        //std::cerr << "Downloaded " << url.str() << " (";
        //std::cerr << clock.GetElapsedTime() << " seconds)" << std::endl;
    }
    else
    {
        std::cerr << "Unable to create curl instance" << std::endl;
        return false;
    }

    return true;
}

std::string OSMConnection::getFilenameString(int zoom, int x, int y)
{
    std::stringstream format;
    format << cacheDir;
    format << "osm-flyer-tile-" << zoom << "-" << x << "-" << y;
    format << ".png";
    return format.str();
}
