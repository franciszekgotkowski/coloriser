#pragma once

#include <typedefs.h>
#include <Pane.h>

namespace Coloriser {
#define MAX_AMOUNT_OF_PANES 10

    class Window {
    public:
        Pane panes[MAX_AMOUNT_OF_PANES];
        u32 amountOfPanes = 0;

        std::string title;

        u32 widht;
        u32 height;
        u32 fps;
        Color clearColor;

        bool shouldClose = false;

        u32 borderThickness = (widht + height) / 200;

        Window(
            u32 widht,
            u32 height,
            u32 fps,
            Color clearColor,
            std::string title
        );

        // returns index of this pane
        i32 AddNewPane(
            i8 leftNeighbourIdx,
            i8 rightNeighbourIdx,
            i8 UpperNeighbourIdx,
            i8 BelowNeighbourIdx,
            std::string name
        );

        void InitializeGuiWindow();

        void RenderLoop();
    };
}
