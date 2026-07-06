#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "localization_manager.h"
#include <stdbool.h>

typedef struct {
    SystemLanguage language;
    float volume;
    bool is_muted;
} ConfigData;

typedef struct {
    ConfigData data;
} ConfigManager;

void init_config_manager(ConfigManager *manager);
void save_config(ConfigManager *manager);

#endif
