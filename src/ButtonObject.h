#pragma once

#include <UiObject.h>
#include <typedefs.h>

namespace Coloriser {

	class Button : public UiObject {

		public:
		Button(
			u32 xPos = 0,
			u32 yPos = 0,
			u32 width = 0,
			u32 heigh = 0
		);

		void Draw() override;

	};

}