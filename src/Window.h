#pragma once

#include <typedefs.h>
#include <Pane.h>

#define MAX_AMOUNT_OF_PANES 10

namespace Coloriser {
    class Window {
    public:
        Pane panes[MAX_AMOUNT_OF_PANES];
        u32 amountOfPanes = 0;

        u32 widht;
        u32 height;
        u32 fps;

        u32 borderThickness = (widht + height)/200;

        Window(
            u32 widht,
            u32 height,
            u32 fps
        );

        // returns index of this pane
        i32 AddNewPane(Pane);
    };
}

