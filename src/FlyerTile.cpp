#include <SFML/Graphics.hpp>
#include "FlyerTile.h"

void FlyerTile::setPosition(float const& lat, float const& lng)
{
    tileLat = lat;
    tileLong = lng;
}

void FlyerTile::paint()
{
}
