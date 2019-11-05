#include QMK_KEYBOARD_H

#define _BASE 0
#define _FN1 1

bool is_alt_tab_active = false;
bool is_ctrl_tab_active = false;
uint16_t alt_tab_timer = 0;
uint16_t ctrl_tab_timer = 0;

enum custom_keycodes { 
  ALT_TAB = SAFE_RANGE,
  CTRL_TAB,
  PRINTSCR,
  ACOPY,
  PASTE,
  CLEAR
};

uint32_t layer_state_set_user(uint32_t state) 
{
	switch (biton32(state)) 
	{
		case _BASE:
			//left led on
			DDRB |= (1<<0);
			PORTB &= ~(1<<0);
			//right led off
			DDRD &= ~(1<<5);
			PORTD &= ~(1<<5);
		break;
		case _FN1:
			// right led on
			DDRD |= (1<<5);
			PORTD &= ~(1<<5);
			//left led off
			DDRB &= ~(1<<0);
			PORTB &= ~(1<<0);
		break;
	}  
	return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
	case CTRL_TAB:
	  if (record->event.pressed) {		
        if (!is_ctrl_tab_active) {
          is_ctrl_tab_active = true;
          register_code(KC_LCTRL);
        }
        ctrl_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
	case PRINTSCR:
		if (record->event.pressed){
			SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)SS_TAP(X_S)SS_UP(X_LSHIFT)SS_UP(X_LCTRL));
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

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_ctrl_tab_active) {
	  if (timer_elapsed(ctrl_tab_timer) > 1000) {
      unregister_code(KC_LCTRL);
      is_ctrl_tab_active = false;
    }
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = 
{

	[_BASE] = LAYOUT(
		KC_7, KC_8, KC_9, \
		KC_4, KC_5, KC_6, \
		KC_1, KC_2, KC_3, \
		TG(1), KC_0, KC_DOT \
	),
  
	[_FN1] = LAYOUT(
		CLEAR, KC_HOME, PRINTSCR, \
		KC_TRNS, KC_END, KC_PGDN, \
		KC_TRNS, KC_TRNS, KC_TRNS, \
		KC_TRNS, ALT_TAB, CTRL_TAB \
	)
};
