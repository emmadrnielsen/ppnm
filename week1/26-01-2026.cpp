#include<iostream>
#include<string>

int fib(int n){
    if(n<0)   return -1;
    if(n==0)  return 0;
    if(n==1)  return 1;
    return fib(n-1)+fib(n-2);
}

int main(int argc, char** argv){
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <n>\n";
        return 1;
    }
    int n = std::stoi(argv[1]);
    std::cout << "n=" << n << "\n";
    for(int i=0; i<=n; i++)
        std::cout << "fib(" << i << ") " << fib(i) << std::endl;
}

