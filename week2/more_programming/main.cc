
#include<iostream>
#include<cstdio>
#include<vector>
#include"hello.h"

int main(){
    hello();

    double a=1.0;
    double b=a;

    if (a == b) {std::cout << "a=b\n";}
    else {std::cout << "a!=b\n";}
    std::vector<double> v {1,2,3};

    for(size_t i=0;i<v.size();i++) {std::cout << v[i] << " ";}
    std::cout << "\n";

    for(auto vi : v)std::cout << vi << " ";
    std::cout << "\n";

    for(double vi : v)std::cout << vi << " ";
    std::cout << "\n";

    for(auto vi : v) vi=6; //creates copy
    for(auto vi : v) std::cout << vi << " ";
    std::cout << "\n";

    for(auto& vi : v) vi=6; //reference type. references same object
    for(auto& vi : v) std::cout << vi << " ";
    std::cout << "\n";

    std::cout << "now comes the while loop \n";
    size_t i = 0;
    while(i<v.size()) {
        std::cout << "v[" << i << "]=" << v[i] << "\n";
        i+=1;
    }
    std::cout << "now comes the do loop \n";
    i=0;
    do{
        std::cout << "v[" << i << "]=" << v[i] << "\n";
        i+=1;
    }while(i<v.size()); //checks condition after running
    std::cout << "\n";
    //auto u=v; //creates variable u with same type as v
    //auto& w=v; //w refers to v (alias for the same vector)
return 0; //return 0 upon successful completion
}