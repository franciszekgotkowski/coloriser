#include <ButtonObject.h>
#include <UiObject.h>
#include <iostream>
#include <raygui.h>

namespace Coloriser {


	Button::Button(
		u32 xPos,
		u32 yPos,
		u32 width,
		u32 height
	) : UiObject(
		xPos,
		yPos,
		width,
		height
	) {}

	void Button::Draw() {
		if ( GuiButton(
			this->coordinates.RlRect(),
			"Click me!"
		)) {
			std::cout << "clicked!\n" ;
		}
	}

}