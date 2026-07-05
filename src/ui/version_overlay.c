#include "version_overlay.h"
#include "../version.h"
#include "../core/color_manager.h"
#include "../core/engine.h"

#define VERSION_FONT_SIZE 14
#define VERSION_PADDING_X 8
#define VERSION_PADDING_Y 22

void draw_version_overlay(font_manager_t *fm) {
  ALLEGRO_FONT *font = get_font(fm, FONT_REGULAR, VERSION_FONT_SIZE);
  if (!font) return;

  al_draw_text(
    font,
    get_color(COLOR_TEXT_DISABLED),
    VERSION_PADDING_X,
    SCREEN_HEIGHT - VERSION_PADDING_Y,
    0,
    "v" GAME_VERSION
  );
}
