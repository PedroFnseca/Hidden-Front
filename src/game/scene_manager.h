#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "state.h"
#include <stdbool.h>

#define MAX_SCENES_IN_STACK 32

typedef struct {
  AppState stack[MAX_SCENES_IN_STACK];
  int top;
} SceneManager;

void init_scene_manager(SceneManager *sm);
bool push_scene(SceneManager *sm, AppState state);
AppState pop_scene(SceneManager *sm);
AppState get_current_scene(const SceneManager *sm);
bool is_scene_stack_empty(const SceneManager *sm);

#endif
