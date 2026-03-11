
#include<iostream>
#include<string>
#include<functional>

struct func {
    double operator()(double x){return x*x*x;}
};

double square(double x){return x*x;}; //you can put as many semicolons ;;; as you want tbh
double eval(std::function<double(double)> f, double x=2){
    return f(x);
};

template<typename T>
void echo(const T& arg){ //if you don't have & then you create a copy. with & you create a reference. you can also mark it as const if you promise to never change the object.
        std::cout << "echo: arg = " << arg << "\n";
}

template<typename T> //this block is c code 
struct list{
    T* data; //this is a c array, which we will not be using
    int size;
    T& operator[](int i){return data[i];}
    list(int n){size = n; data = new T[n];}
    ~list(){size=0; delete[] data;}
};

template<typename T>
struct bar {
    T datum;
    void print(){ std::cout << "bar: datum = " << datum << "\n"; }
};

int main(){
    echo(1);
    echo(1.235);
    echo("hello");
    bar<int> intbar {1};
    bar<double> doublebar {1.234};
    bar<std::string> stringbar {"hello"};
    intbar.print();
    doublebar.print();
    stringbar.print();
    int n=5;
    list<double> doublelist(n);
    doublelist[0]=1.23;

    std::cout << "square(2) = " << square(2) << "\n";
    std::function<double(double)> f = square;
    std::cout << "f(2) = " << f(2) << "\n";
    std::cout << "eval(f,2) = " << eval(f,2) << "\n";
    std::cout << "eval(square,2) = " << eval(square,2) << "\n";
    func cube;
    std::function<double(double)> g = cube;
    std::cout << "cube(2) = " << cube(2) << "\n";
    std::cout << "g(2) = " << g(2) << "\n";

    double a=1;
    auto h = [a]()->double{return a;}; //this is called anonymous function
    auto q = [&a]()->double{return a;}; //here you capture the variable a by reference
    std::cout << "h() = " << h() << "\n";
    std::cout << "q() = " << q() << "\n";
    a=2;
    std::cout << "h() = " << h() << "\n";
    std::cout << "q() = " << q() << "\n";
    
return 0;
}
