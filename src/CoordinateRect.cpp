#include <raylib.h>
#include <CoordinateRect.h>

namespace Coloriser {

	Rectangle CoordinateRect::RlRect() {
		return (Rectangle){
			.x = (f32)this->xPos,
			.y = (f32)this->yPos,
			.width = (f32)this->width,
			.height = (f32)this->height
		};
	}
}