#include "main.h"
#include <string>

using namespace std;

void setFrontMobileGoalLift (int value){
  mobileGoalFront = value;
}

void setBackMobileGoalLift (int value){
  mobileGoalBack = value;
}

void frontMobileGoalOperatorControl (){
  int mobileGoalValue;
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
    mobileGoalValue = 63;
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
    mobileGoalValue = -63;
  } else {
    mobileGoalValue = 0;
  }
  setFrontMobileGoalLift(mobileGoalValue);
}

void backMobileGoalOperatorControl (){
  int backMobileGoalValue;
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    backMobileGoalValue = 127;
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    backMobileGoalValue = -127;
  } else {
    backMobileGoalValue = 0;
  }
  setBackMobileGoalLift(backMobileGoalValue);
}

void mobileGoalFrontDown (){
  mobileGoalFront.tare_position();
  while (abs(mobileGoalFront.get_position()) < 2300){
    setFrontMobileGoalLift(-127);
  }
  setFrontMobileGoalLift(0);
}

void mobileGoalFrontUp(){
  mobileGoalFront.tare_position();
  while(mobileGoalFront.get_position() < 1340){
    mobileGoalFront = 127;
  }
  mobileGoalFront = 0;
}

void mobileGoalBackUp (){
  mobileGoalBack.tare_position();
  while(mobileGoalBack.get_position() < 10000){
    mobileGoalBack = 127;
  }
  mobileGoalBack = 0;
}

void mobileGoalDrop (){
  mobileGoalFront.tare_position();
  while(abs(mobileGoalFront.get_position()) < 1340){
    mobileGoalFront = -127;
  }
  mobileGoalFront = 0;
}
