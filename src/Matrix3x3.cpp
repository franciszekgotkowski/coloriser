#include <Matrix3x3.h>
#include <cassert>
#include <cstdio>
#include <raylib.h>
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
        return (Matrix3x3){
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
        r.x = (v3){
            .x = x.x,
            .y = y.x,
            .z = z.x
        };
        r.y = (v3){
            .x = x.y,
            .y = y.x,
            .z = z.x
        };
        r.z = (v3){
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

    static void GornotrojkatnaDoDiagonalnej(
        Matrix3x3 *m,
        v3 *v
    ) {
        assert(m);
        assert(v);

        for range(x, 3) {
            u32 yy = x + 1;
            while (yy < 3) {
                assert(m->arr[yy].arr[x] == 0.0f);
                yy++;
            }
        }

        for (i32 x = 2; x >= 0; x--) {
            i32 y = x;
            for (i32 yy = y - 1; yy >= 0; yy--) {
                f32 dzielnik;
                if (m->arr[y].arr[x] == 0.0f) {
                    dzielnik = 0.0f;
                }

                dzielnik = m->arr[yy].arr[x] / m->arr[y].arr[x];
                for range(xx, 3) {
                    m->arr[yy].arr[xx] -= dzielnik * m->arr[y].arr[xx];
                }
                v->arr[yy] -= dzielnik * v->arr[y];
            }
        }
    }

    static void DoGornotrojkatnej(
        Matrix3x3 *m,
        v3 *v
    ) {
        assert(m);
        assert(v);

        for range(y, 3) {
            // jeżeli mamy 0 na diagonali
            bool shouldSkip = false;
            if (m->arr[y].arr[y] == 0.0f) {
                shouldSkip = true;
                u32 i = y + 1;
                while (i < 3) {
                    if (m->arr[i].arr[y] != 0.0f) {
                        v3 t = m->arr[i];
                        m->arr[i] = m->arr[y];
                        m->arr[y] = t;

                        f32 tf = v->arr[i];
                        v->arr[i] = v->arr[y];
                        v->arr[y] = tf;

                        shouldSkip = false;
                        break;
                    }
                    i++;
                }
            }
            if (shouldSkip) {
                continue;
            }

            // odejmujemy wartości w wie
            u32 x = y;
            u32 yy = y + 1;
            while (yy < 3) {
                assert(m->arr[y].arr[x] != 0.0f);
                if (m->arr[y].arr[x] == 0.0f) {
                    continue;
                }
                f32 dzielnik = m->arr[yy].arr[x] / m->arr[y].arr[x];
                for range(xx, 3) {
                    m->arr[yy].arr[xx] -= dzielnik * m->arr[y].arr[xx];
                }
                v->arr[yy] -= v->arr[y] * dzielnik;

                yy++;
            }
        }
    }

    static void PodzielWyrazyDiagonali(
        Matrix3x3 *m,
        v3 *v
    ) {
        assert(m);
        assert(v);

        for range(y, 3) {
            for range(x, 3) {
                if (x != y) {
                    assert(m->arr[y].arr[x] == 0.0f);
                }
            }
        }

        for range(i, 3) {
            v->arr[i] /= m->arr[i].arr[i];
            m->arr[i].arr[i] = 1.0;
        }
    }

    Vector3 SolveMatrix(
        Matrix3x3 m,
        Vector3 v,
        bool *success
    ) {
        v3 vec = makev3(v);
        DoGornotrojkatnej(&m, &vec);
        GornotrojkatnaDoDiagonalnej(&m, &vec);
        PodzielWyrazyDiagonali(&m, &vec);

        for range(y, 3) {
            if (
                m.arr[y].arr[y] == 0.0f &&
                vec.arr[y] != 0.0f
            ) {
                *success = false;
            }
        }

        *success = true;
        return (Vector3){
            .x = vec.x,
            .y = vec.y,
            .z = vec.z
        };
    }

    void printMatrix(
        Matrix3x3 m
    ) {
        for range(y, 3) {
            printf("|%f, %f, %f|\n", m.arr[y].x, m.arr[y].y, m.arr[y].z);
        }
        printf("\n");
    }

    void printSolutionMatrix(
        Matrix3x3 m,
        v3 v
    ) {
        for range(y, 3) {
            printf("|%f, %f, %f| %f\n", m.arr[y].x, m.arr[y].y, m.arr[y].z, v.arr[y]);
        }
        printf("\n");
    }


    Matrix3x3 InvertMatrix(
        Matrix3x3 m
    ) {
        Matrix3x3 mcp = m;
        if (
            mcp.x.x == 0.254901946f &&
            mcp.x.y == -0.247058839f &&
            mcp.x.z == 1.0f &&

            mcp.y.x == 0.545098066f &&
            mcp.y.y == -0.247058839f &&
            mcp.y.z == 1.0f &&

            mcp.z.x == 0.545098066f &&
            mcp.z.y == 0.0941176713f &&
            mcp.z.z == 0.0f
            ) {
        printMatrix(mcp);
        }
        Matrix3x3 id = NewMatrix(
            (Vector3){1.0f, 0.0f, 0.0f},
            (Vector3){0.0f, 1.0f, 0.0f},
            (Vector3){0.0f, 0.0f, 1.0f}
        );

        // sprowadx do gornotrojkatnej
        for range(y, 3) {
            // jeżeli mamy 0 na diagonali
            bool shouldSkip = false;
            if (m.arr[y].arr[y] == 0.0f) {
                shouldSkip = true;
                u32 i = y + 1;
                while (i < 3) {
                    if (m.arr[i].arr[y] != 0.0f) {
                        v3 t = m.arr[i];
                        m.arr[i] = m.arr[y];
                        m.arr[y] = t;

                        v3 tf = id.arr[i];
                        id.arr[i] = id.arr[y];
                        id.arr[y] = tf;

                        shouldSkip = false;
                        break;
                    }
                    i++;
                }
            }
            if (shouldSkip) {
                continue;
            }

            // odejmujemy wartości w wie
            u32 x = y;
            u32 yy = y + 1;
            while (yy < 3) {
                assert(m.arr[y].arr[x] != 0.0f);
                if (m.arr[y].arr[x] == 0.0f) {
                    continue;
                }
                f32 dzielnik = m.arr[yy].arr[x] / m.arr[y].arr[x];
                for range(xx, 3) {
                    f32 t  =  m.arr[yy].arr[xx] - dzielnik * m.arr[y].arr[xx];
                    printf("%f - %f = %f\n", m.arr[yy].arr[xx], dzielnik * m.arr[y].arr[xx], t);
                    m.arr[yy].arr[xx] = t;
                    t = id.arr[yy].arr[xx] - dzielnik * id.arr[y].arr[xx];
                    id.arr[yy].arr[xx] = t;
                    // m.arr[yy].arr[xx] -= dzielnik * m.arr[y].arr[xx];
                    // id.arr[yy].arr[xx] -= dzielnik * id.arr[y].arr[xx];
                    // v.arr[yy] -= v.arr[y] * dzielnik;
                }

                yy++;
            }
        }

        // gornotrojkatna do diagonalnej
        for range(x, 3) {
            u32 yy = x + 1;
            while (yy < 3) {
                assert(
                    (m.arr[yy].arr[x] == 0.0f && x != yy) ||
                    (x == yy)
                    );
                yy++;
            }
        }

        for (i32 x = 2; x >= 0; x--) {
            i32 y = x;
            for (i32 yy = y - 1; yy >= 0; yy--) {
                f32 dzielnik;
                if (m.arr[y].arr[x] == 0.0f) {
                    dzielnik = 0.0f;
                }

                dzielnik = m.arr[yy].arr[x] / m.arr[y].arr[x];
                for range(xx, 3) {
                    m.arr[yy].arr[xx] -= dzielnik * m.arr[y].arr[xx];
                    id.arr[yy].arr[xx] -= dzielnik * id.arr[y].arr[xx];
                }
            }
        }

        // podziel wyrazy diagonali
        for range(y, 3) {
            for range(x, 3) {
                id.arr[y].arr[x] /= m.arr[y].arr[y];
            }
        }

        return id;
    }
}
