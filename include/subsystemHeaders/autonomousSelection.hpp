#include "main.h"

void autonSelect ();

void homeScreenFunction ();

void positionScreenFunction ();

void mogoScreenFunction ();

void statisticsScreenFunction ();

static lv_res_t screenNavigation (lv_obj_t * button);

static lv_res_t startPosition(lv_obj_t * matrix, const char * txt);

static lv_res_t mobileGoals(lv_obj_t * matrix, const char * txt);

static lv_res_t getPlatform(lv_obj_t * button);
