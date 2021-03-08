#include <cassert>
#include <iostream>

struct stars{
	stars(void (stars::*)(int)){}
	void operator ->*(int) { }
	int val;
};

auto times=
[](auto ... a){
	return (1 *...* a);
};

auto fourdots =
		[](auto ...pm){
	stars s{};
	(s.*... .*pm);
};

void onestar() {
	int stars::* pm{&stars::val};
	(stars)&stars::operator->*.*pm;
}

namespace XX {
struct X{
	X(float){}
};

void foo(X){
	std::cout<< "here";
}
}

template <typename T>
struct TT{
	void bar(T t){
		foo(t);
	}
};


int main(){
	TT<XX::X>{}.bar(42);

	int a[20]={};
	int i=10;
	a[i++] = i++;
	std::cout << "i=" << i << std::endl;
	std::cout << "a[11]= " << a[11] << std::endl;
	assert(12==i);
	assert(10 == a[11]);
}
