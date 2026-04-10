#include <raylib.h>
#include <CubeCanvasObject.h>
#include <range.h>
#include <math.h>

namespace Coloriser {
    CubeCanvas::CubeCanvas(
        u32 xPos,
        u32 yPos,
        u32 width,
        u32 heigh,
        u32 borderWidth
    ) : UiObject(
        xPos,
        yPos,
        width,
        heigh,
        borderWidth
    ) {
        this->Resize(
            xPos,
            yPos,
            width,
            heigh,
            borderWidth
        );
    }

    CubeCanvas::CubeCanvas(
        ColorisingMethod method,
        u32 amountOfColors
    ) : CubeCanvas() {
        this->SetNewRenderingMode(
            method,
            amountOfColors
        );
    }

    // if method is plane amountOfColors will not be taken into acount because always 3 colors will be needed
    void CubeCanvas::SetNewRenderingMode(
        ColorisingMethod method,
        u32 amountOfColors
    ) {
        this->colorisingMethod = method;

        if (this->colorisingMethod == ColorisingMethod::PLANE) {
            this->SetNewAmountOfColors(3);
            this->colors[0] = RAYWHITE;
            this->colors[1] = PINK;
            this->colors[2] = BROWN;
        } else if (this->colorisingMethod == ColorisingMethod::SPHERE) {
            this->SetNewAmountOfColors(amountOfColors);
        }
    }

    void CubeCanvas::SetNewAmountOfColors(
        u32 amountOfColors
    ) {
        this->colors.resize(amountOfColors);
    }

    void CubeCanvas::Resize(
        u32 xPos,
        u32 yPos,
        u32 width,
        u32 height,
        u32 borderWidth
    ) {
        this->coordinates = {
            .xPos = xPos,
            .yPos = yPos,
            .width = width,
            .height = height
        };

        if (this->renderTextureExists) {
            UnloadRenderTexture(this->renderTexture);
            this->renderTextureExists = false;
        }
        this->renderTexture = LoadRenderTexture(
            width,
            height
        );
        this->renderTextureExists = true;
    }

    Vector3 CubeCanvas::rgbToCubePosition(
        Color color
    ) {
        Vector3 cubeBase = {
            this->cubeLocation.x - this->cubeSize / 2.0f,
            this->cubeLocation.y - this->cubeSize / 2.0f,
            this->cubeLocation.z - this->cubeSize / 2.0f
        };

        Vector3 colorOffsets = {
            ((f32) color.r / 255.0f) * this->cubeSize,
            ((f32) color.g / 255.0f) * this->cubeSize,
            ((f32) color.b / 255.0f) * this->cubeSize
        };

        return (Vector3){
            cubeBase.x + colorOffsets.x,
            cubeBase.y + colorOffsets.y,
            cubeBase.z + colorOffsets.z
        };
    }

    void CubeCanvas::DrawJustCube() {
        DrawCube(
            this->cubeLocation,
            this->cubeSize,
            this->cubeSize,
            this->cubeSize,
            RED
        );
    }

    Vector2 CubeCanvas::GetWorldScreenForCurrentRenderTexture(
        Vector3 location
    ) {
        // Vector3 position, Camera camera, int width, int height
        return GetWorldToScreenEx(
            location,
            this->camera,
            this->renderTexture.texture.width,
            this->renderTexture.texture.height
            );
    }

    void CubeCanvas::DrawDot(
        Color color,
        Vector3 location
    ) {
        Vector2 screenspacePosition = this->GetWorldScreenForCurrentRenderTexture(
            location
        );

        DrawCircleV(
            screenspacePosition,
            (f32) ((this->renderTexture.texture.width + this->renderTexture.texture.width) / 100 + 1),
            BLACK
        );
        DrawCircleV(
            screenspacePosition,
            (f32) ((this->renderTexture.texture.width + this->renderTexture.texture.width) / 100),
            color
        );
    }

    void CubeCanvas::DrawColorDots() {
        for range(i, this->colors.size()) {
            Color c = this->colors[i];
            c.a = 255;
            DrawDot(
                c,
                this->rgbToCubePosition(this->colors[i])
            );
        }
    }

    void CubeCanvas::DrawPlane() {
    }

    void CubeCanvas::DrawSphere() {
    }

    void CubeCanvas::Draw() {
        BeginTextureMode(this->renderTexture);
        ClearBackground(this->clearColor);
        BeginMode3D(this->camera);

        this->camera.position.x = 3 * sin(GetTime());
        this->camera.position.z = 3 * cos(GetTime());

        this->DrawJustCube();
        switch (this->colorisingMethod) {
            case ColorisingMethod::PLANE:
                this->DrawPlane();
                break;
            case ColorisingMethod::SPHERE:
                this->DrawSphere();
                break;
        }

        EndMode3D();
        this->DrawColorDots();

        EndTextureMode();

        DrawTextureRec(
            this->renderTexture.texture,
            (Rectangle){
                .x = 0.0f,
                .y = 0.0f,
                .width = (f32) this->renderTexture.texture.width,
                .height = (f32) -this->renderTexture.texture.height
            },
            (Vector2){
                (f32) this->coordinates.xPos,
                (f32) this->coordinates.yPos
            },
            WHITE
        );
    }
}
