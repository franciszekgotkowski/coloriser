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


		Color clearColor;
		std::string title;


		public:
		u32 borderWidth;
		std::unique_ptr<Pane> rootPane;

		Window(
			u32 width,
			u32 height,
			u32 fps,
			Color clearColor,
			std::string name,
			std::unique_ptr<Pane> rootPane = nullptr
		);

		void OpenGuiWindow();

		// after pane percentages for children are changed run this to update all panes
		void UpdatePanesToNewSizes();

		void DrawProgram();

	};

}