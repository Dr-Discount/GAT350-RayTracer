#pragma once

#include <cstdlib>
#include <random>
#include <cmath>
#include <type_traits>
#include <glm/glm.hpp>

constexpr float twoPi = 6.283185307179586476925286766559f;

namespace random {
    inline std::mt19937& generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    inline int getInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    inline int getInt() {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    // Type trait to detect glm vector types (vec2/vec3/vec4)
    template <typename T>
    struct is_glm_vec : std::false_type {};

    template <typename T, glm::qualifier Q>
    struct is_glm_vec<glm::vec<2, T, Q>> : std::true_type {};
    template <typename T, glm::qualifier Q>
    struct is_glm_vec<glm::vec<3, T, Q>> : std::true_type {};
    template <typename T, glm::qualifier Q>
    struct is_glm_vec<glm::vec<4, T, Q>> : std::true_type {};

    // Primary getReal for floating point types only (default T = float)
    template <typename T = float>
    inline std::enable_if_t<std::is_floating_point_v<T>, T> getReal(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    template <typename T = float>
    inline std::enable_if_t<std::is_floating_point_v<T>, T> getReal(T max) {
        return getReal<T>(static_cast<T>(0), static_cast<T>(max));
    }

    template <typename T = float>
    inline std::enable_if_t<std::is_floating_point_v<T>, T> getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    // Overloads for glm vectors - generate per-component random real in [min, max)
    template <typename Vec>
    inline std::enable_if_t<is_glm_vec<Vec>::value, Vec> getReal(const Vec& min, const Vec& max) {
        Vec result;
        // GLM vectors expose operator[] and size via length() in newer versions; fall back to component count using sizeof
        constexpr int components = Vec::length();
        for (int i = 0; i < components; ++i) {
            using comp_t = typename Vec::value_type;
            result[i] = getReal<comp_t>(min[i], max[i]);
        }
        return result;
    }

    template <typename Vec>
    inline std::enable_if_t<is_glm_vec<Vec>::value, Vec> getReal(const Vec& max) {
        Vec zero(static_cast<typename Vec::value_type>(0));
        return getReal<Vec>(zero, max);
    }

    inline glm::vec2 onUnitCircle() {
        float radians = getReal(twoPi);
        return glm::vec2{ std::cos(radians), std::sin(radians) };
    }
}