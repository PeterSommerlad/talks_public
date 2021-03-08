#include <atomic>
#include <thread>
#include <iostream>

using namespace std::this_thread;

void outputWhenReady(std::atomic_flag & flag, std::ostream & out) {
	while (flag.test_and_set(std::memory_order_acquire))
		yield();
	out << "Here is thread: " << get_id() << std::endl;
	flag.clear(std::memory_order_release);
}

int main() {
	using std::cout;
	using std::endl;
	std::atomic_flag flag { };
	std::thread t { [&flag] {outputWhenReady(flag, cout);} };
	outputWhenReady(flag, cout);
	t.join();
}
