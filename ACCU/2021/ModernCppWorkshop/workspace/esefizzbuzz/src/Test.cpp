#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <string>
using namespace std::string_literals;

struct bla{
	int computeresult(int i) const {
		return i;
	}
	void tunix() {
		computeresult(42);
	}
	bla & operator=(bla const &) & = default;
};

void testbla(){
	bla  b { };
	b.computeresult(5);
	b.tunix();
	bla{}.tunix();
	b = bla{};
	(bla{} = b);
}
std::string fizzbuzz(int const &i) {
	std::string result{}; // "value/default initialization"
	if(0 == i % 3) result += "fizz";
	if(0 == i % 5) result += "buzz";
	if(result.size()==0)
	   result=std::to_string(i);
	return result;
}

void testFizzBuzz1Is1() {
	ASSERT_EQUAL("1"s,fizzbuzz(1));
}
void testFizzBuzz2Is2() {
	ASSERT_EQUAL("2"s,fizzbuzz(2));
}
void testFizzBuzz3IsFizz() {
	ASSERT_EQUAL("fizz"s,fizzbuzz(3));
}
void testFizzBuzz5IsBuzz() {
	ASSERT_EQUAL("buzz"s,fizzbuzz(5));
}
void testFizzBuzz6IsFizz() {
	ASSERT_EQUAL("fizz"s,fizzbuzz(6));
}
void testFizzBuzz15IsFizzBuzz() {
	ASSERT_EQUAL("fizzbuzz"s,fizzbuzz(15));
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testFizzBuzz1Is1));
	s.push_back(CUTE(testFizzBuzz3IsFizz));
	s.push_back(CUTE(testFizzBuzz2Is2));
	s.push_back(CUTE(testFizzBuzz5IsBuzz));
	s.push_back(CUTE(testFizzBuzz6IsFizz));
	s.push_back(CUTE(testFizzBuzz15IsFizzBuzz));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
