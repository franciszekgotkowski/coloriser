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
            std::string name
        );

        // Connections are placed in square grid with the size of MAX_AMOUNT_OF_PANES
        // Only top right triangle will be looked at because connections are 2 directional
        //    0  1  2  3 x
        // 0  0  1  0  0
        // 1  0  1  1  0
        // 2  0  0  0  0
        // 3  0  0  0  0
        // y
        // This means that
        void LoadInPaneConnections(bool* connections);

        void InitializeGuiWindow();

        void RenderLoop();
    };
}
