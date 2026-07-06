#ifndef SETTINGS_H
#define SETTINGS_H

#include "../game/context.h"

#define SETTINGS_NUM_BUTTONS 3
#define SETTINGS_BTN_START_Y 500
#define SETTINGS_BTN_WIDTH 400
#define SETTINGS_BTN_HEIGHT 60
#define SETTINGS_BTN_SPACING 80

#define SETTINGS_FONT_SIZE 32

void run_settings_scene(GameContext *ctx);

#endif
