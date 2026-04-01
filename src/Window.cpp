#include <Window.h>

Coloriser::Window::Window(
    u32 widht,
    u32 height,
    u32 fps
) {
    this->widht = widht;
    this->height = height;
    this->fps = fps;
}

i32 Coloriser::Window::AddNewPane(Pane pane) {
    if (this->amountOfPanes >= MAX_AMOUNT_OF_PANES) {
        return -1;
    }

    this->panes[this->amountOfPanes] = pane;
    this->amountOfPanes++;
    return this->amountOfPanes-1;
}
