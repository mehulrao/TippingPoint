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
extern pros::Motor mobileGoalFront;
extern pros::Motor mobileGoalBack;

//CONTROLLER
extern pros::Controller masterController;
extern pros::Controller partnerController;

//Sensors
extern pros::Vision visionSensor;

#endif
