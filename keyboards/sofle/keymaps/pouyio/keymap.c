#include QMK_KEYBOARD_H
#include "../../../../quantum/keymap_extras/keymap_spanish.h"

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE = LT(_RAISE, KC_ESC),
    KC_PRVWD,
    KC_NXTWD,
    KC_WBSPC, // word backspace
    KC_WDEL, // word delete
    KC_C_LT, // custom less than: < due to bug mac/linux not using the same key
    KC_C_WINDOW, // change window (win: alt+tab, mac: gui+tab)
    KC_C_TAB, // change tab (ctrl+tab)
    KC_C_TAB_PREV // change tab window prev (shift+ctrl+tab),
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_TAP,
    TD_HOLD
} td_state_t;

enum tap_dances {
    SFT_CAP,
    BRKT,
    BRCE,
};

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_TAP;
        else return TD_HOLD;
    }
    return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void bracket_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_TAP: register_code16(ES_LBRC); break;
        case TD_HOLD: register_code16(ES_RBRC); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_TAP: unregister_code16(ES_LBRC); break;
        case TD_HOLD: unregister_code16(ES_RBRC); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
    tap_state.state = TD_NONE;
}

void brace_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_TAP: register_code16(ES_LCBR); break;
        case TD_HOLD: register_code16(ES_RCBR); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
}

void brace_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_TAP: unregister_code16(ES_LCBR); break;
        case TD_HOLD: unregister_code16(ES_RCBR); break;
        case TD_NONE: break;
        case TD_UNKNOWN: break;
    }
    tap_state.state = TD_NONE;
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SFT_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS), // shift on tap, caps lock on double tap
    [BRKT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bracket_finished, bracket_reset),
    [BRCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, brace_finished, brace_reset)
};

#define TD_SFT_CAP TD(SFT_CAP)

#define PRV_WPC LCTL(LGUI(KC_LEFT)) // previous workspace, combo for ctrl+super+left
#define NXT_WPC LCTL(LGUI(KC_RGHT)) // next workspace, combo for ctrl+super+right

#define PLUS LT(_QWERTY, KC_RBRC) // tap/hold for plus/apostrophe

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L |   Ñ   |  ´   |
 * |------+------+------+------+------+------|  Mute |    |  Play |------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |  -  | RSft '|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      | LGUI | LAlt |LOWER | / Space /       \Enter \  |RAISE | FDel |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT( \
  XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC, \
  TD_SFT_CAP,  KC_A,  KC_S,  KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,  ES_NTIL, KC_QUOT, \
  KC_LCTRL,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     KC_MPLY,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  RSFT_T(KC_MINS), \
                 XXXXXXX,KC_LGUI,KC_LALT, KC_LOWER, KC_SPC,      KC_ENT,  KC_RAISE, KC_DELETE,    XXXXXXX, XXXXXXX\
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  !   |    |PRV_WPC|NXT_WPC|      |                    |    & |   /  |  (   |   )  |   =  |WRDDEL|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |KC_C_WINDOW| |-------.    ,-------|      |   <  |  {}  |  []  |  +*  |   Ç  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | |KC_C_TAB_prev|KC_C_TAB|  |-------|    |-------|   `  |      |   ;  |   :  |   _  |   ?  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |  WDEL |      |      |
 *            |      |      |      |      |/       /         \      \ |      |       |      |      |
 *            `----------------------------------'           '------''----------------------------'
 *  SHIFT(`) = ^
 */
[_LOWER] = LAYOUT( \
  _______,  _______, _______, _______, _______ ,_______,                    _______,   _______,   _______,   _______, _______,  _______,\
  _______,  S(ES_1), S(ES_2),  PRV_WPC,    NXT_WPC, _______,                   S(ES_6),  S(ES_7)  , S(ES_8),  S(ES_9) ,  S(ES_0), KC_WBSPC,\
  _______,  _______, _______,_______,KC_C_WINDOW, _______,                       _______, KC_C_LT, TD(BRCE), TD(BRKT), PLUS, KC_PIPE, \
  _______,  _______, _______,KC_C_TAB_PREV,KC_C_TAB, _______, _______,       _______, ES_GRV, _______, S(KC_COMM), S(KC_DOT), S(ES_MINS), S(ES_QUOT), \
                       _______, _______, _______, _______, _______,       _______, _______, KC_WDEL, _______, _______\
),
/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  |   |  @   |  #   |   $  |   %  |                    |      | PWrd |  Up  | NWrd |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down | Rigth|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | LStr |      | LEnd |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT( \
  _______,_______,_______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, \
  _______, ALGR(ES_1), ALGR(ES_2),ALGR(ES_3),S(ES_4),S(ES_5),               _______, KC_PRVWD,  KC_UP, KC_NXTWD, _______, _______, \
  _______, _______, _______,  _______, _______, _______,                    _______, KC_LEFT, KC_DOWN,  KC_RGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______,  _______,    _______, _______, KC_HOME, _______, KC_END,  _______, _______, \
                    _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|   ¡  |QWERTY|   €  |      |      |                    |      |   7  |  8   |  9   |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   \  |MACWIN|      |      |      |-------.    ,-------|      |   4  |  5   |  6   |  ~   |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   1  |  2   |  3   |      |   ¿  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET   , KC_EQL,KC_QWERTY, ALGR(ES_E),XXXXXXX,XXXXXXX,                    XXXXXXX, KC_7,     KC_8,     KC_9,    KC_0, XXXXXXX, \
  XXXXXXX , ALGR(ES_MORD), CG_TOGG, XXXXXXX, XXXXXXX,  XXXXXXX,              XXXXXXX, KC_4,     KC_5,     KC_6, ALGR(ES_NTIL), XXXXXXX, \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,XXXXXXX,KC_1,     KC_2,     KC_3, XXXXXXX, KC_PLUS, \
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ \
  )
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    // static const char PROGMEM raw_logo[] = {
    //     0,  0,  0,128,128,  0,  0,  0,  0,128,128,128,  0,  0,  0,  0,128,128,128,128,128,128,128,  0,  0,  0,128,128,128,128,128,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0, 12,144,176,224,114, 49,155,222,206,236,238,233,233,236,207,218,153, 62, 98,228,196,112, 16, 16,  0,  0,  0,  0,  0,  0,  0, 96,192,192,128,128,  2,133,133,135,133,137,137,146,234,198,196, 72, 80, 96, 64, 64, 64, 64,192,224, 80, 40, 16, 16, 96,192, 64, 64, 64, 64,128,128,128,128,128,224,248,252,248,240,  0,  0,  0,  0,  0,  0,
    //     0,127,195,192,192,112, 15,  1,  1,193,255,  0,  0,  0,192,192,192,192,192,192,255,127,  0,  0,192,224,176,152,140,134,131,129,192,  0,  0,  0,  0,  0,  0,  0,  0, 64, 33, 51, 59,123,255,  0,124,255,255,255,255,255,255,255,255,255,255,255,255,255,124,  1,255,222,140,  4, 12,  8,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,127,128,128,190,190,128,128,128,193,255,128,  4, 50, 94, 28, 61, 38, 16,193,255, 62,  0,  0,  8, 54,193,  8,  8, 20,119,148,148,148,247,148,247,156,156,255,255, 30,  0,  0,  0,  0,  0,  0,  0, 
    //     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  2,  6, 77, 79,140,249,115, 55, 39, 47, 47,175,239,111,119, 23, 51,121,204, 31, 49, 32, 33,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64,224,160,160,208,144, 72, 72, 37, 43, 17,  9,  5,  3,  1,  1,  1,  1,  1,  1,  1,  3,  2,  4,  3,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  3, 15, 31, 15,  3,  0,  0,  0,  0,
    // };
    // oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n\n"), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("  WIN"), false);
    } else {
        oled_write_ln_P(PSTR("  MAC"), false);
    }

    oled_write_P(PSTR("\n\n\n"), false);
    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("     "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJUS"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    if(led_usb_state.caps_lock) {
        oled_write_ln_P(PSTR("CAPS"), true);
    } else {
        oled_write_ln_P(PSTR("     "), false);
    } 
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_180;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                unregister_mods(MOD_LGUI);
                unregister_mods(MOD_LCTL);
                unregister_mods(MOD_LALT);
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            // return false;
            break;
        case _ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_ADJUST);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_C_WINDOW:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(MOD_LALT);
                    register_code(KC_TAB);
                } else {
                    register_mods(MOD_LGUI);
                    register_code(KC_TAB);
                }
            } else {
                    unregister_code(KC_TAB);
            }
            return false;
        case KC_C_TAB:
            if (record->event.pressed) {
                    register_mods(MOD_LCTL);
                    register_code(KC_TAB);
            } else {
                    unregister_code(KC_TAB);
            }
            return false;
        case KC_C_TAB_PREV:
            if (record->event.pressed) {
                    register_mods(MOD_LCTL);
                    add_mods(MOD_LSFT);
                    register_code(KC_TAB);
            } else {
                    del_mods(MOD_LSFT);
                    unregister_code(KC_TAB);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                register_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_LEFT) : LALT(KC_LEFT));
            } else {
                unregister_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_LEFT) : LALT(KC_LEFT));
            }
            return false;
        case KC_NXTWD:
             if (record->event.pressed) {
                register_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_RIGHT) : LALT(KC_RIGHT));
            } else {
                unregister_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_RIGHT) : LALT(KC_RIGHT));
            }
            return false;
        case KC_WBSPC:
            if (record->event.pressed) {
                register_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_BSPC) : LALT(KC_BSPC));
            } else {
                unregister_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_BSPC) : LALT(KC_BSPC));
            }
            return false;
        case KC_WDEL:
            if (record->event.pressed) {
                register_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_DELETE) : LALT(KC_DELETE));
            } else {
                unregister_code16(keymap_config.swap_lctl_lgui ? LCTL(KC_DELETE) : LALT(KC_DELETE));
            }
            return false;
        case KC_C_LT:
             if (record->event.pressed) {
                register_code16(keymap_config.swap_lctl_lgui ? KC_NUBS : KC_GRV);
            } else {
                unregister_code16(keymap_config.swap_lctl_lgui ? KC_NUBS : KC_GRV);
            }
            return false;
        case PLUS:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_RCBR); // Intercept hold function to send KC_RCBR
                return false;
            }
            return true;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            // next track
            tap_code(KC_MNXT);
        } else {
            // previous track
            tap_code(KC_MPRV);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

#endif
