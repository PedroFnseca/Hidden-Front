#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "../core/input.h"

bool is_mouse_over_box(const MouseState *mouse_state, int x, int y, int width, int height);

#endif
