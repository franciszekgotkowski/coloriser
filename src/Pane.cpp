#include <Pane.h>

#include <typedefs.h>

Coloriser::Pane::Pane(
    u32 x,
    u32 y,
    u32 width,
    u32 height
) {
    this->x = x;
    this->y = y;
    this->widht = width;
    this->height = height;
    this->active = true;
}

Coloriser::Pane::Pane() {
    this->x = 0;
    this->y = 0;
    this->widht = 0;
    this->height = 0;
    this->active = false;
}