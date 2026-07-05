#include "button.h"
#include <allegro5/allegro_primitives.h>
#include "../utils/collision.h"

bool draw_button(struct Button *button, const GameInfo *GAME_INFO) {
  int text_width = al_get_text_width(button->font, button->text);
  int text_height = al_get_font_line_height(button->font);

  int text_x = button->x + button->width / 2;
  int text_y = button->y + button->height / 2 - text_height / 2;

  bool is_hovering = false;
  if (GAME_INFO) {
    is_hovering = is_mouse_over_box(&GAME_INFO->mouse_state, button->x, button->y, button->width, button->height);
  }

  ALLEGRO_COLOR bg_color = button->background_color;
  
  if (is_hovering) {
    float r, g, b;
    al_unmap_rgb_f(bg_color, &r, &g, &b);
    
    r = r * 1.2f; if (r > 1.0f) r = 1.0f;
    g = g * 1.2f; if (g > 1.0f) g = 1.0f;
    b = b * 1.2f; if (b > 1.0f) b = 1.0f;
    
    bg_color = al_map_rgb_f(r, g, b);
  }

  if (button->type == FILLED) {
    al_draw_filled_rectangle(button->x, button->y, button->x + button->width, button->y + button->height, bg_color);
    al_draw_text(button->font, button->font_color, text_x, text_y, ALLEGRO_ALIGN_CENTRE, button->text);
  } else {
    al_draw_rectangle(button->x, button->y, button->x + button->width, button->y + button->height, bg_color, 2);
    al_draw_text(button->font, button->font_color, text_x, text_y, ALLEGRO_ALIGN_CENTRE, button->text);
  }

  return is_hovering;
}
