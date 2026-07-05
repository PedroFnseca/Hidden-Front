#include "input.h"

void update_mouse_state(MouseState *mouse_state, ALLEGRO_EVENT *event) {
  if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
    mouse_state->x = event->mouse.x;
    mouse_state->y = event->mouse.y;
  } else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
    if (event->mouse.button == 1) {
      mouse_state->clicked = true;
    }
  } else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
    if (event->mouse.button == 1) {
      mouse_state->clicked = false;
    }
  }
}
