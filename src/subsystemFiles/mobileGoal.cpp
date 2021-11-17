#include "main.h"
#include <string>

using namespace std;

void setFrontMobileGoalLift(int value)
{
  mobileGoalFront = value;
}

void setBackMobileGoalLift(int value)
{
  mobileGoalBack = value;
}

void frontMobileGoalOperatorControl()
{
  int mobileGoalValue;
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
  {
    mobileGoalValue = 63;
  }
  else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
  {
    mobileGoalValue = -63;
  }
  else
  {
    mobileGoalValue = 0;
  }
  setFrontMobileGoalLift(mobileGoalValue);
}

void mobileGoalLiftOperatorControl (){
  int liftValue;
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    liftValue = 127;
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    liftValue = -127;
  } else {
    liftValue = 0;
  }
  setBackMobileGoalLift(liftValue);
}
