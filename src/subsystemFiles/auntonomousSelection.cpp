#include "main.h"
#include <string>

using namespace std;

lv_obj_t * homeScreen = lv_obj_create(NULL, NULL);

lv_obj_t * leftButton;
lv_obj_t * rightButton;

lv_obj_t * leftLabel;
lv_obj_t * rightLabel;

lv_obj_t * sideContainer;
lv_obj_t * sideLabel;
const char * side = "";
std::string sideString = "";

void autonSelect(){
  lv_scr_load(homeScreen);

  leftButton = lv_btn_create(homeScreen, NULL);
  leftLabel = lv_label_create(leftButton, NULL);
  lv_label_set_text(leftLabel, "LEFT");
  lv_obj_set_size(leftButton, 25, 50);
  lv_obj_set_pos(leftButton, 126, 50);
  lv_btn_set_action(leftButton, LV_BTN_ACTION_CLICK, leftButtonPress);

  rightButton = lv_btn_create(homeScreen, NULL);
  rightLabel = lv_label_create(rightButton, NULL);
  lv_label_set_text(rightLabel, "RIGHT");
  lv_obj_set_size(rightButton, 25, 50);
  lv_obj_set_pos(rightButton, 303, 50);
  lv_btn_set_action(rightButton, LV_BTN_ACTION_CLICK, rightButtonPress);

  sideContainer = lv_cont_create(homeScreen, NULL);
  sideLabel = lv_label_create(sideContainer, NULL);
  lv_obj_set_pos(sideContainer, 215, 80);
}

static lv_res_t leftButtonPress(lv_obj_t * btn){
  side = "left";
  sideString = "left";
  lv_label_set_text(sideLabel, side);
  return LV_RES_OK;
}

static lv_res_t rightButtonPress(lv_obj_t * btn){
  side = "right";
  sideString = "right";
  lv_label_set_text(sideLabel, side);
  return LV_RES_OK;
}
