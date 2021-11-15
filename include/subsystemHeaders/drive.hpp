#include "main.h"

//Helper Functions
void setDrive (int left, int right);
void tareDrive();
void findInitialPosition ();

//Driver Functions
void driveControl();

void driveTo (int x, int y, double angle, std::string direction, std::string movementType);

void linearDriveTo (int x, int y, int finishAngle, std::string turn1Type, std::string turn2Type, std::string direction);

void turnToPoint (int x, int y);

void driveStraight (double distance, int direction, int power);

void swingTurn (int angle, std::string side, int direction);
