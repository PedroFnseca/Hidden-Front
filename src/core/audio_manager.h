#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <allegro5/allegro_audio.h>

#define MAX_LOADED_SOUNDS 16

typedef enum {
  SOUND_MOUSE_CLICK,
  SOUND_MAX
} sound_effect_t;

typedef struct {
  sound_effect_t effect;
  ALLEGRO_SAMPLE *sample;
} sound_entry_t;

typedef struct {
  sound_entry_t loaded_sounds[MAX_LOADED_SOUNDS];
  int sound_count;
} audio_manager_t;

void init_audio_manager(audio_manager_t *am);
void play_sound(audio_manager_t *am, sound_effect_t effect);
void cleanup_audio_manager(audio_manager_t *am);

#endif
