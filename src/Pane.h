#pragma once

#include <raylib.h>
#include <string>
#include <typedefs.h>
#include <UiObject.h>
#include <memory>

namespace Coloriser{
	enum class Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN,

		UNKNOWN,

		AMOUNT_OF_DIRECTIONS
	};

	class Pane {
		CoordinateRect paneCoordinates;
		CoordinateRect canvasCoordinates;

		std::string name;

		std::unique_ptr<UiObject> uiObject;

		u32 percentOfCanvasForChild = 50;
		Direction whereIsChild = Direction::UNKNOWN;
		std::unique_ptr<Pane> childPane;

		public:
		Pane(
			u32 xPos = 0,
			u32 yPos = 0,
			u32 width = 0,
			u32 heigth = 0,
			u32 borderWidth = 0,
			std::string name = "ERROR: NO NAME",
			std::unique_ptr<UiObject> uiObject = nullptr
		);

		Pane(
			std::string name,
			std::unique_ptr<UiObject> uiObject
		);

		// If there is some window resize or function initialization this function will be called
		// It (based on the data it recieved) sets new coordinates for position and child width and height. This function will be used recursively for updating UI
		void SetNewCoordinateVariables (
			u32 xPos,
			u32 yPos,
			u32 width,
			u32 heigth,
			u32 borderWidth
		);

		void AssignUiObject (
			std::unique_ptr<UiObject> uiObject
		);

		// you need to be in raylibs drawing mode to start
		void Draw();
	};
}