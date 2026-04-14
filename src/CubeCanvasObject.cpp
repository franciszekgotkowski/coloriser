#include <StubWarning.h>
#include <Window.h>
#include <cassert>
#include <cstdio>
#include <raylib.h>
#include <CubeCanvasObject.h>
#include <range.h>
#include <math.h>
#include <rlgl.h>
#include <raymath.h>

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
		u32 amountOfColors,
		std::shared_ptr<ColorPool> colorPool
	) : CubeCanvas() {
		assert(colorPool);
		this->colorPool = colorPool;
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
		this->colorPool->SetNewColorisingMethod(method);

		if (this->colorPool->colorisingMethod == ColorisingMethod::PLANE) {
			this->SetNewAmountOfColors(3);
			this->colorPool->colors[0] = MAROON;
			this->colorPool->colors[1] = PINK;
			this->colorPool->colors[2] = BROWN;
		} else if (this->colorPool->colorisingMethod == ColorisingMethod::SPHERE) {
			this->SetNewAmountOfColors(amountOfColors);
		}
	}

	void CubeCanvas::SetNewAmountOfColors(
		u32 amountOfColors
	) {
		this->colorPool->colors.resize(amountOfColors);
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

	Vector3 CubeCanvas::rgbToCubePosition(
		Color color
	) {
		Vector3 cubeBase = {
			this->cubeLocation.x - this->cubeSize / 2.0f,
			this->cubeLocation.y - this->cubeSize / 2.0f,
			this->cubeLocation.z - this->cubeSize / 2.0f
		};

		Vector3 colorOffsets = {
			((f32) color.r / 255.0f) * this->cubeSize,
			((f32) color.g / 255.0f) * this->cubeSize,
			((f32) color.b / 255.0f) * this->cubeSize
		};

		return (Vector3){
			cubeBase.x + colorOffsets.x,
			cubeBase.y + colorOffsets.y,
			cubeBase.z + colorOffsets.z
		};
	}

	void CubeCanvas::DrawJustCube() {
		DrawCubeWires(
			this->cubeLocation,
			this->cubeSize,
			this->cubeSize,
			this->cubeSize,
			GRAY
		);

		// musze tu dodać jakieś linie do kostki żeby była bardziej czytelna
	}

	Vector2 CubeCanvas::GetWorldToScreenForCurrentRenderTexture(
		Vector3 location
	) {
		// Vector3 position, Camera camera, int width, int height
		return GetWorldToScreenEx(
			location,
			this->camera,
			this->renderTexture.texture.width,
			this->renderTexture.texture.height
		);
	}

	void CubeCanvas::DrawDot(
		Color color,
		Vector3 location
	) {
		Vector2 screenspacePosition = this->GetWorldToScreenForCurrentRenderTexture(
			location
		);

		DrawCircleV(
			screenspacePosition,
			(f32) ((this->renderTexture.texture.width + this->renderTexture.texture.width) / 100 + 2),
			BLACK
		);
		DrawCircleV(
			screenspacePosition,
			(f32) ((this->renderTexture.texture.width + this->renderTexture.texture.width) / 100),
			color
		);
	}

	void CubeCanvas::DrawColorDots() {

		for range(i, this->colorPool->colors.size()) {
			Color c = this->colorPool->colors[i];
			c.a = 255;
			DrawDot(
				c,
				this->rgbToCubePosition(this->colorPool->colors[i])
			);
		}
	}

	void CubeCanvas::DrawPlane() {

		// // Now i will get vectors that will generate the color plane space
		// Vector3 loc1 = rgbToCubePosition(this->colorPool->colors[0]);
		// Vector3 loc2 = rgbToCubePosition(this->colorPool->colors[1]);
		// Vector3 loc3 = rgbToCubePosition(this->colorPool->colors[2]);

		// Vector3 v1 = Vector3Subtract(loc2, loc1);
		// Vector3 v2 = Vector3Subtract(loc3, loc1);
		// Vector3 startingPoint = loc3;



		rlBegin(RL_TRIANGLES);
		for range(i, this->colorPool->colors.size()) {
		Vector2 screenspacePos = GetWorldToScreenForCurrentRenderTexture(
			rgbToCubePosition(this->colorPool->colors[i])
		);
		rlColor4ub(
			this->colorPool->colors[i].r,
			this->colorPool->colors[i].g,
			this->colorPool->colors[i].b,
			255
		);
		rlVertex2f(screenspacePos.x, screenspacePos.y);
	}
	rlEnd();
}

void CubeCanvas::DrawSphere() {
	STUB_NOT_IMPLEMENTED;
}

void CubeCanvas::Draw() {
	BeginTextureMode(this->renderTexture);
	ClearBackground(this->clearColor);

	BeginMode3D(this->camera);
	this->camera.position.x = 3 * sin(0.25f * GetTime());
	this->camera.position.z = 3 * cos(0.25f * GetTime());
	this->DrawJustCube();
	EndMode3D();

	switch (this->colorPool->colorisingMethod) {
		case ColorisingMethod::PLANE:
		this->DrawPlane();
		break;
		case ColorisingMethod::SPHERE:
		this->DrawSphere();
		break;
	}

	this->DrawColorDots();

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
			(f32) this->coordinates.xPos,
			(f32) this->coordinates.yPos
		},
		WHITE
	);
}
}
