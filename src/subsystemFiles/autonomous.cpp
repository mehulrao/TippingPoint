#include "main.h"

void runLeftAuton (){
  mobileGoalFrontDown();
  driveStraight(18.5, 1, 127);
  pros::delay(100);
  driveTo(0, 0, 52, "forwards", "pivot");
  pros::delay(100);
  driveStraight(52, 1, 75);
  mobileGoalFrontUp();
  pros::delay(100);
  driveStraight(45, -1, 127);
  pros::delay(100);
  driveTo(0, 0, 270, "forwards", "pivot");
  mobileGoalDrop();
  driveStraight(8, -1, 127);
  pros::delay(100);
  driveTo(0, 0, 46.2, "forwards", "pivot");
  pros::delay(100);
  driveStraight(61.5, 1, 75);
  pros::delay(250);
  mobileGoalFrontUp();
  pros::delay(750);
  driveStraight(100, -1, 100);
  pros::delay(100);
  driveStraight(10, 1, 127);
}

void runRightAuton(){
  mobileGoalFrontDown();
  driveStraight(10.5, 1, 75);
  pros::delay(100);
  mobileGoalFrontUp();
  pros::delay(100);
  swingTurn (60, "right", 1);
  /**pros::delay(100);
  driveStraight(40, 1, 75);
  pros::delay(100);
  driveTo(0, 0, 315, "forwards", "pivot");
  pros::delay(100);
  driveStraight(10.5, -1, 65);
  mobileGoalBackUp();
  pros::delay(100);
  driveStraight(24, 1, 50);*/
}
