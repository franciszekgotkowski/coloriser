#include <raylib.h>
#include <raygui.h>
#include <Pane.h>
#include <string>
#include <typedefs.h>
#include <utility>

namespace Coloriser {
    Pane::Pane(
        u32 xPos,
        u32 yPos,
        u32 width,
        u32 heigth,
        u32 borderWidth,
        std::string name,
        std::unique_ptr<UiObject> uiObject
    ) {
        this->name = name;

        this->AssignUiObject(std::move(uiObject));
        this->SetNewCoordinateVariables(
            xPos,
            yPos,
            width,
            heigth,
            borderWidth
        );
    }

    Pane::Pane(
        std::string name,
        std::unique_ptr<UiObject> uiObject
    ) : Pane(
        0,
        0,
        0,
        0,
        0,
        name,
        std::move(uiObject)
    ) {
    }

    void Pane::SetNewCoordinateVariables(
        u32 xPos,
        u32 yPos,
        u32 width,
        u32 heigth,
        u32 borderSize
    ) {
        this->paneCoordinates = (CoordinateRect){
            .xPos = xPos,
            .yPos = yPos,
            .width = width,
            .height = heigth
        };

        this->canvasCoordinates = (CoordinateRect){
            .xPos = xPos,
            .yPos = yPos,
            .width = width,
            .height = heigth
        };

        this->borderWidth = borderSize;

        CoordinateRect childCoordinates;
        CoordinateRect uiObjectCoordinates;

        if (this->childPane == nullptr) {
            this->percentOfCanvasForChild = 0;
            if (this->uiObject == nullptr) {
                return;
            }
        }
        if (this->childPane != nullptr) {
            switch (this->whereIsChild) {
                case Direction::LEFT:
                    childCoordinates = (CoordinateRect){
                        .xPos = this->canvasCoordinates.xPos,
                        .yPos = this->canvasCoordinates.yPos,
                        .width = (this->canvasCoordinates.width - borderSize) * this->percentOfCanvasForChild / 100,
                        .height = this->canvasCoordinates.height,
                    };
                    uiObjectCoordinates = {
                        .xPos = this->canvasCoordinates.xPos + childCoordinates.width + borderSize,
                        .yPos = this->canvasCoordinates.yPos,
                        .width = this->canvasCoordinates.width - (childCoordinates.width + borderSize),
                        .height = this->canvasCoordinates.height,
                    };
                    break;
                case Direction::RIGHT:
                    uiObjectCoordinates = (CoordinateRect){
                        .xPos = this->canvasCoordinates.xPos,
                        .yPos = this->canvasCoordinates.yPos,
                        .width = (this->canvasCoordinates.width - borderSize) * this->percentOfCanvasForChild / 100,
                        .height = this->canvasCoordinates.height,
                    };
                    childCoordinates = {
                        .xPos = this->canvasCoordinates.xPos + uiObjectCoordinates.width + borderSize,
                        .yPos = this->canvasCoordinates.yPos,
                        .width = this->canvasCoordinates.width - (uiObjectCoordinates.width + borderSize),
                        .height = this->canvasCoordinates.height,
                    };
                    break;
                case Direction::UP:
                    childCoordinates = (CoordinateRect){
                        .xPos = this->canvasCoordinates.xPos,
                        .yPos = this->canvasCoordinates.yPos,
                        .width = this->canvasCoordinates.width,
                        .height = (this->canvasCoordinates.height - borderSize) * this->percentOfCanvasForChild / 100,
                    };
                    uiObjectCoordinates = (CoordinateRect){
                        .xPos = this->canvasCoordinates.xPos,
                        .yPos = this->canvasCoordinates.yPos + borderSize + childCoordinates.height,
                        .width = this->canvasCoordinates.width,
                        .height = this->canvasCoordinates.height - (childCoordinates.height + borderSize)
                    };
                    break;
                case Direction::DOWN:
                    uiObjectCoordinates = (CoordinateRect){
                        .xPos = this->canvasCoordinates.xPos,
                        .yPos = this->canvasCoordinates.yPos,
                        .width = this->canvasCoordinates.width,
                        .height = (this->canvasCoordinates.height - borderSize) * this->percentOfCanvasForChild / 100,
                    };
                    childCoordinates = (CoordinateRect){
                        .xPos = this->canvasCoordinates.xPos,
                        .yPos = this->canvasCoordinates.yPos + borderSize + uiObjectCoordinates.height,
                        .width = this->canvasCoordinates.width,
                        .height = this->canvasCoordinates.height - (uiObjectCoordinates.height + borderSize)
                    };
                    break;
                default:
                    break;
            }
            this->childPane->SetNewCoordinateVariables(
                childCoordinates.xPos,
                childCoordinates.yPos,
                childCoordinates.width,
                childCoordinates.height,
                borderSize
            );
        } else {
            uiObjectCoordinates = {
                .xPos = this->canvasCoordinates.xPos,
                .yPos = this->canvasCoordinates.yPos,
                .width = this->canvasCoordinates.width,
                .height = this->canvasCoordinates.height,
            };
        }


        if (this->uiObject != nullptr) {
            this->uiObject->Resize(
                uiObjectCoordinates.xPos,
                uiObjectCoordinates.yPos,
                uiObjectCoordinates.width,
                uiObjectCoordinates.height,
                this->borderWidth
            );
        }
    }

    void Pane::AssignUiObject(
        std::unique_ptr<UiObject> newUiObject
    ) {
        if (newUiObject) {
            this->uiObject = std::move(newUiObject);
        }
    }

    void Pane::Draw() {
        // GuiGroupBox(
        // 	(Rectangle) {
        // 		(f32)this->paneCoordinates.xPos,
        // 		(f32)this->paneCoordinates.yPos,
        // 		(f32)this->paneCoordinates.width,
        // 		(f32)this->paneCoordinates.height,
        // 	},
        // 	this->name.c_str()
        // );

        if (this->uiObject) {
            this->uiObject->Draw();
        }

        if (this->childPane) {
            this->childPane->Draw();
        }
    };

    void Pane::ResetCoordinateVariables() {
        this->SetNewCoordinateVariables(
            this->paneCoordinates.xPos,
            this->paneCoordinates.yPos,
            this->paneCoordinates.width,
            this->paneCoordinates.height,
            this->borderWidth
        );
    }

    void Pane::AssignChildPane(
        std::unique_ptr<Pane> childPanePtr,
        u32 canvasPercentForCHild,
        Direction childLocation
    ) {
        if (childPanePtr && !this->childPane) {
            this->childPane = std::move(childPanePtr);
            this->percentOfCanvasForChild = canvasPercentForCHild;
            this->whereIsChild = childLocation;
        }
        this->ResetCoordinateVariables();
    }
}
