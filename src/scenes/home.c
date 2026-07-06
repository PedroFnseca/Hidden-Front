#include "home.h"
#include "../ui/button.h"
#include "../ui/version_overlay.h"
#include "../core/color_manager.h"
#include "../core/audio_manager.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>

void run_home_scene(GameContext *ctx) {
  ALLEGRO_BITMAP *bg = al_load_bitmap("assets/images/background/default.png");
  if (!bg) {
    fprintf(stderr, "Failed to load default.png for home scene!\n");
  }

  ALLEGRO_FONT *font = get_font(&ctx->engine.font_manager, FONT_BOLD, HOME_FONT_SIZE);
  if (!font) {
    fprintf(stderr, "Failed to get font from manager!\n");
    pop_scene(&ctx->scene_manager);
    return;
  }

  struct Button btns[HOME_NUM_BUTTONS];
  const char *labels[] = {"Jogar", "Multiplayer", "Configuracoes", "Creditos", "SAIR"};

  for (int i = 0; i < HOME_NUM_BUTTONS; i++) {
    btns[i].x = SCREEN_WIDTH / 2 - HOME_BTN_WIDTH / 2;
    btns[i].y = HOME_BTN_START_Y + i * HOME_BTN_SPACING;
    btns[i].width = HOME_BTN_WIDTH;
    btns[i].height = HOME_BTN_HEIGHT;
    btns[i].type = FILLED;
    btns[i].background_color = get_color(COLOR_PANEL);
    btns[i].font_color = get_color(COLOR_TEXT_PRIMARY);
    btns[i].font = font;
    btns[i].text = labels[i];
  }

  bool running = true;
  while (running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(ctx->engine.event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      while (!is_scene_stack_empty(&ctx->scene_manager)) pop_scene(&ctx->scene_manager);
      break;
    }

    update_mouse_state(&ctx->info.mouse_state, &event);

    if (event.type == ALLEGRO_EVENT_TIMER || event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
      if (bg) al_draw_bitmap(bg, 0, 0, 0);
      else al_clear_to_color(get_color(COLOR_BACKGROUND));

      for (int i = 0; i < HOME_NUM_BUTTONS; i++) {
        bool hover = draw_button(&btns[i], &ctx->info);
        if (hover && ctx->info.mouse_state.clicked) {
          ctx->info.mouse_state.clicked = false;
          play_sound(&ctx->engine.audio_manager, SOUND_MOUSE_CLICK);
          if (i == HOME_NUM_BUTTONS - 1) {
            pop_scene(&ctx->scene_manager);
            running = false;
          } else if (i == 2) {
            push_scene(&ctx->scene_manager, APP_STATE_SETTINGS);
            running = false;
          } else {
            push_scene(&ctx->scene_manager, APP_STATE_FALLBACK);
            running = false;
          }
        }
      }
      draw_version_overlay(&ctx->engine.font_manager);
      al_flip_display();
    }
  }

  if (bg) al_destroy_bitmap(bg);
}
