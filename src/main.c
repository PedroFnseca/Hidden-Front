#include "core/engine.h"
#include "game/context.h"
#include "scenes/welcome.h"
#include "scenes/home.h"
#include "scenes/fallback.h"
#include "scenes/settings.h"
#include "scenes/credits.h"

int main(int argc, char **argv) {
  GameContext ctx;

  if (!init_engine(&ctx.engine, SCREEN_WIDTH, SCREEN_HEIGHT, "Hidden Front")) {
    return -1;
  }

  init_scene_manager(&ctx.scene_manager);
  
  push_scene(&ctx.scene_manager, APP_STATE_WELCOME);

  void (*scene_map[])(GameContext*) = {
    run_welcome_scene,
    run_home_scene,
    run_settings_scene,
    run_credits_scene,
    run_fallback_scene
  };

  while (!is_scene_stack_empty(&ctx.scene_manager)) {
    AppState current_state = get_current_scene(&ctx.scene_manager);

    if (current_state == APP_STATE_QUIT) {
      while(!is_scene_stack_empty(&ctx.scene_manager)) {
        pop_scene(&ctx.scene_manager);
      }
    } else {
      scene_map[current_state](&ctx);
    }
  }

  cleanup_engine(&ctx.engine);

  return 0;
}
