#pragma once
#include <iostream>
#include <cmath>
#include <string>

namespace pp {

template<typename T>
struct vec {
    T x, y, z;

    vec() = default;

    vec(T x, T y, T z)
        : x(x), y(y), z(z)
    {}

    vec(const vec&) = default;
    vec(vec&&) = default;
    ~vec() = default;

    vec& operator=(const vec&) = default;
    vec& operator=(vec&&) = default;

    vec& operator+=(const vec& other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec& operator-=(const vec& other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec& operator*=(T c){
        x *= c;
        y *= c;
        z *= c;
        return *this;
    }

    vec& operator/=(T c){
        x /= c;
        y /= c;
        z /= c;
        return *this;
    }

    void print(const std::string& s = "") const {
        std::cout << s << x << " " << y << " " << z << "\n";
    }
};

template<typename T>
vec<T> operator+(vec<T> a, const vec<T>& b){
    return a += b;
}

template<typename T>
vec<T> operator-(vec<T> a, const vec<T>& b){
    return a -= b;
}

template<typename T>
vec<T> operator-(const vec<T>& a){
    return vec<T>(-a.x, -a.y, -a.z);
}

template<typename T>
vec<T> operator*(vec<T> a, T c){
    return a *= c;
}

template<typename T>
vec<T> operator*(T c, vec<T> a){
    return a *= c;
}

template<typename T>
vec<T> operator/(vec<T> a, T c){
    return a /= c;
}

template<typename T>
T dot(const vec<T>& a, const vec<T>& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

template<typename T>
vec<T> cross(const vec<T>& a, const vec<T>& b){
    return vec<T>(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

template<typename T>
auto norm(const vec<T>& a){
    return std::sqrt(dot(a,a));
}

template<typename T>
bool approx(T a, T b, double acc=1e-9, double eps=1e-9){
    return std::abs(a-b) <= acc + eps*std::abs(b);
}

template<typename T>
bool approx(const vec<T>& a, const vec<T>& b, double acc=1e-9, double eps=1e-9){
    return approx(a.x,b.x,acc,eps)
        && approx(a.y,b.y,acc,eps)
        && approx(a.z,b.z,acc,eps);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vec<T>& v){
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    return os;
}

}