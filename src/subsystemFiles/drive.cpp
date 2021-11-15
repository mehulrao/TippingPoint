#include "main.h"
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

#define PI 3.1415926535

int currentAngle = 90;
double currentY;
double currentX;
int leftDrive;
int rightDrive;
std::string directionText;
bool reverseDrive = false;
double arcRadius;
int angleDifference;
double leftArcRadius;
double rightArcRadius;
double leftArcCircumference;
double rightArcCircumference;
double leftArcLength;
double rightArcLength;
double leftArcTicks;
double rightArcTicks;
double arcTicks;
double proportion;
int xDifference;
int yDifference;
double distanceTicks;
double driveDistance;
int startAngle;
double pointAngle;
int leftValue;
int rightValue;

//Helper Functions
void setDrive (int left, int right){
  driveRightFront = right;
  driveRightBack = right;
  driveRightCenter = right;
  driveLeftFront = left;
  driveLeftBack = left;
  driveLeftCenter = left;
}

void tareDrive (){
  driveLeftFront.tare_position();
  driveLeftCenter.tare_position();
  driveLeftBack.tare_position();
  driveRightFront.tare_position();
  driveRightCenter.tare_position();
  driveRightBack.tare_position();
}

void findInitialPosition (){

}

//Driver Functions
void driveControl () {
  if(masterController.get_digital(pros::E_CONTROLLER_DIGITAL_A))  {
      reverseDrive = !reverseDrive;
      if (reverseDrive){
        directionText = "Drive: Backwards";
        masterController.set_text(0, 0, directionText);
      } else {
        directionText = "Drive: Forwards ";
        masterController.set_text(0, 0, directionText);
      }
      pros::delay(150);
   }
   if (reverseDrive){
     leftDrive = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * -1 + (masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
     rightDrive = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * -1 - (masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

   }
   if (!reverseDrive) {
     leftDrive = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
     rightDrive = masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

   }
   /**if (abs(masterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) <= 10 || abs(masterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) <=10){
     setDrive(0, 0);
   }*/
   setDrive(leftDrive, rightDrive);
}

void driveTo (int x, int y, double angle, std::string direction, std::string movementType){
  tareDrive();
  if (movementType == "odometry"){ //odometry movement
    //determine arc
    if (angle > currentAngle){
      angleDifference = angle - currentAngle;
    } else if (angle < currentAngle){
      angleDifference = currentAngle - angle;
    }
    if (x > currentX){
      xDifference = x - currentX;
    } else {
      xDifference = currentX - x;
    }
    if (y > currentY){
      yDifference = y - currentY;
    } else {
      yDifference = currentY - y;
    }
    arcRadius = (sqrt(pow(xDifference, 2) + pow(yDifference, 2))) / sqrt(2 - (2 * cos(angleDifference * (PI / 180))));
    if (direction == "forwards"){
      if (angle > currentAngle){
        leftArcRadius = arcRadius - 8.37;
        rightArcRadius = arcRadius + 8.37;
      } else {
        leftArcRadius = arcRadius + 8.37;
        rightArcRadius = arcRadius - 8.37;
      }
    } else {
      if (angle > currentAngle){
        leftArcRadius = arcRadius + 8.37;
        rightArcRadius = arcRadius - 8.37;
      } else {
        leftArcRadius = arcRadius - 8.37;
        rightArcRadius = arcRadius + 8.37;
      }
    }
    leftArcCircumference = 2 * leftArcRadius * PI;
    rightArcCircumference = 2 * rightArcRadius * PI;

    leftArcLength = angleDifference * (leftArcCircumference / 360);
    rightArcLength = angleDifference * (rightArcCircumference / 360);
    std::string leftArcString = to_string(leftArcLength);
    masterController.set_text(0, 0, leftArcString);

    leftArcTicks = (leftArcLength / (3.25 * PI)) * 360 * (5 / 3);
    rightArcTicks = (rightArcLength / (3.25 * PI)) * 360 * (5 / 3);

    if (direction == "forwards"){
      if (angle > currentAngle){
        proportion = leftArcTicks / rightArcTicks;
      } else {
        proportion = rightArcTicks / leftArcTicks;
      }
    } else {
      if (angle > currentAngle){
        proportion = rightArcTicks / leftArcTicks;
      } else {
        proportion = leftArcTicks / rightArcTicks;
      }
    }
    if (direction == "forwards"){
      while ((driveLeftFront.get_position() < leftArcTicks) && (driveRightFront.get_position() < rightArcTicks)) {
        if (angle > currentAngle){
          setDrive(127 * proportion, 127);
        } else {
          setDrive(127, 127 * proportion);
        }
      }
    } else {
      while ((abs(driveLeftFront.get_position()) < leftArcTicks) && (abs(driveRightFront.get_position()) < rightArcTicks)) {
        if (angle > currentAngle){
            setDrive(-127, -127 * proportion);
        } else {
          setDrive(-127 * proportion, -127);
        }
      }
    }
    setDrive(0,0);
  }  else if (movementType == "pivot"){ //pivot
    tareDrive();
    arcRadius = 8.37;
    if (angle > currentAngle){
      angleDifference = angle - currentAngle;
      arcTicks = 2 * angleDifference * arcRadius / 3.25 * (5 / 3);
      leftArcTicks = arcTicks * -1;
      rightArcTicks = arcTicks;
      while ((driveLeftFront.get_position() > leftArcTicks) && (driveRightFront.get_position() < rightArcTicks)){
        setDrive(-100, 100);
      }
      setDrive(0,0);
    } else {
      angleDifference = currentAngle - angle;
      arcTicks = 2 * angleDifference * arcRadius / 3.25 * (5 / 3);
      leftArcTicks = arcTicks;
      rightArcTicks = arcTicks * -1;
      while ((driveLeftFront.get_position() < leftArcTicks) && (driveRightFront.get_position() > rightArcTicks)){
        setDrive(100, -100);
      }
      setDrive(0,0);
    }
  } else if (movementType == "swing"){
    if (angle > currentAngle){
      angleDifference = angle - currentAngle;
    } else {
      angleDifference = currentAngle - angle;
    }
    arcTicks = angleDifference * 2 * 16.74 / 3.25 * (5 / 3);
    if (angle > currentAngle){
      while (driveRightFront.get_position() < arcTicks){
        setDrive(0, 127);
      }
    } else {
      while (driveLeftFront.get_position() < arcTicks){
        setDrive(127, 0);
      }
    }
  }
  currentX = x;
  currentY = y;
  currentAngle = angle;
}

void linearDriveTo (int x, int y, int finishAngle, std::string turn1Type, std::string turn2Type, std::string direction){
  if (x > currentX){
    xDifference = x - currentX;
  } else {
    xDifference = currentX - x;
  }
  if (y > yDifference){
    yDifference = y - currentY;
  } else {
    yDifference = currentY - y;
  }
  startAngle = atan(y / x);
  if (currentAngle != startAngle){
    driveTo(currentX, currentY, startAngle, direction, turn1Type);
    currentAngle = startAngle;
  }

  tareDrive();

  driveDistance = sqrt(pow(xDifference, 2) + pow(yDifference, 2));
  distanceTicks = (driveDistance * 360) / (3.25 * PI) * (5 / 3);
  while (distanceTicks < ((abs(driveLeftFront.get_position()) + abs(driveRightFront.get_position()) / 2))){
    if (direction == "forward"){
      setDrive(127, 127);
    } else {
      setDrive(-127, -127);
    }
  }
  tareDrive();

  setDrive(0, 0);
  if (currentAngle != finishAngle){
    driveTo(x, y, finishAngle, direction, turn2Type);
  }
  currentX = x;
  currentY = y;
  currentAngle = finishAngle;
}

void turnToPoint (int x, int y){
  pointAngle = atan(y/x);
  driveTo(currentX, currentY, pointAngle, "forwards", "pivot");
}

void driveStraight (double distance, int direction, int power){
  tareDrive();
  distanceTicks = (distance / (3.25 * PI)) * 360 * (5 / 3);
  while(driveLeftFront.get_position() < distanceTicks && distanceTicks > abs(driveRightFront.get_position())){
    setDrive(power * direction, power * direction);
  }
  setDrive(0, 0);
}

void swingTurn (int angle, std::string side, int direction){
  tareDrive();
  arcTicks = angle * 2 * 16.74 / 3.25 * (5 / 3);
  if (side == "right"){
    rightValue = direction * 75;
    leftValue = 0;
  } else {
    rightValue = 0;
    leftValue = direction * 75;
  }
  while(abs(driveLeftFront.get_position()) < arcTicks && abs(driveRightFront.get_position()) < arcTicks){
    setDrive(leftValue, rightValue);
  }
  setDrive(0, 0);
}
