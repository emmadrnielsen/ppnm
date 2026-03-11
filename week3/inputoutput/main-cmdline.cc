#include<iostream>
#include<fstream>
#include <vector>
#include<cmath>
#include<string>


int main (int argc, char* argv[]) {
	std::vector<double> numbers;

	for(int i=1;i<argc;++i){
		std::string arg=argv[i];
		if(arg=="-n" && i+1<argc)
			numbers.push_back(std::stod(argv[++i])); // ++i skips the value you consumed so you don't re-read it next iteration
	}
for(auto n: numbers)
	std::cout << n <<" "<< std::sin(n) <<" "<< std::cos(n) <<std::endl;
exit(EXIT_SUCCESS);
}

