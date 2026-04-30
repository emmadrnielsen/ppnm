
#pragma once
#include<string>
#include<iostream>
#include<cstdio>
#include<cmath>

namespace pp{
struct vec{           //struct and class is basically the same. for struct everything is public
    double x,y,z;

    // From class:
    //ctors
    // vec(double a, double b, double c){ // parm. ctor
    //     std::cout << "parametrized constructor called ...\n";
    //     x = a; y = b; z = c;
    //     }
    // vec() : vec(0,0,0) { // default ctor
    //     std::cout << "default constructor called ...\n";
    //     }
    // vec(const vec&)=default; // copy ctor: vec a(b); Remember: (mark all things that are not supposed to be changed as const)
    // vec(vec&&)=default; // move ctor: vec a(b+c);

    // //dtor
    // ~vec(){ std::cout << "destructor called...\n";};

    // From chatgpt:
    vec(double, double, double);
    vec() = default;
    vec(const vec&)=default;
    vec(vec&&)=default;
    ~vec() = default;

    //assignments
    vec& operator=(const vec&)=default; // copy assign. : a=b;  (vec& a=b (a and b refer to same object), vec a=b (deep copy))
    vec& operator=(vec&&)=default; // move assign. : a=b+c;

    //member operators
    vec& operator+=(const vec&); // a+=b; (a is changed by adding b to it)
    vec& operator-=(const vec&);
    vec& operator*=(double);
    vec& operator/=(double);

    //for debugging
    void print(const std::string& s = "") const;

    // stream output
    friend std::ostream& operator<<(std::ostream&, const vec&);
};
// non-members
vec operator-(const vec&);
vec operator-(vec, const vec&);
vec operator+(vec, const vec&); // a=b+c     Remember: & betyder at det er en reference i stedet for en kopi 

// vec operator-(const vec&, const vec&); old
// vec operator*(const vec&, double);
// vec operator*(double, const vec&);
// vec operator/(const vec&, double);

vec operator*(vec, double);
vec operator*(double, vec);
vec operator/(vec, double);

// dot product + cross product + norm
double dot(const vec&, const vec&);
vec cross(const vec&, const vec&);
double norm(const vec&);

// approx
bool approx(double, double, double acc=1e-9, double eps=1e-9);
bool approx(const vec&, const vec&, double acc=1e-9, double eps=1e-9);
}