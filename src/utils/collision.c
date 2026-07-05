#include "collision.h"

bool is_mouse_over_box(const MouseState *mouse_state, int x, int y, int width, int height) {
  if (!mouse_state) {
    return false;
  }
  return (mouse_state->x >= x && mouse_state->x <= x + width &&
          mouse_state->y >= y && mouse_state->y <= y + height);
}
