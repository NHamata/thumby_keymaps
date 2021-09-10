#include QMK_KEYBOARD_H
#include <stdio.h>

//TO DO
// ()  combo L-IM R-IM
// {}  combo L-MR R-MR
// []  combo L-RP R-RP
// <>  combo L-I(down)R  R-I(down)R
// ; combo  R-IR
// : combo  L-IR
// = combo L-IP 
// / R-IP
// - combo R-I(down)M
// _ combo L-I(down)M 
// ' triple tap J
// " triple tap U 
// ` triple tap Y 




// NAV layer
// ~ layer
void triple_tap_symbol(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 3) {
        // immediately finish on third press
        tap_code16(pair->kc2);
        register_code16(pair->kc2);
        state->finished = true;
    }
}

void triple_tap_symbol_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc1);
    } else if (state->count == 2) {
        // tap plus hold
        register_code16(pair->kc2);
    } else if (state->count == 3) {
        tap_code16(pair->kc2);
        register_code16(pair->kc2);
    }
}

void triple_tap_symbol_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    if (state->count == 1) {
        // 1-tap and 2-tap both result in `kc1` pressed so release it
        unregister_code16(pair->kc1);
    } else if( state->count == 2 || state->count == 3 ) {
        // 1-tap and 2-tap both result in `kc1` pressed so release it
        unregister_code16(pair->kc2);
    }
}

#define TRIPLE_TAP_SYMBOL(kc1, kc2) \
        { .fn = {triple_tap_symbol, triple_tap_symbol_finished, triple_tap_symbol_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, kc2}), }

///EDIT TAP
void triple_tap_edit(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 3) {
        // immediately finish on third press
        register_code16(pair->kc2);
        state->finished = true;
    }
}

void triple_tap_edit_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc1);
    } else if (state->count == 2) {
        // tap plus hold
        tap_code16(pair->kc1);
        register_code16(pair->kc1);
    } else if (state->count == 3) {
        register_code16(pair->kc2);
    }
}

void triple_tap_edit_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1 || state->count == 2) {
        // 1-tap and 2-tap both result in `kc1` pressed so release it
        unregister_code16(pair->kc1);
    } else if (state->count == 3) {
        unregister_code16(pair->kc2);
    }
}

#define TRIPLE_TAP_EDIT(kc1, kc2) \
        { .fn = {triple_tap_edit, triple_tap_edit_finished, triple_tap_edit_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, kc2}), }

// Tap Dance declarations
enum {
    ESC_CAPS,
    SPC_TABS,
    J_DOUBLE_QUOTE,
    U_SINGLE_QUOTE,
    Y_BACK_TICK,
    C_CC_COPY,
    V_VV_PASTE,
    X_XX_CUT,
    WBCK_WFWD
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [SPC_TABS] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_TAB),
    [WBCK_WFWD] = ACTION_TAP_DANCE_DOUBLE(KC_WBAK, KC_WFWD),
    [J_DOUBLE_QUOTE] = TRIPLE_TAP_SYMBOL (KC_J,KC_DOUBLE_QUOTE),
    [U_SINGLE_QUOTE] = TRIPLE_TAP_SYMBOL (KC_U,KC_QUOTE),
    [Y_BACK_TICK] = TRIPLE_TAP_SYMBOL (KC_Y,KC_GRAVE),
    [C_CC_COPY] = TRIPLE_TAP_EDIT(KC_C, LCTL(KC_C)),
    [V_VV_PASTE] = TRIPLE_TAP_EDIT(KC_V, LCTL(KC_V)),
    [X_XX_CUT] = TRIPLE_TAP_EDIT(KC_X, LCTL(KC_X))
};


//combos
// L/R-XXX: Left Right
// I: Index finger
// M: middle finger
// R: ring finger
// P: pinky finger
// () combo L-IM R-IM
// {} combo L-MR R-MR
// [] combo L-RP R-RP
// <> combo L-I(down)R  R-I(down)R
// ; combo R-IR
// : combo L-IR
// = combo L-IP 
// / combo R-IP
// - combo R-I(down)M
// _ combo L-I(down)M 
// + combo R-P(down)R
// ? combo R-P(down)M
// | combo L-P(down)R
// \ combo L-P(down)M

const uint16_t PROGMEM lprn_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {KC_N, KC_L, COMBO_END};
const uint16_t PROGMEM lcbr_combo[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM rcbr_combo[] = {KC_L, KC_I, COMBO_END};
const uint16_t PROGMEM lbrc_combo[] = {KC_A, KC_R, COMBO_END};
const uint16_t PROGMEM rbrc_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM labk_combo[] = {KC_D, KC_R, COMBO_END};
const uint16_t PROGMEM rabk_combo[] = {KC_H, KC_I, COMBO_END};
const uint16_t PROGMEM coln_combo[] = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM scln_combo[] = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM pmns_combo[] = {KC_H, KC_L, COMBO_END};
const uint16_t PROGMEM unds_combo[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM eql_combo[] = {KC_A, KC_T, COMBO_END};
const uint16_t PROGMEM slsh_combo[] = {KC_N, KC_O, COMBO_END};
const uint16_t PROGMEM pgup_combo[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM pgdn_combo[] = {KC_UP, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM pscr_combo[] = {KC_4, KC_INSERT, COMBO_END};
const uint16_t PROGMEM ppls_combo[] = {KC_Z, KC_R, COMBO_END};
const uint16_t PROGMEM ques_combo[] = {KC_Z, KC_S, COMBO_END};
const uint16_t PROGMEM pipe_combo[] = {KC_I, KC_ENT, COMBO_END};
const uint16_t PROGMEM bsls_combo[] = {KC_L, KC_ENT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(lprn_combo, KC_LPRN),
    COMBO(rprn_combo, KC_RPRN),
    COMBO(lcbr_combo, KC_LCBR),
    COMBO(rcbr_combo, KC_RCBR),
    COMBO(lbrc_combo, KC_LBRC),
    COMBO(rbrc_combo, KC_RBRC),
    COMBO(labk_combo, KC_LABK),
    COMBO(rabk_combo, KC_RABK),
    COMBO(coln_combo, KC_COLN),
    COMBO(scln_combo, KC_SCLN),
    COMBO(pmns_combo, KC_PMNS),
    COMBO(unds_combo, KC_UNDS),
    COMBO(eql_combo, KC_EQL),
    COMBO(slsh_combo, KC_SLSH),
    COMBO(pgup_combo, KC_PGUP),
    COMBO(pgdn_combo, KC_PGDN),
    COMBO(pscr_combo, KC_PSCR),
    COMBO(ppls_combo, KC_PPLS),
    COMBO(ques_combo, KC_QUES),
    COMBO(pipe_combo, KC_PIPE),
    COMBO(bsls_combo ,KC_BSLS)  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------------------------------------.      ,----------------------------------------------------------------------------------------------------.
       TD(ESC_CAPS),       KC_Q,           KC_W,           KC_F,               KC_P,           KC_B,                 KC_BSPC,   TD(J_DOUBLE_QUOTE), TD(U_SINGLE_QUOTE), TD(Y_BACK_TICK),   KC_TAB,     OSM(MOD_HYPR),
  //|----------------+----------------+----------------+----------------+----------------+----------------|      |----------------+----------------+----------------+----------------+----------------+----------------|
       OSM(MOD_LSFT),       KC_A,           KC_R,           KC_S,               KC_T,           KC_G,                   KC_M,            KC_N,            KC_L,            KC_I,           KC_O,    OSM(MOD_LSFT|MOD_LCTL),
  //|----------------+----------------+----------------+----------------+----------------+----------------|      |----------------+----------------+----------------+----------------+----------------+----------------|
       OSM(MOD_LGUI),       KC_Z,       TD(X_XX_CUT),    TD(C_CC_COPY),         KC_D,      TD(V_VV_PASTE),              KC_K,            KC_H,          KC_COMM,          KC_DOT,         KC_ENT,   OSM(MOD_LSFT|MOD_LALT),
  //|----------------+----------------+----------------+----------------+----------------+----------------+-|  |-+----------------+----------------+----------------+----------------+----------------+----------------|
                                                             TT(1),       OSM(MOD_LCTL),        KC_SPC,                 KC_E,         OSM(MOD_LALT),      TT(2)
                                                      //`---------------------------------------------------'  `----------------------------------------------------'

  ),
  
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSM(MOD_LSFT), KC_1, KC_2,    KC_3,    KC_4,  KC_INSERT,                    KC_HOME,   KC_6,    KC_7,    KC_8,    KC_9, TD(WBCK_WFWD),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LEFT, KC_DOWN,  KC_UP,  KC_RIGHT,  KC_5,   KC_DEL,                       KC_END,   KC_0,   KC_H,    KC_J,    KC_K,   KC_L,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          TO(0), OSM(MOD_RCTL),OSM(MOD_RALT), OSM(MOD_RGUI),OSM(MOD_RSFT), TT(2)
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX,                      XXXXXXX,   KC_H,    KC_J,    KC_K,   KC_L,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,                      XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          TT(1),   MO(3),  KC_SPC,     KC_ENT, _______, TO(0)
                                      //`--------------------------'  `--------------------------'
  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE