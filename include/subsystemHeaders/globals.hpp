#include "main.h"

using namespace pros;

#ifndef GLOBALS
#define GLOBALS

//MOTORS
extern pros::Motor driveLeftFront;
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftCenter;
extern pros::Motor driveRightFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightCenter;
extern pros::Motor mobileGoalLeft;
extern pros::Motor mobileGoalRight;

//CONTROLLER
extern pros::Controller masterController;
extern pros::Controller partnerController;

//Sensors
extern pros::Vision visionSensor;
extern pros::Imu inertialSensor;

//Pneumatics
extern pros::ADIDigitalOut liftRightPiston;
extern pros::ADIDigitalOut liftMiddlePiston;
extern pros::ADIDigitalOut liftLeftPiston;
extern pros::ADIDigitalOut backMobileGoalLeftPiston;
extern pros::ADIDigitalOut backMobileGoalRightPiston;

#endif
