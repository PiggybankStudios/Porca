/*
File:   main.c
Author: Taylor Robbins
Date:   09\17\2023
Description: 
	** Holds the main entry point for our program,
	** and also is the only file that is directly compiled (all others are #included by this one)
*/

#include "gylib/gy_defines_check.h"

#define GYLIB_LOOKUP_PRIMES_10
#include "gylib/gy.h"

#include "main.h"

#include "orca_helpers.cpp"

PigState_t pig = {};

ORCA_EXPORT void oc_on_init(void)
{
	pig.initialized = true;
	pig.frameSizei = NewVec2i(400, 400);
	pig.frameSize = ToVec2(pig.frameSizei);
	
	oc_window_set_title(OC_STR8(PROJECT_NAME));
	oc_window_set_size(ToOcVec2(pig.frameSize));
	
	pig.surface = oc_surface_canvas();
	pig.canvas = oc_canvas_create();
	
	oc_unicode_range ranges[5] = {
		OC_UNICODE_BASIC_LATIN,
		OC_UNICODE_C1_CONTROLS_AND_LATIN_1_SUPPLEMENT,
		OC_UNICODE_LATIN_EXTENDED_A,
		OC_UNICODE_LATIN_EXTENDED_B,
		OC_UNICODE_SPECIALS
	};
	pig.font = oc_font_create_from_path(OC_STR8("/segoeui.ttf"), 5, ranges);
	
	CreateRandomSeries(&pig.random);
	SeedRandomSeriesU64(&pig.random, 1234);
}

ORCA_EXPORT void oc_on_resize(u32 width, u32 height)
{
	pig.frameSizei = NewVec2i((i32)width, (i32)height);
	pig.frameSize = ToVec2(pig.frameSizei);
}

ORCA_EXPORT void oc_on_frame_refresh(void)
{
	oc_canvas_select(pig.canvas);
	oc_set_color_rgba(.25, .15, .35, 1);
	oc_clear();
	
	v2 center = pig.frameSize / 2;
	r32 circleRadius = MinR32(pig.frameSize.width, pig.frameSize.height) / 2;
	
	oc_set_color_rgba(1, 1, 1, 0.1f);
	oc_circle_fill(center.x, center.y, circleRadius);
	
	const f32 fontSize = 26 * 1.0f;
	oc_set_font(pig.font);
	oc_set_font_size(fontSize);
	oc_set_color_rgba(1, 1, 1, 1);
	oc_str8 displayStr = OC_STR8("Hello Orca!");
	rec textRec = ToRec(oc_font_text_metrics(pig.font, fontSize, displayStr).ink);
	v2 textPos = center - textRec.size/2 - textRec.topLeft;
	oc_text_fill(textPos.x, textPos.y, displayStr);
	
	oc_surface_select(pig.surface);
	oc_render(pig.canvas);
	oc_surface_present(pig.surface);
}
