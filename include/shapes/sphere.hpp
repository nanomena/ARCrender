#ifndef shapes_sphere_hpp
#define shapes_sphere_hpp

#include "../shape.hpp"

class Sphere : public Shape {
public:
    Sphere(
        const BxDF *bxdf, const Light *light,
        const Medium *inside, const Medium *outside,
        Vec3 o, double r
    );

    bool intersect(const Ray &ray, double &t, Vec3 &pos, Vec2 &texPos) const override;
    Vec3 normal(const Vec2 &texPos) const override;
    Vec3 tangent(const Vec2 &texPos) const override;

private:
    Vec3 o;
    double r;
};

#ifdef ARC_IMPLEMENTATION

Sphere::Sphere(
    const BxDF *bxdf, const Light *light,
    const Medium *inside, const Medium *outside,
    Vec3 o, double r
) : Shape(bxdf, light, inside, outside), o(o), r(r) {
    box = Box3(o - Vec3(r, r, r), o + Vec3(r, r, r));
}

bool Sphere::intersect(const Ray &ray, double &t, Vec3 &pos, Vec2 &texPos) const {
//    cerr << ray.o << " " << ray.d << " " << o << " " << r << endl;
    double x = (o - ray.o) * ray.d, y = (ray.o + ray.d * x - o).length();
    if (r < y) {
        return false;
    }
    if ((o - ray.o).length() < r + EPS) {
        t = x + sqrt(r * r - y * y);
    } else {
        t = x - sqrt(r * r - y * y);
    }
//    cerr << t << endl;
    if (t < EPS) return false;
    pos = ray.o + ray.d * t;
    texPos = {
        fmod(atan2((pos - o).y(), (pos - o).x()) / (2 * pi) + 1, 1),
        asin((pos - o).z() / r) / pi + .5
    };
    return true;
}

Vec3 Sphere::normal(const Vec2 &texPos) const {
    return {
        cos(texPos.x() * (2 * pi)) * cos((texPos.y() - .5) * pi),
        sin(texPos.x() * (2 * pi)) * cos((texPos.y() - .5) * pi),
        sin((texPos.y() - .5) * pi)
    };
}

Vec3 Sphere::tangent(const Vec2 &texPos) const {
    return {sin(texPos.x() * (2 * pi)), -cos(texPos.x() * (2 * pi)), 0};
}

#endif
#endif /* shapes_sphere_hpp */