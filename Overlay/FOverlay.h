#include "..//main.h"

#ifndef FOverlay_H
#define FOverlay_H

class FOverlay
{
public:
	auto window_set_style()-> void;
	auto window_set_transparency()-> void;
	auto window_set_top_most()-> void;
	auto retrieve_window()->HWND;
	auto window_init()->BOOL;
	auto d2d_shutdown()-> void;
	auto init_d2d()->BOOL;
	auto begin_scene()-> void;
	auto end_scene()-> void;
	auto clear_scene()-> void;
	auto draw_text(int x, int y, const char* str, ...)-> void;
	auto clear_screen()-> void;

};

#endif