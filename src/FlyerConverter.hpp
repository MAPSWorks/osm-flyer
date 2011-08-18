#ifndef FLYERCONVERTER_H
#define FLYERCONVERTER_H
int pos2tile(float const& pos);
float tile2pos(int tile);
float xpos2lat(float const& xpos,int zoom);
float zpos2long(float const& zpos, int zoom);
float lat2xpos(float const& lat,int zoom);
float long2zpos(float const& lng,int zoom);
int long2tilex(float const& lng, int zoom);
int lat2tiley(float const& lng, int zoom);
float tilex2long(int tilex, int zoom);
float tiley2lat(int tiley, int zoom);
#endif
