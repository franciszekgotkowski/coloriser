#pragma once

#include <raylib.h>
#include <typedefs.h>
#include <Pane.h>
#include <memory>

namespace Coloriser {

	class Window {
		u32 width;
		u32 height;
		u32 fps;

		u32 borderWidth;

		Color clearColor;
		std::string title;

		std::unique_ptr<Pane> rootPane;

		public:
		Window(
			u32 width,
			u32 height,
			u32 fps,
			Color clearColor,
			std::string name,
			std::unique_ptr<Pane> rootPane = nullptr
		);

		void OpenGuiWindow();

		void DrawProgram();

	};

}