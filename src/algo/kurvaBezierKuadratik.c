#include "kurvaBezierKuadratik.h"

// Fungsi helper buat menghitung titik pada kurva Bezier Kuadratik
// t adalah nilai antara 0.0 (awal) hingga 1.0 (akhir)
Vector2 GetQuadraticBezierPoint(Vector2 p0, Vector2 p1, Vector2 p2, float t) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;

    Vector2 p;
    p.x = uu * p0.x + 2 * u * t * p1.x + tt * p2.x;
    p.y = uu * p0.y + 2 * u * t * p1.y + tt * p2.y;
    return p;
}
