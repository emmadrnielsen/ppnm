
#include<iostream>
#include<cstdio>
#include<vector>
#include"vec.h"

int main(){
    pp::vec q{1,2,3};
    q.x=6;
    std::cout << q.x << " " << q.y << " " << q.z << "\n";
return 0; //return 0 upon successful completion
}