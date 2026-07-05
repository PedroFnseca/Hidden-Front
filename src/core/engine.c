#include "engine.h"
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

bool init_engine(EngineContext *ctx, int width, int height, const char *title) {
  if (!al_init()) {
    fprintf(stderr, "Failed to initialize allegro!\n");
    return false;
  }

  if (!al_init_image_addon()) {
    fprintf(stderr, "Failed to initialize allegro_image addon!\n");
    return false;
  }

  if (!al_install_mouse()) {
    fprintf(stderr, "Failed to initialize mouse!\n");
    return false;
  }

  if (!al_init_primitives_addon()) {
    fprintf(stderr, "Failed to initialize allegro_primitives addon!\n");
    return false;
  }

  if (!al_init_font_addon()) {
    fprintf(stderr, "Failed to initialize allegro_font addon!\n");
    return false;
  }

  if (!al_init_ttf_addon()) {
    fprintf(stderr, "Failed to initialize allegro_ttf addon!\n");
    return false;
  }

  if (!al_install_audio()) {
    fprintf(stderr, "Failed to initialize audio addon!\n");
    return false;
  }

  if (!al_init_acodec_addon()) {
    fprintf(stderr, "Failed to initialize acodec addon!\n");
    return false;
  }

  if (!al_reserve_samples(16)) {
    fprintf(stderr, "Failed to reserve audio samples!\n");
    return false;
  }

  al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
  ctx->display = al_create_display(width, height);
  if (!ctx->display) {
    fprintf(stderr, "Failed to create display!\n");
    return false;
  }

  al_set_window_title(ctx->display, title);

  ctx->event_queue = al_create_event_queue();
  if (!ctx->event_queue) {
    fprintf(stderr, "Failed to create event queue!\n");
    al_destroy_display(ctx->display);
    return false;
  }

  al_register_event_source(ctx->event_queue, al_get_display_event_source(ctx->display));
  al_register_event_source(ctx->event_queue, al_get_mouse_event_source());

  init_font_manager(&ctx->font_manager);
  init_audio_manager(&ctx->audio_manager);

  return true;
}

void cleanup_engine(EngineContext *ctx) {
  cleanup_audio_manager(&ctx->audio_manager);
  cleanup_font_manager(&ctx->font_manager);

  if (ctx->event_queue) {
    al_destroy_event_queue(ctx->event_queue);
    ctx->event_queue = NULL;
  }
  if (ctx->display) {
    al_destroy_display(ctx->display);
    ctx->display = NULL;
  }
}
