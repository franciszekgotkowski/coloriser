#include <CoordinateRect.h>
#include <UiObject.h>

namespace Coloriser {

	void UiObject::Resize(
		u32 xPos,
		u32 yPos,
		u32 width,
		u32 height
	) {
		this->coordinates = (CoordinateRect) {
			.xPos = xPos,
			.yPos = yPos,
			.width = width,
			.height = height
		};
	}

	UiObject::UiObject(
		u32 xPos,
		u32 yPos,
		u32 width,
		u32 height
	) {
		this->Resize(
			xPos,
			yPos,
			width,
			height
		);
	}
}