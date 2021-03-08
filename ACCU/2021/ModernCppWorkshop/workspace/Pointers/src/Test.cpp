#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <algorithm>

#include <array>
#include <cctype>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <span>
#include <vector>

namespace simplified {
template <typename T>
using observer_ptr=T *;
}


int demo(int *const pi){
	//*pi++;
	(*pi)++;
	return *pi;
}
void dont_demo(int *const pi){
	1[pi]=42;
	pi[0]=41;
}
void simpleTestHandler() {
	using simplified::observer_ptr;
	int i{42};

	observer_ptr<int> oi=&i;
	ASSERT_EQUAL(i,*oi);
}
void testDemo(){
	int i{42};
	int j=demo(&i);
	ASSERT_EQUAL(i,j);
}
void testDont(){
	std::array<int,2> a{};
	dont_demo(a.data());
	std::initializer_list<int> exp{41,42};
	ASSERT_EQUAL_RANGES(begin(exp),end(exp),begin(a),end(a));

}

void takecharptr(char *s){
	for (; *s; ++s)
		*s = std::toupper(*s);
}

void testTakeCharPtr(){
	char s[] = "hello world";
	takecharptr(s);
	ASSERT_EQUAL("HELLO WORLD",s);
}

void takechararray(char s[]){
	for (; *s; ++s)
		*s = std::toupper(*s);
}
void testTakeCharArray(){
	char s[] = "hello world";
	takecharptr(s);
	ASSERT_EQUAL("HELLO WORLD",s);
}
std::string takestringview(std::string_view s){
	std::string res{};
	transform(s.begin(),s.end(),
			std::back_inserter(res),
			[](char c){return std::toupper(c);});
	return res;
}

void testTakeStringview(){
	char s[] = "hello world";
	auto res=takestringview(s);
	ASSERT_EQUAL("HELLO WORLD",res);
}

void takestring(std::string &s){
	transform(s.begin(),s.end(),
			s.begin(),
			[](char c){return std::toupper(c);});
}

void testTakeString(){
	std::string s{"hello world"};
	takestring(s);
	ASSERT_EQUAL("HELLO WORLD",s);
}


void absintarray(int a[], size_t const len) {
	for(size_t i=0; i <len;++i)
		a[i] = a[i] < 0? -a[i]:a[i];
}

void testtakeintarray(){
	int a[] = { -1, 2 , -3 , -4 };
	absintarray(a,sizeof(a)/sizeof(*a));
	ASSERT_EQUAL(10,std::reduce(std::begin(a),std::end(a),0));
}

template<size_t N>
void absintarray(int (&a)[N]) {
	for(size_t i=0; i < N; ++i)
		a[i] = a[i] < 0? -a[i]:a[i];
}

void testtakeintarraydeduced(){
	int a[] = { -1, 2 , -3 , -4 };
	absintarray(a);
	ASSERT_EQUAL(10,std::reduce(std::begin(a),std::end(a),0));
}

template<size_t N>
void absintarray(std::array<int,N> &a){
	for(size_t i=0; i < N; ++i)
		a[i] = a[i] < 0? -a[i] : a[i];
}
void testtakeintstdarraydeduced(){
	std::array a { -1, 2 , -3 , -4 };
	absintarray(a);
	ASSERT_EQUAL(10,std::reduce(std::begin(a),std::end(a),0));
}

void absintptrrange(int *b, int *e){
	for (;b != e ; ++b){
		if(*b < 0) *b = - *b;
	}
}

void testtakeintptrrange(){
	int a[] = { -1, 2 , -3 , -4 };
	absintptrrange(a,a + sizeof(a)/sizeof(*a));
	ASSERT_EQUAL(10,std::reduce(std::begin(a),std::end(a),0));
}


template <typename FWDITER>
void absintarray(FWDITER b, FWDITER e){
	std::transform(b,e,b,[](auto i){ return std::abs(i);});
}
void testtakeintranged(){
	std::array a { -1, 2 , -3 , -4 };
	absintarray(a.begin(),a.end());
	ASSERT_EQUAL(10,std::reduce(std::begin(a),std::end(a),0));
}

void absintarray(std::vector<int> &a){
	std::transform(std::begin(a),std::end(a),std::begin(a),[](auto i){ return std::abs(i);});
}
void testtakeintvector(){
	std::vector a { -1, 2 , -3 , -4 };
	absintarray(a);
	ASSERT_EQUAL(10,std::reduce(std::begin(a),std::end(a),0));
}


// C++ 20 or Guideline support library
void absintarrayspan(std::span<int> a){
	for(size_t i=0; i < a.size(); ++i)
		a[i] = a[i] < 0? -a[i] : a[i];
}
void testtakeintstdarrayspan(){
	std::array a { -1, 2 , -3 , -4 };
	absintarrayspan(a);
	ASSERT_EQUAL(10,std::reduce(std::begin(a),std::end(a),0));
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(simpleTestHandler));
	s.push_back(CUTE(testDemo));
	s.push_back(CUTE(testDont));
	s.push_back(CUTE(testTakeCharPtr));
	s.push_back(CUTE(testtakeintarray));
	s.push_back(CUTE(testTakeCharArray));
	s.push_back(CUTE(testtakeintarraydeduced));
	s.push_back(CUTE(testtakeintstdarraydeduced));
	s.push_back(CUTE(testtakeintstdarrayspan));
	s.push_back(CUTE(testtakeintvector));
	s.push_back(CUTE(testtakeintranged));
	s.push_back(CUTE(testTakeStringview));
	s.push_back(CUTE(testTakeString));
	s.push_back(CUTE(testtakeintptrrange));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
