#include <chrono>


#include <iostream>
#include <mutex>
#include <thread>

#include <boost/interprocess/sync/null_mutex.hpp>

template <typename Mutex = std::mutex>
struct ConcurrentCounter {
	using Lock = std::scoped_lock<Mutex>;
	void increment() {
		Lock lock{m};
		++value;
	}

	int current() const {
		Lock lock{m};
		return value;
	}
private:
	mutable Mutex m{};
	int value{};
};



int main () {
	ConcurrentCounter counter{};
//	ConcurrentCounter<boost::interprocess::null_mutex> counter{};
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
