#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

//----------- demo for consumption -----

struct literPerkm {
	explicit literPerkm(double c)
	: consumption { c } {}
	double get() const { return consumption;}
	literPerkm operator/(double factor) const {
		return literPerkm{consumption / factor};
	}
	literPerkm operator*(double factor)const { return literPerkm{consumption*factor};}
private:
	double consumption;
};
struct kmDriven{
	explicit kmDriven(double k)
	: km { k } {}
	double get() const { return km;}
	kmDriven operator/(double factor) const { return kmDriven{ km / factor};}
private:
	double km;
};
struct literGas{
	explicit literGas(double ll)
	: l { ll } {}
	literPerkm operator/(kmDriven const &km)const {
		return literPerkm{l / km.get()};
	}
	literGas operator*(double factor)const { return literGas{l*factor};}
private:
	double l;
};

literPerkm consumption(literGas l, kmDriven km) {
	return l/(km/100.0);
}

literPerkm consumption(kmDriven km,literGas l){
	return (l/km)*100.0;
}

void testConsumption1over1(){
	literGas const l {1} ;
	kmDriven const km { 1 } ;
	ASSERT_EQUAL(100.0,consumption(l,km).get());
}

void testConsumption40over500(){
	literGas const l { 40 };
	kmDriven const km { 500 };
	ASSERT_EQUAL(8.0,consumption(l,km).get());
}

void testConsumption40over500Wrong(){
	literGas const l { 40 };
	kmDriven const km { 500 };
	ASSERT_EQUAL(8.0,consumption(km,l).get()); // 2nd overload
}
void testConsumptionEvenMoreStrange(){
//	ASSERT_EQUAL(8.0,consumption(consumption({40},{500}),{100}));
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testConsumption1over1));
	s.push_back(CUTE(testConsumption40over500));
	s.push_back(CUTE(testConsumption40over500Wrong));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
