#include <nanogui/nanogui.h>
#include <nanogui/graph.h>
#include <iostream>

using namespace nanogui;

double amp = 1;
double freq = 1;

void calc_sin(std::vector<float> &func)
{
	func.resize(100);
	for (int i = 0; i < 100; ++i){
		double x = 2*M_PI*i/100;
		func[i] = 0.5f* amp * std::sin(freq*x) + 0.5*amp;
	}
}

int main(int /* argc */, char ** /* argv */) {
	nanogui::init();

	ref<Screen> screen;
	screen = new Screen(Vector2i(1200, 800), "NanoGUI test");
	
	auto window = new Window(screen, "Graphing Test");
	window->set_position(Vector2i(15,15));
	window->set_layout(new GroupLayout());
	
	TabWidget* tab_widget = window->add<TabWidget>();
	
	Widget* layer = new Widget(tab_widget);
	GridLayout *layout =
		new GridLayout(Orientation::Horizontal, 5,
					   Alignment::Middle, 15, 5);
	layout->set_col_alignment(
		{ Alignment::Maximum, Alignment::Fill });
	layout->set_spacing(0, 10);
	layer->set_layout(layout);
	
	Graph *graph = layer->add<Graph>("");
	graph->set_fixed_size(Vector2i(600,400));
	calc_sin(graph->values());
	
	{
		new Label(layer, "Amplitude :", "sans-bold");
		auto text_box = new TextBox(layer);
		text_box->set_editable(true);
		text_box->set_fixed_size(Vector2i(100, 20));
		text_box->set_value("1");
		text_box->set_default_value("0.0");
		text_box->set_font_size(16);
		text_box->set_format("[-]?[0-9]*\\.?[0-9]+");
		text_box->set_callback([graph](const std::string& s) -> bool {
			amp = stod(s);
			calc_sin(graph->values());
			return true;
		});
	}
	{
		new Label(layer, "Frequency :", "sans-bold");
		auto text_box = new TextBox(layer);
		text_box->set_editable(true);
		text_box->set_fixed_size(Vector2i(100, 20));
		text_box->set_value("1");
		text_box->set_default_value("0.0");
		text_box->set_font_size(16);
		text_box->set_format("[-]?[0-9]*\\.?[0-9]+");
		text_box->set_callback([graph](const std::string& s) -> bool {
			freq = stod(s);
			calc_sin(graph->values());
			return true;
		});
	}
	tab_widget->append_tab("Sin Function", layer);
		
	tab_widget->set_callback([tab_widget, screen, graph] (int id) mutable {
		std::cout << "tab_widget callback..." << std::endl;
		calc_sin(graph->values());
		screen->perform_layout();
	});
	
	screen->set_visible(true);
	screen->perform_layout();
	nanogui::mainloop(-1);

	nanogui::shutdown();
	return 0;
}