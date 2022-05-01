#ifndef POUYIO_UTILS
#define POUYIO_UTILS

#include QMK_KEYBOARD_H
#include "../../../../quantum/keymap_extras/keymap_spanish.h"

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

// addind definitions to .c file wont compile (?)
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


#endif