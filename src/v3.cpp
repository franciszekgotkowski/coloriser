#include <cstdio>
#include <typedefs.h>
#include <v3.h>

namespace Coloriser {

	v3 AddScalarTov3 (
		v3 v,
		f32 f
	) {
		return {
			.x = v.x + f,
			.y = v.y + f,
			.z = v.z + f
		};
	}


	v3 MultiplyScalarTov3 (
		v3 v,
		f32 f
	) {
		return {
			.x = v.x * f,
			.y = v.y * f,
			.z = v.z * f
		};
	}

	v3 SubtractVectors(
		v3 vec1,
		v3 vec2
	) {
		return {
			.x = vec1.x - vec2.x,
			.y = vec1.y - vec2.y,
			.z = vec1.z - vec2.z,
		};
	}


	v3 AddVectors(
		v3 vec1,
		v3 vec2
	) {
		return {
			.x = vec1.x + vec2.x,
			.y = vec1.y + vec2.y,
			.z = vec1.z + vec2.z,
		};
	}


	void printV3(
		v3 v
	) {
		printf("{ %f %f %f }\n", v.x, v.y, v.z);
	}

	Vector3 Vector3fromv3(
		v3 v
	) {
		return (Vector3){
			.x = v.x,
			.y = v.y,
			.z = v.z
		};
	}

	v3 v3fromVector3(
		Vector3 v
	) {
		return (v3){
			.x = v.x,
			.y = v.y,
			.z = v.z
		};
	}

	v3 MultiplyMatrix(
		Matrix3x3 m,
		v3 v
	) {
		v3 r = {};

		for range(y, 3) {
			for range(x, 3) {
				r.arr[y] += m.arr[y].arr[x] * v.arr[y];
			}
		}

		return r;
	}
}