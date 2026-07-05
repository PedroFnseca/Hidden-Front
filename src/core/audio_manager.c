#include "audio_manager.h"
#include <stdio.h>

static const char* get_sound_path(sound_effect_t effect) {
  static const char* sound_path_map[] = {
    "assets/sounds/mouse-click.mp3"
  };

  if (effect < 0 || effect >= SOUND_MAX) {
    return NULL;
  }
  
  return sound_path_map[effect];
}

void init_audio_manager(audio_manager_t *am) {
  am->sound_count = 0;
  for (int i = 0; i < MAX_LOADED_SOUNDS; i++) {
    am->loaded_sounds[i].sample = NULL;
  }
}

static ALLEGRO_SAMPLE* get_sample(audio_manager_t *am, sound_effect_t effect) {
  for (int i = 0; i < am->sound_count; i++) {
    if (am->loaded_sounds[i].effect == effect) {
      return am->loaded_sounds[i].sample;
    }
  }

  if (am->sound_count >= MAX_LOADED_SOUNDS) {
    fprintf(stderr, "Audio Manager Error: Max loaded sounds reached!\n");
    return NULL;
  }

  const char* path = get_sound_path(effect);
  if (!path) return NULL;

  ALLEGRO_SAMPLE *new_sample = al_load_sample(path);

  if (!new_sample) {
    fprintf(stderr, "Audio Manager Error: Failed to load sound %s!\n", path);
    return NULL;
  }

  am->loaded_sounds[am->sound_count].effect = effect;
  am->loaded_sounds[am->sound_count].sample = new_sample;
  am->sound_count++;

  return new_sample;
}

void play_sound(audio_manager_t *am, sound_effect_t effect) {
  ALLEGRO_SAMPLE *sample = get_sample(am, effect);
  if (sample) {
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
  }
}

void cleanup_audio_manager(audio_manager_t *am) {
  for (int i = 0; i < am->sound_count; i++) {
    if (am->loaded_sounds[i].sample) {
      al_destroy_sample(am->loaded_sounds[i].sample);
      am->loaded_sounds[i].sample = NULL;
    }
  }
  am->sound_count = 0;
}
