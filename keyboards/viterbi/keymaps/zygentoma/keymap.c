#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SWAPCTRLALT 1
#define _SWAPSHIFTMOD2 2
#define _FUNCTION 11
#define _CURSOR 12
#define _NUMPAD 13
#define _MOUSE 15
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FUNCTION,
  NUMPAD,
  CURSOR,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_FN FUNCTION
#define KC_NMPD NUMPAD
#define KC_CUR CURSOR
#define KC_AJST ADJUST
#define KC_MOUS MOUSE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     ESC, GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,MINS,BSPC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     EQL ,TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,LBRC,DEL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     RBRC,NUHS, A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,NUHS,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     NUBS,LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,NUBS,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
      FN ,NMPD,LALT,LWIN,LCTL,,  ENT   ,        SPC  ,,RCTL,RWIN,RALT,CUR , FN  
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_SWAPCTRLALT] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,LCTL,    ,LALT,,        ,             ,,RALT,    ,RCTL,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_SWAPSHIFTMOD2] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,LSFT,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,RSFT,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,NUHS,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,NUHS,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,             ,,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FUNCTION] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     PSCR,    , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,MNXT,VOLD,VOLU,MPLY,MUTE,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,             ,,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_CURSOR] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,PGUP,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,PGUP,BSPC, UP ,DEL ,PGDN,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,HOME,LEFT,DOWN,RGHT,END ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,PGDN,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,             ,,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_MOUSE] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,BTN3,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,BTN1,MS_U,BTN2,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,MS_L,MS_D,MS_R,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,             ,,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,    ,         ,NLCK,PSLS,PAST,PMNS,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         , P7 , P8 , P9 ,PPLS,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         , P4 , P5 , P6 ,PEQL,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         , P1 , P2 , P3 ,PENT,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,        P0   ,, P0 ,PDOT,PCMM,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_ADJUST] = LAYOUT(
    KC_PSCR, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
    QWERTY,  RESET,   _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL,  _______, \
    TG(_SWAPCTRLALT), _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, KC_MUTE, \
    TG(_SWAPSHIFTMOD2), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;

    case CURSOR:
      if (record->event.pressed) {
        layer_on(_CURSOR);
      } else {
        layer_off(_CURSOR);
      }
      update_tri_layer(_CURSOR, _FUNCTION, _MOUSE);
      return false;

    case NUMPAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
      } else {
        layer_off(_NUMPAD);
      }
      update_tri_layer(_NUMPAD, _FUNCTION, _ADJUST);
      return false;

    case FUNCTION:
      if (record->event.pressed) {
        layer_on(_FUNCTION);
      } else {
        layer_off(_FUNCTION);
      }
      update_tri_layer(_CURSOR, _FUNCTION, _MOUSE);
      update_tri_layer(_NUMPAD, _FUNCTION, _ADJUST);
      return false;
      
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
  }
  return true;
}
