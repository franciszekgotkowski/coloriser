#pragma once

#include <raylib.h>
#include <typedefs.h>

namespace Coloriser {

	class CoordinateRect{
		public:
		u32 xPos;
		u32 yPos;
		u32 width;
		u32 height;

		Rectangle RlRect();
	};

}