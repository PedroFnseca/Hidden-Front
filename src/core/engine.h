#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "font_manager.h"
#include "audio_manager.h"
#include "config_manager.h"
#include "localization_manager.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct {
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *event_queue;
  font_manager_t font_manager;
  audio_manager_t audio_manager;
  ConfigManager config_manager;
  LocalizationManager localization_manager;
} EngineContext;

bool init_engine(EngineContext *ctx, int width, int height, const char *title);
void cleanup_engine(EngineContext *ctx);

#endif
