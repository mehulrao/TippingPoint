#include "main.h"
#include <string>

using namespace std;

bool backMobileGoalToggle = false;


void setMobileGoalLift(int value)
{
  mobileGoalLeft = value;
  mobileGoalRight = value;
}

void frontMobileGoalOperatorControl (){
  int liftValue;
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
    liftValue = 127;
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
    liftValue = -127;
  } else {
    liftValue = 0;
  }
  setMobileGoalLift(liftValue);
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    liftRightPiston.set_value(true);
    liftMiddlePiston.set_value(true);
    liftLeftPiston.set_value(true);

    pros::delay(500);

    liftRightPiston.set_value(false);
    liftMiddlePiston.set_value(false);
    liftLeftPiston.set_value(false);
  }
}

void backMobileGoalOperatorControl(){
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    backMobileGoalToggle = !backMobileGoalToggle;

    backMobileGoalPiston.set_value(backMobileGoalToggle);
    pros::delay(750);
  }
}

void backMobileGoalAuton (){
  backMobileGoalToggle = !backMobileGoalToggle;

  backMobileGoalPiston.set_value(backMobileGoalToggle);
}

void frontMobileGoalAuton (int position){
  if (position == 1){
    while (mobileGoalLeft.get_position() > 0){
      setMobileGoalLift(-127);
    }
  } else if (position == 2){
    while (mobileGoalLeft.get_position() > 125){
      setMobileGoalLift(-127);
    }
    while (mobileGoalLeft.get_position() < 125){
      setMobileGoalLift(127);
    }
  } else {
    while (mobileGoalLeft.get_position() < 1125){
      setMobileGoalLift(127);
    }
  }
}
