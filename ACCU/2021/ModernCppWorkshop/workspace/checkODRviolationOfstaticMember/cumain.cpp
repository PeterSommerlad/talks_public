#include "templatewithstaticmember.h"
#include <iostream>

int setDummyTo42();

int main(){
	std::cout << staticmember<double>::dummy << '\n';
	std::cout << staticmember<int>::dummy << '\n';
	std::cout << setDummyTo42() << '\n';
	std::cout << staticmember<int>::dummy << '\n';
}
