#ifndef Light_hpp
#define Light_hpp

#include "utils.hpp"
#include "sampler.hpp"
#include "spectrum.hpp"

class Light {
public:
    Spectrum evaluate(const Vec3 &n, const Vec3 &v) const;
    Spectrum sampleStV(const Vec3 &n, Vec3 &v) const;

private:
    virtual Spectrum evaluate(const Vec3 &vLocal) const {
        throw invalid_argument("NotImplementedError");
    }
    virtual Spectrum sample(Vec3 &vLocal, double &pdf) const {
        throw invalid_argument("NotImplementedError");
    }
};

#ifdef ARC_IMPLEMENTATION

Spectrum Light::evaluate(const Vec3 &n, const Vec3 &v) const {
    Mat3 T, TInv;
    rotateAxis(n, v, T, TInv);
    Vec3 vT = T * v;
    return evaluate(vT);
}

Spectrum Light::sampleStV(const Vec3 &n, Vec3 &v) const {
    Mat3 T, TInv;
    rotateAxis(n, n, T, TInv);
    Vec3 vT;
    double pdf;
    Spectrum s = sample(vT, pdf);
    v = TInv * vT;
    return s / pdf;
}

#endif
#endif /* Light_hpp */
