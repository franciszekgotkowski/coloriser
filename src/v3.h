#pragma once

#include <raylib.h>
#include <typedefs.h>

#include "Matrix3x3.h"

namespace Coloriser {
    v3 v3fromVector3(
        Vector3 v
    );

    Vector3 Vector3fromv3(
        v3 v
    );

    v3 AddScalarTov3(
        v3 v,
        f32 f
    );

    v3 MultiplyScalarTov3(
        v3 v,
        f32 f
    );

    v3 AddVectors(
        v3 vec1,
        v3 vec2
    );

    v3 SubtractVectors(
        v3 vec1,
        v3 vec2
    );

    void printV3(
        v3 v
    );

    v3 MultiplyMatrix(
        Matrix3x3 m,
        v3 v
    );
}
