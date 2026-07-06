#include "localization_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

static const char* string_keys[STRING_COUNT] = {
    "WELCOME_TITLE",
    "PRESS_START",
    "HOME_PLAY",
    "HOME_MULTIPLAYER",
    "HOME_SETTINGS",
    "HOME_CREDITS",
    "HOME_QUIT",
    "SETTINGS_TITLE",
    "MUTE_AUDIO",
    "YES",
    "NO",
    "VOLUME",
    "LANGUAGE",
    "BACK",
    "CREDITS_TITLE",
    "CREDITS_AUTHOR",
    "FALLBACK_MESSAGE"
};

static void load_language_file(LocalizationManager *manager, SystemLanguage lang, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) return;

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        char *space = strchr(line, ' ');
        if (space) {
            *space = '\0';
            char *key = line;
            char *value = space + 1;

            for (int i = 0; i < STRING_COUNT; i++) {
                if (strcmp(key, string_keys[i]) == 0) {
                    manager->strings[lang][i] = strdup(value);
                    break;
                }
            }
        }
    }
    fclose(file);

    for (int i = 0; i < STRING_COUNT; i++) {
        if (!manager->strings[lang][i]) {
            manager->strings[lang][i] = strdup("MISSING_STRING");
        }
    }
}

void init_localization_manager(LocalizationManager *manager, SystemLanguage default_lang) {
    manager->current_language = default_lang;
    
    for (int i = 0; i < LANG_COUNT; i++) {
        for (int j = 0; j < STRING_COUNT; j++) {
            manager->strings[i][j] = NULL;
        }
    }
    
    load_language_file(manager, LANG_EN, "assets/text/en.txt");
    load_language_file(manager, LANG_PT, "assets/text/pt.txt");
}

void cleanup_localization_manager(LocalizationManager *manager) {
    for (int i = 0; i < LANG_COUNT; i++) {
        for (int j = 0; j < STRING_COUNT; j++) {
            if (manager->strings[i][j]) {
                free(manager->strings[i][j]);
                manager->strings[i][j] = NULL;
            }
        }
    }
}

void set_language(LocalizationManager *manager, SystemLanguage lang) {
    if (lang >= 0 && lang < LANG_COUNT) {
        manager->current_language = lang;
    }
}

const char* get_localized_string(LocalizationManager *manager, StringId id) {
    if (id < 0 || id >= STRING_COUNT) {
        return "";
    }
    
    SystemLanguage lang = manager->current_language;
    if (lang < 0 || lang >= LANG_COUNT) {
        lang = LANG_EN;
    }
    
    return manager->strings[lang][id] ? manager->strings[lang][id] : "";
}

SystemLanguage get_system_default_language(void) {
#ifdef _WIN32
    LANGID langid = GetUserDefaultUILanguage();
    int primary_lang = PRIMARYLANGID(langid);
    if (primary_lang == LANG_PORTUGUESE) {
        return LANG_PT;
    }
#endif
    return LANG_EN;
}
