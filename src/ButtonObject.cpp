#include <ButtonObject.h>
#include <UiObject.h>
#include <iostream>
#include <raygui.h>

namespace Coloriser {
    Button::Button(
        u32 xPos,
        u32 yPos,
        u32 width,
        u32 height,
        u32 borderWidth
    ) : UiObject(
        xPos,
        yPos,
        width,
        height,
        borderWidth
    ) {}

    Button::Button(
        std::string text
    ) : Button() {
        this->text = text;
    }

    void Button::Draw() {
        if (GuiButton(
            this->coordinates.RlRect(),
            this->text.c_str()
        )) {
            std::cout << "clicked!\t" << this->text << std::endl;
        }
    }
}
