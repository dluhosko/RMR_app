#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <math.h>

class Definitions{

public:
    typedef struct point{
        double x;
        double y;
    } POINT;

    static constexpr double RAD2DEG = 57.2957795130823;
    static constexpr double DEG2RAD = 0.0174532925199432;

    Definitions();

    static double getDistance(POINT p1, POINT p2){

        double diff_x = p1.x - p2.x;
        double diff_y = p1.y - p2.y;

        return sqrt(pow(diff_x, 2.0) + pow(diff_y, 2.0));
    }

    //p1 ziadany bod a p2 aktualny bod
    static double getAngle(POINT p1, POINT p2){

        double diff_x = p1.x - p2.x;
        double diff_y = p1.y - p2.y;

        double angle = atan2(diff_y, diff_x);

        if (angle < 0) {
            angle += 2*M_PI;
        }
        return angle;
    }
};
#endif // DEFINITIONS_H
