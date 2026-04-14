#include "raylib.h"
#include <ColorPool.h>
#include <ColorisingMethod.h>
#include <assert.h>
#include <StubWarning.h>

namespace Coloriser {

	void ColorPool::SetNewAmountOfColors(
		u32 amountOfColors
	) {
		this->colors.resize(amountOfColors);
	}

	void ColorPool::SetNewColorisingMethod(
		ColorisingMethod colorisingMethod
	) {
		this->colorisingMethod = colorisingMethod;
		if (this->colorisingMethod == ColorisingMethod::PLANE) {
			this->SetNewAmountOfColors(3);
		}
	}

	ColorPool::ColorPool(
		ColorisingMethod colorisingMethod,
		u32 amountOfColors
	) {
		SetNewAmountOfColors(amountOfColors);
		SetNewColorisingMethod(colorisingMethod);
	}

	void ColorPool::SetColors(
		std::vector<Color> colors
	) {
		assert(colors.size() == this->colors.size());
		this->colors = colors;
	}

	void ColorPool::SetColor(
		Color color,
		u32 idx
	) {
		assert(idx < this->colors.size());
		this->colors[idx] = color;
	}

	Color ColorPool::PlaneFilter(
		Color color
	) {
		STUB_WARNING("Not implemented");
		return (Color){};
	}

	Color ColorPool::SphereFilter(
		Color color
	) {
		STUB_WARNING("Not implemented");
		return (Color){};
	}


	Color ColorPool::RunColorisingFilter(
		Color color
	) {
		switch (this->colorisingMethod) {
			case ColorisingMethod::PLANE:
			return this->PlaneFilter(color);
			break;

			case ColorisingMethod::SPHERE:
			return this->SphereFilter(color);
			break;

			default:
			return (Color){};
			break;
		}
	}

}