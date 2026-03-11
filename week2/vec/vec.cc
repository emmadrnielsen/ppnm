#include<iostream>
#include<string>
#include"vec.h"
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

vec operator+(const vec& a,const vec& b){
	vec r(a);
	r+=b;
	return r;
}

}
