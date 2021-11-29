#include "main.h"
#include <string>

using namespace std;

//Screens
lv_obj_t homeScreen;
lv_obj_t positionScreen;
lv_obj_t mogoScreen;
lv_obj_t statisticsScreen;

//Navigation Buttons
lv_obj_t continueButton;
lv_obj_t backButton;

//Images
lv_obj_t homeImage;
lv_obj_t fieldImage;

//Button Matixes
lv_obj_t positionMatrix;
lv_obj_t mobileGoalMatrix;

//Buttons
lv_obj_t platformButton;

//Labels/Button Maps
lv_obj_t continueLabel;
lv_obj_t backLabel;
const char * positionMatrixMap [] = {"Left", "Right", ""};
const char * mobileGoalMatrixMap [] = {"Short", "Tall", "Both", "None", ""}

void homeScreenFunction (){
  //Creates Home Screen
  homeScreen = lv_obj_create(NULL, NULL);

  //Navigation Buttons
    //Continue Button
    continueButton = lv_btn_create(homeScreen, NULL);
    lv_obj_set_pos(continueButton, 50, 50);
    lv_obj_set_size(continueButton, 100, 50);

}

void autonSelect()
{
  
}
