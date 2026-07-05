#include "welcome.h"
#include "../core/color_manager.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>

void run_welcome_scene(GameContext *ctx) {
  ALLEGRO_BITMAP *welcome_image = al_load_bitmap("assets/images/background/default.png");
  if (!welcome_image) {
    fprintf(stderr, "Failed to load default.png!\n");
    pop_scene(&ctx->scene_manager);
    return;
  }

  al_clear_to_color(get_color(COLOR_BACKGROUND));
  al_draw_bitmap(welcome_image, 0, 0, 0);
  al_flip_display();

  al_rest(WELCOME_SCREEN_TIME);

  al_destroy_bitmap(welcome_image);
  
  pop_scene(&ctx->scene_manager);
  push_scene(&ctx->scene_manager, APP_STATE_HOME);
}
