#ifndef SLIDER_H
#define SLIDER_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "../core/input.h"

struct Slider {
  int x;
  int y;
  int width;
  int height;
  float value; // 0.0f to 1.0f
  ALLEGRO_COLOR background_color;
  ALLEGRO_COLOR fill_color;
  ALLEGRO_COLOR font_color;
  ALLEGRO_FONT *font;
  const char *text;
  bool is_dragging;
};

bool draw_slider(struct Slider *slider, const GameInfo *GAME_INFO);

#endif
