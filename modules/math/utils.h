#ifndef POMEGRANATEENGINE_UTILS_H
#define POMEGRANATEENGINE_UTILS_H

template<typename T>
T clamp(T value, T min, T max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

#endif //POMEGRANATEENGINE_UTILS_H
