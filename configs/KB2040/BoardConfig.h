/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2021 Jason Skuby (mytechtoybox.com)
 */

#ifndef PICO_BOARD_CONFIG_H_
#define PICO_BOARD_CONFIG_H_

#include <GamepadEnums.h>
#include "NeoPico.hpp"

#define PIN_DPAD_UP     27
#define PIN_DPAD_DOWN   29
#define PIN_DPAD_RIGHT  28
#define PIN_DPAD_LEFT   26
#define PIN_BUTTON_B1   3
#define PIN_BUTTON_B2   2
#define PIN_BUTTON_B3   5
#define PIN_BUTTON_B4   4
#define PIN_BUTTON_S2   18
#define PIN_BUTTON_S1   19 // Not connected

#define PIN_BUTTON_L1   6  // Not connected
#define PIN_BUTTON_R1   7  // Not connected
#define PIN_BUTTON_R2   8  // Not connected
#define PIN_BUTTON_L2   9  // Not connected
#define PIN_BUTTON_L3   10 // Not connected
#define PIN_BUTTON_R3   20 // Not connected
#define PIN_BUTTON_A1   13 // Not connected
#define PIN_BUTTON_A2   13 // Not connected

#define DEFAULT_SOCD_MODE SOCD_MODE_NEUTRAL
#define BUTTON_LAYOUT BUTTON_LAYOUT_ARCADE

#define BOARD_LEDS_PIN 17

#define LED_BRIGHTNESS_MAXIMUM 100
#define LED_BRIGHTNESS_STEPS 5
#define LED_FORMAT LED_FORMAT_GRB
#define LEDS_PER_PIXEL   1
#define LEDS_DPAD_LEFT   0
#define LEDS_DPAD_DOWN   0
#define LEDS_DPAD_RIGHT  0
#define LEDS_DPAD_UP     0
#define LEDS_BUTTON_B3   0
#define LEDS_BUTTON_B4   0
#define LEDS_BUTTON_R1   0
#define LEDS_BUTTON_L1   0
#define LEDS_BUTTON_B1   0
#define LEDS_BUTTON_B2   0
#define LEDS_BUTTON_R2   0
#define LEDS_BUTTON_L2   0

#endif
