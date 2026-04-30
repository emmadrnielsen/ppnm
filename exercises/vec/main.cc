#include<iostream>
#include<vector>
#include"hello.h"
#include"vec.h"
#include <cmath>
#include <string>

int main(){
	hello();

	double a=1.0;
	double b=a;
	if(a==b) {std::cout<<"a==b\n";}
	else {std::cout<<"a!=b\n";}

	std::vector<double> v {1,2,3};
	std::cout<<"for(size_t=0....) loop:\n";
	for(size_t i=0;i<v.size();i++)std::cout<<v[i]<<" ";

	std::cout<<"\nfor(auto vi : v) loop:";
	for(auto vi : v) std::cout<<vi<<" ";
	std::cout<<"\nfor(double vi :v) loop:";
	for(double vi : v) std::cout<<vi<<" ";
	std::cout<<"\n";

	//for(auto vi : v) vi=6;
	//printf("is v changed after 'auto vi' ?\n");
	//for(auto vi : v) printf("%g ",vi);

	std::cout<<"\n";
	for(auto& vi : v) vi=6;
	std::cout<<"is v changed after 'auto& vi' ?\n";
	for(auto& vi : v) printf("%g ",vi);

	std::cout<<"\n now comes the while loop:  ";
	size_t i=0;
	while(i<v.size()) {
		std::cout<<" v["<<i<<"]= "<<v[i];
		i+=1;
	}

	std::cout<<"\n now comes the do loop:  ";
	i=0;
	do{ 
		std::cout<<" v["<<i<<"]= "<<v[i];
		i+=1;
	}while(i<v.size());
	std::cout<<"\n";

	{
		std::cout<<"two constructors are going to be called shortly...\n";
        pp::vec i(9,9,9);
        pp::vec ip( -1,-1,-1);   // or whatever name you want

        i.x = 0;

        std::cout << "here comes vec i: " << i.x << " " << i.y << " " << i.z << "\n";
        std::cout << "calling friend operator<< on vec " ;
        std::cout << "i: " << i << "\n";
        std::cout << "here comes vec ip: " << ip << "\n";
        std::cout << "ip + i: " << (ip + i) << "\n";

		std::cout<<"now a couple of destructors are going to be called...\n";
	}

	
std::cout << "\n--- extensive vec tests ---\n";

int failed = 0;

auto test = [&](bool condition, const std::string& name){
    if(condition) std::cout << "[passed] " << name << "\n";
    else {
        std::cout << "[FAILED] " << name << "\n";
        failed++;
    }
};

pp::vec vec_a(1.0, 2.0, 3.0);
pp::vec vec_b(4.0, 5.0, 6.0);

vec_a.print("vec_a = ");
vec_b.print("vec_b = ");

std::cout << "vec_a = " << vec_a << "\n";
std::cout << "vec_b = " << vec_b << "\n";

// constructors
pp::vec vec_zero;
test(pp::approx(vec_zero, pp::vec(0,0,0)), "default constructor");

pp::vec vec_copy(vec_a);
test(pp::approx(vec_copy, vec_a), "copy constructor");

pp::vec vec_moved(pp::vec(7,8,9));
test(pp::approx(vec_moved, pp::vec(7,8,9)), "move constructor");

// assignment
pp::vec vec_x;
vec_x = vec_a;
test(pp::approx(vec_x, vec_a), "copy assignment");

pp::vec vec_y;
vec_y = pp::vec(10,11,12);
test(pp::approx(vec_y, pp::vec(10,11,12)), "move assignment");

// unary minus
test(pp::approx(-vec_a, pp::vec(-1,-2,-3)), "unary minus");

// addition / subtraction
test(pp::approx(vec_a + vec_b, pp::vec(5,7,9)), "operator+");
test(pp::approx(vec_a - vec_b, pp::vec(-3,-3,-3)), "operator-");

// compound operators
pp::vec vec_c = vec_a;
vec_c += vec_b;
test(pp::approx(vec_c, pp::vec(5,7,9)), "operator+=");

vec_c = vec_a;
vec_c -= vec_b;
test(pp::approx(vec_c, pp::vec(-3,-3,-3)), "operator-=");

// scalar multiplication
test(pp::approx(vec_a * 2.0, pp::vec(2,4,6)), "vec * double");
test(pp::approx(2.0 * vec_a, pp::vec(2,4,6)), "double * vec");

vec_c = vec_a;
vec_c *= 2.0;
test(pp::approx(vec_c, pp::vec(2,4,6)), "operator*=");

// scalar division
test(pp::approx(vec_a / 2.0, pp::vec(0.5,1.0,1.5)), "operator/");

vec_c = vec_a;
vec_c /= 2.0;
test(pp::approx(vec_c, pp::vec(0.5,1.0,1.5)), "operator/=");

// dot product
test(pp::approx(pp::dot(vec_a, vec_b), 32.0), "dot product");

// cross product
test(pp::approx(pp::cross(vec_a, vec_b), pp::vec(-3,6,-3)), "cross product");

// norm
test(pp::approx(pp::norm(vec_a), std::sqrt(14.0)), "norm");

// approx tests
test(pp::approx(pp::vec(1,2,3), pp::vec(1+1e-10,2,3)), "approx(vec, vec)");
test(pp::approx(1.0, 1.0+1e-10), "approx(double, double)");

std::cout << "\nNumber of failed tests: " << failed << "\n";
std::cout << "--- end vec tests ---\n";
return 0;
}




// #include<iostream>
// #include<cstdio>
// #include<vector>
// #include"vec.h"

// int main(){
//     pp::vec q{1,2,3};
//     q.x=6;
//     std::cout << q.x << " " << q.y << " " << q.z << "\n";
// return 0; //return 0 upon successful completion
// }

