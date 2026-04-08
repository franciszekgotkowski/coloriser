#pragma once

#include <UiObject.h>
#include <typedefs.h>
#include <string>

namespace Coloriser {

	class Button : public UiObject {

		std::string text;

		public:
		Button(
			u32 xPos = 0,
			u32 yPos = 0,
			u32 width = 0,
			u32 heigh = 0
		);

		Button(
			std::string text
		);

		void Draw() override;

	};

}