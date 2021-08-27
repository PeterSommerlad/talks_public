#include <iostream>
#include <string>
#include <cxxabi.h> // __cxa_demangle
#include <memory> // unique_ptr
#include <fmt/core.h>

struct freeDeleter {
    template<typename T>
	void operator()(T* toBeFreed)const{
		::free(toBeFreed);
	}
};

using name_ptr = std::unique_ptr<char,freeDeleter>;

void setDummyTo42(){}
struct bar{
	void operator()(){}
};

void match(bool b){
	std::cout << (b?"":"no ") << "match\n";
}

std::string demangle(char const *name){
	name_ptr ptr{ __cxxabiv1::__cxa_demangle(name,0,0,0)};
	return {ptr.get()};
}

int main(){
	using namespace std;
	cout << demangle(typeid(&setDummyTo42).name()) << '\n';
	cout << demangle(typeid(bar()).name()) << '\n';
	cout << demangle(typeid((bar())).name()) << '\n';
	cout << demangle(typeid(42U * (-2) ).name()) << '\n';
	cout << fmt::format("value (42ULL * (-2LL)): {0} {0:#0b} {0:#x}\n" , (42u * (-2)));
	match (typeid(setDummyTo42) == typeid(void()));
	match(typeid(setDummyTo42) == typeid((bar())()));
}
