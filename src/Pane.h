#pragma once

#include <typedefs.h>

namespace Coloriser {
    enum class PaneNeighbour {
        LEFT,
        RIGHT,
        UP,
        DOWN,

        AMOUNT_OF_DIRECTIONS
    };

    class Pane {
        PaneNeighbour paneNeighboursIdx[(u32)PaneNeighbour::AMOUNT_OF_DIRECTIONS];

        u32 x;
        u32 y;
        u32 widht;
        u32 height;

        bool active = false; // this field is to tell if object have been activated or is it just an array filler

    public:
        Pane(
            u32 x,
            u32 y,
            u32 width,
            u32 height
        );

        Pane();
    };
}
