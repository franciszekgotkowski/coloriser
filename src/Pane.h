#pragma once

#include <typedefs.h>
#include <raylib.h>
#include <PaneContents.h>

#include <string>
#include <memory>

namespace Coloriser {
    enum class PaneNeighbour {
        LEFT,
        RIGHT,
        UP,
        DOWN,

        AMOUNT_OF_DIRECTIONS
    };

    enum class MouseRelativePosition {
        INSIDE,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        DIAGONALL,

        AMOUNT_OF_DIRECTIONS
    };

    class Pane {
    public:
        PaneNeighbour paneNeighboursIdx[(u32)PaneNeighbour::AMOUNT_OF_DIRECTIONS];
        std::string name;

        u32 x = 0;
        u32 y = 0;
        u32 widht = 0;
        u32 height = 0;

        i8 leftNeighbourIdx = -1;
        i8 rightNeighbourIdx = -1;
        i8 upperNeighbourIdx = -1;
        i8 belowNeighbourIdx = -1;

        bool active = false; // this field is to tell if object have been activated or is it just an array filler

        Pane(
            i8 leftNeighbourIdx,
            i8 rightNeighbourIdx,
            i8 upperNeighbourIdx,
            i8 belowNeighbourIdx,
            std::string name
        );

        Pane();

        MouseRelativePosition RelativeMousePosition(
            Vector2 mousePosition
        );

        void DrawOutline();

        std::unique_ptr<Coloriser::PaneContents> contents;
    };
}
