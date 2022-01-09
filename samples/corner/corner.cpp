//#define ARC_IMPLEMENTATION
#include "arc.hpp"
#include <bits/stdc++.h>
using namespace std;

//#define DEBUG_FLAG
int main() {
    ios::sync_with_stdio(false);


    long long T0 = time(nullptr);


    auto medium = new Transparent(Spectrum(1, 1, 1));
//    auto medium = new Scatter(0.3, Spectrum(1, 1, 1));

    auto camera = new SimulatedCamera(
        Vec3(.6, -.8, .05),
        Vec3(0.8, 0, 0),
        Vec3(0, 0.6, 0),
        0.6,
        0.58, 0.003, 0.05
    );
    auto scene = new Scene(camera, Spectrum(0), medium);

    auto curve = new Spline(3,
        Vec2(0, 0), Vec2(0.16, 0),
        Vec2(.24, 0), Vec2(.30, .10),
        Vec2(.24, .20), Vec2(.16, .30),
        Vec2(.16, .40), Vec2(.16, .50),
        Vec2(.16, .60)
    );

    scene->addObject(
        new Revolved(
            new MtlExtGGX(
                TextureMap(new Texture("textures/Tiles_049/Tiles_049_basecolor.jpg"), Spectrum(2.5)),
                TextureMap(new Texture("textures/Tiles_049/Tiles_049_metallic.jpg"), Spectrum(1)),
                TextureMap(new Texture("textures/Tiles_049/Tiles_049_roughness.jpg"), Spectrum(1)),
                20, 1,
                TextureMap(new Texture("textures/Tiles_049/Tiles_049_normal.jpg"), Spectrum(1))
            ), nullptr,
            medium, medium,
            Ray(Vec3(.68, -1, -1.32), Vec3(0, 1, 0)), curve
        )
    );

    scene->addObject(
        new Sphere(
            new BiGGX(2.5, 0.2), nullptr,
            new Transparent(Spectrum(0.2, 1, 0.2)),
            medium,
            Vec3(.43, -.95, -.58), .05
        )
    );

    scene->addObject(
        new Sphere(
            new MtlExtGGX(
                TextureMap(new Texture("textures/Metal_Gold/Metal_Gold_001_basecolor.jpg"), Spectrum(2.5)),
                TextureMap(new Texture("textures/Metal_Gold/Metal_Gold_001_metallic.jpg"), Spectrum(1)),
                TextureMap(new Texture("textures/Metal_Gold/Metal_Gold_001_roughness.jpg"), Spectrum(3)),
                30, 0.2,
                TextureMap(new Texture("textures/Metal_Gold/Metal_Gold_001_normal.jpg"), Spectrum(1))
            ), nullptr,
            new Scatter(8, Spectrum(1, 1, 1),
            new Sphere(nullptr, nullptr, nullptr, nullptr, Vec3(), INF / 10)),
            medium,
            Vec3(.40, -.93, -.82), .07
        )
    );

    scene->addObject(
        new Sphere(
            new BiGGX(2.5, 0.1), nullptr,
            medium, medium,
            Vec3(.55, -.95, -0.68), .05
        )
    );

    Model model("models/teapot.obj", "models/", Trans3(
        Vec3(0.78, -1, -0.63),
        Vec3(0.036, 0, 0),
        Vec3(0, 0.036, 0),
        Vec3(0, 0, 0.036)
    ), medium);
    scene->addObjects(model.get());

    Model model2("models/rose.obj", "models/", Trans3(
        Vec3(0.78, -0.94, -0.63),
        Vec3(0.022, 0, 0),
        Vec3(0, 0.022 * sqrt(4. / 5), -0.022 * sqrt(1. / 5)),
        Vec3(0, 0.022 * sqrt(1. / 5), 0.022 * sqrt(4. / 5))
    ), medium, true);
    scene->addObjects(model2.get());

    scene->addObject(
        new Flat(
            new Lambert(Spectrum(0)),
            new UniformLight(Spectrum(10)),
            medium, medium,
            Vec3(-0.3, 0.99, -0.7),
            Vec3(-0.3, 0.99, -1.3),
            Vec3(0.3, 0.99, -1.3),
            Vec3(0.3, 0.99, -0.7)
        ), "light"
    );

    scene->addObject(
        new Flat(
            new GGX(rgb256(250, 250, 250), 0.8), nullptr,
            medium, medium,
            Vec3(-1, -1, -2),
            Vec3(-1, -1, 2),
            Vec3(1, -1, 2),
            Vec3(1, -1, -2)
        ), "down"
    );

    scene->addObject(
        new Flat(
            new GGX(rgb256(250, 250, 250), 0.8), nullptr,
            medium, medium,
            Vec3(-1, 1, 2),
            Vec3(-1, 1, -2),
            Vec3(1, 1, -2),
            Vec3(1, 1, 2)
        ), "up"
    );

    scene->addObject(
        new Flat(
            new GGX(rgb256(170, 170, 250), 0.8), nullptr,
            medium, medium,
            Vec3(1, -1, -2),
            Vec3(1, -1, 2),
            Vec3(1, 1, 2),
            Vec3(1, 1, -2)
        ), "right"
    );

    scene->addObject(
        new Flat(
            new GGX(rgb256(250, 170, 170), 0.8), nullptr,
            medium, medium,
            Vec3(-1, -1, 2),
            Vec3(-1, -1, -2),
            Vec3(-1, 1, -2),
            Vec3(-1, 1, 2)
        ), "left"
    );

    scene->addObject(
        new Flat(
            new Lambert(rgb256(250, 250, 250)), nullptr,
            medium, medium,
            Vec3(-1, 1, -2),
            Vec3(-1, -1, -2),
            Vec3(1, -1, -2),
            Vec3(1, 1, -2)
        ), "back"
    );

    scene->addObject(
        new Flat(
            new Lambert(rgb256(250, 250, 250)), nullptr,
            medium, medium,
            Vec3(-1, -1, 2),
            Vec3(-1, 1, 2),
            Vec3(1, 1, 2),
            Vec3(1, -1, 2)
        ),
        "front"
    );

    auto tracer = new BidirectionalPathTracer(1600, 1200, scene);

    char output[100];
    sprintf(output, "samples/corner/result.png");

    int epoch = 1000;

    cerr << "[T + " << time(nullptr) - T0 << "] | target : " << epoch << endl;
    for (int i = 1; i <= epoch; ++i) {
        tracer->epoch();
        cerr << "[T + " << time(nullptr) - T0 << "] | epoch " << i << endl;
        tracer->savePNG(output, 1);
    }
}
