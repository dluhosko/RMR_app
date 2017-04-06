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

    void update(){
        //map->setValue(-5.4,  2.3, grid_map::OCCUPIED);
    }

private:
    double x,y,theta;
   grid_map::Map *map;
};



#endif // MAPPING_H
