#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
uint16_t timer = 0;
bool windows_run = false;
char code[4] = "code";

enum custom_keycodes {
	VS_FORMAT = SAFE_RANGE,
    VS_COMMENT,
    VS_UNCOMMENT,
    VS_EXTRACTMETHOD,
    RUN_VSCODE,
    CLEAR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_LAYER0] = LAYOUT_65_ansi_blocker( /* Base */
			KC_GESC,       KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_HOME,\
		    KC_TAB,        KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,\
			CTL_T(KC_CAPS),KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDN,\
		    KC_LSFT,       KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,           KC_UP,     KC_END,\
		    KC_LCTL,       KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT,           MO(1),    KC_LEFT,           KC_DOWN,   KC_RIGHT),
		[_LAYER1] = LAYOUT_65_ansi_blocker( /* FN1 */
			CLEAR,       KC_F1,    KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,   KC_HOME,\
		    KC_TRNS,     KC_TRNS,  KC_TRNS, VS_EXTRACTMETHOD,KC_TRNS, KC_TILDE, KC_TRNS, VS_UNCOMMENT, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK,  KC_PAUS, KC_TRNS, KC_PGUP,\
			CTL_T(KC_CAPS),KC_TRNS,  KC_TRNS, KC_TRNS,VS_FORMAT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS,  KC_PGDN,\
		    KC_LSFT,     KC_TRNS,  KC_TRNS, VS_COMMENT,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_VOLU,  KC_MUTE,\
		    KC_TRNS,     KC_TRNS,  KC_TRNS,                  KC_MPLY,                   MO(2),          KC_TRNS,  KC_MPRV,          KC_VOLD,  KC_MNXT),
		[_LAYER2] = LAYOUT_65_ansi_blocker( /* FN2 */
			RESET,       KC_F13,    KC_F14,   KC_F15,  KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,  KC_F24,  RGB_HUD,   RGB_TOG,\
		    KC_TRNS,     RGB_TOG,  RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, RGB_SAD, RGB_SPI, RGB_SPD, KC_TRNS, KC_PSCR, KC_SLCK,  KC_PAUS, RESET,    RGB_MOD,\
			CTL_T(KC_CAPS),RGB_SPI,  RGB_SPD, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          EEP_RST,  RGB_RMOD,\
		    KC_LSFT,     KC_TRNS,  EEPROM_RESET, RUN_VSCODE,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,      RGB_VAI,  KC_MUTE,\
		    KC_TRNS,     KC_TRNS,  KC_TRNS,                  KC_TRNS,                   KC_TRNS,          KC_TRNS,  RGB_SAD,          RGB_VAD,  RGB_SAI),
};

const uint8_t PROGMEM layerleds[][DRIVER_LED_TOTAL] = {
  [1] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 1, 1, 0, 1, 1, 1,
  },
  [2] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 1, 1, 1,
  }
};

void matrix_init_user(void) {

}

void set_leds_color(int layer) {

  int r = 125, g = 0, b = 255;

  if (layer == 2){
      r = 255, b = 90;
  }

  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint8_t val = pgm_read_byte(&layerleds[layer][i]);
    if (val == 1)
    {
        rgb_matrix_set_color( i, r, g, b );
    } else {
        rgb_matrix_set_color( i, 0, 30, 0 );
    }
  }
}

void rgb_matrix_indicators_user(void)
{
    if (IS_LED_ON(host_keyboard_leds(), USB_LED_CAPS_LOCK))
    {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }

  uint32_t mode = rgblight_get_mode();
  // assign colors if the matrix is on and the current mode
  // is SOLID COLORS => No animations running
  if(mode == 1) {
    switch (biton32(layer_state)) {
      case _LAYER0:
        break;
      case _LAYER1:
        set_leds_color(1);
        break;
      case _LAYER2:
        set_leds_color(2);
        break;
    }
  }
}

void matrix_scan_user(void)
{
  if (windows_run) {
    if (timer_elapsed(timer) > 500) {
      windows_run = false;
      SEND_STRING(code);
      timer = 0;
    }
  }
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//         case _LAYER0:
//             rgblight_enable();
//             break;
//         case _LAYER1:
//             rgblight_disable();
//             //set_leds_color(1);
//             break;
//         case _LAYER2:
//             rgblight_disable();
//             //set_leds_color(2);
//             break;
//         default: //  for any other layers, or the default layer
//             rgblight_mode(28);
//             break;
//         }
//   return state;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	switch (keycode) {
		case VS_FORMAT:
            if (record->event.pressed){
                SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_K)SS_TAP(X_F)SS_UP(X_LCTRL));
            }
		    break;
        case VS_COMMENT:
        	if (record->event.pressed){
			    SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_K)SS_TAP(X_C)SS_UP(X_LCTRL));
		    }
            break;
        case VS_UNCOMMENT:
        	if (record->event.pressed){
			    SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_K)SS_TAP(X_U)SS_UP(X_LCTRL));
		    }
		    break;
        case VS_EXTRACTMETHOD:
            if (record->event.pressed){
			    SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_R)SS_TAP(X_M)SS_UP(X_LCTRL));
		    }
            break;
        case RUN_VSCODE:
            if (record->event.pressed){
			    SEND_STRING(SS_DOWN(X_LGUI)SS_TAP(X_R)SS_UP(X_LGUI));
		    } else {
                timer = timer_read();
                windows_run = true;
            }
            break;
        case CLEAR:
            if (record->event.pressed){
                clear_keyboard();
            }
		break;
	}

	  return true;
}
