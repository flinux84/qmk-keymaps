#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2

enum custom_keycodes {
	VS_FORMAT,
    VS_COMMENT,
    VS_UNCOMMENT,
    VS_EXTRACTMETHOD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_LAYER0] = LAYOUT_65_ansi_blocker( /* Base */
			KC_GESC,       KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_HOME,\
		    KC_TAB,        KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,\
			CTL_T(KC_CAPS),KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDN,\
		    KC_LSFT,       KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,           KC_UP,     KC_END,\
		    KC_LCTL,       KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT,           MO(1),    KC_LEFT,           KC_DOWN,   KC_RIGHT),
		[_LAYER1] = LAYOUT_65_ansi_blocker( /* FN1 */
			KC_GESC,       KC_F1,    KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,   KC_HOME,\
		    KC_TRNS,       KC_TRNS,  KC_TRNS, VS_EXTRACTMETHOD,KC_TRNS, KC_TRNS, KC_TRNS, VS_UNCOMMENT, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK,  KC_PAUS, KC_TRNS,    KC_PGUP,\
			CTL_T(KC_CAPS),KC_TRNS,  KC_TRNS, KC_TRNS,VS_FORMAT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS,  KC_PGDN,\
		    KC_LSFT,       KC_TRNS,  KC_TRNS, VS_COMMENT,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_VOLU,  KC_MUTE,\
		    KC_TRNS,       KC_TRNS,  KC_TRNS,                  KC_MPLY,                   MO(2),          KC_TRNS,  KC_MPRV,          KC_VOLD,  KC_MNXT),
		[_LAYER2] = LAYOUT_65_ansi_blocker( /* FN2 */
			RESET,       KC_F13,    KC_F14,   KC_F15,  KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,  KC_F24,  RGB_HUD,   RGB_TOG,\
		    KC_TRNS,       RGB_TOG,  RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, RGB_SAD, RGB_SPI, RGB_SPD, KC_TRNS, KC_PSCR, KC_SLCK,  KC_PAUS, RESET,    RGB_MOD,\
			CTL_T(KC_CAPS),RGB_SPI,  RGB_SPD, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          EEP_RST,  RGB_RMOD,\
		    KC_LSFT,       KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          RGB_VAI,  KC_MUTE,\
		    KC_TRNS,       KC_TRNS,  KC_TRNS,                  KC_TRNS,                   KC_TRNS,          KC_TRNS,  RGB_SAD,          RGB_VAD,  RGB_SAI),
};

void rgb_matrix_indicators_user(void)
{
	    if (IS_LED_ON(host_keyboard_leds(), USB_LED_CAPS_LOCK))
	    {
	      rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
	    }
}

void matrix_init_user(void)
{
  //user initialization
}

void matrix_scan_user(void)
{
  //user matrix
}

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
	}

	  return true;
}
