#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "irobotcreate.h"
#include "definitions.h"
#include <math.h>

class Navigation{
public:

   // const static double RAD2DEG = 57.2957795130823;
  //  const static double DEG2RAD = 0.0174532925199432;

    const double ANGLE_MIN_ERROR = Definitions::DEG2RAD*10;

    const double MIN_DIST =  50;

    Navigation(iRobotCreate *robot): x(0), y(0), theta(0), Kp_lin(0.7), Kp_ang(50){
        this->robot = robot;
	last_linear_speed = 0;
        last_angular_speed = 0;
        request_linear_speed = 0;
    }

    Navigation(iRobotCreate *robot, double Kp_lin, double Kp_ang): x(0), y(0), theta(0){
        this->robot = robot;    
        this->Kp_lin = Kp_lin;
        this->Kp_ang = Kp_ang;

        last_linear_speed = 0;
        request_linear_speed = 0;
        last_angular_speed = 0;


    }
    void setPosition(double x, double y, double theta){
        this->x = x;
        this->y = y;
        this->theta = theta;

    }

    bool turn(double request_angle){

        if (request_angle < 0) {
            request_angle += 2*M_PI;
        }
        if (theta < 0) {
            theta += 2*M_PI;
        }

        double angle_diff = theta - request_angle;

        static bool turning = false;
        printf("\nrequested angle %f \ntheta %f\n", request_angle, theta);

        if (fabs(angle_diff) > ANGLE_MIN_ERROR) {

            if ((int)last_linear_speed != 0){
                goForward(0);
                regulationSpeedLinear();
                return false;
            }

            if (!turning) {
                turning = true;

                if (angle_diff > M_PI ) {
                    turnLeft(50);
                   // turnLeft(fabs(angle_diff)*Kp_ang);

                } else if (angle_diff <= M_PI / 2 && angle_diff > 0) {
                    turnRight(50);
                    //turnRight(fabs(angle_diff)*Kp_ang);

                } else if (angle_diff <= 0 && angle_diff > -M_PI) {
                    turnLeft(50);
                    //turnLeft(fabs(angle_diff)*Kp_ang);

                } else {
                   turnRight(50);
                   // turnRight(fabs(angle_diff)*Kp_ang);
                }
            } else printf("kkt sa otaca");
        } else {
            turning = false;
            //goForward(0);
            return true;
            }
        regulationSpeedAngular();
        return false;
    }
    bool goToPoint(double x, double y){

        bool retval;
        double diff_x = x - this->x;
        double diff_y = y - this->y;
        double dist = sqrt(pow(diff_x, 2.0) + pow(diff_y, 2.0));

       double request_angle = atan2(diff_y, diff_x);
        if (dist > MIN_DIST) {
            if (turn(request_angle)) {
 //--------------FORWARD MODE (REQ ANGLE IS OK)---------------------//
                 goForward(dist * Kp_lin);

            }  else return false;    //-------TURNING MODE - return from function

        } else{                     //--------------ROBOT REACH TARGET - STOPING

           goForward(0);
           if ((int)last_linear_speed == 0)
               retval = true;
           else retval = false;
        }

        regulationSpeedLinear();
        return retval;
    }

protected:
    virtual void turnLeft(double speed){

       // robot->move((int)speed, (int)-speed);
        request_angular_speed = -speed;
    }

    virtual void turnRight(double speed){

       request_angular_speed = speed;
       // robot->move((int)-speed, (int) speed);

    }

    virtual void goForward(double speed){

        request_linear_speed = speed;
      //  robot->move( (int) speed, (int)speed);
    }

    virtual void regulationSpeedAngular(){

        if (last_angular_speed < request_angular_speed - 50) {
            last_angular_speed += 50;
        }
        else if (last_angular_speed > request_angular_speed+50){
            last_angular_speed -=50;
        }
        else
            last_angular_speed = request_angular_speed;

        if ((int) last_angular_speed < 50 && (int) last_angular_speed > 0)
            last_angular_speed = 50;


        robot->move(-(int)last_angular_speed, (int)last_angular_speed);



        // robot->move(-(int)request_angular_speed, (int)request_angular_speed);
    }

    virtual void regulationSpeedLinear(){

	const int step = 35;

        if (last_linear_speed < request_linear_speed- step){
                 last_linear_speed += step;

        } else if (last_linear_speed > request_linear_speed + step){
                last_linear_speed -= step;

        } else last_linear_speed = request_linear_speed;

        if ((int) last_linear_speed < step && (int) last_linear_speed > 0)
            last_linear_speed = step;

        robot->move((int)last_linear_speed, (int)last_linear_speed);
    }

private:
    iRobotCreate *robot;
    double x,y,theta;
    double linear_vel, angular_vel;
    double request_angular_speed;
    double request_linear_speed;
    double last_linear_speed;
    double last_angular_speed;
    double Kp_lin;
    double Kp_ang;
};


#endif
