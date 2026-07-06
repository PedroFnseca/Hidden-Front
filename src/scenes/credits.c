#include "credits.h"
#include "../ui/button.h"
#include "../ui/version_overlay.h"
#include "../core/color_manager.h"
#include "../core/audio_manager.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LEN 256

void run_credits_scene(GameContext *ctx) {
  ALLEGRO_BITMAP *bg = al_load_bitmap("assets/images/background/default.png");
  
  ALLEGRO_FONT *font = get_font(&ctx->engine.font_manager, FONT_REGULAR, 32);
  ALLEGRO_FONT *btn_font = get_font(&ctx->engine.font_manager, FONT_BOLD, 32);

  if (!font || !btn_font) {
    fprintf(stderr, "Failed to load fonts for credits scene.\n");
    pop_scene(&ctx->scene_manager);
    return;
  }
  
  char lines[MAX_LINES][MAX_LINE_LEN];
  int line_count = 0;
  
  FILE *f = fopen("assets/text/credits.txt", "r");
  if (f) {
    while (line_count < MAX_LINES && fgets(lines[line_count], MAX_LINE_LEN, f)) {
      lines[line_count][strcspn(lines[line_count], "\r\n")] = 0;
      line_count++;
    }
    fclose(f);
  } else {
    strcpy(lines[0], "Creditos nao encontrados.");
    line_count = 1;
  }

  struct Button back_btn;
  back_btn.width = 300;
  back_btn.height = 60;
  back_btn.x = SCREEN_WIDTH / 2 - back_btn.width / 2;
  back_btn.y = SCREEN_HEIGHT - 100;
  back_btn.type = FILLED;
  back_btn.background_color = get_color(COLOR_PANEL);
  back_btn.font_color = get_color(COLOR_TEXT_PRIMARY);
  back_btn.font = btn_font;
  back_btn.text = (char*)get_localized_string(&ctx->engine.localization_manager, STRING_BACK);

  bool running = true;
  float scroll_y = 0;
  
  while (running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(ctx->engine.event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      while (!is_scene_stack_empty(&ctx->scene_manager)) pop_scene(&ctx->scene_manager);
      break;
    }

    if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
      if (event.mouse.dz != 0) {
        scroll_y += event.mouse.dz * 40;
      }
    }

    update_mouse_state(&ctx->info.mouse_state, &event);

    if (event.type == ALLEGRO_EVENT_TIMER || event.type == ALLEGRO_EVENT_MOUSE_AXES || event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
      if (bg) al_draw_bitmap(bg, 0, 0, 0);
      else al_clear_to_color(get_color(COLOR_BACKGROUND));

      int base_start_y = 500;
      int line_height = al_get_font_line_height(font) + 10;
      int total_text_height = line_count * line_height;
      
      int max_visible_height = back_btn.y - base_start_y - 20; 
      float min_scroll = 0;
      if (total_text_height > max_visible_height) {
        min_scroll = -(total_text_height - max_visible_height);
      }
      
      if (scroll_y > 0) scroll_y = 0;
      if (scroll_y < min_scroll) scroll_y = min_scroll;

      int current_start_y = base_start_y + (int)scroll_y;
      
      int clip_start_y = base_start_y - 50; 
      int clip_end_y = back_btn.y - 20;
      al_set_clipping_rectangle(0, clip_start_y, SCREEN_WIDTH, clip_end_y - clip_start_y);

      for (int i = 0; i < line_count; i++) {
         al_draw_text(font, get_color(COLOR_TEXT_PRIMARY), SCREEN_WIDTH / 2, current_start_y + i * line_height, ALLEGRO_ALIGN_CENTRE, lines[i]);
      }
      
      al_set_clipping_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

      if (total_text_height > max_visible_height) {
        float visible_ratio = (float)max_visible_height / total_text_height;
        int scrollbar_w = 8;
        int scrollbar_x = SCREEN_WIDTH - 40;
        int scrollbar_y = clip_start_y;
        int scrollbar_h = max_visible_height;

        al_draw_filled_rectangle(scrollbar_x, scrollbar_y, scrollbar_x + scrollbar_w, scrollbar_y + scrollbar_h, get_color(COLOR_BORDER));

        int thumb_h = (int)(scrollbar_h * visible_ratio);
        if (thumb_h < 20) thumb_h = 20;

        float scroll_progress = scroll_y / min_scroll;
        int max_thumb_y = scrollbar_h - thumb_h;
        int thumb_y = scrollbar_y + (int)(scroll_progress * max_thumb_y);

        al_draw_filled_rectangle(scrollbar_x, thumb_y, scrollbar_x + scrollbar_w, thumb_y + thumb_h, get_color(COLOR_TEXT_SECONDARY));
      }

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

  if (bg) al_destroy_bitmap(bg);
}
