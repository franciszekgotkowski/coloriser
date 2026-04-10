#pragma once

#include <vector>
#include <raylib.h>
#include <typedefs.h>
#include <ColorisingMethod.h>

namespace Coloriser {
    class ColorPool {
        std::vector<Color> colors;
        ColorisingMethod colorisingMethod;

        Color PlaneFilter(
            Color color
        );

        Color SphereFilter(
            Color color
        );

    public:
        ColorPool(
            ColorisingMethod colorisingMethod,
            u32 amountOfColors
        );

        void SetNewColorisingMethod(
            ColorisingMethod colorisingMethod
        );

        void SetNewAmountOfColord(
            u32 amountOfColors
        );

        void SetColors(
            std::vector<Color> colors
        );

        void SetColor(
            Color color
        );

        Color RunColorisingFilter(
            Color color
        );
    };
}
