#include "fallback.h"
#include "../ui/button.h"
#include "../ui/version_overlay.h"
#include "../core/color_manager.h"
#include "../core/audio_manager.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

void run_fallback_scene(GameContext *ctx) {
  ALLEGRO_FONT *font = get_font(&ctx->engine.font_manager, FONT_MEDIUM, FALLBACK_FONT_SIZE);
  if (!font) {
    fprintf(stderr, "Failed to get font from manager!\n");
    pop_scene(&ctx->scene_manager);
    return;
  }

  struct Button back_btn;
  back_btn.width = FALLBACK_BTN_WIDTH;
  back_btn.height = FALLBACK_BTN_HEIGHT;
  back_btn.x = SCREEN_WIDTH / 2 - back_btn.width / 2;
  back_btn.y = SCREEN_HEIGHT / 2 + FALLBACK_BTN_OFFSET_Y;
  back_btn.type = OUTLINED;
  back_btn.background_color = get_color(COLOR_DANGER);
  back_btn.font_color = get_color(COLOR_TEXT_PRIMARY);
  back_btn.font = font;
  back_btn.text = (char*)get_localized_string(&ctx->engine.localization_manager, STRING_BACK);

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
      al_clear_to_color(get_color(COLOR_BACKGROUND));

      al_draw_text(font, get_color(COLOR_TEXT_PRIMARY), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, get_localized_string(&ctx->engine.localization_manager, STRING_FALLBACK_MESSAGE));

      bool hover = draw_button(&back_btn, &ctx->info);
      if (hover && ctx->info.mouse_state.clicked) {
        ctx->info.mouse_state.clicked = false;
        play_sound(&ctx->engine.audio_manager, SOUND_MOUSE_CLICK);
        pop_scene(&ctx->scene_manager);
        running = false;
      }

      draw_version_overlay(&ctx->engine.font_manager);
      al_flip_display();
    }
  }
}
