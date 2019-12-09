#include "main.h"

static void render(FOverlay* overlay)
{

	while (TRUE)
	{
		std::cout << "render loop is running..." << std::endl;
		overlay->begin_scene();

		overlay->clear_scene();

		overlay->draw_text(300, 300, "helloWorld");

		overlay->end_scene();
	}

	return;
}


static void _init(FOverlay* overlay)
{
	// Initialize the window
	if (!overlay->window_init())
		return;

	// D2D Failed to initialize?
	if (!overlay->init_d2d())
		return;

	// Jump into the main render
	render(overlay);

	overlay->d2d_shutdown();

	return;
}


int main()
{
	FOverlay* overlay = { 0 };
	_init(overlay);

	std::cin.get();
}
