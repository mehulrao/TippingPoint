#include "main.h"
#include <string>

using namespace std;

typedef  FILE * pc_file_t;

int screenCounter = 0;
std::string position;
std::string mobileGoal;
bool platform;

//Screens
lv_obj_t * homeScreen;
lv_obj_t * positionScreen;
lv_obj_t * mogoScreen;
lv_obj_t * statisticsScreen;

//Navigation Buttons
lv_obj_t * continueButton;
lv_obj_t * backButton;

//Images
lv_obj_t * homeImage;
lv_obj_t * fieldImage;

//Button Matixes
lv_obj_t * positionMatrix;
lv_obj_t * mobileGoalMatrix;

//Buttons
lv_obj_t * platformButton;

//Labels/Button Maps
lv_obj_t * continueLabel;
lv_obj_t * backLabel;
lv_obj_t * platformLabel;
const char * positionMatrixMap [] = {"Left", "Right", ""};
const char * mobileGoalMatrixMap [] = {"Short", "Tall", "Both", "None", ""};

//Create Driver For Images
static lv_fs_res_t pcfs_open( void * file_p, const char * fn, lv_fs_mode_t mode)
{
    errno = 0;
    const char * flags = "";
    if(mode == LV_FS_MODE_WR) flags = "wb";
    else if(mode == LV_FS_MODE_RD) flags = "rb";
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) flags = "a+";

    char buf[256];
    sprintf(buf, "/%s", fn);
    pc_file_t f = fopen(buf, flags);

    if(f == NULL)
      return LV_FS_RES_UNKNOWN;
    else {
      fseek(f, 0, SEEK_SET);
      pc_file_t * fp = (pc_file_t *)file_p;
      *fp = f;
    }

    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_close( void * file_p)
{
    pc_file_t * fp = (pc_file_t *)file_p;
    fclose(*fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_read( void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    pc_file_t * fp =  (pc_file_t *)file_p;
    *br = fread(buf, 1, btr, *fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_seek( void * file_p, uint32_t pos)
{
    pc_file_t * fp = (pc_file_t *)file_p;
    fseek(*fp, pos, SEEK_SET);
    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_tell( void * file_p, uint32_t * pos_p)
{
    pc_file_t * fp =  (pc_file_t *)file_p;
    *pos_p = ftell(*fp);
    return LV_FS_RES_OK;
}

void homeScreenFunction (){
  //Creates Home Screen
  homeScreen = lv_obj_create(NULL, NULL);

  //Image
  homeImage = lv_img_create(homeScreen, NULL);


  //Navigation Buttons
    //Continue Button
    continueButton = lv_btn_create(homeScreen, NULL);
    lv_obj_set_pos(continueButton, 50, 50);
    lv_obj_set_size(continueButton, 100, 50);
    lv_btn_set_action(continueButton, LV_BTN_ACTION_CLICK, screenNavigation);

    continueLabel = lv_label_create(continueButton, NULL);
    lv_label_set_text(continueLabel, "CONTINUE");
}

void positionScreenFunction (){
  //Creates Position Screen
  positionScreen = lv_obj_create(NULL, NULL);

  //Image
  fieldImage = lv_img_create(positionScreen, NULL);

  //Position Matrix
  positionMatrix = lv_btnm_create(positionScreen, NULL);
  lv_btnm_set_map(positionMatrix, positionMatrixMap);
  lv_btnm_set_toggle(positionMatrix, true, 0);
  lv_btnm_set_action(positionMatrix, startPosition);

  //Navigation Buttons
    //Continue Button
    continueButton = lv_btn_create(positionScreen, NULL);
    lv_obj_set_pos(continueButton, 50, 50);
    lv_obj_set_size(continueButton, 100, 50);
    lv_btn_set_action(continueButton, LV_BTN_ACTION_CLICK, screenNavigation);

    continueLabel = lv_label_create(continueButton, NULL);
    lv_label_set_text(continueLabel, "CONTINUE");

    //Back Button
    backButton = lv_btn_create(positionScreen, NULL);
    lv_obj_set_pos(backButton, 200, 50);
    lv_obj_set_size(backButton, 100, 50);
    lv_btn_set_action(backButton, LV_BTN_ACTION_CLICK, screenNavigation);

    backLabel = lv_label_create(backButton, NULL);
    lv_label_set_text(backLabel, "BACK");
}

void mogoScreenFunction (){
  //Creates Mobile Goal Screen
  mogoScreen = lv_obj_create(NULL, NULL);

  //Image
  fieldImage = lv_img_create(mogoScreen, NULL);

  //Platform Button
  platformButton = lv_btn_create(mogoScreen, NULL);
  lv_btn_set_toggle(platformButton, true);
  lv_btn_set_action(platformButton, LV_BTN_ACTION_CLICK, getPlatform);
  lv_obj_set_hidden(platformButton, true);

  platformLabel = lv_label_create(platformButton, NULL);
  lv_label_set_text(platformLabel, "Platform");

  //Collection Matrix
  mobileGoalMatrix = lv_btnm_create(mogoScreen, NULL);
  lv_btnm_set_map(mobileGoalMatrix, mobileGoalMatrixMap);
  lv_btnm_set_toggle(mobileGoalMatrix, true, 0);
  lv_btnm_set_action(mobileGoalMatrix, mobileGoals);

  //Navigation Buttons
    //Continue Button
    continueButton = lv_btn_create(mogoScreen, NULL);
    lv_obj_set_pos(continueButton, 50, 50);
    lv_obj_set_size(continueButton, 100, 50);
    lv_btn_set_action(continueButton, LV_BTN_ACTION_CLICK, screenNavigation);

    continueLabel = lv_label_create(continueButton, NULL);
    lv_label_set_text(continueLabel, "CONTINUE");

    //Back Button
    backButton = lv_btn_create(mogoScreen, NULL);
    lv_obj_set_pos(backButton, 200, 50);
    lv_obj_set_size(backButton, 100, 50);
    lv_btn_set_action(backButton, LV_BTN_ACTION_CLICK, screenNavigation);

    backLabel = lv_label_create(backButton, NULL);
    lv_label_set_text(backLabel, "BACK");
}

void statisticsScreenFunction (){
  
}

void autonSelect()
{
  
  lv_fs_drv_t pcfs_drv;                         /*A driver descriptor*/
    memset(&pcfs_drv, 0, sizeof(lv_fs_drv_t));    /*Initialization*/

    pcfs_drv.file_size = sizeof(pc_file_t);       /*Set up fields...*/
    pcfs_drv.letter = 'S';
    pcfs_drv.open = pcfs_open;
    pcfs_drv.close = pcfs_close;
    pcfs_drv.read = pcfs_read;
    pcfs_drv.seek = pcfs_seek;
    pcfs_drv.tell = pcfs_tell;
    lv_fs_add_drv(&pcfs_drv);
  
  homeScreenFunction();
}

static lv_res_t screenNavigation (lv_obj_t * button){
    if (button == continueButton){
     screenCounter ++;
    } else {
      screenCounter --;
    }
    if (screenCounter == 0){
      lv_obj_del(lv_scr_act());
      homeScreenFunction();
    } else if (screenCounter == 1){
      lv_obj_del(lv_scr_act());
      positionScreenFunction();
    } else if (screenCounter == 2){
      lv_obj_del(lv_scr_act());
      mogoScreenFunction();
    } else {
      lv_obj_del(lv_scr_act());
      statisticsScreenFunction();
    }
  return LV_RES_OK;
}

static lv_res_t startPosition(lv_obj_t * matrix, const char * txt){
  position = txt;
  return LV_RES_OK;
}

static lv_res_t mobileGoals(lv_obj_t * matrix, const char * txt){
  mobileGoal = txt;
  if (txt != "None"){
    lv_obj_set_hidden(platformButton, false);
  }
  return LV_RES_OK;
}

static lv_res_t getPlatform(lv_obj_t * button){
  platform = lv_btn_get_toggle(button);
  return LV_RES_OK;
}
