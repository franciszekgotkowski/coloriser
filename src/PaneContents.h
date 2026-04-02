#pragma once

namespace Coloriser{
    class Pane;

    class PaneContents {
        const Coloriser::Pane* parent;

    public:
        virtual void Draw() = 0;

        PaneContents(
            Coloriser::Pane* parent
        );
    };

}
