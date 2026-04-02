#include <cstring>
#include <Window.h>
#include <range.h>

Coloriser::Window::Window(
    u32 widht,
    u32 height,
    u32 fps,
    Color clearColor,
    std::string title
) {
    this->widht = widht;
    this->height = height;
    this->fps = fps;
    this->clearColor = clearColor;
    this->title = title;
}

i32 Coloriser::Window::AddNewPane(
    i8 leftNeighbourIdx,
    i8 rightNeighbourIdx,
    i8 UpperNeighbourIdx,
    i8 BelowNeighbourIdx,
    std::string name
) {
    if (this->amountOfPanes >= MAX_AMOUNT_OF_PANES) {
        return -1;
    }

    this->panes[this->amountOfPanes] = Pane(
        leftNeighbourIdx,
        rightNeighbourIdx,
        UpperNeighbourIdx,
        BelowNeighbourIdx,
        name
    );
    this->amountOfPanes++;
    return this->amountOfPanes - 1;
}

void Coloriser::Window::InitializeGuiWindow() {
    InitWindow(
        this->widht,
        this->height,
        this->title.c_str()
    );

    SetTargetFPS(this->fps);
}

void Coloriser::Window::RenderLoop() {
    while (!this->shouldClose) {
        BeginDrawing();

        ClearBackground(this->clearColor);

        for range(i, this->amountOfPanes) {
            this->panes[i].DrawOutline();
        }

        EndDrawing();
        this->shouldClose = WindowShouldClose();
    }
}
