#pragma once

#include <UiObject.h>
#include <typedefs.h>
#include <ColorisingMethod.h>
#include <vector>
#include <raylib.h>

namespace Coloriser {
    class CubeCanvas : public UiObject {
        ColorisingMethod colorisingMethod;

        Color clearColor = RAYWHITE;
        RenderTexture2D renderTexture;
        bool renderTextureExists = false;

        Vector3 cubeLocation = {
            0.0f,
            0.0f,
            0.0f
        };
        f32 cubeSize = 1.0f;

        Camera camera = {
            .position = {
                3.0f,
                2.0f,
                3.0f
            },
            .target = {
                0.0f,
                0.0f,
                0.0f
            },
            .up = (Vector3){0.0f, 1.0f, 0.0f},
            .fovy = 45.0f,
            .projection = CAMERA_PERSPECTIVE
        };

        Vector3 rgbToCubePosition(
            Color color
        );

        Vector2 GetWorldScreenForCurrentRenderTexture(
            Vector3 location
        );

        void DrawJustCube();

        void DrawColorDots();

        void DrawDot(
            Color color,
            Vector3 location
        );

        void DrawPlane();

        void DrawSphere();

        CubeCanvas(
            u32 xPos = 0,
            u32 yPos = 0,
            u32 width = 0,
            u32 heigh = 0,
            u32 borderWidth = 0
        );

    public:
        std::vector<Color> colors;

        CubeCanvas(
            ColorisingMethod method,
            u32 amountOfColors
        );

        // if method is plane amountOfColors will not be taken into acount because always 3 colors will be needed
        void SetNewRenderingMode(
            ColorisingMethod method,
            u32 amountOfColors
        );

        void SetNewAmountOfColors(
            u32 amountOfColors
        );

        void Draw() override;

        void Resize(
            u32 xPos,
            u32 yPos,
            u32 width,
            u32 height,
            u32 borderWidth
        ) override;
    };
}
