#include "settings.h"
#include "../ui/button.h"
#include "../ui/slider.h"
#include "../ui/version_overlay.h"
#include "../core/color_manager.h"
#include "../core/audio_manager.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>

void run_settings_scene(GameContext *ctx) {
  ALLEGRO_BITMAP *bg = al_load_bitmap("assets/images/background/default.png");
  if (!bg) {
    fprintf(stderr, "Failed to load default.png for settings scene!\n");
  }

  ALLEGRO_FONT *font = get_font(&ctx->engine.font_manager, FONT_BOLD, SETTINGS_FONT_SIZE);
  if (!font) {
    fprintf(stderr, "Failed to get font from manager!\n");
    pop_scene(&ctx->scene_manager);
    return;
  }

  struct Button btns[SETTINGS_NUM_BUTTONS];
  char mute_text[32];
  char vol_text[32];
  
  btns[0].x = SCREEN_WIDTH / 2 - SETTINGS_BTN_WIDTH / 2;
  btns[0].y = SETTINGS_BTN_START_Y;
  btns[0].width = SETTINGS_BTN_WIDTH;
  btns[0].height = SETTINGS_BTN_HEIGHT;
  btns[0].type = FILLED;
  btns[0].background_color = get_color(COLOR_PANEL);
  btns[0].font_color = get_color(COLOR_TEXT_PRIMARY);
  btns[0].font = font;

  struct Slider vol_slider;
  vol_slider.x = SCREEN_WIDTH / 2 - SETTINGS_BTN_WIDTH / 2;
  vol_slider.y = SETTINGS_BTN_START_Y + SETTINGS_BTN_SPACING;
  vol_slider.width = SETTINGS_BTN_WIDTH;
  vol_slider.height = SETTINGS_BTN_HEIGHT;
  vol_slider.value = ctx->engine.audio_manager.volume;
  vol_slider.background_color = al_map_rgb(100, 100, 100);
  vol_slider.fill_color = get_color(COLOR_PRIMARY_ACCENT);
  vol_slider.font_color = get_color(COLOR_TEXT_PRIMARY);
  vol_slider.font = font;
  
  vol_slider.is_dragging = false;
  
  btns[1].x = SCREEN_WIDTH / 2 - SETTINGS_BTN_WIDTH / 2;
  btns[1].y = SETTINGS_BTN_START_Y + 2 * SETTINGS_BTN_SPACING;
  btns[1].width = SETTINGS_BTN_WIDTH;
  btns[1].height = SETTINGS_BTN_HEIGHT;
  btns[1].type = FILLED;
  btns[1].background_color = get_color(COLOR_PANEL);
  btns[1].font_color = get_color(COLOR_TEXT_PRIMARY);
  btns[1].font = font;

  bool running = true;
  while (running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(ctx->engine.event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      while (!is_scene_stack_empty(&ctx->scene_manager)) pop_scene(&ctx->scene_manager);
      break;
    }

    update_mouse_state(&ctx->info.mouse_state, &event);

    if (event.type == ALLEGRO_EVENT_TIMER || event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
      if (bg) al_draw_bitmap(bg, 0, 0, 0);
      else al_clear_to_color(get_color(COLOR_BACKGROUND));

      snprintf(mute_text, sizeof(mute_text), "Mutar Audio: %s", ctx->engine.audio_manager.is_muted ? "SIM" : "NAO");
      snprintf(vol_text, sizeof(vol_text), "Volume: %.0f%%", vol_slider.value * 100);
      
      btns[0].text = mute_text;
      btns[1].text = "Voltar";
      vol_slider.text = vol_text;

      bool slider_released = draw_slider(&vol_slider, &ctx->info);
      set_volume(&ctx->engine.audio_manager, vol_slider.value);
      
      if (slider_released) {
        play_sound(&ctx->engine.audio_manager, SOUND_MOUSE_CLICK);
      }

      for (int i = 0; i < SETTINGS_NUM_BUTTONS; i++) {
        bool hover = draw_button(&btns[i], &ctx->info);
        if (hover && ctx->info.mouse_state.clicked) {
          ctx->info.mouse_state.clicked = false;
          play_sound(&ctx->engine.audio_manager, SOUND_MOUSE_CLICK);
          
          if (i == 0) {
            toggle_mute(&ctx->engine.audio_manager);
          } else if (i == 1) {
            pop_scene(&ctx->scene_manager);
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
