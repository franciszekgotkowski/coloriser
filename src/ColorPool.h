#pragma once

#include <vector>
#include <raylib.h>
#include <typedefs.h>
#include <ColorisingMethod.h>

namespace Coloriser {
    class ColorPool {

        Color PlaneFilter(
            Color color
        );

        Color SphereFilter(
            Color color
        );

    public:
    	std::vector<Color> colors;
     	ColorisingMethod colorisingMethod;

        ColorPool(
            ColorisingMethod colorisingMethod,
            u32 amountOfColors = 3
        );

        void SetNewColorisingMethod(
            ColorisingMethod colorisingMethod
        );

        void SetNewAmountOfColors(
            u32 amountOfColors
        );

        void SetColors(
            std::vector<Color> colors
        );

        void SetColor(
            Color color,
            u32 idx
        );

        Color RunColorisingFilter(
            Color color
        );

    };

}
