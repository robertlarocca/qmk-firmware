#include QMK_KEYBOARD_H

enum custom_keycodes {
	SHIFT_BSPC_DEL,	// shift + backspace = delete
};

#define KC_BSDL SHIFT_BSPC_DEL

enum custom_layers {
	BASE = 0,	// base layer (default)
	FUNC = 1,	// function layer
	LIGHT = 2,	// lighting layer
};

static uint16_t KC_SHIFT = 0;
static bool shift_status = false;
static bool bspc_del_mod = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case KC_LSFT:
		shift_status = record->event.pressed;
		KC_SHIFT = keycode;
		return true;
		break;
	case KC_RSFT:
		shift_status = record->event.pressed;
		KC_SHIFT = keycode;
		return true;
		break;
	case SHIFT_BSPC_DEL:
		if (record->event.pressed) {
			if (shift_status) {
				unregister_code(KC_SHIFT);
				register_code(KC_DEL);
				bspc_del_mod = true;
			} else {
				register_code(KC_BSPC);
			}
		} else {
			if (bspc_del_mod) {
				unregister_code(KC_DEL);
				bspc_del_mod = false;
			} else {
				unregister_code(KC_BSPC);
			}
		}
		return false;
		break;
	}
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_60_tsangan_hhkb(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSDL,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, TT(1),
		KC_NO, KC_LGUI, KC_LCTL, KC_SPC, KC_RALT, KC_APP, KC_NO
	),
	[FUNC] = LAYOUT_60_tsangan_hhkb(
		TO(0), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_PGDN, KC_UP, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BRID, KC_BRIU, KC_TRNS,
		KC_TRNS, KC_MPLY, KC_MPRV, KC_MSTP, KC_MNXT, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSEL, KC_TRNS, KC_TRNS,
		KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TT(2), KC_NO
	),
	[LIGHT] = LAYOUT_60_tsangan_hhkb(
		TO(1), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_SPD, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_TOGG, RGB_TOG, RGB_VAD, RGB_VAI, RGB_RMOD, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, EEP_RST, DEBUG, RESET, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
	),
};

