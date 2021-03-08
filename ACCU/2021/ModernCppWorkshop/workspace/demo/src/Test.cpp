#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <memory>

int32_t demoIntegralOverflow() {
	unsigned short us { 0xffffu };
	return us * us ;
}

//#define Abs(x) ((x) < 0 ? -(x):(x))

constexpr auto
Abs = [](auto &&x){ return x < 0 ? -x : x ; };

void testAbsMacroPositive(){
	ASSERT_EQUAL(42,Abs(42));
}
void testAbsMacroNegative(){
	ASSERT_EQUAL(42,Abs(-42));
}
void testAbsMacroZero(){
	ASSERT_EQUAL(0.0,Abs(-0.0));
}

constexpr uint32_t MyBufferSize = 512;


void demoNewDelete(){
	int *onTheHeap = new int(42); // @suppress("Un- or ill-initialized variables")
	//... do something
	delete onTheHeap; // error prone
}

void demoMakeUnique(){
	auto onTheHeap{std::make_unique<int>(42)};
	//... do something
}






void thisIsATest() {
	ASSERTM("start writing tests", false);	
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	s.push_back(CUTE(testAbsMacroPositive));
	s.push_back(CUTE(testAbsMacroNegative));
	s.push_back(CUTE(testAbsMacroZero));
	s.push_back(CUTE(demoNewDelete));
	s.push_back(CUTE(demoMakeUnique));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
