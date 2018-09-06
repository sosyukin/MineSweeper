#pragma once

#include "resource.h"

#define CR_LIGHT 0xffffff
#define CR_SHADOW 0x808080

#define CR_BACKGROUND 0xc0c0c0
#define CR_BACKGROUND_LINE 0x808080
#define CR_SURFACE 0xc0c0c0

#define CR_COUNTER_BG 0x000000
#define CR_COUNTER_LIGHT_ON 0x0000ff
#define CR_COUNTER_LIGHT_OFF 0x000080

#define CR_MINENUM_1 0xff0000
#define CR_MINENUM_2 0x008000
#define CR_MINENUM_3 0x0000ff
#define CR_MINENUM_4 0x800000
#define CR_MINENUM_5 0x000080
#define CR_MINENUM_6 0x808000
#define CR_MINENUM_7 0x000000
#define CR_MINENUM_8 0x808080

#define MINESTYLE int
#define MS_MINE 9
#define MS_FLAG 10

#define RESETBUTTON_NORMAL 11

#define FLAGSTYLE int
#define FS_NULL 0
#define FS_FLAG 1
#define FS_QUESTIONMARK 2

#include "Box.h"
#include "Field.h"
#include "Block.h"

#include "LEDLight.h"
#include "Panel.h"
#include "Counter.h"
#include "GameManager.h"
