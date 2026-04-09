#pragma once

#include <memory>
#include <string>
#include <typedefs.h>

#include <UiObject.h>

namespace Coloriser {
    class GroupBox : public UiObject {
        std::string text;
        std::unique_ptr<UiObject> guiObject;
        u32 borderWidth;
        CoordinateRect canvasCoordinates;

    public:
        GroupBox(
            u32 xPos = 0,
            u32 yPos = 0,
            u32 width = 0,
            u32 heigh = 0,
            u32 borderWidth = 0
        );

        GroupBox(
            std::string text
        );

        GroupBox(
            std::string text,
            std::unique_ptr<UiObject> guiObject,
            u32 borderWidth
        );

        void Resize(
            u32 xPos,
            u32 yPos,
            u32 width,
            u32 height,
            u32 borderWidth
        ) override;

        void Draw() override;
    };
}
