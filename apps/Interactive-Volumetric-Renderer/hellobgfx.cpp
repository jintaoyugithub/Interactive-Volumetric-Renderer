/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bx/uint32_t.h>
#include <entry/entry.h>
#include <util/bgfx_utils.h>
#include <util/common.h>
#include <util/imgui/imgui.h>

#include <filesystem>
#include <iostream>
#include <string>

static const uint8_t s_logo[4000] = {
    0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ........ . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x08, //  . . . . . . ...
    0xdc, 0x03, 0xdc, 0x07, 0xdc, 0x07, 0xdc, 0x08,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ........ . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0xde, 0x03, 0xb0, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b,
    0xdb, 0x3b, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ...;.;.;.; . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0xdc, 0x03, 0xb1, 0x3b, 0xb2, 0x3b, //  . . . . ....;.;
    0xdb, 0x3b, 0xdf, 0x03, 0xdf, 0x3b, 0xb2, 0x3f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // .;...;.? . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b,
    0xb2, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  ..;.;.;.? . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b, //  . . . . ..;.;.;
    0xb2, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0xdf, 0x03,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // .? . ... . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb1, 0x3b,
    0xb1, 0x3f, 0xdc, 0x0b, 0xdc, 0x03, 0xdc, 0x03, //  ..;.;.;.?......
    0xdc, 0x03, 0xdc, 0x03, 0x20, 0x0f, 0x20, 0x0f,
    0xdc, 0x08, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, // .... . .........
    0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x08,
    0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb1, 0x3b, // ........ ..;.;.;
    0xb1, 0x3f, 0xb1, 0x3f, 0xb2, 0x0b, 0x20, 0x0f,
    0x20, 0x0f, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, // .?.?.. . .......
    0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x03, 0xdc, 0x03,
    0xdc, 0x03, 0x20, 0x0f, 0x20, 0x01, 0x20, 0x0f, //  . ....... . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b,
    0xb0, 0x3f, 0x20, 0x0f, 0xde, 0x03, 0xb0, 0x3f, //  ..;.;.;.? ....?
    0xb1, 0x3f, 0xb2, 0x3f, 0xdd, 0x03, 0xde, 0x03,
    0xdb, 0x03, 0xdb, 0x03, 0xb2, 0x3f, 0x20, 0x0f, // .?.?.........? .
    0x20, 0x0f, 0xb0, 0x3f, 0xb1, 0x3f, 0xb2, 0x3f,
    0xde, 0x38, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, //  ..?.?.?.8.;.;.;
    0xb0, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0xb0, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b, 0xb2, 0x3f, // .? . . ..;.;.;.?
    0xdd, 0x03, 0xde, 0x03, 0xb0, 0x3f, 0xb1, 0x3f,
    0xb2, 0x3f, 0xdd, 0x03, 0x20, 0x01, 0x20, 0x0f, // .....?.?.?.. . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b,
    0xb0, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0xdb, 0x03, //  ..;.;.;.? . ...
    0xb0, 0x3f, 0xb1, 0x3f, 0xdd, 0x03, 0xb1, 0x3b,
    0xb0, 0x3b, 0xdb, 0x03, 0xb1, 0x3f, 0x20, 0x0f, // .?.?...;.;...? .
    0x20, 0x0f, 0x20, 0x3f, 0xb0, 0x3f, 0xb1, 0x3f,
    0xb0, 0x3b, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, //  . ?.?.?.;.;.;.;
    0xb0, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0xdc, 0x08, 0xdc, 0x3b, 0xb1, 0x3b, 0xb1, 0x3f, // .? . . ....;.;.?
    0xb1, 0x3b, 0xb0, 0x3b, 0xb2, 0x3b, 0xb0, 0x3f,
    0xdc, 0x03, 0x20, 0x0f, 0x20, 0x01, 0x20, 0x0f, // .;.;.;.?.. . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b,
    0xb0, 0x3f, 0xdc, 0x0b, 0xdc, 0x07, 0xdb, 0x03, //  ..;.;.;.?......
    0xdb, 0x03, 0xdc, 0x38, 0x20, 0x0f, 0xdf, 0x03,
    0xb1, 0x3b, 0xb0, 0x3b, 0xb0, 0x3f, 0xdc, 0x03, // ...8 ....;.;.?..
    0xdc, 0x07, 0xb0, 0x3f, 0xb1, 0x3f, 0xb2, 0x3f,
    0xdd, 0x3b, 0xb2, 0x3b, 0xb1, 0x3b, 0xdc, 0x78, // ...?.?.?.;.;.;.x
    0xdf, 0x08, 0x20, 0x0f, 0x20, 0x0f, 0xde, 0x08,
    0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, 0xb0, 0x3f, // .. . ....;.;.;.?
    0x20, 0x0f, 0xdf, 0x03, 0xb1, 0x3b, 0xb2, 0x3b,
    0xdb, 0x03, 0xdd, 0x03, 0x20, 0x01, 0x20, 0x0f, //  ....;.;.... . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0xdc, 0x08, 0xdc, 0x08, 0xdc, 0x08, 0x20, 0x0f, //  . . . ....... .
    0x20, 0x0f, 0xb0, 0x3f, 0xb0, 0x3f, 0xb1, 0x3f,
    0xdd, 0x3b, 0xdb, 0x0b, 0xdf, 0x03, 0x20, 0x0f, //  ..?.?.?.;.... .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0xdf, 0x08, 0xdf, 0x03, 0xdf, 0x03, 0xdf, 0x08, //  . . . .........
    0x20, 0x0f, 0x20, 0x0f, 0xdf, 0x08, 0xdf, 0x03,
    0xdf, 0x03, 0x20, 0x0f, 0x20, 0x01, 0x20, 0x0f, //  . ....... . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0xdb, 0x08, 0xb2, 0x38, 0xb1, 0x38, 0xdc, 0x03, //  . . . ....8.8..
    0xdc, 0x07, 0xb0, 0x3b, 0xb1, 0x3b, 0xdf, 0x3b,
    0xdf, 0x08, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ...;.;.;.. . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
    0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x2d, 0x08, 0x3d, 0x08, 0x20, 0x0a, 0x43, 0x0b,
    0x72, 0x0b, 0x6f, 0x0b, 0x73, 0x0b, 0x73, 0x0b, // -.=. .C.r.o.s.s.
    0x2d, 0x0b, 0x70, 0x0b, 0x6c, 0x0b, 0x61, 0x0b,
    0x74, 0x0b, 0x66, 0x0b, 0x6f, 0x0b, 0x72, 0x0b, // -.p.l.a.t.f.o.r.
    0x6d, 0x0b, 0x20, 0x0b, 0x72, 0x0b, 0x65, 0x0b,
    0x6e, 0x0b, 0x64, 0x0b, 0x65, 0x0b, 0x72, 0x0b, // m. .r.e.n.d.e.r.
    0x69, 0x0b, 0x6e, 0x0b, 0x67, 0x0b, 0x20, 0x0b,
    0x6c, 0x0b, 0x69, 0x0b, 0x62, 0x0b, 0x72, 0x0b, // i.n.g. .l.i.b.r.
    0x61, 0x0b, 0x72, 0x0b, 0x79, 0x0b, 0x20, 0x0f,
    0x3d, 0x08, 0x2d, 0x08, 0x20, 0x01, 0x20, 0x0f, // a.r.y. .=.-. . .
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a,
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a,
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a,
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a,
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a,
    0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f,
    0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
};

namespace {

class ExampleHelloWorld : public entry::AppI {
public:
  ExampleHelloWorld(const char *_name, const char *_description,
                    const char *_url)
      : entry::AppI(_name, _description, _url) {}

  void init(int32_t _argc, const char *const *_argv, uint32_t _width,
            uint32_t _height) override {
    // reset current dir
    std::filesystem::path pth =
        std::filesystem::current_path().parent_path().parent_path() / "assets";
    std::string pth_s = pth.string();
    std::cout << pth_s << std::endl;
    entry::setCurrentDir(pth_s.c_str());

    Args args(_argc, _argv);

    m_width = _width;
    m_height = _height;
    m_debug = BGFX_DEBUG_TEXT;
    m_reset = BGFX_RESET_VSYNC;

    bgfx::Init init;
    init.type = args.m_type;
    init.vendorId = args.m_pciId;
    init.platformData.nwh =
        entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
    init.platformData.ndt = entry::getNativeDisplayHandle();
    init.platformData.type = entry::getNativeWindowHandleType();
    init.resolution.width = m_width;
    init.resolution.height = m_height;
    init.resolution.reset = m_reset;
    bgfx::init(init);

    // Enable debug text.
    bgfx::setDebug(m_debug);

    // Set view 0 clear state.
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f,
                       0);

    imguiCreate();
  }

  virtual int shutdown() override {
    imguiDestroy();

    // Shutdown bgfx.
    bgfx::shutdown();

    return 0;
  }

  bool update() override {
    if (!entry::processEvents(m_width, m_height, m_debug, m_reset,
                              &m_mouseState)) {
      imguiBeginFrame(m_mouseState.m_mx, m_mouseState.m_my,
                      (m_mouseState.m_buttons[entry::MouseButton::Left]
                           ? IMGUI_MBUT_LEFT
                           : 0) |
                          (m_mouseState.m_buttons[entry::MouseButton::Right]
                               ? IMGUI_MBUT_RIGHT
                               : 0) |
                          (m_mouseState.m_buttons[entry::MouseButton::Middle]
                               ? IMGUI_MBUT_MIDDLE
                               : 0),
                      m_mouseState.m_mz, uint16_t(m_width), uint16_t(m_height));

      showExampleDialog(this);

      imguiEndFrame();

      // Set view 0 default viewport.
      bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

      // This dummy draw call is here to make sure that view 0 is cleared
      // if no other draw calls are submitted to view 0.
      bgfx::touch(0);

      // Use debug font to print information about this example.
      bgfx::dbgTextClear();

      const bgfx::Stats *stats = bgfx::getStats();

      bgfx::dbgTextImage(
          bx::max<uint16_t>(uint16_t(stats->textWidth / 2), 20) - 20,
          bx::max<uint16_t>(uint16_t(stats->textHeight / 2), 6) - 6, 40, 12,
          s_logo, 160);
      bgfx::dbgTextPrintf(0, 1, 0x0f,
                          "Color can be changed with ANSI "
                          "\x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;"
                          "mp\x1b[14;me\x1b[0m code too.");

      bgfx::dbgTextPrintf(
          80, 1, 0x0f,
          "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    "
          "\x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
      bgfx::dbgTextPrintf(
          80, 2, 0x0f,
          "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    "
          "\x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

      bgfx::dbgTextPrintf(
          0, 2, 0x0f,
          "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.",
          stats->width, stats->height, stats->textWidth, stats->textHeight);

      // Advance to next frame. Rendering thread will be kicked to
      // process submitted rendering primitives.
      bgfx::frame();

      return true;
    }

    return false;
  }

  entry::MouseState m_mouseState;

  uint32_t m_width;
  uint32_t m_height;
  uint32_t m_debug;
  uint32_t m_reset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
    ExampleHelloWorld, "00-helloworld", "Initialization and debug text.",
    "https://bkaradzic.github.io/bgfx/examples.html#helloworld");

int _main_(int _argc, char **_argv) { return 0; };
