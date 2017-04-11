#ifndef MAPPING_H
#define MAPPING_H

#include "definitions.h"
#include "grid_map.h"

class Mapping{
public:


 Mapping(grid_map::Map *map){
     this->map = map;
 }

    void setPosition(double x, double y, double theta){
        this->x = x;
        this->y = y;
        this->theta = theta;

    }

    void update(const LaserMeasurement *measure){

        //PRIKLAD setovania mapy
        //  map->setValue(x, y, grid_map::EMPTY); //volne policko
        //  map->setValue(x + 1, y, grid_map::OCCUPIED); //obsadene policko

    }

private:
    double x,y,theta;
   grid_map::Map *map;
};



#endif // MAPPING_H
