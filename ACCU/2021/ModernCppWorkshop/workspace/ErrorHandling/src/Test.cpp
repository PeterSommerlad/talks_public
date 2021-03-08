#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <algorithm>

#include <cctype>
#include <iterator>
#include <sstream>
#include <string>

#include <variant>


namespace error_with_variant {

constexpr auto
isalpha = [](char c) {
	return std::isalpha(c);
};

enum class error_code { empty, invalid};

std::variant<std::string, error_code> inputName(std::istream &is){
	std::string input{};
	is >> input;
	if (input.size()){
		if (all_of(cbegin(input), cend(input), isalpha)) {
				return input;
			} else {
				return error_code::invalid;
		}
	} else {
		return error_code::empty;
	}
}

void inputOK(){
	std::string expect{"Peter"};
	std::istringstream is{expect};
	auto res = inputName(is);
	ASSERT_EQUAL(expect,std::get<std::string>(res));
	// throws bad_variant_access if not a string
}

void inputEmpty(){
	std::string expect{};
	std::istringstream is{expect};
	auto res = inputName(is);
	ASSERT_EQUAL(error_code::empty,std::get<error_code>(res));
	// throws bad_variant_access if not a string
}
void inputInvalid(){
	std::string expect{"1n5a11d"};
	std::istringstream is{expect};
	auto res = inputName(is);
	ASSERT_EQUAL(error_code::invalid,std::get<error_code>(res));
	// throws bad_variant_access if not a string
}


}

namespace error_as_side_effect {

std::optional<int> inputNumber(std::istream &in){
	int number{};
	in >> number; // error as side effect
	if (in.fail()) {
		in.clear(); // reset error state
		return std::nullopt;
	}
	return number;
}

void testInputNumberOK(){
	std::istringstream is{"42"};
	ASSERT_EQUAL(42, inputNumber(is).value());
}
void testInputNumberFails(){
	std::istringstream is{"abc"};
	ASSERT( not inputNumber(is).has_value());
}


}


namespace error_with_exception {

struct input_failed{};

int inputNumber(std::istream &in){
	int number{};
	if (in >> number){
		return number;
	}
	throw input_failed{};
}

void testInputNumberThrows(){
	std::istringstream is{"abc"};
	ASSERT_THROWS(inputNumber(is),input_failed);
}

}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(error_with_variant::inputOK));
	s.push_back(CUTE(error_with_variant::inputEmpty));
	s.push_back(CUTE(error_with_variant::inputInvalid));
	s.push_back(CUTE(error_as_side_effect::testInputNumberOK));
	s.push_back(CUTE(error_as_side_effect::testInputNumberFails));
	s.push_back(CUTE(error_with_exception::testInputNumberThrows));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
