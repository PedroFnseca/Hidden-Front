#include "config_manager.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path, 0777)
#endif

#define CONFIG_PATH "data/config.txt"

static void load_config(ConfigManager *manager) {
    FILE *file = fopen(CONFIG_PATH, "r");
    if (!file) {
        manager->data.language = get_system_default_language();
        manager->data.volume = 1.0f;
        manager->data.is_muted = false;
        return;
    }

    char key[64];
    float value;
    
    manager->data.language = get_system_default_language();
    manager->data.volume = 1.0f;
    manager->data.is_muted = false;

    while (fscanf(file, "%63[^=]=%f\n", key, &value) == 2) {
        if (strcmp(key, "language") == 0) {
            manager->data.language = (SystemLanguage)value;
        } else if (strcmp(key, "volume") == 0) {
            manager->data.volume = value;
        } else if (strcmp(key, "is_muted") == 0) {
            manager->data.is_muted = (bool)value;
        }
    }

    fclose(file);
}

void init_config_manager(ConfigManager *manager) {
    MKDIR("data");
    
    load_config(manager);
}

void save_config(ConfigManager *manager) {
    MKDIR("data");
    
    FILE *file = fopen(CONFIG_PATH, "w");
    if (!file) {
        fprintf(stderr, "Failed to open config file for writing!\n");
        return;
    }

    fprintf(file, "language=%.0f\n", (float)manager->data.language);
    fprintf(file, "volume=%.2f\n", manager->data.volume);
    fprintf(file, "is_muted=%.0f\n", (float)manager->data.is_muted);

    fclose(file);
}
