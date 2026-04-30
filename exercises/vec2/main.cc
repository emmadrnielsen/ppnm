#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "hello.h"
#include "vec.h"

int main(){
    hello();

    double a = 1.0;
    double b = a;

    if(a == b) std::cout << "a==b\n";
    else std::cout << "a!=b\n";

    std::vector<double> v {1,2,3};

    std::cout << "for(size_t=0....) loop:\n";
    for(size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";

    std::cout << "\nfor(auto vi : v) loop:";
    for(auto vi : v)
        std::cout << vi << " ";

    std::cout << "\nfor(double vi : v) loop:";
    for(double vi : v)
        std::cout << vi << " ";

    std::cout << "\n\n";

    for(auto& vi : v)
        vi = 6;

    std::cout << "is v changed after 'auto& vi' ?\n";
    for(auto& vi : v)
        std::cout << vi << " ";

    std::cout << "\n now comes the while loop:  ";
    size_t idx = 0;
    while(idx < v.size()){
        std::cout << " v[" << idx << "]= " << v[idx];
        idx++;
    }

    std::cout << "\n now comes the do loop:  ";
    idx = 0;
    do{
        std::cout << " v[" << idx << "]= " << v[idx];
        idx++;
    } while(idx < v.size());

    std::cout << "\n";

    {
        std::cout << "two constructors are going to be called shortly...\n";

        pp::vec<double> vec_i(9,9,9);
        pp::vec<double> vec_ip(-1,-1,-1);

        vec_i.x = 0;

        std::cout << "here comes vec_i: "
                  << vec_i.x << " " << vec_i.y << " " << vec_i.z << "\n";

        std::cout << "calling friend operator<< on vec_i: "
                  << vec_i << "\n";

        std::cout << "here comes vec_ip: " << vec_ip << "\n";
        std::cout << "vec_ip + vec_i: " << (vec_ip + vec_i) << "\n";

        std::cout << "now a couple of destructors are going to be called...\n";
    }

    std::cout << "\n--- extensive vec<double> tests ---\n";

    int failed = 0;

    auto test = [&](bool condition, const std::string& name){
        if(condition) std::cout << "[passed] " << name << "\n";
        else {
            std::cout << "[FAILED] " << name << "\n";
            failed++;
        }
    };

    pp::vec<double> vec_a(1.0, 2.0, 3.0);
    pp::vec<double> vec_b(4.0, 5.0, 6.0);

    vec_a.print("vec_a = ");
    vec_b.print("vec_b = ");

    std::cout << "vec_a = " << vec_a << "\n";
    std::cout << "vec_b = " << vec_b << "\n";

    pp::vec<double> vec_zero;
    test(pp::approx(vec_zero, pp::vec<double>(0,0,0)), "default constructor");

    pp::vec<double> vec_copy(vec_a);
    test(pp::approx(vec_copy, vec_a), "copy constructor");

    pp::vec<double> vec_moved(pp::vec<double>(7,8,9));
    test(pp::approx(vec_moved, pp::vec<double>(7,8,9)), "move constructor");

    pp::vec<double> vec_x;
    vec_x = vec_a;
    test(pp::approx(vec_x, vec_a), "copy assignment");

    pp::vec<double> vec_y;
    vec_y = pp::vec<double>(10,11,12);
    test(pp::approx(vec_y, pp::vec<double>(10,11,12)), "move assignment");

    test(pp::approx(-vec_a, pp::vec<double>(-1,-2,-3)), "unary minus");

    test(pp::approx(vec_a + vec_b, pp::vec<double>(5,7,9)), "operator+");
    test(pp::approx(vec_a - vec_b, pp::vec<double>(-3,-3,-3)), "operator-");

    pp::vec<double> vec_c = vec_a;
    vec_c += vec_b;
    test(pp::approx(vec_c, pp::vec<double>(5,7,9)), "operator+=");

    vec_c = vec_a;
    vec_c -= vec_b;
    test(pp::approx(vec_c, pp::vec<double>(-3,-3,-3)), "operator-=");

    test(pp::approx(vec_a * 2.0, pp::vec<double>(2,4,6)), "vec * double");
    test(pp::approx(2.0 * vec_a, pp::vec<double>(2,4,6)), "double * vec");

    vec_c = vec_a;
    vec_c *= 2.0;
    test(pp::approx(vec_c, pp::vec<double>(2,4,6)), "operator*=");

    test(pp::approx(vec_a / 2.0, pp::vec<double>(0.5,1.0,1.5)), "operator/");

    vec_c = vec_a;
    vec_c /= 2.0;
    test(pp::approx(vec_c, pp::vec<double>(0.5,1.0,1.5)), "operator/=");

    test(pp::approx(pp::dot(vec_a, vec_b), 32.0), "dot product");
    test(pp::approx(pp::cross(vec_a, vec_b), pp::vec<double>(-3,6,-3)), "cross product");
    test(pp::approx(pp::norm(vec_a), std::sqrt(14.0)), "norm");

    test(pp::approx(
        pp::vec<double>(1,2,3),
        pp::vec<double>(1 + 1e-10, 2, 3)
    ), "approx(vec, vec)");

    test(pp::approx(1.0, 1.0 + 1e-10), "approx(double, double)");

    std::cout << "\n--- vec<float> template test ---\n";

    pp::vec<float> vec_f(1.0f, 2.0f, 3.0f);
    pp::vec<float> vec_g(4.0f, 5.0f, 6.0f);

    vec_f.print("vec_f = ");
    vec_g.print("vec_g = ");

    std::cout << "vec_f + vec_g = " << vec_f + vec_g << "\n";
    std::cout << "dot(vec_f, vec_g) = " << pp::dot(vec_f, vec_g) << "\n";
    std::cout << "norm(vec_f) = " << pp::norm(vec_f) << "\n";

    std::cout << "\nNumber of failed tests: " << failed << "\n";
    std::cout << "--- end vec tests ---\n";

    return 0;
}