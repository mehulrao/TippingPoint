#include "main.h"
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

//Constants
#define PI 3.1415926535
#define CIRCUMFERANCE 20.4203522

//Operator Control varibles
int leftDrive;
int rightDrive;
std::string directionText;
bool reverseDrive = false;

//Odometry varibles
double currentX;
double currentY;
double proportion;
double leftArc;
double rightArc;

//Linear Drive varibles
double angleRads;
double wheelTicks;

//Helper Functions
void setDrive(int left, int right)
{
  driveRightFront = right;
  driveRightBack = right;
  driveRightCenter = right;
  driveLeftFront = left;
  driveLeftBack = left;
  driveLeftCenter = left;
}

void tareDrive()
{
  driveLeftFront.tare_position();
  driveLeftCenter.tare_position();
  driveLeftBack.tare_position();
  driveRightFront.tare_position();
  driveRightCenter.tare_position();
  driveRightBack.tare_position();
}

//Driver Functions

  //Operator Control Drive Functions
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
      setDrive(leftDrive, rightDrive);
    }

  //Autonomous Drive Functions
    void driveTo (double x, double y, double finalAngle, int direction){
      tareDrive();

      double xDiff = abs(currentX - x);
      double yDiff = abs(currentY - y);
      double angleDiff = abs(inertialSensor.get_heading() - finalAngle);

      angleRads = angleDiff * (PI / 180);
      double radius = (sqrt(pow(xDiff,2) + pow(yDiff,2)))/ sqrt(2 * (1-cos(angleRads)));

      if (inertialSensor.get_heading() > finalAngle && direction > 0 || inertialSensor.get_heading() < finalAngle && direction < 0){
        leftArc = (radius + 8.37) * angleRads;
        rightArc = (radius - 8.37) * angleRads;
      } else {
        leftArc = (radius - 8.37) * angleRads;
        rightArc = (radius + 8.37) * angleRads;
      }

      double leftArcTicks = ((leftArc / CIRCUMFERANCE) * (3 / 5)) * 900;
      double rightArcTicks = ((leftArc /CIRCUMFERANCE) * (3 / 5)) * 900;

      if (inertialSensor.get_heading() > finalAngle && direction > 0 || inertialSensor.get_heading() < finalAngle && direction < 0){
        proportion = rightArcTicks / leftArcTicks;
      } else {
       proportion = leftArcTicks / rightArcTicks;
     }

     while (leftArcTicks < driveLeftFront.get_position() && rightArcTicks < driveRightFront.get_position()){
        if (inertialSensor.get_heading() > finalAngle && direction > 0 || inertialSensor.get_heading() < finalAngle && direction < 0){
         setDrive(127 * direction, 127 * proportion * direction);
        } else {
          setDrive(127 * proportion * direction, 127 * direction);
        }
      }
      currentX = x;
      currentY = y;
    }

    void pivot (double angle){
      while (inertialSensor.get_heading() > angle - 1 && inertialSensor.get_heading() < angle + 1){
        if (angle < inertialSensor.get_heading()){
          setDrive(127,-127);
        } else {
          setDrive(-127,127);
        }
      }
    }

    void driveStraight (double distance, int direction){
      angleRads = inertialSensor.get_heading() * (PI / 180);
      currentX += distance * cos(angleRads) * direction;
      currentY += distance * sin(angleRads) * direction;

      wheelTicks = (leftArc / CIRCUMFERANCE) * (3 / 5) * 900;

      while (wheelTicks > ((driveLeftFront.get_position() + driveRightFront.get_position()) / 2)){
        setDrive(127 * direction, 127 * direction);
      }
    }

    void swing (double angle){
      if (angle < inertialSensor.get_heading()){
        while (inertialSensor.get_heading() > angle){
          setDrive(127,0);
        }
      } else {
        while(inertialSensor.get_heading() < angle){
          setDrive(0, 127);
        }
      }
    }

    void stopDrive (){
      setDrive(0, 0);
    }
