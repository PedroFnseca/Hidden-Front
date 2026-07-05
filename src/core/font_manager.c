#include "font_manager.h"
#include <stdio.h>

static const char* get_font_path(font_weight_t weight) {
  static const char* font_path_map[] = {
    "assets/fonts/PixelifySans-Regular.ttf",
    "assets/fonts/PixelifySans-Medium.ttf",
    "assets/fonts/PixelifySans-SemiBold.ttf",
    "assets/fonts/PixelifySans-Bold.ttf"
  };

  if (weight < 0 || weight > FONT_BOLD) {
    return font_path_map[FONT_REGULAR];
  }
  
  return font_path_map[weight];
}

void init_font_manager(font_manager_t *fm) {
  fm->font_count = 0;
  for (int i = 0; i < MAX_LOADED_FONTS; i++) {
    fm->loaded_fonts[i].font = NULL;
  }
}

ALLEGRO_FONT* get_font(font_manager_t *fm, font_weight_t weight, int size) {
  for (int i = 0; i < fm->font_count; i++) {
    if (fm->loaded_fonts[i].weight == weight && fm->loaded_fonts[i].size == size) {
      return fm->loaded_fonts[i].font;
    }
  }

  if (fm->font_count >= MAX_LOADED_FONTS) {
    fprintf(stderr, "Font Manager Error: Max loaded fonts reached!\n");
    return NULL;
  }

  const char* path = get_font_path(weight);
  ALLEGRO_FONT *new_font = al_load_ttf_font(path, size, 0);

  if (!new_font) {
    fprintf(stderr, "Font Manager Error: Failed to load font %s at size %d!\n", path, size);
    return NULL;
  }

  fm->loaded_fonts[fm->font_count].weight = weight;
  fm->loaded_fonts[fm->font_count].size = size;
  fm->loaded_fonts[fm->font_count].font = new_font;
  fm->font_count++;

  return new_font;
}

void cleanup_font_manager(font_manager_t *fm) {
  for (int i = 0; i < fm->font_count; i++) {
    if (fm->loaded_fonts[i].font) {
      al_destroy_font(fm->loaded_fonts[i].font);
      fm->loaded_fonts[i].font = NULL;
    }
  }
  fm->font_count = 0;
}
