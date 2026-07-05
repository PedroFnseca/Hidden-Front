#include "scene_manager.h"
#include <stdio.h>

void init_scene_manager(SceneManager *sm) {
  sm->top = -1;
}

bool push_scene(SceneManager *sm, AppState state) {
  if (sm->top >= MAX_SCENES_IN_STACK - 1) {
    fprintf(stderr, "Error: Scene stack overflow\n");
    return false;
  }
  sm->stack[++sm->top] = state;
  return true;
}

AppState pop_scene(SceneManager *sm) {
  if (sm->top < 0) {
    return APP_STATE_QUIT;
  }
  AppState state = sm->stack[sm->top--];
  return state;
}

AppState get_current_scene(const SceneManager *sm) {
  if (sm->top < 0) {
    return APP_STATE_QUIT;
  }
  return sm->stack[sm->top];
}

bool is_scene_stack_empty(const SceneManager *sm) {
  return sm->top < 0;
}
