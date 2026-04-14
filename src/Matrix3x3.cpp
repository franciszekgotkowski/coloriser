#include <Matrix3x3.h>
#include <cstdio>
#include <raylib.h>
#include <raymath.h>
#include <v3.h>

namespace Coloriser {
	static inline v3 makev3(
		Vector3 vec
	) {
		return (v3){
			.x = vec.x,
			.y = vec.y,
			.z = vec.z
		};
	}

	// create new matrix by inputting its rows
	Matrix3x3 NewMatrixRows(
		Vector3 x,
		Vector3 y,
		Vector3 z
	) {
		return (Matrix3x3) {
			.x = makev3(x),
			.y = makev3(y),
			.z = makev3(z)
		};
	}

	// create new matrix by inputting its columns
	Matrix3x3 NewMatrixColumns(
		Vector3 x,
		Vector3 y,
		Vector3 z
	) {
		Matrix3x3 r;
		r.x = (v3) {
			.x = x.x,
			.y = y.x,
			.z = z.x
		};
		r.y = (v3) {
			.x = x.y,
			.y = y.x,
			.z = z.x
		};
		r.z = (v3) {
			.x = x.z,
			.y = y.z,
			.z = z.z
		};
		return r;
	}

	// create new matrix by inputting its columns
	Matrix3x3 NewMatrix(
		Vector3 x,
		Vector3 y,
		Vector3 z
	) {
		return NewMatrixRows(
			x,
			y,
			z
		);
	}

	Matrix3x3 TransposeMatrix(
		Matrix3x3 m
	) {
		Matrix3x3 r;

		r.x.x = m.x.x;
		r.x.y = m.y.x;
		r.x.z = m.z.x;

		r.y.x = m.x.y;
		r.y.y = m.y.y;
		r.y.z = m.z.y;

		r.z.x = m.x.z;
		r.z.y = m.y.z;
		r.z.z = m.z.z;

		return r;
	}

	Vector3 SolveMatrix(
		Matrix3x3 m,
		Vector3 v,
		bool* success
	) {
		// v3 vec = makev3(v);

		// for range(y, 3) {
		// 	if (m.arr[y].arr[y] == 0.0f) {
		// 		u32 idx = (y+1)%3;
		// 		m.arr[y] = AddVectors(m.arr[y], m.arr[idx]);
		// 		vec.arr[y] += vec.arr[idx];
		// 	}
		// 	for range(yy, 2-y) {
		// 		u32 odejmujaca = y;
		// 		u32 odejmowana = y + yy;

		// 		f32 dzielnik =
		// 	}
		// }
		//
		return (Vector3){};
	}

	void printMatrix(
		Matrix3x3 m
	) {
		for range(y, 3) {
			printf("|%f, %f, %f|\n", m.arr[y].x,  m.arr[y].y, m.arr[y].z);
		}
		printf("\n");
	}

}