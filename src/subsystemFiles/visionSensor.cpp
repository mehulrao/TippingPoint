#include "main.h"

#define YELLOWMOBILEGOAL 1
#define REDMOBILEGOAL 2
#define BLUEMOBILEGOAL 3

pros::vision_signature_s_t yellowSig = pros::Vision::signature_from_utility (YELLOWMOBILEGOAL, 1847, 2617, 2232, -6799, -6425, -6612, 11.000, 0);
pros::vision_signature_s_t redSig = pros::Vision::signature_from_utility (REDMOBILEGOAL, 10679, 12081, 11380, -2175, -1623, -1899, 11.000, 0);
pros::vision_signature_s_t blueSig= pros::Vision::signature_from_utility (BLUEMOBILEGOAL, -4561, -3603, -4082, 8791, 10159, 9475, 11.000, 0);

pros::vision_object_s_t yellowMG = visionSensor.get_by_sig(0, YELLOWMOBILEGOAL);
pros::vision_object_s_t redMG = visionSensor.get_by_sig(0, REDMOBILEGOAL);
pros::vision_object_s_t blueMG = visionSensor.get_by_sig(0, BLUEMOBILEGOAL);

void align (){
    if (yellowMG.x_middle_coord > 10){
        setDrive(127,-127);
    } else if (yellowMG.x_middle_coord < -10){
        setDrive(-127, 127);
    } else {
        setDrive(0,0);
    }
}
