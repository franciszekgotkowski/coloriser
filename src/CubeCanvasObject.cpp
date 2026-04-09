#include "raylib.h"
#include <CubeCanvasObject.h>

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

    void CubeCanvas::DrawJustCube() {
        DrawCube(
            (Vector3){
                0.0f,
                0.0f,
                0.0f
            },
            1.0f,
            1.0f,
            1.0f,
            RED
        );
    }

    void CubeCanvas::DrawPlane() {
    }

    void CubeCanvas::DrawSphere() {
    }

    void CubeCanvas::Draw() {
        BeginTextureMode(this->renderTexture);
        ClearBackground(this->clearColor);
        BeginMode3D(this->camera);


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
                (f32)this->coordinates.xPos,
                (f32)this->coordinates.yPos
            },
            WHITE
        );
    }
}
