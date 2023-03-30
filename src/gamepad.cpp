/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2021 Jason Skuby (mytechtoybox.com)
 */

#include "pico/stdlib.h"
#include "gamepad.h"
#include "display.h"
#include "storage.h"
#include "display.h"
#include "OneBitDisplay.h"
#include "SNESpad.h"

// Pins for SNES controller
#define LATCH_PIN 6
#define CLOCK_PIN 5
#define DATA_PIN 7

SNESpad snesPad = SNESpad(LATCH_PIN, CLOCK_PIN, DATA_PIN);

void Gamepad::setup()
{
	load();

	// Configure pin mapping
	f2Mask = (GAMEPAD_MASK_A1 | GAMEPAD_MASK_S2);
	BoardOptions boardOptions = getBoardOptions();

	mapDpadUp    = new GamepadButtonMapping(boardOptions.pinDpadUp,    GAMEPAD_MASK_UP);
	mapDpadDown  = new GamepadButtonMapping(boardOptions.pinDpadDown,  GAMEPAD_MASK_DOWN);
	mapDpadLeft  = new GamepadButtonMapping(boardOptions.pinDpadLeft,  GAMEPAD_MASK_LEFT);
	mapDpadRight = new GamepadButtonMapping(boardOptions.pinDpadRight, GAMEPAD_MASK_RIGHT);
	mapButtonB1  = new GamepadButtonMapping(boardOptions.pinButtonB1,  GAMEPAD_MASK_B1);
	mapButtonB2  = new GamepadButtonMapping(boardOptions.pinButtonB2,  GAMEPAD_MASK_B2);
	mapButtonB3  = new GamepadButtonMapping(boardOptions.pinButtonB3,  GAMEPAD_MASK_B3);
	mapButtonB4  = new GamepadButtonMapping(boardOptions.pinButtonB4,  GAMEPAD_MASK_B4);
	mapButtonL1  = new GamepadButtonMapping(boardOptions.pinButtonL1,  GAMEPAD_MASK_L1);
	mapButtonR1  = new GamepadButtonMapping(boardOptions.pinButtonR1,  GAMEPAD_MASK_R1);
	mapButtonL2  = new GamepadButtonMapping(boardOptions.pinButtonL2,  GAMEPAD_MASK_L2);
	mapButtonR2  = new GamepadButtonMapping(boardOptions.pinButtonR2,  GAMEPAD_MASK_R2);
	mapButtonS1  = new GamepadButtonMapping(boardOptions.pinButtonS1,  GAMEPAD_MASK_S1);
	mapButtonS2  = new GamepadButtonMapping(boardOptions.pinButtonS2,  GAMEPAD_MASK_S2);
	mapButtonL3  = new GamepadButtonMapping(boardOptions.pinButtonL3,  GAMEPAD_MASK_L3);
	mapButtonR3  = new GamepadButtonMapping(boardOptions.pinButtonR3,  GAMEPAD_MASK_R3);
	mapButtonA1  = new GamepadButtonMapping(boardOptions.pinButtonA1,  GAMEPAD_MASK_A1);
	mapButtonA2  = new GamepadButtonMapping(boardOptions.pinButtonA2,  GAMEPAD_MASK_A2);

	gamepadMappings = new GamepadButtonMapping *[GAMEPAD_DIGITAL_INPUT_COUNT]
	{
		mapDpadUp,   mapDpadDown, mapDpadLeft, mapDpadRight,
		mapButtonB1, mapButtonB2, mapButtonB3, mapButtonB4,
		mapButtonL1, mapButtonR1, mapButtonL2, mapButtonR2,
		mapButtonS1, mapButtonS2, mapButtonL3, mapButtonR3,
		mapButtonA1, mapButtonA2
	};

	// for (int i = 0; i < GAMEPAD_DIGITAL_INPUT_COUNT; i++)
	// {
	// 	gpio_init(gamepadMappings[i]->pin);             // Initialize pin
	// 	gpio_set_dir(gamepadMappings[i]->pin, GPIO_IN); // Set as INPUT
	// 	#ifdef PIN_ACTIVE_HIGH
	// 		gpio_pull_down(gamepadMappings[i]->pin);    // Set as PULLDOWN
	// 	#else
	// 		gpio_pull_up(gamepadMappings[i]->pin);      // Set as PULLUP
	// 	#endif
	// }

	// #ifdef PIN_SETTINGS
	// 	gpio_init(PIN_SETTINGS);             // Initialize pin
	// 	gpio_set_dir(PIN_SETTINGS, GPIO_IN); // Set as INPUT
	// 	gpio_pull_up(PIN_SETTINGS);          // Set as PULLUP
	// #endif
}

void Gamepad::read()
{
	// Need to invert since we're using pullups
	// #ifdef PIN_ACTIVE_HIGH
	// 	uint32_t values = gpio_get_all();
	// #else
	// 	uint32_t values = ~gpio_get_all();
	// #endif

	// #ifdef PIN_SETTINGS
	// state.aux = 0
	// 	| ((values & (1 << PIN_SETTINGS)) ? (1 << 0) : 0)
	// ;
	// #endif

	uint32_t values = snesPad.buttons(SNES_MOUSE_FAST);

	// Read dpad inputs
	state.dpad = 0
		| ((values & SNES_UP)    ? (options.invertYAxis ? mapDpadDown->buttonMask : mapDpadUp->buttonMask) : 0)
		| ((values & SNES_DOWN)  ? (options.invertYAxis ? mapDpadUp->buttonMask : mapDpadDown->buttonMask) : 0)
		| ((values & SNES_LEFT)  ? mapDpadLeft->buttonMask  : 0)
		| ((values & SNES_RIGHT) ? mapDpadRight->buttonMask : 0)
	;

	// Read button inputs
	state.buttons = 0
		| ((values & SNES_B)  ? mapButtonB1->buttonMask  : 0)
		| ((values & SNES_A)  ? mapButtonB2->buttonMask  : 0)
		| ((values & SNES_Y)  ? mapButtonB3->buttonMask  : 0)
		| ((values & SNES_X)  ? mapButtonB4->buttonMask  : 0)
		| ((values & SNES_L)  ? mapButtonL1->buttonMask  : 0)
		| ((values & SNES_R)  ? mapButtonR1->buttonMask  : 0)
		| ((values & 0)  ? mapButtonL2->buttonMask  : 0)
		| ((values & 0)  ? mapButtonR2->buttonMask  : 0)
		| ((values & SNES_SELECT) ? mapButtonS1->buttonMask  : 0)
		| ((values & SNES_START)  ? mapButtonS2->buttonMask  : 0)
		| ((values & 0)  ? mapButtonL3->buttonMask  : 0)
		| ((values & 0)  ? mapButtonR3->buttonMask  : 0)
		| ((values & 0)  ? mapButtonA1->buttonMask  : 0)
		| ((values & 0)  ? mapButtonA2->buttonMask  : 0)
	;

    // No analog, but could read them here with analogRead() or fill outside of this method
	state.lx = GAMEPAD_JOYSTICK_MID;
	state.ly = GAMEPAD_JOYSTICK_MID;
	state.rx = GAMEPAD_JOYSTICK_MID;
	state.ry = GAMEPAD_JOYSTICK_MID;
	state.lt = 0;
	state.rt = 0;
}
