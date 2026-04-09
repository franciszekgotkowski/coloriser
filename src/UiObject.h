#pragma once

#include <CoordinateRect.h>

namespace Coloriser {

	class UiObject {
		protected:
		CoordinateRect coordinates;

		public:
		UiObject(
			u32 xPos,
			u32 yPos,
			u32 width,
			u32 height,
			u32 borderWidth
		);

		virtual void Resize(
			u32 xPos,
			u32 yPos,
			u32 width,
			u32 height,
			u32 borderWidth
		);
		virtual void Draw() = 0;
	};

}