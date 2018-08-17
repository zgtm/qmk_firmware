#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FAKENEO 1
#define _SWAPCTRLALT 2
#define _SWAPSHIFTMOD2 3
#define _FUNCTION 11
#define _CURSOR 12
#define _NUMPAD 13

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FUNCTION,
  NUMPAD,
  CURSOR,
  MOD3Y,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_FN MO(_FUNCTION)
#define KC_NMPD MO(_NUMPAD)
#define KC_CUR MO(_CURSOR)
#define KC_AJST ADJUST
#define KC_SH_Q MT(MOD_RSFT, KC_QUOT)
#define KC_NEO  TG(_FAKENEO)
#define KC_T_CA TG(_SWAPCTRLALT)
#define KC_T_SM TG(_SWAPSHIFTMOD2)
#define KC_RSET RESET
#define KC_MD3Y MOD3Y

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     ESC , F1 , F2 , F3 , F4 , F5 , F6 ,      F7 , F8 , F9 ,F10 ,F11 ,F12 ,MINS,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,    ,         , Y  , U  , I  , O  , P  ,LBRC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     NUHS, A  , S  , D  , F  , G  ,    ,         , H  , J  , K  , L  ,SCLN,MD3Y,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,DEL ,     BSPC, N  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     NMPD, FN ,LALT,LCTL,ENT ,NMPD,NMPD,     CUR ,CUR ,SPC ,RCTL,RALT, FN ,CUR
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FAKENEO] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         , X  , V  , L  , C  , W  ,    ,         , K  , H  , G  , F  , Q  ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         , U  , I  , A  , E  , O  ,    ,         , S  , N  , R  , T  , D  , Z  ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,LBRC,SCLN,QUOT, P  , Y  ,    ,         , B  , M  ,    ,    , J  ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,             ,,    ,    ,    ,    ,
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
         ,    ,LCTL,LALT,    ,,        ,             ,,    ,RALT,RCTL,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_SWAPSHIFTMOD2] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LSFT,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,SH_Q,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     NUHS,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,NUHS,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,             ,,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FUNCTION] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,BTN3,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     RSET,    ,BTN1,MS_U,BTN2,    ,    ,         ,    ,MNXT,VOLD,VOLU,MPLY,MUTE,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     T_SM,NEO ,MS_L,MS_D,MS_R,    ,NEO ,     NEO ,    ,    ,    ,    ,NEO ,T_SM,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     T_SM,   ,     ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,T_SM,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,T_CA,T_CA,    ,,        ,             ,,    ,T_CA,T_CA,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_CURSOR] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,PGUP,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,PGUP,BSPC, UP ,DEL ,PGDN,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,HOME,LEFT,DOWN,RGHT,END ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,PGDN,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,             ,,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,    ,         ,    ,NLCK,PSLS,PAST,PMNS,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    , P7 , P8 , P9 ,PPLS,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    , P4 , P5 , P6 ,PEQL,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    , P1 , P2 , P3 ,PENT,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,,        ,        PENT ,, P0 ,PCMM,PDOT,PCMM,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),
};

uint8_t mod3y_depressed = 0;
uint8_t mod3y_other = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOD3Y:
      if (record->event.pressed) {
        mod3y_depressed = 1;
        mod3y_other = 0;
      } else {
        mod3y_depressed = 0;
        if (mod3y_other) {
          unregister_code16(KC_NUHS);
        }
        else {
          register_code16(KC_QUOT);
          unregister_code16(KC_QUOT);
        }
      }
      return false;

    default:
      if (record->event.pressed) {
        if (mod3y_depressed && !mod3y_other) {
          register_code16(KC_NUHS);
          mod3y_other = 1;
        }
      }
  }
  return true;
}
