#include "slider.h"
#include <allegro5/allegro_primitives.h>
#include "../utils/collision.h"

bool draw_slider(struct Slider *slider, const GameInfo *GAME_INFO) {
  bool just_released = false;
  if (GAME_INFO) {
    bool is_hovering = is_mouse_over_box(&GAME_INFO->mouse_state, slider->x, slider->y, slider->width, slider->height);
    
    if (is_hovering && GAME_INFO->mouse_state.clicked) {
      slider->is_dragging = true;
    }
    
    if (slider->is_dragging && !GAME_INFO->mouse_state.is_down) {
      slider->is_dragging = false;
      just_released = true;
    }
    
    if (slider->is_dragging) {
      float relative_x = GAME_INFO->mouse_state.x - slider->x;
      slider->value = relative_x / (float)slider->width;
      if (slider->value < 0.0f) slider->value = 0.0f;
      if (slider->value > 1.0f) slider->value = 1.0f;
    }
  }

  al_draw_filled_rectangle(slider->x, slider->y, slider->x + slider->width, slider->y + slider->height, slider->background_color);
  
  int fill_width = (int)(slider->width * slider->value);
  al_draw_filled_rectangle(slider->x, slider->y, slider->x + fill_width, slider->y + slider->height, slider->fill_color);

  al_draw_rectangle(slider->x, slider->y, slider->x + slider->width, slider->y + slider->height, al_map_rgb(255, 255, 255), 2);

  if (slider->font && slider->text) {
    int text_x = slider->x + slider->width / 2;
    int text_height = al_get_font_line_height(slider->font);
    int text_y = slider->y + slider->height / 2 - text_height / 2;
    al_draw_text(slider->font, slider->font_color, text_x, text_y, ALLEGRO_ALIGN_CENTRE, slider->text);
  }

  return just_released;
}
