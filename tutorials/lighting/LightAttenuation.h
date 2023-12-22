//
// Created by Patrik Aradi on 2023/12/22.
//

#ifndef LIGHTATTENUATION_H
#define LIGHTATTENUATION_H

namespace LightAttenuation {
constexpr float linear[] = {
    0.7f,
    0.35f,
    0.22f,
    0.14f,
    0.09f,
    0.07f,
    0.045f,
    0.027f,
    0.022f,
    0.014f,
    0.007f,
    0.0014f,
};

constexpr float quadratic[] = {
    1.8f,
    0.44f,
    0.20f,
    0.07f,
    0.032f,
    0.017f,
    0.0075f,
    0.0028f,
    0.0019f,
    0.0007f,
    0.0002f,
    0.000007f,
};

enum AttenuationRadius {
    A_7 = 0,
    A_13 = 1,
    A_20 = 2,
    A_32 = 3,
    A_50 = 4,
    A_65 = 5,
    A_100 = 6,
    A_160 = 7,
    A_200 = 8,
    A_325 = 9,
    A_600 = 10,
    A_3250 = 11,
};
}

#endif //LIGHTATTENUATION_H
