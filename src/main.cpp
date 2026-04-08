#include <raylib.h>
#include <rlgl.h>

#include <typedefs.h>

#include <Window.h>

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
    Coloriser::Window MainWindow = Coloriser::Window(
        800,
        600,
        60,
        RAYWHITE,
        "Coloriser");

    MainWindow.InitializeGuiWindow();

    MainWindow.AddNewPane("The Cube");
    MainWindow.AddNewPane("Settings");
    MainWindow.AddNewPane("Image");



    MainWindow.RenderLoop();

    return 0;
}
