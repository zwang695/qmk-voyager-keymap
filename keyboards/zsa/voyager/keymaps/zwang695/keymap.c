#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum layers {
  L_BASE,
  L_SYM,
  L_NAV,
  L_NUM,
  L_MAGIC,
};

enum custom_keycodes {
  ARROW = ZSA_SAFE_RANGE,
  SRCHSEL,
  RGB_SLD,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
};



#define CTL_A LCTL_T(KC_A)
#define OPT_S LALT_T(KC_S)
#define CMD_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)
#define SFT_J RSFT_T(KC_J)
#define CMD_K RGUI_T(KC_K)
#define OPT_L RALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)
#define UND_NAV LT(2, KC_F19)

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT_voyager(
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
                         '*', '*',       '*', '*'
  );

bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTL_A:
    case OPT_S:
    case CMD_D:
    case SFT_F:
    case SFT_J:
    case CMD_K:
    case OPT_L:
    case CTL_SCLN:
      return true;
  }
  return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_voyager(
    KC_PLUS,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,
    CW_TOGG,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
    KC_TAB,         CTL_A,          OPT_S,          CMD_D,          SFT_F,          KC_G,                                           KC_H,           SFT_J,          CMD_K,          OPT_L,          CTL_SCLN,       KC_QUOTE,
    MO(4),          KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_ENTER,
                                                    UND_NAV,        LT(1, KC_BSPC),                                 LT(3, KC_ESCAPE),KC_SPACE
  ),
  [L_SYM] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_GRAVE,       KC_LABK,        KC_RABK,        KC_MINS,        KC_PIPE,                                        KC_CIRC,        KC_LCBR,        KC_RCBR,        KC_DLR,         ARROW,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_EXLM,        KC_ASTR,        KC_SLSH,        KC_EQUAL,       KC_AMPR,                                        KC_HASH,        KC_LPRN,        KC_RPRN,        KC_SCLN,        KC_DQUO,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TILD,        KC_PLUS,        KC_LBRC,        KC_RBRC,        KC_PERC,                                        KC_AT,          KC_COLN,        KC_COMM,        KC_DOT,         KC_QUOT,        KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [L_NAV] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LCMD(KC_R),     LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   KC_WBAK,        KC_WFWD,                                        KC_PAGE_UP,     KC_HOME,        KC_UP,          KC_END,         SRCHSEL,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LCTL,        KC_LALT,        KC_LGUI,        KC_LSFT,        KC_TRANSPARENT,                                 KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_DEL,         KC_TRANSPARENT,
    KC_TRANSPARENT, LCMD(KC_Z),     LCMD(KC_X),     LCMD(KC_C),     LCMD(KC_V),     KC_TRANSPARENT,                                 KC_TRANSPARENT, SELWBAK,        SELWORD,        SELLINE,        KC_TRANSPARENT, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 LCMD(KC_TAB),   QK_LLCK
  ),
  [L_NUM] = LAYOUT_voyager(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_GRAVE,       KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                        KC_7,           KC_8,           KC_9,           KC_MINUS,       KC_SLASH,       KC_F12,
    KC_TRANSPARENT, KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,                                        KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_ASTR,        KC_BSPC,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_LBRC,        KC_RBRC,        KC_LCBR,        KC_RCBR,                                        KC_1,           KC_2,           KC_3,           KC_DOT,         KC_EQUAL,       KC_ENTER,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_0
  ),
  [L_MAGIC] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 RM_TOGG,        QK_KB,          RM_NEXT,        RGB_SLD,        RM_VALD,        RM_VALU,
    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HSV_0_255_255,  HSV_74_255_255, HSV_169_255_255,
    KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
};











bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ARROW:
      if (record->event.pressed) {
        const uint8_t real_mods = get_mods();
        const uint8_t weak_mods = get_weak_mods();
        const uint8_t oneshot_mods =
#ifndef NO_ACTION_ONESHOT
          get_oneshot_mods()
#else
          0
#endif
          ;
        const uint8_t mods = real_mods | weak_mods | oneshot_mods;
        const bool shifted = mods & MOD_MASK_SHIFT;
        const bool alted = mods & MOD_MASK_ALT;

        clear_mods();
        clear_weak_mods();
#ifndef NO_ACTION_ONESHOT
        clear_oneshot_mods();
#endif
        if (alted) {
          send_string(shifted ? "<=>" : "<->");
        } else {
          send_string(shifted ? "=>" : "->");
        }
        set_mods(real_mods);
        set_weak_mods(weak_mods);
      }
      return false;
    case QK_MODS ... QK_MODS_MAX:
      // Mouse and consumer keys (volume, media) with modifiers work inconsistently across operating systems,
      // this makes sure that modifiers are always applied to the key that was pressed.
      if (IS_CONSUMER_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
        if (record->event.pressed) {
          add_mods(QK_MODS_GET_MODS(keycode));
          send_keyboard_report();
          wait_ms(2);
          register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
          return false;
        } else {
          wait_ms(2);
          del_mods(QK_MODS_GET_MODS(keycode));
        }
      }
      break;

    case SRCHSEL:
      if (record->event.pressed) {
        const uint8_t real_mods = get_mods();
        const uint8_t weak_mods = get_weak_mods();
        const uint8_t oneshot_mods =
#ifndef NO_ACTION_ONESHOT
          get_oneshot_mods()
#else
          0
#endif
          ;

        clear_mods();
        clear_weak_mods();
#ifndef NO_ACTION_ONESHOT
        clear_oneshot_mods();
#endif
        tap_code16(LCMD(KC_C));
        wait_ms(50);
        tap_code16(LCMD(KC_T));
        wait_ms(50);
        tap_code16(LCMD(KC_V));
        tap_code(KC_ENTER);
        set_mods(real_mods);
        set_weak_mods(weak_mods);
#ifndef NO_ACTION_ONESHOT
        set_oneshot_mods(oneshot_mods);
#endif
      }
      return false;
    case UND_NAV:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_UNDS);
        } else {
          unregister_code16(KC_UNDS);
        }
      } else {
        if (record->event.pressed) {
          layer_on(L_NAV);
        } else {
          layer_off(L_NAV);
        }
      }
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
      }
      return false;
    case HSV_0_255_255:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv(0,255,255);
      }
      return false;
    case HSV_74_255_255:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv(74,255,255);
      }
      return false;
    case HSV_169_255_255:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv(169,255,255);
      }
      return false;
  }
  return true;
}
