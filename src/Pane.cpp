#include <Pane.h>
#include <typedefs.h>
#include <range.h>

#include <raylib.h>
#include <raygui.h>

Coloriser::Pane::Pane(
    std::string name
) {
    this->name = name;
}

Coloriser::Pane::Pane() {
    this->x = 0;
    this->y = 0;
    this->widht = 0;
    this->height = 0;
    this->active = false;
    this->name = "NO NAME";
}


Coloriser::MouseRelativePosition Coloriser::Pane::RelativeMousePosition(
    Vector2 mousePosition
) {
    u32 mouseX = (u32)mousePosition.x;
    u32 mouseY = (u32)mousePosition.y;

    bool relativeMousePos[3][3] = {
        {true, true, true},
        {true, true, true},
        {true, true, true}
    };

    if (mouseY > this->y + this->height) {
        // mouse below pane
        for range(xpos, 3) {
            relativeMousePos[0][xpos] = false;
            relativeMousePos[1][xpos] = false;
        }
    }
    else if (mouseY >= this->y) {
        // mouse on Y level of Pane
        for range(xpos, 3) {
            relativeMousePos[0][xpos] = false;
            relativeMousePos[2][xpos] = false;
        }
    }
    else {
        // mouse above pane
        for range(xpos, 3) {
            relativeMousePos[1][xpos] = false;
            relativeMousePos[2][xpos] = false;
        }
    }

    if (mouseX > this->x + this->widht) {
        // mouse right from pane
        for range(ypos, 3) {
            relativeMousePos[ypos][0] = false;
            relativeMousePos[ypos][1] = false;
        }
    }
    else if (mouseX >= this->x) {
        // mouse on X level of Pane
        for range(ypos, 3) {
            relativeMousePos[ypos][0] = false;
            relativeMousePos[ypos][2] = false;
        }
    }
    else {
        // mouse left from pane
        for range(ypos, 3) {
            relativeMousePos[ypos][1] = false;
            relativeMousePos[ypos][2] = false;
        }
    }

    if (relativeMousePos[0][0] ||
        relativeMousePos[0][2] ||
        relativeMousePos[2][0] ||
        relativeMousePos[2][2]) {
        return MouseRelativePosition::DIAGONALL;
    }

    if (relativeMousePos[0][1]) {
        return MouseRelativePosition::UP;
    }

    if (relativeMousePos[2][1]) {
        return MouseRelativePosition::DOWN;
    }

    if (relativeMousePos[1][2]) {
        return MouseRelativePosition::RIGHT;
    }

    if (relativeMousePos[1][0]) {
        return MouseRelativePosition::LEFT;
    }

    return MouseRelativePosition::INSIDE;
}

void Coloriser::Pane::DrawOutline() {
    GuiGroupBox(
        (Rectangle) {
            .x = (f32)this->x,
            .y = (f32)this->y,
            .width = (f32)this->widht,
            .height = (f32)this->height
        },
        this->name.c_str()
        );
}
