#pragma once
#include "imgui.h"

static inline ImVec4 main_color(0.7f, 0.f, 0.f, 1.f);
static inline ImVec4 color_particle(0.7f, 0.f, 0.f, 1.f);

static inline ImColor background_color(24, 24, 24, 255);

static inline ImVec4 second_color(0.09f, 0.09f, 0.09f, 1.f);


static inline ImVec2 frame_size = ImVec2(605, 65);

static inline float anim_speed = 8.f;

static inline bool draw_grind;

static inline float pos_offset;
static inline bool size_change;

static inline ImFont* icon_font;
static inline ImFont* tab_font;
static inline ImFont* hint_font;
static inline ImFont* second_font;
