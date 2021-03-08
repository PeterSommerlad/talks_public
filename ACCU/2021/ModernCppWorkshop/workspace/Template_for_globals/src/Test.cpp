#include "shared_state.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <csignal>
#include <thread>
#include <chrono>
#include <atomic>
using shared_state=std::atomic<int>;

namespace{
shared_state theState{};

template<auto &state>
void report_state(std::ostream& out){
	int i{};
	if constexpr (std::is_same_v<int,std::decay_t<decltype(state)>>){
			std::swap(i,state);
	} else {
		// assume atomic_int
		i = state.exchange(i);
	}
	out << "shared state: " << i << " - reset to 0";
}
int teststate{};
}
void nonatomic_simpleTestHandler() {
	std::ostringstream os;
	signal_handler<teststate>(1);
	report_state<teststate>(os);
	ASSERT_EQUAL("shared state: 1 - reset to 0",os.str());
}


void simpleTestHandler() {
	std::ostringstream os;
	signal_handler<theState>(1);
	report_state<theState>(os);
	ASSERT_EQUAL("shared state: 1 - reset to 0",os.str());
}

shared_state theSignalHandlerState{0};

extern "C"
void sighandler(int i){
	std::signal(i,SIG_IGN);
	signal_handler<theSignalHandlerState>(i);
}

void useSignaling(){
	std::ostringstream os;
	std::signal(SIGUSR1,&sighandler);
	std::raise(SIGUSR1);
	report_state<theSignalHandlerState>(os);
	std::string expected = "shared state: " + std::to_string(SIGUSR1) + " - reset to 0";
	ASSERT_EQUAL(expected,os.str());
}

void useSignalingWithThreads(){
	using namespace std::chrono_literals;
	std::ostringstream os;
	std::signal(SIGUSR1,&sighandler);
	std::thread t1{[]{
			std::this_thread::sleep_for(0.5s);
			std::raise(SIGUSR1);
	}};
	//report_state<theSignalHandlerState>(os);
	std::this_thread::sleep_for(1s);
	t1.join();
	report_state<theSignalHandlerState>(os);
	std::string expected = "shared state: " + std::to_string(SIGUSR1) + " - reset to 0";
	ASSERT_EQUAL(expected,os.str());
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(simpleTestHandler));
	s.push_back(CUTE(useSignaling));

	s.push_back(CUTE(useSignalingWithThreads));
	s.push_back(CUTE(nonatomic_simpleTestHandler));	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
