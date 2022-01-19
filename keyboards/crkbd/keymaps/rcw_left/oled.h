#pragma once

enum crkbd_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _GAME,
  _GAME_ALT
};


bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
