#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

struct Old{
	int val{};

	int foo() const {
		return val;
	}
	Old& inc() {
		++val;
		return *this;
	}
};

void DemoOldConstOnConstLValue(){
	Old const x { };
	ASSERT_EQUAL(0,x.foo());
	//x.inc(); // does not compile as it should
}
void DemoOldTemporary(){
	ASSERT_EQUAL(0,Old{}.foo());
	Old{}.inc(); // compiles, but shouldn't
}

void DemoOldLValue(){
	Old x{};
	ASSERT_EQUAL(0,x.foo());
	x.inc();
	ASSERT_EQUAL(1,x.foo());
}

struct Modern{
	int val{};
	int foo() const & {
		return val;
	}
	Modern& inc() & {
		++val;
		return *this;
	}
	int consume() && {
		auto const ret { val };
		val = -1; // create moved-from state
		return ret;
	}
};

void DemoModernConstOnConstLvalue(){
	Modern const x{};
	ASSERT_EQUAL(0,x.foo());
	//x.consume(); // does not compile
	//x.inc(); // does not compile
}

void DemoModernLValue(){
	Modern x{};
	ASSERT_EQUAL(&x,&(x.inc()));
	ASSERT_EQUAL(1,x.foo());
	//x.consume(); // does not compile
	ASSERT_EQUAL(1,std::move(x).consume());
	ASSERT_EQUAL(-1,x.foo());
}

void DemoModernTemoporary(){
	ASSERT_EQUAL(0,Modern{}.foo());
	//Modern{}.inc(); // does not compile
	ASSERT_EQUAL(0,Modern{}.consume());
}

struct OverloadAmbiguity {
	int val{};
	int foo() const & {
		return val;
	}
	int foo() & {
		++val;
		return val;
	}
	int foo() && {
		val = -1; // create moved-from state
		return val;
	}
//	int foo() const && { // compiles, if not existent const & is used
//		return -42;
//	}

};
void DemoOverloadConstLValue(){
	OverloadAmbiguity const x{};
	ASSERT_EQUAL(0,x.foo());
	ASSERT_EQUAL(0,std::move(x).foo()); // still binds to const&, if const&& is not defined!
}


void DemoOverloadTemporary(){
	ASSERT_EQUAL(-1,OverloadAmbiguity{}.foo());
	ASSERT_EQUAL(0,static_cast<OverloadAmbiguity const&>(OverloadAmbiguity{}).foo());
	//ASSERT_EQUAL(-42,static_cast<OverloadAmbiguity const>(OverloadAmbiguity{}).foo());
	ASSERT_EQUAL(-42,static_cast<OverloadAmbiguity const&&>(OverloadAmbiguity{}).foo());

}

void DemoOverloadLValue(){
	OverloadAmbiguity x{};
	ASSERT_EQUAL(1,x.foo());
	ASSERT_EQUAL(1,static_cast<OverloadAmbiguity const&>(x).foo());
	ASSERT_EQUAL(2,x.foo());
	ASSERT_EQUAL(-1,std::move(x).foo());
	ASSERT_EQUAL(0,x.foo());
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(DemoOldConstOnConstLValue));
	s.push_back(CUTE(DemoOldTemporary));
	s.push_back(CUTE(DemoOldLValue));
	s.push_back(CUTE(DemoModernConstOnConstLvalue));
	s.push_back(CUTE(DemoModernLValue));
	s.push_back(CUTE(DemoModernTemoporary));
	s.push_back(CUTE(DemoOverloadConstLValue));
	s.push_back(CUTE(DemoOverloadTemporary));
	s.push_back(CUTE(DemoOverloadLValue));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner = cute::makeRunner(lis, argc, argv);
	bool const success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
