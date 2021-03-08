#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>

template<typename T, typename MUTEX = std::mutex>
struct ThreadsafeQueue {
	using guard = std::lock_guard<MUTEX>;
	using lock = std::unique_lock<MUTEX>;

	void push(T const & t) {
		guard lk { mx };
		q.push(t);
		notEmpty.notify_one();
	}

	T pop() {
		lock lk { mx };
		notEmpty.wait(lk, [this] {return !q.empty();});
		T t = q.front();
		q.pop();
		return t;
	}

	bool empty() const {
		guard lk { mx };
		return q.empty();
	}

	void swap(ThreadsafeQueue & other) {
		if (this == &other) {
			return;
		}

		std::scoped_lock both { mx, other.mx };

		std::swap(q, other.q);
	}

private:
	mutable MUTEX mx { };
	std::condition_variable notEmpty { };
	std::queue<T> q { };
};

#endif /* THREADSAFEQUEUE_H_ */
