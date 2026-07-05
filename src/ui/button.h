#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "../core/input.h"

typedef enum {
  FILLED,
  OUTLINED
} ButtonType;

struct Button {
  int x;
  int y;
  int width;
  int height;
  ButtonType type;
  ALLEGRO_COLOR background_color;
  ALLEGRO_COLOR font_color;
  ALLEGRO_FONT *font;
  const char *text;
};

bool draw_button(struct Button *button, const GameInfo *GAME_INFO);

#endif
