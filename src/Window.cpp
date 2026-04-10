#include <typedefs.h>
#include <Window.h>
#include <raylib.h>
#include <utility>

namespace Coloriser {

	Window::Window (
		u32 width,
		u32 height,
		u32 fps,
		Color clearColor,
		std::string title,
		std::unique_ptr<Pane> rootPane
	) {

		this->borderWidth = (width + height) / 200;

		this->width = width;
		this->height = height;
		this->fps = fps;
		this->clearColor = clearColor;
		this->title = title;

		if (rootPane) {
			this->rootPane = std::move(rootPane);
		}
		this->rootPane->SetNewCoordinateVariables(
			borderWidth,
			borderWidth,
			this->width - 2 * borderWidth,
			this->height - 2 * borderWidth,
			this->borderWidth
		);
	}

	void Window::OpenGuiWindow() {
		SetConfigFlags(FLAG_WINDOW_HIGHDPI);
		InitWindow(
			this->width,
			this->height,
			this->title.c_str()
		);
		SetTargetFPS(this->fps);
	}

	void Window::DrawProgram() {
		BeginDrawing();
		ClearBackground(this->clearColor);
		if (this->rootPane) {
			this->rootPane->Draw();
		}
		EndDrawing();
	}

	void Window::UpdatePanesToNewSizes() {
		if (this->rootPane) {
			this->rootPane->ResetCoordinateVariables();
		}
	}
}
