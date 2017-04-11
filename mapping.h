#ifndef MAPPING_H
#define MAPPING_H

#include "definitions.h"
#include "grid_map.h"
#include "rplidar.h"
#include "lidar.h"

class Mapping{
public:


 Mapping(grid_map::Map *map){
     this->map = map;
 }

    void setPosition(double x, double y, double theta){
        this->xRobot = x;
        this->yRobot = y;
        this->thetaRobot = theta;
        lowerLimit = 10.0;
        upperLimit = 500.0;

    }

    void update(const LaserMeasurement *measure){

        //ako zistim ktoru zlozku z measurement si mam zobrat??
        distanceLidar = measure->Data[0].scanDistance*LIDAR_CONST;
        angleLidar = measure->Data[0].scanAngle;

        xObstacle = xRobot + distanceLidar * cos((thetaRobot + (360 - angleLidar)) * DEG2RAD);
        yObstacle = xRobot + distanceLidar * cos((thetaRobot + (360 - angleLidar)) * DEG2RAD);
        //xObstacle = xRobot + measure->Data[0].scanDistance*LIDAR_CONST * cos((thetaRobot + (360 - measure->Data[0].scanAngle))*DEG2RAD);
        //yObstacle = yRobot + measure->Data[0].scanDistance*LIDAR_CONST * sin((thetaRobot + (360 - measure->Data[0].scanAngle))*DEG2RAD);

        if ((distanceLidar > lowerLimit) && (distanceLidar < upperLimit)) {
            map->setValue(xObstacle, yObstacle , grid_map::OCCUPIED);
      }else {
            printf("bad measuremet\n");
            map->setValue(xObstacle, yObstacle, grid_map::EMPTY);
        }


    }

private:
    double xRobot,yRobot,thetaRobot;
    double distanceLidar,angleLidar;
    double xObstacle, yObstacle;
    static double lowerLimit,upperLimit;
    static const double LIDAR_CONST = 1.42;
   grid_map::Map *map;
};



#endif // MAPPING_H
