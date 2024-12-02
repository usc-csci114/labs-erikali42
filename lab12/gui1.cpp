#include <nanogui/nanogui.h>
#include <iostream>

using namespace nanogui;

int main(int /* argc */, char ** /* argv */) {
	nanogui::init();

	ref<Screen> screen;
	screen = new Screen(Vector2i(500, 700), "NanoGUI test");
	
	screen->set_visible(true);
	screen->perform_layout();
	nanogui::mainloop(-1);

	nanogui::shutdown();
	return 0;
}