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
	) {}

	void Pane::SetNewCoordinateVariables (
		u32 xPos,
		u32 yPos,
		u32 width,
		u32 heigth,
		u32 borderWidth
	) {
		this->paneCoordinates = (CoordinateRect){
			.xPos = xPos,
			.yPos = yPos,
			.width = width,
			.height = heigth
		};

		this->canvasCoordinates = (CoordinateRect){
			.xPos = xPos + borderWidth,
			.yPos = yPos + borderWidth,
			.width = width - 2 * borderWidth,
			.height = heigth - 2 * borderWidth
		};

		this->borderWidth = borderWidth;

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
					.width = (this->canvasCoordinates.width-borderWidth)*this->percentOfCanvasForChild/100,
					.height = this->canvasCoordinates.height,
				};
				uiObjectCoordinates = {
					.xPos = this->canvasCoordinates.xPos + borderWidth + (this->canvasCoordinates.width-borderWidth)*this->percentOfCanvasForChild/100,
					.yPos = this->canvasCoordinates.yPos,
					.width = (this->canvasCoordinates.width-borderWidth)*(100-this->percentOfCanvasForChild)/100,
					.height = this->canvasCoordinates.height,
				};
				break;
				case Direction::RIGHT:
				uiObjectCoordinates = (CoordinateRect){
					.xPos = this->canvasCoordinates.xPos,
					.yPos = this->canvasCoordinates.yPos,
					.width = (this->canvasCoordinates.width-borderWidth)*this->percentOfCanvasForChild/100,
					.height = this->canvasCoordinates.height,
				};
				childCoordinates = {
					.xPos = this->canvasCoordinates.xPos + borderWidth + (this->canvasCoordinates.width-borderWidth)*this->percentOfCanvasForChild/100,
					.yPos = this->canvasCoordinates.yPos,
					.width = (this->canvasCoordinates.width-borderWidth)*(100-this->percentOfCanvasForChild)/100,
					.height = this->canvasCoordinates.height,
				};
				break;
				case Direction::UP:
				childCoordinates = (CoordinateRect) {
					.xPos = this->canvasCoordinates.xPos,
					.yPos = this->canvasCoordinates.yPos,
					.width = this->canvasCoordinates.width,
					.height = (this->canvasCoordinates.height-borderWidth)*this->percentOfCanvasForChild/100,
				};
				uiObjectCoordinates = (CoordinateRect) {
					.xPos = this->canvasCoordinates.xPos,
					.yPos = this->canvasCoordinates.yPos + borderWidth + (this->canvasCoordinates.height-borderWidth)*this->percentOfCanvasForChild/100,
					.width = this->canvasCoordinates.width,
					.height = (this->canvasCoordinates.height-borderWidth)*(100-this->percentOfCanvasForChild)/100,
				};
				break;
				case Direction::DOWN:
				uiObjectCoordinates = (CoordinateRect) {
					.xPos = this->canvasCoordinates.xPos,
					.yPos = this->canvasCoordinates.yPos,
					.width = this->canvasCoordinates.width,
					.height = (this->canvasCoordinates.height-borderWidth)*this->percentOfCanvasForChild/100,
				};
				childCoordinates = (CoordinateRect) {
					.xPos = this->canvasCoordinates.xPos,
					.yPos = this->canvasCoordinates.yPos + borderWidth + (this->canvasCoordinates.height-borderWidth)*this->percentOfCanvasForChild/100,
					.width = this->canvasCoordinates.width,
					.height = (this->canvasCoordinates.height-borderWidth)*(100-this->percentOfCanvasForChild)/100,
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
				borderWidth
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
				uiObjectCoordinates.height
			);
		}
	}

	void Pane::AssignUiObject(
		std::unique_ptr<UiObject> uiObject
	) {
		if (uiObject) {
			this->uiObject = std::move(uiObject);
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

	void Pane::AssignChildPane (
		std::unique_ptr<Pane> childPane,
		u32 percentOfCanvasForChild
	) {
		if (childPane) {
			this->childPane = std::move(childPane);
			this->percentOfCanvasForChild = percentOfCanvasForChild;
		}
		this->ResetCoordinateVariables();
	}
}