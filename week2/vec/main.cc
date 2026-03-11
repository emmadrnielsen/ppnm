#include<iostream>
#include<vector>
#include"hello.h"
#include"vec.h"

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

