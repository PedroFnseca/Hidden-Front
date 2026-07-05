#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <allegro5/allegro.h>

typedef struct {
  int x;
  int y;
  bool clicked;
  bool is_down;
} MouseState;

typedef struct {
  MouseState mouse_state;
} GameInfo;

void update_mouse_state(MouseState *mouse_state, ALLEGRO_EVENT *event);

#endif
