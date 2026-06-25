#include QMK_KEYBOARD_H
#include "navigator.h"
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum layers {
  L_BASE,
  L_CURSOR,
  L_SYM,
  L_NUM,
  L_MAGIC,
  L_MOUSE,
};

enum custom_keycodes {
  ARROW = ZSA_SAFE_RANGE,
  SRCHSEL,
  GESTURE,
  RGB_SLD,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
};



#define CTL_A LCTL_T(KC_A)
#define OPT_S LALT_T(KC_S)
#define CMD_D LGUI_T(KC_D)
#define SYM_F LT(L_SYM, KC_F)
#define SYM_J LT(L_SYM, KC_J)
#define CMD_K RGUI_T(KC_K)
#define OPT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)
#define GESTURE_STROKE_SIZE 300
#define GESTURE_MOVEMENT_THRESHOLD 3
#define GESTURE_COOLDOWN_MS 500

static bool gesture_active = false;
static bool gesture_scroll_restore = false;
static bool gesture_cooling_down = false;
static uint16_t gesture_cooldown_timer = 0;
static int32_t gesture_accum_x = 0;
static int32_t gesture_accum_y = 0;

static void update_status_leds(layer_state_t state) {
  STATUS_LED_1(layer_state_cmp(state, L_MOUSE));
  STATUS_LED_2(set_scrolling);
  STATUS_LED_3(is_layer_locked(L_CURSOR) || is_layer_locked(L_NUM));
  STATUS_LED_4(is_caps_word_on());
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT_voyager(
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
                         '*', '*',       '*', '*'
  );

layer_state_t layer_state_set_user(layer_state_t state) {
  update_status_leds(state);
  return state;
}

bool layer_lock_set_user(layer_state_t locked_layers) {
  (void)locked_layers;
  update_status_leds(layer_state);
  return true;
}

void caps_word_set_user(bool active) {
  (void)active;
  update_status_leds(layer_state);
}

bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTL_A:
    case OPT_S:
    case CMD_D:
    case SYM_F:
    case SYM_J:
    case CMD_K:
    case OPT_L:
    case CTL_SCLN:
      return true;
  }
  return false;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
  (void)record;

  if (!is_flow_tap_key(prev_keycode)) {
    return 0;
  }

  switch (keycode) {
    case SYM_F:
    case SYM_J:
      return FLOW_TAP_TERM_INDEX_SHIFT;
  }

  if (is_flow_tap_key(keycode)) {
    return FLOW_TAP_TERM;
  }

  return 0;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_voyager(
    KC_PLUS,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
    KC_ESCAPE,      CTL_A,          OPT_S,          CMD_D,          SYM_F,          KC_G,                                           KC_H,           SYM_J,          CMD_K,          OPT_L,          CTL_SCLN,       KC_QUOTE,
    MO(L_MAGIC),    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       CW_TOGG,
                                                    LT(L_CURSOR, KC_BSPC),KC_LSFT,                                   KC_ENTER,       LT(L_NUM, KC_SPACE)
  ),
  [L_SYM] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_GRAVE,       KC_LABK,        KC_RABK,        KC_MINS,        KC_PIPE,                                        KC_CIRC,        KC_LCBR,        KC_RCBR,        KC_DLR,         ARROW,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_EXLM,        KC_ASTR,        KC_SLSH,        KC_EQUAL,       KC_AMPR,                                        KC_HASH,        KC_LPRN,        KC_RPRN,        KC_SCLN,        KC_DQUO,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TILD,        KC_PLUS,        KC_LBRC,        KC_RBRC,        KC_PERC,                                        KC_AT,          KC_COLN,        KC_QUOT,        KC_UNDS,        KC_QUES,        KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [L_CURSOR] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LCMD(KC_R),     LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   LCMD(KC_LBRC),  LCMD(KC_RBRC),                                  KC_PAGE_UP,     KC_HOME,        KC_UP,          KC_END,         SRCHSEL,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LCTL,        KC_LALT,        KC_LGUI,        KC_LSFT,        MS_BTN1,                                        KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       LCTL(LCMD(LSFT(KC_4))),KC_TRANSPARENT,
    KC_TRANSPARENT, LCMD(KC_Z),     LCMD(LSFT(KC_Z)),LCMD(KC_C),    LCMD(KC_V),     LCMD(LSFT(KC_V)),                               LCMD(KC_L),     SELWBAK,        SELWORD,        SELLINE,        LCTL(LCMD(LSFT(KC_3))),KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 LCMD(KC_TAB),   QK_LLCK
  ),
  [L_NUM] = LAYOUT_voyager(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_NO,          KC_SLSH,        KC_9,           KC_8,           KC_7,           KC_ASTR,                                        KC_NO,          KC_NO,          KC_LBRC,        KC_RBRC,        KC_NO,          KC_F12,
    KC_NO,          KC_MINS,        KC_3,           KC_2,           KC_1,           KC_PLUS,                                        KC_NO,          KC_RSFT,        KC_RGUI,        KC_RALT,        KC_RCTL,        KC_NO,
    KC_NO,          KC_X,           KC_6,           KC_5,           KC_4,           KC_PERC,                                        KC_NO,          KC_NO,          KC_COMM,        KC_DOT,         KC_NO,          KC_NO,
                                                    KC_0,           KC_NO,                                           QK_LLCK,        KC_NO
  ),
  [L_MAGIC] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 RM_TOGG,        QK_KB,          RM_NEXT,        RGB_SLD,        RM_VALD,        RM_VALU,
    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HSV_0_255_255,  HSV_74_255_255, HSV_169_255_255,
    KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [L_MOUSE] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    MO(L_MOUSE),    OSM(MOD_LCTL),  OSM(MOD_LALT),  OSM(MOD_LGUI),  OSM(MOD_LSFT),  GESTURE,                                        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_ESCAPE,      KC_NO,          KC_MS_BTN3,     KC_MS_BTN2,     KC_MS_BTN1,     KC_NO,                                          KC_NO,          NAVIGATOR_INC_CPI,NAVIGATOR_DEC_CPI,TOGGLE_SCROLL,KC_NO,        KC_NO,
    KC_NO,          NAVIGATOR_DEC_CPI,NAVIGATOR_INC_CPI,LCMD(KC_C), LCMD(KC_V),     KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                    DRAG_SCROLL,    TOGGLE_SCROLL,                                  QK_LLCK,        KC_NO
  ),
};











static int32_t abs32(int32_t value) {
  return value < 0 ? -value : value;
}

static void reset_gesture_accumulation(void) {
  gesture_accum_x = 0;
  gesture_accum_y = 0;
}

static void tap_gesture_key(void) {
  if (abs32(gesture_accum_x) > abs32(gesture_accum_y)) {
    tap_code16(LCTL(gesture_accum_x > 0 ? KC_RIGHT : KC_LEFT));
  } else {
    tap_code16(LCTL(gesture_accum_y > 0 ? KC_DOWN : KC_UP));
  }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (!gesture_active) {
    return mouse_report;
  }

  if (gesture_cooling_down) {
    if (timer_elapsed(gesture_cooldown_timer) < GESTURE_COOLDOWN_MS) {
      mouse_report.x = 0;
      mouse_report.y = 0;
      mouse_report.h = 0;
      mouse_report.v = 0;
      return mouse_report;
    }
    gesture_cooling_down = false;
  }

  int16_t dx = mouse_report.x;
  int16_t dy = mouse_report.y;

  if (abs32(dx) < GESTURE_MOVEMENT_THRESHOLD) {
    dx = 0;
  }
  if (abs32(dy) < GESTURE_MOVEMENT_THRESHOLD) {
    dy = 0;
  }

  gesture_accum_x += dx;
  gesture_accum_y += dy;

  if (abs32(gesture_accum_x) + abs32(gesture_accum_y) >= GESTURE_STROKE_SIZE) {
    tap_gesture_key();
    reset_gesture_accumulation();
    gesture_cooling_down = true;
    gesture_cooldown_timer = timer_read();
  }

  mouse_report.x = 0;
  mouse_report.y = 0;
  mouse_report.h = 0;
  mouse_report.v = 0;
  return mouse_report;
}

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
      if (IS_MOUSE_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode)) || IS_CONSUMER_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
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
    case GESTURE:
      if (record->event.pressed) {
        gesture_active = true;
        gesture_scroll_restore = set_scrolling;
        gesture_cooling_down = false;
        reset_gesture_accumulation();
        set_scrolling = false;
      } else {
        gesture_active = false;
        gesture_cooling_down = false;
        reset_gesture_accumulation();
        set_scrolling = gesture_scroll_restore;
      }
      update_status_leds(layer_state);
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

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  (void)record;
  switch (keycode) {
    case DRAG_SCROLL:
    case TOGGLE_SCROLL:
      update_status_leds(layer_state);
      break;
  }
}
