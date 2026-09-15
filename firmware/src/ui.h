#pragma once
#include "data.h"
#include "ble.h"

enum screen_t {
    SCREEN_SPLASH,
    SCREEN_HOME,       // icon-grid launcher — the "start menu" between splash and any app
    SCREEN_USAGE,      // the Claude usage app
    SCREEN_PERMISSION,
    SCREEN_RAIN,       // ephemeral rain-soon alert — auto-reverts after a timeout
    SCREEN_COUNT,
};

void ui_init(void);
void ui_update(const UsageData* data);
void ui_tick_anim(void);
void ui_show_screen(screen_t screen);
void ui_toggle_splash(void);
screen_t ui_get_current_screen(void);
void ui_update_ble_status(ble_state_t state, const char* name, const char* mac);
void ui_update_battery(int percent, bool charging);

// Permission-approval screen. `id` ties the eventual tap back to the host's
// pending request; `tool` and `summary` are short, pre-truncated strings.
void ui_show_permission_request(const char* id, const char* tool, const char* summary);

// Ephemeral "rain soon" alert — a small cloud + falling-raindrop animation.
// Auto-reverts to whatever was showing before after a fixed duration, or on
// tap. Call on the daemon payload's rain_soon rising edge only (main.cpp).
void ui_show_rain_alert(void);
