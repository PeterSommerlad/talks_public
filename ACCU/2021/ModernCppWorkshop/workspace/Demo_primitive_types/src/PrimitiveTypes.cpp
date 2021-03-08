#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void crazyConversions(){
	ASSERT_EQUAL(0.0,sin(false));
	ASSERT_EQUAL_DELTA(1.0,sin(true),0.2);
	ASSERT_EQUAL(true,bool(sin(true)));
}

void crazyPromotion(){
	unsigned char const c{'A'};
	unsigned char const f{2};
	auto const x = c * f;
	static_assert(std::is_signed_v<decltype(x)>); // int!
	ASSERT_EQUAL(130,x);
}

void crazyOverflow(){ // assumes 32/64 bit
	static_assert(std::numeric_limits<int>::max() < std::numeric_limits<long>::max());
	unsigned int const l = std::numeric_limits<int>::max();
	unsigned long const ll { l * l }; // undetected overflow
	ASSERT_EQUAL(0x7FFF'FFFF,l);
	ASSERT_EQUAL(0x7FFF'FFFF'FFFF'FFFF,std::numeric_limits<long>::max());
	ASSERT_EQUAL(0x3FFF'FFFF'00000001ul, 0x7ffffffful*l);
	ASSERT_EQUAL(1ul,ll); // wrong result due to overflow
	//ASSERT_EQUAL(0x3FFFFFFF00000001ul, ll); // what should be
}


//----------- demo for consumption -----

double consumption(double l, double km) {
	return l/(km/100.0);
}

void testConsumption1over1(){
	double const l {1} ;
	double const km { 1 } ;
	ASSERT_EQUAL(100.0,consumption(l,km));
}

void testConsumption40over500(){
	double const l { 40 };
	double const km { 500 };
	ASSERT_EQUAL(8.0,consumption(l,km));
}

void testConsumption40over500Wrong(){
	double const l { 40 };
	double const km { 500 };
	ASSERT_EQUAL(1250.0,consumption(km,l)); // no check.
}
void testConsumptionEvenMoreStrange(){
	ASSERT_EQUAL(8.0,consumption(consumption(40,500),100));
}




bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(crazyConversions));
	s.push_back(CUTE(crazyPromotion));
	s.push_back(CUTE(testConsumption1over1));
	s.push_back(CUTE(testConsumption40over500));
	s.push_back(CUTE(testConsumption40over500Wrong));
	s.push_back(CUTE(testConsumptionEvenMoreStrange));
	s.push_back(CUTE(crazyOverflow));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
