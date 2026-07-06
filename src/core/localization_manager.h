#ifndef LOCALIZATION_MANAGER_H
#define LOCALIZATION_MANAGER_H

#include <stdbool.h>

typedef enum {
    LANG_EN,
    LANG_PT,
    LANG_COUNT
} SystemLanguage;

typedef enum {
    STRING_WELCOME_TITLE,
    STRING_PRESS_START,
    STRING_HOME_PLAY,
    STRING_HOME_MULTIPLAYER,
    STRING_HOME_SETTINGS,
    STRING_HOME_CREDITS,
    STRING_HOME_QUIT,
    STRING_SETTINGS_TITLE,
    STRING_MUTE_AUDIO,
    STRING_YES,
    STRING_NO,
    STRING_VOLUME,
    STRING_LANGUAGE,
    STRING_BACK,
    STRING_CREDITS_TITLE,
    STRING_CREDITS_AUTHOR,
    STRING_FALLBACK_MESSAGE,
    STRING_COUNT
} StringId;

typedef struct {
    SystemLanguage current_language;
    char *strings[LANG_COUNT][STRING_COUNT];
} LocalizationManager;

void init_localization_manager(LocalizationManager *manager, SystemLanguage default_lang);
void cleanup_localization_manager(LocalizationManager *manager);
void set_language(LocalizationManager *manager, SystemLanguage lang);
const char* get_localized_string(LocalizationManager *manager, StringId id);
SystemLanguage get_system_default_language(void);

#endif
