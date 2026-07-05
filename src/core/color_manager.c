#include "color_manager.h"

ALLEGRO_COLOR get_color(color_id_t id) {
  static const unsigned char color_map[][3] = {
    {32, 36, 44},   // COLOR_BACKGROUND
    {52, 58, 64},   // COLOR_PANEL
    {96, 82, 60},   // COLOR_BORDER
    {212, 175, 55}, // COLOR_PRIMARY_ACCENT
    {120, 170, 255},// COLOR_SECONDARY_ACCENT
    {196, 58, 58},  // COLOR_DANGER
    {72, 176, 97},  // COLOR_SUCCESS
    {245, 240, 220},// COLOR_TEXT_PRIMARY
    {180, 180, 180},// COLOR_TEXT_SECONDARY
    {120, 120, 120},// COLOR_TEXT_DISABLED
    {255, 220, 90}  // COLOR_TEXT_HIGHLIGHT
  };

  if (id < 0 || id > COLOR_TEXT_HIGHLIGHT) {
    return al_map_rgb(255, 0, 255);
  }

  return al_map_rgb(color_map[id][0], color_map[id][1], color_map[id][2]);
}
