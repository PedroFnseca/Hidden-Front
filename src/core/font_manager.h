#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define MAX_LOADED_FONTS 32

typedef enum {
  FONT_REGULAR,
  FONT_MEDIUM,
  FONT_SEMIBOLD,
  FONT_BOLD
} font_weight_t;

typedef struct {
  font_weight_t weight;
  int size;
  ALLEGRO_FONT *font;
} font_entry_t;

typedef struct {
  font_entry_t loaded_fonts[MAX_LOADED_FONTS];
  int font_count;
} font_manager_t;

void init_font_manager(font_manager_t *fm);
ALLEGRO_FONT* get_font(font_manager_t *fm, font_weight_t weight, int size);
void cleanup_font_manager(font_manager_t *fm);

#endif
