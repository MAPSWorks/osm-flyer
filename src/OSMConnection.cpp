#include <curl/curl.h>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <SFML/Graphics.hpp>
#include "OSMConnection.hpp"

/**
 * Creates cache directory if it does not exist using mkdir
 */
OSMConnection::OSMConnection():cacheDir(""),uri("http://a.tile.openstreetmap.org/")
{
    char command[PATH_MAX];
    struct passwd *pw = getpwuid(getuid());
    std::string const homeDir(pw->pw_dir);
    cacheDir = homeDir + "/.cache/osmflyer/tiles/";
    
    sprintf(command,"mkdir -p %s",cacheDir.c_str());
    system(command);
}

/**
 * Saves image into cache directory if it does not exist
 */
bool OSMConnection::getImage(int zoom, int x, int y)
{
    std::string filename = getFilenameString(zoom,x,y);

    // See if image is in directory already, return if it is
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

    // If not download image using curl
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

/**
 * Return string for filename given the OSM parameters
 */
std::string OSMConnection::getFilenameString(int zoom, int x, int y)
{
    std::stringstream format;
    format << cacheDir;
    format << "tile-" << zoom << "-" << x << "-" << y;
    format << ".png";
    return format.str();
}
