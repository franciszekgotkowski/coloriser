#include <ButtonObject.h>
#include <ColorPool.h>
#include <ColorisingMethod.h>
#include <GroupBoxObject.h>
#include <Matrix3x3.h>
#include <Pane.h>
#include <Window.h>
#include <cstdio>
#include <raylib.h>
#include <rlgl.h>
#include <typedefs.h>
#include <math.h>
#include <memory>
#include <raymath.h>

#include <CubeCanvasObject.h>
#include <ColorPool.h>
#include <v3.h>

typedef struct {
    Vector3 position;
    Color color;
} Edge;

Vector3 ColorToPosition(Color col) {
    return (Vector3){
        .x = ((f32) col.r / 255.0f) - 0.5f,
        .y = ((f32) col.g / 255.0f) - 0.5f,
        .z = ((f32) col.b / 255.0f) - 0.5f,
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


void updatePosition(Triangle *tri) {
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
    Coloriser::Window window = Coloriser::Window(
        800,
        600,
        60,
        RAYWHITE,
        "Coloriser",
        std::make_unique<Coloriser::Pane>(
            "BUTTON PANE",
            std::make_unique<Coloriser::Button>("B1")
        )
    );

    Coloriser::Matrix3x3 m1 = Coloriser::NewMatrix(
        (Vector3){1.0f, 0.0f, 2.0f},
        (Vector3){0.0f, 1.0f, 0.0f},
        (Vector3){3.0f, 0.0f, 7.0f}
    );
    Coloriser::printMatrix(m1);
    Coloriser::printMatrix(
        Coloriser::InvertMatrix(m1)
    );
    Coloriser::Matrix3x3 m2 = Coloriser::NewMatrix(
        (Vector3){1.0f, 2.0f, 3.0f},
        (Vector3){0.0f, 1.0f, 4.0f},
        (Vector3){0.0f, 0.0f, 1.0f}
    );
    Coloriser::printMatrix(m2);
    Coloriser::printMatrix(
        Coloriser::InvertMatrix(m2)
    );
    Coloriser::Matrix3x3 m3 = Coloriser::NewMatrix(
        (Vector3){1.0f, 2.0f, 1.0f},
        (Vector3){2.0f, 5.0f, 2.0f},
        (Vector3){1.0f, 2.0f, 2.0f}
    );
    Coloriser::printMatrix(m3);
    Coloriser::printMatrix(
        Coloriser::InvertMatrix(m3)
    );

    std::shared_ptr<Coloriser::ColorPool> colors = std::make_shared<Coloriser::ColorPool>(
        Coloriser::ColorisingMethod::PLANE
    );

    window.rootPane->AssignChildPane(
        std::make_unique<Coloriser::Pane>(
            "SECOND PANE",
            std::make_unique<Coloriser::Button>("B2")
        ),
        30,
        Coloriser::Direction::DOWN
    );
    window.rootPane->childPane->AssignChildPane(
        std::make_unique<Coloriser::Pane>(
            "THIRD PANE",
            std::make_unique<Coloriser::GroupBox>(
                "B3",
                std::make_unique<Coloriser::CubeCanvas>(
                    Coloriser::ColorisingMethod::PLANE,
                    3,
                    colors
                ),
                window.borderWidth
            )
        ),
        50,
        Coloriser::Direction::RIGHT
    );
    window.OpenGuiWindow();
    window.rootPane->ResetCoordinateVariables();

    while (!WindowShouldClose()) {
        // colors->colors[0].r = 100 + 100 * sin(2*GetTime());
        // colors->colors[0].b = 150 + 50 * cos(2*GetTime());

        // colors->colors[1].g = 128 + 127 * cos(GetTime());

        window.DrawProgram();
    }
}
