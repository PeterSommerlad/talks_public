#include <chrono>


#include <iostream>
#include <thread>

struct UnsynchronizedCounter {
	void increment() {
		++value;
	}

	int current() const {
		return value;
	}
private:
	int value{};
};


int main () {
	UnsynchronizedCounter counter{};
	auto run = [&counter]{
		for (int i = 0; i < 100'000'000; ++i) {
			counter.increment();
		}
	};

	auto const startTime = std::chrono::high_resolution_clock::now();
	std::thread t1{run};
	std::thread t2{run};
	t1.join();
	t2.join();
	auto const endTime = std::chrono::high_resolution_clock::now();
	auto const duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	std::cout << "Counter " << counter.current() << " primes in " << duration.count() << "ms" << std::endl;
}
