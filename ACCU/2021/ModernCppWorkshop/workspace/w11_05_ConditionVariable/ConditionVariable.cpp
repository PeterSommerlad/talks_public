#include "ThreadsafeQueue.h"
#include <thread>
#include <iostream>
#include <cassert>
#include <shared_mutex>

int main() {
	using namespace std::this_thread;
	using namespace std::chrono_literals;
	ThreadsafeQueue<int> queue { };

	std::thread prod1 { [&] {
		sleep_for(10ms);
		for(int j=0; j < 10; ++j) {
			queue.push(j);
			yield(); //sleep_for(1ms);
		}
	} };
	std::thread prod2 { [&] {
		sleep_for(9ms);
		for(int i=0; i < 10; ++i) {
			queue.push(i*11);
			yield(); //sleep_for(1ms);
		}
	} };
	std::thread cons { [&] {
		do {
			std::cout << queue.pop() << '\n';
			yield();
		} while (!queue.empty());
	} };
	prod1.join(), prod2.join(), cons.join();
	ThreadsafeQueue<int> q2;
	q2.push(1);
	queue.swap(q2);
	assert(1 == queue.pop());
	assert(queue.empty());
	std::cout << "non-processed elements:\n";
	while (!q2.empty()) {
		std::cout << q2.pop() << '\n';
	}
	assert(q2.empty());
}

