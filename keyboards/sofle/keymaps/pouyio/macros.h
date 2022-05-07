// Common tap holds
#define PLUS LT(_QWERTY, KC_RBRC) // tap/hold for +*
// won't work, will send ´
// #define BRCE LT(_QWERTY, ES_LCBR) // tap/hold for {}
// #define BRKT LT(_QWERTY, ES_LBRC) // tap/hold for []

// Common workspace
#define PRV_WPC LCTL(LGUI(KC_LEFT)) // previous workspace, combo for ctrl+super+left
#define NXT_WPC LCTL(LGUI(KC_RGHT)) // next workspace, combo for ctrl+super+right

// Windows
#define WDEL LCTL(KC_DELETE) // delete word
#define WBSPC LCTL(KC_BSPC) // delete word backspace
#define NXTWD LCTL(KC_RIGHT) // next word
#define PRVWD LCTL(KC_LEFT) // previous word

// Macos
#define M_WDEL LALT(KC_DELETE) 
#define M_WBSPC LALT(KC_BSPC)
#define M_NXTWD LALT(KC_RIGHT)
#define M_PRVWD LALT(KC_LEFT)