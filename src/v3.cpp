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
}