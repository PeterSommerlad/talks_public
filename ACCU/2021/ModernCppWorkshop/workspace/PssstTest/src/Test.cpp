#include "pssst.h"
#include "ArraySizeDiffStrong.h"
#include "Degrees.h"
#include "Consumption.h"
#include "StrongWithEncapsulation.h"
#include "StrongWithConstructor.h"
#include "SafeArithmetic.h"
#include "StringOperations.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <string>
#include "BooleanTest.h"
#include "BitOperationsTest.h"


using namespace Pssst;
struct Int: strong<int,Int>,ops<Int,Order,Inc,Add,Out>{
};


struct Size: strong<unsigned,Size>,ops<Size,Order,Inc,Add,Out> {
};
static_assert(sizeof(Size)==sizeof(unsigned),"no overhead");

void testSizeworks(){
	Size sz{42};
	//ASSERT_EQUAL(42,sz);// doesn't compile
	//ASSERT_EQUAL(42u,sz);//doesn't compile
	ASSERT_EQUAL(Size{21}+Size{21},sz);
}


void testBoolConverts(){
	//bool b=Bool{};
//	Bool b42{42}; // unfortunately, only a SFINAE ctor  could diallow that, not considered narrowing
	//int i{b42}; // no automatic conversion
//	ASSERTM("start writing tests", b42);
}




	struct uptest:strong<int,uptest>,ops<uptest,UPlus>{};


void testUPlus(){
	uptest one{1};
	ASSERT_EQUAL(one.value,(+one).value);
}
void testUMinus(){
	struct umtest:strong<int,umtest>,ops<umtest,UMinus>{};
	umtest one{1};
	ASSERT_EQUAL(-(one.value),(-one).value);
}
void testUInc(){
	struct uinctest:strong<int,uinctest>,ops<uinctest,Inc>{};
	uinctest var{1};
	ASSERT_EQUAL(2,(++var).value);
	ASSERT_EQUAL(2,(var++).value);
	ASSERT_EQUAL(3,var.value);
}
void testUDec(){
	struct udtest:strong<int,udtest>,ops<udtest,Dec>{};
	udtest var{2};
	ASSERT_EQUAL(1,(--var).value);
	ASSERT_EQUAL(1,(var--).value);
	ASSERT_EQUAL(0,var.value);
}


void testWithStringBase(){
	struct S:strong<std::string,S>,ops<S,Out,Eq>{};
	S s{"hello"};
	ASSERT_EQUAL(S{"hello"},s);
}
//namespace testRelativeOps{
//struct WidthD : Relative<WidthD,double>{};
//
//void testWidthDConstructionEq(){
//	WidthD w{3.14};
//	ASSERT_EQUAL(WidthD{3.14},w);
//}
//
//void testWidthDMultiplyWith(){
//	WidthD w{42.0};
////	w /= 2.0;
//	w *= 2.0;
////	w += w;
////	w /= 2;
//	ASSERT_EQUAL(WidthD{42},w);
//}
//void testWidthDAddable(){
//	WidthD w{42.0};
//	w += w;
//	w++;
//	ASSERT_EQUAL(WidthD{86},++w);
//}
//void testWidthDSubtractable(){
//	WidthD w{42.0};
//	w -= WidthD{-2};
//	w--;
//	ASSERT_EQUAL(WidthD{42},--w);
//}
//void testWidthDivides(){
//	WidthD w{42.0};
//	auto d= w / WidthD{21};
//	static_assert(std::is_same_v<decltype(d),underlying_value_type<WidthD>>,"should be double");
//	ASSERT_EQUAL(2,d);
//}
////struct Diff : strong<std::ptrdiff_t,Diff>,ops<Diff,RelArithmetic<std::ptrdiff_t>::apply,Eq,Cmp,Out>{};
//struct Diff:Relative<Diff,std::ptrdiff_t>{};
//void testDiffCtorEq(){
//	Diff d{42};
//	ASSERT_EQUAL(Diff{42},d);
//}
//
//}
struct WaitC:strong<unsigned,WaitC>
            ,ops<WaitC,Eq,Inc,Out>{};
static_assert(sizeof(unsigned)==sizeof(WaitC));
void testWaitCounter(){
	WaitC c{};
	WaitC const one{1};
	ASSERT_EQUAL(WaitC{0},c);
	ASSERT_EQUAL(one,++c);
	ASSERT_EQUAL(one,c++);
	ASSERT_EQUAL(2,c.value);
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testWithStringBase));
	s.push_back(CUTE(testSizeworks));
	//	s.push_back(CUTE(testRelativeOps::testWidthDConstructionEq));
	//	s.push_back(CUTE(testRelativeOps::testWidthDMultiplyWith));
	//	s.push_back(CUTE(testRelativeOps::testWidthDAddable));
	//	s.push_back(CUTE(testRelativeOps::testWidthDSubtractable));
	//	s.push_back(CUTE(testRelativeOps::testWidthDivides));
	//	s.push_back(CUTE(testRelativeOps::testDiffCtorEq));
	s.push_back(CUTE(testUPlus));
	s.push_back(CUTE(testUMinus));
	s.push_back(CUTE(testUInc));
	s.push_back(CUTE(testUDec));
	s.push_back(CUTE(testBoolConverts));
	s.push_back(CUTE(testWaitCounter));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	cute::suite BitOperationsTest = make_suite_BitOperationsTest();
	success &= runner(BitOperationsTest, "BitOperationsTest");
	cute::suite ArraySizeDiffStrong = make_suite_ArraySizeDiffStrong();
	success = runner(ArraySizeDiffStrong, "ArraySizeDiffStrong") && success;
	cute::suite Degrees = make_suite_Degrees();
	success = runner(Degrees, "Degrees") && success;
	cute::suite Consumption = make_suite_Consumption();
	success = runner(Consumption, "Consumption") && success;
	cute::suite StrongWithEncapsulation = make_suite_StrongWithEncapsulation();
	success = runner(StrongWithEncapsulation, "StrongWithEncapsulation") && success;
	cute::suite StrongWithConstructor = make_suite_StrongWithConstructor();
	success = runner(StrongWithConstructor, "make_suite_StrongWithConstructor") && success;
	cute::suite SafeArithmetic = make_suite_SafeArithmetic();
	success = runner(SafeArithmetic, "SafeArithmetic") && success;
	cute::suite StringOperations = make_suite_StringOperations();
	success = runner(StringOperations, "StringOperations") && success;
	cute::suite BooleanTest = make_suite_BooleanTest();
	success &= runner(BooleanTest, "BooleanTest");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
