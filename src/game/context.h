#ifndef CONTEXT_H
#define CONTEXT_H

#include "../core/engine.h"
#include "../core/input.h"
#include "scene_manager.h"

typedef struct {
  EngineContext engine;
  SceneManager scene_manager;
  GameInfo info;
} GameContext;

#endif
