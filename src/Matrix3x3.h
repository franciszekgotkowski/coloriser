#pragma once

#include <range.h>
#include <typedefs.h>

#include <raylib.h>

namespace Coloriser {

	typedef union {
		struct {
			v3 x;
			v3 y;
			v3 z;
		};
		v3 arr[3];
	} Matrix3x3;

	// create new matrix by inputting its rows
	Matrix3x3 NewMatrixRows(
		Vector3 x,
		Vector3 y,
		Vector3 z
	);

	// create new matrix by inputting its columns
	Matrix3x3 NewMatrixColumns(
		Vector3 x,
		Vector3 y,
		Vector3 z
	);

	// create new matrix by inputting its columns
	Matrix3x3 NewMatrix(
		Vector3 x,
		Vector3 y,
		Vector3 z
	);

	Matrix3x3 TransposeMatrix(
		Matrix3x3 m
	);

	Matrix3x3 InvertMatrix(
		Matrix3x3 m
	);

	Vector3 SolveMatrix(
		Matrix3x3 m,
		Vector3 v,
		bool* success
	);

	void printMatrix(
		Matrix3x3 m
	);

	void printSolutionMatrix(
		Matrix3x3 m,
		v3 v
	);
}