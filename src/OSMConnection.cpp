#include <curl/curl.h>
#include <sstream>
#include <string>
#include <iostream>
#include "OSMConnection.hpp"

bool OSMConnection::getImage(int zoom, int x, int y)
{
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
