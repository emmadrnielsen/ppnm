#include<iostream>
#include<string>
#include"vec.h"
#include <cmath>
namespace pp{

void vec::print(const std::string& s) const{
	std::cout << s << x << " " << y << " " << z;
}

std::ostream& operator<<(std::ostream& os, const vec& v){
	os << "{ " << v.x << ", " << v.y << ", " << v.z << " } ";
	return os;
}

vec& vec::operator+=(const vec& other){
	x+=other.x;
	y+=other.y;
	z+=other.z;
	return (*this); // (*this) ~ python's "self"
	}

vec operator+(vec a,const vec& b){
	a += b;
	return a;
}

vec& vec::operator-=(const vec& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec operator-(vec a, const vec& b){
    return a -= b;
}

vec& vec::operator*=(double c){
    x *= c;
    y *= c;
    z *= c;
    return *this;
}

vec operator*(vec a, double c){
    return a *= c;
}

vec operator*(double c, vec a){
    return a *= c;
}

vec& vec::operator/=(double c){
    x /= c;
    y /= c;
    z /= c;
    return *this;
}

vec operator/(vec a, double c){
    return a /= c;
}

vec operator-(const vec& a){
    return vec(-a.x, -a.y, -a.z);
}

double dot(const vec& a, const vec& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec cross(const vec& a, const vec& b){
    return vec(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

double norm(const vec& a){
    return std::sqrt(dot(a,a));
}

bool approx(double a, double b, double acc, double eps){
    return std::abs(a-b) <= acc + eps*std::abs(b);
}

bool approx(const vec& a, const vec& b, double acc, double eps){
    if(!approx(a.x, b.x, acc, eps)) return false;
    if(!approx(a.y, b.y, acc, eps)) return false;
    if(!approx(a.z, b.z, acc, eps)) return false;
    return true;
}

vec::vec(double x, double y, double z)
    : x(x), y(y), z(z)
{}

}
