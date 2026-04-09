#include <GroupBoxObject.h>
#include <raygui.h>
#include <iostream>

namespace Coloriser {
    GroupBox::GroupBox(
        u32 xPos,
        u32 yPos,
        u32 width,
        u32 height
    ) : UiObject(
        xPos,
        yPos,
        width,
        height
    ) {
    }

    GroupBox::GroupBox(
        std::string text
    ) : GroupBox() {
        this->text = text;
    }

    GroupBox::GroupBox(
        std::string txt,
        std::unique_ptr<UiObject> guiObject,
        u32 borderWidth
    ) : GroupBox() {
        this->text = txt;
        this->guiObject = std::move(guiObject);
        this->borderWidth = borderWidth;
        this->canvasCoordinates = {
            .xPos = this->coordinates.xPos + borderWidth,
            .yPos = this->coordinates.yPos + borderWidth,
            .width = this->coordinates.width - 2 * borderWidth,
            .height = this->coordinates.height - 2 * borderWidth,
        };
        this->guiObject->Resize(
            this->canvasCoordinates.xPos,
            this->canvasCoordinates.yPos,
            this->canvasCoordinates.width,
            this->canvasCoordinates.height
        );
    }

    void GroupBox::Draw() {
        GuiGroupBox(
            this->coordinates.RlRect(),
            this->text.c_str()
        );
        if (this->guiObject) {
            this->guiObject->Draw();
        }
    }
}
