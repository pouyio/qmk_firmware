#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
#include "macros.h"

bool is_kc_window_active = false;

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _M_QWERTY,
    _LOWER,
    _M_LOWER,
    _RAISE,
    _M_RAISE,
    _ADJUST,
};

// KC_NUBS or KC_GRV custom less than: < due to bug mac/linux not using the same key
enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_M_QWERTY,
    KC_LOWER,
    KC_M_LOWER,
    KC_RAISE,
    KC_M_RAISE,
    KC_ADJUST,
    KC_C_WINDOW, // change window (win: alt+tab)
    KC_M_C_WINDOW, // change window (mac: gui+tab)
    KC_C_TAB, // change tab (ctrl+tab)
    KC_C_TAB_PREV // change tab window prev (shift+ctrl+tab),
};

enum tap_dances {
    BRKT, // []
    BRCE, // {}
};

typedef enum {
    TD_NONE,
    TD_TAP,
    TD_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_TAP;
        else return TD_HOLD;
    }
    return TD_NONE;
}

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
    }
}

void bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_TAP: unregister_code16(ES_LBRC); break;
        case TD_HOLD: unregister_code16(ES_RBRC); break;
        case TD_NONE: break;
    }
    tap_state.state = TD_NONE;
}

void brace_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_TAP: register_code16(ES_LCBR); break;
        case TD_HOLD: register_code16(ES_RCBR); break;
        case TD_NONE: break;
    }
}

void brace_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case TD_TAP: unregister_code16(ES_LCBR); break;
        case TD_HOLD: unregister_code16(ES_RCBR); break;
        case TD_NONE: break;
    }
    tap_state.state = TD_NONE;
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [BRKT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bracket_finished, bracket_reset),
    [BRCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, brace_finished, brace_reset)
};

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
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |  -  | RSft  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      | LGUI | LAlt |LOWER | / Space /       \Enter \  |RAISE | FDel |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT(
  XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_LSFT,  KC_A,  KC_S,  KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,  ES_NTIL, KC_QUOT,
  KC_LGUI,   KC_Z,   KC_X,  KC_C,   KC_V,   KC_B, KC_MUTE,     KC_MPLY,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 XXXXXXX,KC_LCTRL,KC_LALT, LT(_LOWER, KC_ESC), KC_SPC,      KC_ENT, LT(_RAISE, ES_QUOT), KC_DELETE,    XXXXXXX, XXXXXXX
),
/*
 * M_QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L |   Ñ   |  ´   |
 * |------+------+------+------+------+------|  Mute |    |  Play |------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |  -  | RSft  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      | LGUI | LAlt |MLOWER| / Space /       \Enter \  |MRAISE| FDel |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_M_QWERTY] = LAYOUT(
  XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_LSFT,  KC_A,  KC_S,  KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,  ES_NTIL, KC_QUOT,
  KC_LCTRL,   KC_Z,   KC_X,  KC_C,   KC_V,   KC_B, KC_MUTE,     KC_MPLY,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 XXXXXXX,KC_LGUI,KC_LALT, LT(_M_LOWER, KC_ESC), KC_SPC,      KC_ENT,   LT(_M_RAISE, ES_QUOT), KC_DELETE,    XXXXXXX, XXXXXXX
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  !   |   "  |PRV_WPC|NXT_WPC|    |                    |    & |   /  |  (   |   )  |   =  |WRDDEL|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |KC_C_WINDOW| |-------.    ,-------|      |   <  |  {}  |  []  |  +*  |   Ç  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | |KC_C_TAB_prev|KC_C_TAB|  |-------|    |-------|   `  |      |   ;  |   :  |   _  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |  WDEL |      |      |
 *            |      |      |      |      |/       /         \      \ |      |       |      |      |
 *            `----------------------------------'           '------''----------------------------'
 *  SHIFT(`) = ^
 */
[_LOWER] = LAYOUT(
  _______,  _______, _______, _______, _______ ,_______,                    _______,   _______,   _______,   _______, _______,  _______,
  _______,  S(ES_1), S(ES_2),  PRV_WPC,    NXT_WPC, _______,                   S(ES_6),  S(ES_7)  , S(ES_8),  S(ES_9) ,  S(ES_0), WBSPC,
  _______,  _______, _______,_______,KC_C_WINDOW, _______,                       _______, KC_NUBS, TD(BRCE), TD(BRKT), PLUS, KC_PIPE,
  _______,  _______, _______,KC_C_TAB_PREV,KC_C_TAB, _______, _______,       _______, ES_GRV, _______, S(KC_COMM), S(KC_DOT), S(ES_MINS), _______,
                       _______, _______, _______, _______, _______,       _______, KC_RAISE, WDEL, _______, _______
),
/* M_LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  !   |   "  |PRV_WPC|NXT_WPC|    |                    |    & |   /  |  (   |   )  |   =  |WRDDEL|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |    |KC_M_C_WINDOW| |-------.    ,-------|      |   <  |  {}  |  []  |  +*  |   Ç  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | |KC_C_TAB_prev|KC_C_TAB|  |-------|    |-------|   `  |      |   ;  |   :  |   _  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |  WDEL |      |      |
 *            |      |      |      |      |/       /         \      \ |      |       |      |      |
 *            `----------------------------------'           '------''----------------------------'
 *  SHIFT(`) = ^
 */
[_M_LOWER] = LAYOUT(
  _______,  _______, _______, _______, _______ ,_______,                    _______,   _______,   _______,   _______, _______,  _______,
  _______,  S(ES_1), S(ES_2),  PRV_WPC,    NXT_WPC, _______,                   S(ES_6),  S(ES_7)  , S(ES_8),  S(ES_9) ,  S(ES_0), M_WBSPC,
  _______,  _______, _______,_______,KC_M_C_WINDOW, _______,                       _______, KC_GRV, TD(BRCE), TD(BRKT), PLUS, KC_PIPE,
  _______,  _______, _______,KC_C_TAB_PREV,KC_C_TAB, _______, _______,       _______, ES_GRV, _______, S(KC_COMM), S(KC_DOT), S(ES_MINS), _______,
                       _______, _______, _______, _______, _______,       _______, KC_M_RAISE, M_WDEL, _______, _______
),
/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  |   |  @   |   #  |   $  |   %  |                    |      | PWrd |  Up  | NWrd |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |   ?  |      |-------.    ,-------|      | Left | Down | Rigth|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | LStr |      | LEnd |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  _______,_______,_______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  _______, ALGR(ES_1), ALGR(ES_2),ALGR(ES_3),S(ES_4),S(ES_5),               _______, PRVWD,  KC_UP, NXTWD, _______, _______,
  _______, _______, _______,  _______, S(ES_QUOT), _______,                    _______, KC_LEFT, KC_DOWN,  KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______,    _______, _______, KC_HOME, _______, KC_END,  _______, _______,
                    _______, _______, _______, KC_LOWER, _______,      _______, _______, _______, _______, _______
),
/* M_RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  |   |  @   |   #  |   $  |   %  |                    |      | PWrd |  Up  | NWrd |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |   ?  |      |-------.    ,-------|      | Left | Down | Rigth|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | LStr |      | LEnd |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_M_RAISE] = LAYOUT(
  _______,_______,_______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  _______, ALGR(ES_1), ALGR(ES_2),ALGR(ES_3),S(ES_4),S(ES_5),               _______, M_PRVWD,  KC_UP, M_NXTWD, _______, _______,
  _______, _______, _______,  _______, S(ES_QUOT), _______,                    _______, KC_LEFT, KC_DOWN,  KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______,    _______, _______, KC_HOME, _______, KC_END,  _______, _______,
                    _______, _______, _______, KC_M_LOWER, _______,      _______, _______, _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|   ¡  |QWERTY|   €  |      |      |                    |      |   7  |  8   |  9   |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  \  |MQWERTY|      |   ¿  |      |-------.    ,-------|      |   4  |  5   |  6   |   ~  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   1  |  2   |  3   |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
//  ALGR(ES_NTIL) no va en windows, sólo en linux
  [_ADJUST] = LAYOUT(
  XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RESET   , KC_EQL,KC_QWERTY, ALGR(ES_E),XXXXXXX,XXXXXXX,                    XXXXXXX, KC_7,     KC_8,     KC_9,    KC_0, XXXXXXX,
  XXXXXXX , ALGR(ES_MORD), KC_M_QWERTY, XXXXXXX, KC_PLUS,  XXXXXXX,          XXXXXXX, KC_4,     KC_5,     KC_6, ALGR(ES_NTIL), XXXXXXX,
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,XXXXXXX,KC_1,     KC_2,     KC_3, XXXXXXX, _______,
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
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
    oled_write_P(PSTR("\n\n\n"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("  WIN"), false);
            break;
        case _M_QWERTY:
            oled_write_ln_P(PSTR("  MAC"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _M_QWERTY:
        case _QWERTY:
            oled_write_P(PSTR("     "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            break;
        case _M_RAISE:
            oled_write_P(PSTR("MRAI"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _M_LOWER:
            oled_write_P(PSTR("MLOW"), false);
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

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

// unregister mods from K_C_WINDOW and 
layer_state_t layer_state_set_user(layer_state_t  state) {
     if (is_kc_window_active) {
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LGUI);
        is_kc_window_active = false;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Detect the activation of both Shifts
    if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) {
        tap_code(KC_CAPS);
    }
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_M_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_QWERTY);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        case KC_M_LOWER:
            if (record->event.pressed) {
                layer_on(_M_LOWER);
            } else {
                layer_off(_M_LOWER);
            }
            update_tri_layer(_M_LOWER, _M_RAISE, _ADJUST);
            return false;
        case KC_M_RAISE:
            if (record->event.pressed) {
                layer_on(_M_RAISE);
            } else {
                layer_off(_M_RAISE);
            }
            update_tri_layer(_M_LOWER, _M_RAISE, _ADJUST);
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
                if (!is_kc_window_active) {
                    is_kc_window_active = true;
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_M_C_WINDOW:
            if (record->event.pressed) {
                if (!is_kc_window_active) {
                    is_kc_window_active = true;
                    register_code(KC_LGUI);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_C_TAB:
            if (record->event.pressed) {
                if (!is_kc_window_active) {
                    is_kc_window_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_C_TAB_PREV:
            if (record->event.pressed) {
                if (!is_kc_window_active) {
                    is_kc_window_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_LSFT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_mods(MOD_LSFT);
            }
            break;
        case PLUS:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_RCBR); // Intercept hold to send *
                return false;
            }
            return true;
        // won't work, will send ´
        // case BRCE:
        //     if (!record->tap.count && record->event.pressed) {
        //         tap_code16(ES_RCBR); // Intercept hold to send }
        //         return false;
        //     }
        //     return true;
        // case BRKT:
        //     if (!record->tap.count && record->event.pressed) {
        //         tap_code16(ES_RBRC); // Intercept hold to send ]
        //         return false;
        //     }
        //     return true;
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
