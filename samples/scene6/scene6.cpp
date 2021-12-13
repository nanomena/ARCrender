#define ARC_IMPLEMENTATION
#include "arc.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);

    shared_ptr<Shape> skybox = make_shared<Sphere>(
        make_shared<Lambert>(Spectrum(0)),
        nullptr, Vec3(0, 0, 0), INF / 10
    );
    skybox->setIdentifier("skybox");

    shared_ptr<Camera> camera = make_shared<PerspectiveCamera>(
        Vec3(0, 0, 15),
        Vec3(0.8, 0, 0),
        Vec3(0, 0.6, 0),
        0.6
    );

//    shared_ptr<Camera> camera = make_shared<Actinometer>(
//        Vec3(0, 0, 15),
//        Vec3(0, -10, -10)
//    );

    shared_ptr<Scene> scene = make_shared<Scene>(camera, skybox);

    scene->addObject(
        make_shared<Flat>(
            make_shared<Lambert>(Spectrum(0)),
            make_shared<UniformLight>(Spectrum(1)),
            Vec3(-3, 9.9, -7),
            Vec3(-3, 9.9, -13),
            Vec3(3, 9.9, -13),
            Vec3(3, 9.9, -7)
        ), "light"
    );

    scene->addObject(
        make_shared<Flat>(
            make_shared<GGX>(rgb256(250, 250, 250), 0.9),
            nullptr,
            Vec3(-10, -10, -20),
            Vec3(-10, -10, 20),
            Vec3(10, -10, 20),
            Vec3(10, -10, -20)
        ), "down"
    );

    scene->addObject(
        make_shared<Flat>(
            make_shared<GGX>(rgb256(250, 250, 250), 0.3),
            nullptr,
            Vec3(-10, 10, 20),
            Vec3(-10, 10, -20),
            Vec3(10, 10, -20),
            Vec3(10, 10, 20)
        ), "up"
    );
//
    scene->addObject(
        make_shared<Flat>(
            make_shared<Lambert>(rgb256(250, 170, 170)),
            nullptr,
            Vec3(10, -10, -20),
            Vec3(10, -10, 20),
            Vec3(10, 10, 20),
            Vec3(10, 10, -20)
        ), "right"
    );

    scene->addObject(
        make_shared<Flat>(
            make_shared<Lambert>(rgb256(170, 170, 250)),
            nullptr,
            Vec3(-10, -10, 20),
            Vec3(-10, -10, -20),
            Vec3(-10, 10, -20),
            Vec3(-10, 10, 20)
        ), "left"
    );

    scene->addObject(
        make_shared<Flat>(
            make_shared<Lambert>(rgb256(250, 250, 250)),
            nullptr,
            Vec3(-10, 10, -20),
            Vec3(-10, -10, -20),
            Vec3(10, -10, -20),
            Vec3(10, 10, -20)
        ), "back"
    );

    scene->addObject(
        make_shared<Flat>(
            make_shared<Lambert>(rgb256(250, 250, 250)),
            nullptr,
            Vec3(-10, -10, 20),
            Vec3(-10, 10, 20),
            Vec3(10, 10, 20),
            Vec3(10, -10, 20)
        ),
        "front"
    );
//
//
//
//    shared_ptr<Image> image = make_shared<Image>(800, 600, camera);
//    shared_ptr<Render> render = make_shared<LightSampledPathTracer>(image, scene);
//

//    shared_ptr<Tracer> tracer = make_shared<BidirectionalPathTracer>(1, 1, scene);
    shared_ptr<Tracer> tracer = make_shared<BidirectionalPathTracer>(800, 600, scene);
    char output[100];
    sprintf(output, "result.png");

    int epoch = 300000;
    cerr << "[T + " << ((double)clock() / CLOCKS_PER_SEC) << "] | target : " << epoch << endl;
    for (int i = 1; i <= epoch; ++i) {
        tracer->epoch(scene->lights.size());
//        if (i % 100 == 0) {
//            cerr << "[T + " << ((double)clock() / CLOCKS_PER_SEC) << "] | epoch " << i << endl;
//            tracer->color(0, true);
//        }
        if (i % 1 == 0) {
            cerr << "[T + " << ((double)clock() / CLOCKS_PER_SEC) << "] | epoch " << i << endl;
            tracer->savePNG(output, 0.35);
        }
    }

//    int epoch = 30000, cluster = 1;
//    cerr << "[T + " << (clock() / (double)CLOCKS_PER_SEC) << "] | target : " << epoch << endl;
//    int idx = 800 * 100 + 400;
//    for (int i = 1; i <= epoch; ++i)
//    {
//        render->step_one(idx, cluster);
//        cerr << "[T + " << (clock() / (double)CLOCKS_PER_SEC) << "] | epoch " << i << endl;
//        cerr << image->get(idx) << endl;
//    }
////    (0.0044293,0.0044293,0.0044293)
}