#include QMK_KEYBOARD_H
#include "../../../../quantum/keymap_extras/keymap_spanish.h"

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_DLINE,
    KC_WBSPC, // word backspace
    KC_WDEL, // word delete
    KC_C_LT, // custom less than: < due to bug mac/linux not using the same key
    KC_C_WINDOW, // custom window: change window
    KC_C_TAB, // custom change tab window,
    KC_C_TAB_PREV // custom change tab window prev,
};

// PRV_WPC: previous workspace, combo for ctrl+super+j
// NXT_WPC: next workspace, combo for ctrl+super+k

enum tap_dances {
    SFT_CAP,
    DOUBLE_KC_EQL,
    DOUBLE_ES_QUOT,
    DOUBLE_ES_NTIL,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SFT_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS), // shift on tap, caps lock on double tap
    [DOUBLE_KC_EQL] = ACTION_TAP_DANCE_DOUBLE(S(ES_1), KC_EQL), // open exclamation mark on tap, close exclamation mark on double tap
    [DOUBLE_ES_QUOT] = ACTION_TAP_DANCE_DOUBLE(S(ES_QUOT), KC_PLUS), // open question mark on tap, close question mark on double tap
    [DOUBLE_ES_NTIL] = ACTION_TAP_DANCE_DOUBLE(ES_NTIL, ALGR(ES_NTIL)) // open question mark on tap, close question mark on double tap
};

#define TD_SFT_CAP TD(SFT_CAP)
#define TD_DOUBLE_KC_EQL TD(DOUBLE_KC_EQL)
#define TD_DOUBLE_ES_QUOT TD(DOUBLE_ES_QUOT)
#define TD_ES_NTIL TD(DOUBLE_ES_NTIL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L |Ñ 2x(~)|  ´   |
 * |------+------+------+------+------+------|  Mute |    |  Play |------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      | LGUI | LAlt |LOWER | / Space /       \Enter \  |RAISE | FDel |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 * 2x(Shift) = Bloq mayus
 */
[_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC, \
  TD_SFT_CAP,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, TD_ES_NTIL,  KC_QUOT, \
  KC_LCTRL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     KC_MPLY,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 XXXXXXX,KC_LGUI,KC_LALT, KC_LOWER, KC_SPC,      KC_ENT,  KC_RAISE, KC_DELETE,    XXXXXXX, XXXXXXX\
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |     |! 2x(¡)|  "   |   #  |   $  |   %  |                    |  &   |  /   |  (   |  )   |   = |? 2x(¿)|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |     |PRV_WPC|NXT_WPC|     |                    |      |   <  |   [  |   ]  |   +  |WRDDEL|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |KC_C_WINDOW| |-------.    ,-------|      |      |   {  |   }  |   *  |   Ç  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | |KC_C_TAB_prev|KC_C_TAB|  |-------|    |-------|   `  |      |   ;  |   :  |   _  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |  WDEL |      |      |
 *            |      |      |      |      |/       /         \      \ |      |       |      |      |
 *            `----------------------------------'           '------''----------------------------'
 *  SHIFT(`) = ^
 */
[_LOWER] = LAYOUT( \
  _______,  TD_DOUBLE_KC_EQL, S(ES_2) , ALGR(ES_3), S(ES_4) ,S(ES_5),                    S(ES_6),   S(ES_7),   S(ES_8),   S(ES_9),  S(ES_0),  TD_DOUBLE_ES_QUOT,\
  _______,  _______, _______,  LCTL(LGUI(KC_J)), LCTL(LGUI(KC_K)), _______,                       _______, KC_C_LT,  ALGR(ES_GRV),  ALGR(ES_PLUS),  KC_RBRC,  KC_WBSPC, \
  _______,  _______, _______,_______,KC_C_WINDOW, _______,                       _______, _______, ALGR(ES_ACUT), ALGR(ES_CCED), KC_RCBR, KC_PIPE, \
  _______,  _______, _______,KC_C_TAB_PREV,KC_C_TAB, _______, _______,       _______, ES_GRV, _______, S(KC_COMM), S(KC_DOT), S(ES_MINS), _______, \
                       _______, _______, _______, _______, _______,       _______, _______, KC_WDEL, _______, _______\
),
/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |  |   |  @   |  #   |   $  |   %  |                    |   &  |   /  |  (   |   )  |   =  |  ?   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      | PWrd |  Up  | NWrd | DLine| FDel |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT( \
  _______, ALGR(ES_1) , ALGR(ES_2) , ALGR(ES_3) , S(ES_4) , S(ES_5),          S(ES_6),  S(ES_7)  , S(ES_8),  S(ES_9) ,  S(ES_0) ,S(ES_QUOT), \
  _______, _______,  _______, _______,  _______, _______,                   KC_PGUP, KC_PRVWD,   KC_UP, KC_NXTWD,KC_DLINE, KC_DELETE, \
  _______, _______,  _______, _______,  _______, _______,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC, \
  _______,_______, _______, _______, _______, _______,  _______,       _______,  _______, KC_HOME, _______, KC_END,  _______, _______, \
                    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |QWERTY|      |      |      |                    |      |      |      |      |      |altFDl|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX , ALGR(ES_MORD),  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET   , XXXXXXX,KC_QWERTY, XXXXXXX,XXXXXXX,XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LALT(KC_DELETE), \
  XXXXXXX , XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX,  XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
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

    oled_write_P(PSTR("\n\n\n\n"), false);
    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("BASE\n"), false);
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
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
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
            break;
        case KC_C_TAB:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(MOD_LCTL);
                    register_code(KC_TAB);
                } else {
                    register_mods(MOD_LCTL);
                    register_code(KC_TAB);
                }
            } else {
                    unregister_code(KC_TAB);
            }
            break;
        case KC_C_TAB_PREV:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(MOD_LCTL);
                    add_mods(MOD_LSFT);
                    register_code(KC_TAB);
                } else {
                    register_mods(MOD_LCTL);
                    add_mods(MOD_LSFT);
                    register_code(KC_TAB);
                }
            } else {
                    del_mods(MOD_LSFT);
                    unregister_code(KC_TAB);
            }
            break;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(MOD_LCTL);
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(MOD_LCTL);
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(MOD_LCTL);
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(MOD_LCTL);
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_WBSPC:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(MOD_LCTL);
                    register_code(KC_BSPC);
                } else {
                    register_mods(MOD_LALT);
                    register_code(KC_BSPC);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(MOD_LCTL);
                    unregister_code(KC_BSPC);
                } else {
                    unregister_mods(MOD_LALT);
                    unregister_code(KC_BSPC);
                }
            }
            break;
        case KC_WDEL:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(MOD_LCTL);
                    register_code(KC_DELETE);
                } else {
                    register_mods(MOD_LALT);
                    register_code(KC_DELETE);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(MOD_LCTL);
                    unregister_code(KC_DELETE);
                } else {
                    unregister_mods(MOD_LALT);
                    unregister_code(KC_DELETE);
                }
            }
            break;
        case KC_C_LT:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_code(KC_NUBS);
                } else {
                    register_code(KC_GRV);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_code(KC_NUBS);
                } else {
                    unregister_code(KC_GRV);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
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
