#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <rlgl.h>
#include <typedefs.h>

#include "Window.h"

const i32 screenWidth = 800;
const i32 screenHeight = 600;
const u32 borderWidth = (screenHeight + screenWidth) / (2 * 100);

bool isWindowOpen = true;

i32 egde = 0;

typedef struct {
    Vector3 position;
    Color color;
} Edge;

Vector3 ColorToPosition(Color col) {
    return (Vector3){
        .x = ((f32)col.r / 255.0f) - 0.5f,
        .y = ((f32)col.g / 255.0f) - 0.5f,
        .z = ((f32)col.b / 255.0f) - 0.5f,
    };
}

typedef union {
    struct {
        Edge e1;
        Edge e2;
        Edge e3;
    };

    Edge arr[3];
} Triangle;


void updatePosition(Triangle* tri) {
    tri->e1.position = ColorToPosition(tri->e1.color);
    tri->e2.position = ColorToPosition(tri->e2.color);
    tri->e3.position = ColorToPosition(tri->e3.color);
}

void Draw3dTriangle(Triangle triangle) {
    rlBegin(RL_TRIANGLES);

    rlColor4ub(triangle.e1.color.r, triangle.e1.color.g, triangle.e1.color.b, triangle.e1.color.a);
    rlVertex3f(triangle.e1.position.x, triangle.e1.position.y, triangle.e1.position.z);

    rlColor4ub(triangle.e2.color.r, triangle.e2.color.g, triangle.e2.color.b, triangle.e2.color.a);
    rlVertex3f(triangle.e2.position.x, triangle.e2.position.y, triangle.e2.position.z);

    rlColor4ub(triangle.e3.color.r, triangle.e3.color.g, triangle.e3.color.b, triangle.e3.color.a);
    rlVertex3f(triangle.e3.position.x, triangle.e3.position.y, triangle.e3.position.z);

    rlEnd();
}

int main() {
    InitWindow(screenWidth, screenHeight, "raygui - controls test suite");
    SetTargetFPS(60);

    Camera cameraPlayer1 = {};
    cameraPlayer1.fovy = 45.0f;
    cameraPlayer1.up.y = 1.0f;
    cameraPlayer1.target.x = 0.0f;
    cameraPlayer1.target.y = 0.0f;
    cameraPlayer1.position.z = -3.0f;
    cameraPlayer1.position.y = 2.0f;

    RenderTexture screenPlayer1 = LoadRenderTexture((screenWidth - 3 * borderWidth) / 2,
                                                    (screenHeight - 2 * borderWidth));
    Rectangle splitScreenRect = {
        (f32)borderWidth, (f32)borderWidth, (float)screenPlayer1.texture.width, (float)-screenPlayer1.texture.height
    };

    int vertexIndex = 1;

    Triangle tri = {
        .e1 = {
            .position = {-0.5f, -0.5f, 0.5f},
            .color = (Color){0, 0, 255, 255}
        },
        .e2 = {
            .position = {-0.5f, 0.5f, -0.5f},
            .color = (Color){0, 255, 0, 255}
        },
        .e3 = {
            .position = {0.5f, -0.5f, -0.5f},
            .color = (Color){255, 0, 0, 255}
        },
    };

    rlDisableBackfaceCulling();

    int editMode = true;
    while (!WindowShouldClose()) {
        cameraPlayer1.position.x = 3 * cos(GetTime() / 5);
        cameraPlayer1.position.z = 3 * sin(GetTime() / 5);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        Rectangle cube = {
            .x = (f32)borderWidth,
            .y = (f32)borderWidth,
            .width = (f32)(screenWidth - 3 * borderWidth) / 2,
            .height = (f32)(screenHeight - 2 * borderWidth)
        };
        GuiGroupBox(cube, "cube");

        Rectangle menu = {
            .x = (f32)((screenWidth - 3 * borderWidth) / 2 + borderWidth * 2),
            .y = (f32)borderWidth,
            .width = (f32)(screenWidth - 3 * borderWidth) / 2,
            .height = (f32)(screenHeight - 3 * borderWidth) / 2
        };
        GuiGroupBox(menu, "menu");


        Rectangle image = {
            .x = (f32)((screenWidth - 3 * borderWidth) / 2 + borderWidth * 2),
            .y = (f32)(screenHeight - 3 * borderWidth) / 2 + borderWidth * 2,
            .width = (f32)(screenWidth - 3 * borderWidth) / 2,
            .height = (f32)(screenHeight - 3 * borderWidth) / 2
        };
        GuiGroupBox(image, "image");


        Rectangle spinner = {500, 400, 100, 50};
        editMode = GuiSpinner(spinner, "value", &vertexIndex, 0, 2, editMode);
        if (editMode) {
            printf("spinner = %d\n", editMode);
            editMode = !editMode;
        }

        //
        // Rectangle R = {500, 500, 100, 20};
        // Rectangle G = {500, 530, 100, 20};
        // Rectangle B = {500, 560, 100, 20};
        //
        // tempR = GuiSliderBar(R, "0", "255", &tempR, 0.0f, 255.0f);
        // tempG = GuiSliderBar(G, "0", "255", &tempG, 0.0f, 255.0f);
        // tempB = GuiSliderBar(B, "0", "255", &tempB, 0.0f, 255.0f);
        //
        // tri.arr[vertexIndex].color.r = (u8)tempR;
        // tri.arr[vertexIndex].color.g = (u8)tempG;
        // tri.arr[vertexIndex].color.b = (u8)tempB;
        //
        tri.arr[0].color.b = 128 + 127 * sin(1.2 * GetTime());
        tri.arr[0].color.g = 128 + 127 * cos(0.2 * GetTime());
        tri.arr[0].color.r = 128 + 127 * sin(4.0 * GetTime());

        tri.arr[1].color.b = 128 + 127 * cos(GetTime());
        tri.arr[1].color.g = 128 + 127 * sin(GetTime());
        tri.arr[1].color.r = 128 + 127 * sin(GetTime());

        tri.arr[2].color.b = 128 + 127 * sin(GetTime());
        tri.arr[2].color.g = 128 + 127 * sin(GetTime());
        tri.arr[2].color.r = 128 + 127 * cos(GetTime());

        updatePosition(&tri);


        BeginTextureMode(screenPlayer1);
        ClearBackground(RAYWHITE);

        BeginMode3D(cameraPlayer1);

        DrawCubeWires((Vector3){0.0f, 0.0f, 0.0f}, 1, 1, 1, LIGHTGRAY);
        DrawGrid(16, 1.0f / 8.0f);
        Draw3dTriangle(tri);

        EndMode3D();
        EndTextureMode();
        DrawTextureRec(screenPlayer1.texture, splitScreenRect, (Vector2){0, 0}, WHITE);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
