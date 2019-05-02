#include "src/baseHeader.h"
#include "NkWindow.h"
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#include "nuklear.h"
#include "nuklear_glfw_gl3.h"


#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])


NkWindow::NkWindow(GLFWwindow * window,Options *options)
{
	this->window = window;
	this->options = options;
}

NkWindow::~NkWindow()
{
}

void NkWindow::init()
{
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to setup GLEW\n");
		exit(1);
	}
	ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
	{struct nk_font_atlas *atlas;
	nk_glfw3_font_stash_begin(&atlas);
	nk_glfw3_font_stash_end(); }

}

void NkWindow::update()
{

	/* GUI */
	if (nk_begin(ctx, "Demo", nk_rect(0, 0, 800, 100),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

        static int property = 20;
        nk_layout_row_static(ctx, 30, 80, 1);
//		if (nk_button_label(ctx, "pauseresume"))
//		{
//			options->paused = !options->paused;
//		}
        if (!options->gameOver) {
            std::string str = "points: " + std::to_string(options->points);
            nk_button_label(ctx, str.c_str());
        }else{
            nk_button_label(ctx, "Game Over");

        }
		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_float(ctx, "ambientStrength:", 0, &options->ambientStrength, 1, 0.01f, 0.01f);
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, "background:", NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 25, 1);

		struct nk_color background = nk_rgb(options->ambientColor.r, options->ambientColor.g, options->ambientColor.b);

		if (nk_combo_begin_color(ctx, background, nk_vec2(nk_widget_width(ctx), 400))) {
			nk_layout_row_dynamic(ctx, 120, 1);
			background = nk_color_picker(ctx, background, NK_RGB);
			nk_layout_row_dynamic(ctx, 25, 1);
			background.r = (nk_byte)nk_propertyi(ctx, "#R:", 0, background.r, 255, 1, 1);
			background.g = (nk_byte)nk_propertyi(ctx, "#G:", 0, background.g, 255, 1, 1);
			background.b = (nk_byte)nk_propertyi(ctx, "#B:", 0, background.b, 255, 1, 1);

			options->ambientColor = glm::vec3(background.r, background.g, background.b);

			nk_combo_end(ctx);
		}
	}
	nk_end(ctx);
	nk_glfw3_new_frame();
}

void NkWindow::render()
{
	nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}
