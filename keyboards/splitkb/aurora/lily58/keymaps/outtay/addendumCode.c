void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

//This would be useful for setting a different holding term for my LT on the y key
//For now I'm trying a "hold on other key press" and maybe even the permissive. 
//This would still require changes in the config.h and doesn't work just by uncommenting this
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
     case LT(1, KC_Z):
       return TAPPING_TERM - 70;
     default:
       return TAPPING_TERM;
  }
}



/*bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(2, KC_Z):
      // Immediately select the hold action when another key is pressed.
      return true;
    default:
      // Do not select the hold action when another key is pressed.
      return false;
  }
}
*/

/*bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_Z):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
*/


void suspend_wakeup_init_user(void) {
  //soft_reset_keyboard();
}


const uint16_t PROGMEM caps_combo[] = {KC_LEFT_SHIFT, KC_RIGHT_SHIFT, COMBO_END};
combo_t key_combos[] = {
    COMBO(caps_combo, KC_CAPS_LOCK),
};

// This feels stupid, but is needed such that pressing y and then y again
// does the correct thing
// I have to be honest, that I did not really understand it and maybe it's not
// needed after al
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_Z):
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (true) { /* Don't actually care which encoder it is */
        switch (get_highest_layer(layer_state)) {
            case 0: // Base layer
                if (clockwise) {
                    tap_code(KC_VOLU); // Volume up
                } else {
                    tap_code(KC_VOLD); // Volume down
                }
                break;

            case 1: // Layer 1
                if (clockwise) {
                    tap_code(MS_WHLU); // Scroll up
                } else {
                    tap_code(MS_WHLD); // Scroll down
                }
                break;

            case 5:
                if (clockwise) {
                    tap_code(MS_RGHT);
                } else {
                    tap_code(MS_LEFT);
                }
                break;
            case 6:
                if (clockwise) {
                    tap_code(MS_UP);
                } else {
                    tap_code(MS_DOWN);
                }
                break;
            default: // Any other layer
                if (clockwise) {
                    tap_code(KC_VOLU); // Page down (example action)
                } else {
                    tap_code(KC_VOLD); // Page up (example action)
                }
                break;
        }
    }
    else {
    	if (clockwise) {
	    tap_code(KC_VOLU);
	} else {
	    tap_code(KC_VOLD);
	}
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case OTTI_CIRC:
      if (record->event.pressed) {
        tap_code(KC_GRV);
	tap_code(KC_SPC);
      }
      return false; // Skip all further processing of this key
    case OTTI_BACK:
      if (record->event.pressed) {
        tap_code16(KC_PLUS);
	tap_code(KC_SPC);
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}
