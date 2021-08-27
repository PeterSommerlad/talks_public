#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
namespace freefunctions {
struct Counter {
	unsigned value{};
};

unsigned valueOf(Counter const &theCounter) {
	return theCounter.value;
}

void createDefaultCounterIsZero() {
	Counter const theCounter { };
	ASSERT_EQUAL(0u,valueOf(theCounter));
}

void increment(Counter &theCounter) {
	theCounter.value++;
}

void incrementedCounterIsOne(){
	Counter theCounter{};
	increment(theCounter);
	ASSERT_EQUAL(1u,valueOf(theCounter));
}
}
namespace memberfunctions {
struct Counter {
	unsigned value{};
	unsigned valueOf() const {
		return value;
	}
	void increment() {
		value++;
	}
};


void createDefaultCounterIsZero() {
	Counter const theCounter { };
	ASSERT_EQUAL(0u,theCounter.valueOf());
}

void incrementedCounterIsOne(){
	Counter theCounter{};
	theCounter.increment();
	ASSERT_EQUAL(1u,theCounter.valueOf());
}
}
namespace operatorfunctions {
struct Counter {
	unsigned value{};
	unsigned operator*() const {
		return value;
	}
	void operator++() {
		value++;
	}
	void operator++(int) {
		++(*this);
	}
};


void createDefaultCounterIsZero() {
	Counter const theCounter { };
	ASSERT_EQUAL(0u,*theCounter);
}

void incrementedCounterIsOne(){
	Counter theCounter{};
	++theCounter;
	ASSERT_EQUAL(1u,*theCounter);
}
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(freefunctions::createDefaultCounterIsZero));
	s.push_back(CUTE(freefunctions::incrementedCounterIsOne));
	s.push_back(CUTE(memberfunctions::createDefaultCounterIsZero));
	s.push_back(CUTE(memberfunctions::incrementedCounterIsOne));
	s.push_back(CUTE(operatorfunctions::incrementedCounterIsOne));
	s.push_back(CUTE(operatorfunctions::createDefaultCounterIsZero));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
