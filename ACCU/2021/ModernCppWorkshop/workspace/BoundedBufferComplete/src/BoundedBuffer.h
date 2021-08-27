#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iterator>

#include <boost/operators.hpp>
#include <iostream>
template<typename T>
class BoundedBuffer {
public:

	using value_type = T;
	using reference = value_type &;
	using const_reference = value_type const &;
	using size_type = size_t;

	template<typename Iter>
	struct BufferIteratorBase :
			public boost::random_access_iterator_helper<Iter, value_type> {
		using difference_type = typename std::iterator_traits<BufferIteratorBase<Iter>>::difference_type;

		BufferIteratorBase(BoundedBuffer const & buffer, size_type index, bool at_end = false) :
				buffer { buffer }, index { index }, at_end { at_end } {
		}

		bool operator ==(BufferIteratorBase const & other) const {
			return &buffer == &other.buffer && index == other.index && at_end == other.at_end;
		}

		bool operator <(BufferIteratorBase const & other) const {
			checkSameBuffers(other);
			return &buffer == &other.buffer && normalizedIndex() < other.normalizedIndex();
		}

		const_reference operator*() const {
			checkNotAtEnd();
			return buffer.elements()[index];
		}

		friend Iter& operator++(Iter & i) {
			i.checkNotAtEnd();
			i.wrapAroundIncrementIndex();
			i.at_end = (i.index == i.bufferInsertIndex());
			return i;
		}

		friend Iter& operator--(Iter & i) {
			i.checkNotAtBegin();
			i.wrapAroundDecrementIndex();
			i.at_end = false;
			return i;
		}

		friend Iter& operator+=(Iter & i, difference_type diff) {
			if (diff == 0) {
				return i;
			}
			if (i.normalizedIndex() + diff >= i.buffer.capacity()) {
				throw std::logic_error{"must not increase iterator beyond end"};
			}
			if (i.normalizedIndex() + diff < 0) {
				throw std::logic_error{"must not decrease iterator beyond begin"};
			}
			i.index = (i.bufferStartIndex() + i.normalizedIndex() + diff) % i.buffer.capacity();
			i.at_end = (diff > 0) && (i.index == i.bufferStartIndex());

			return i;
		}

		friend Iter& operator-=(Iter& i, difference_type diff) {
			return i += -diff;
		}

		difference_type operator-(BufferIteratorBase const & other) const {
			checkSameBuffers(other);
			return normalizedIndex() - other.normalizedIndex();
		}
	protected:
		void wrapAroundIncrementIndex() {
			index = (index + 1) % buffer.bufferCapacity;
		}

		void wrapAroundDecrementIndex() {
			if (index == 0) {
				index = buffer.bufferCapacity - 1;
			} else {
				index--;
			}
		}

		void checkNotAtEnd() const {
			if (at_end) {
				throw std::logic_error{"must not increment iterator or access element at end"};
			}
		}

		void checkNotAtBegin() const {
			if (index == buffer.startIndex && (!at_end || buffer.empty())) {
				throw std::logic_error{"must not decrement iterator at begin"};
			}
		}

		void checkSameBuffers(BufferIteratorBase const & other) const {
			if (&buffer != &other.buffer) {
				throw std::logic_error{"difference must be on iterators to the same buffer"};
			}
		}

		size_type normalizedIndex() const {
			if (at_end) {
				return buffer.size();
			}
			if (index >= buffer.startIndex) {
				return index - buffer.startIndex;
			}
			return buffer.bufferCapacity - buffer.startIndex + index;
		}

		size_type bufferInsertIndex() const {
			return buffer.getInsertIndex();
		}

		size_type bufferStartIndex() const {
			return buffer.startIndex;
		}

		BoundedBuffer const & buffer;
		size_type index;
		bool at_end;
	};

	struct BufferConstIterator : BufferIteratorBase<BufferConstIterator> {
		using BufferIteratorBase<BufferConstIterator>::BufferIteratorBase;
	};

	struct BufferIterator : BufferIteratorBase<BufferIterator> {
		using BufferIteratorBase<BufferIterator>::BufferIteratorBase;
		reference operator*() const {
			this->checkNotAtEnd();
			return this->buffer.elements()[this->index];
		}
	};


	using const_iterator = BufferConstIterator;
	using iterator = BufferIterator;

	explicit BoundedBuffer(size_type capacity) :
			startIndex { 0 }, nOfElements { 0 }, bufferCapacity { capacity }, values_memory { createElementsMemory(capacity) } {
		if (capacity == 0) {
			throw std::invalid_argument { "Buffer size must be > 0." };
		}
	}

	BoundedBuffer(BoundedBuffer const & other) :
			startIndex { 0 }, nOfElements { other.nOfElements }, bufferCapacity { other.bufferCapacity }, values_memory { createElementsMemory(bufferCapacity) } {
		copyElements(other);
	}

	BoundedBuffer(BoundedBuffer && other) noexcept :
	startIndex {0},
	nOfElements {0},
	bufferCapacity {0},
	values_memory {nullptr}
	{
		swap(other);
	}

	~BoundedBuffer() {
		std::cout << "Deleting" << std::endl;
		popAllElements();
	}

	BoundedBuffer & operator=(BoundedBuffer const & other) {
		if (this != &other) {
			BoundedBuffer copy {other};
			swap(copy);
		}
		return *this;
	}

	BoundedBuffer & operator=(BoundedBuffer && other) {
		swap(other);
		return *this;
	}

	size_type size() const {
		return nOfElements;
	}

	bool empty() const {
		return nOfElements == 0;
	}

	bool full() const {
		return nOfElements == bufferCapacity;
	}

	void push(T const & e) {
		checkNotFull();
		::new(elements() + getInsertIndex())T{ e };
		nOfElements++;
	}

	void push(T && e) {
		checkNotFull();
		::new(elements() + getInsertIndex())T{ std::move(e) };
		nOfElements++;
	}

	reference front() {
		checkNotEmpty();
		return elements()[startIndex];
	}

	const_reference front() const {
		checkNotEmpty();
		return elements()[startIndex];
	}

	reference back() {
		checkNotEmpty();
		return elements()[getLastIndex()];
	}

	const_reference back() const {
		checkNotEmpty();
		return elements()[getLastIndex()];
	}

	void pop() {
		checkNotEmpty();
		front().~T();
		nOfElements--;
		startIndex = (startIndex + 1u) % bufferCapacity;
	}

	void swap(BoundedBuffer & other) {
		std::swap(startIndex, other.startIndex);
		std::swap(nOfElements, other.nOfElements);
		std::swap(bufferCapacity, other.bufferCapacity);
		std::swap(values_memory, other.values_memory);
	}

	iterator begin() {
		return iterator {*this, startIndex, empty()};
	}

	iterator end() {
		return iterator {*this, getInsertIndex(), true};
	}

	const_iterator begin() const {
		return const_iterator {*this, startIndex, empty()};
	}

	const_iterator end() const {
		return const_iterator {*this, getInsertIndex(), true};
	}

	const_iterator cbegin() const {
		return begin();
	}

	const_iterator cend() const {
		return end();
	}

	size_type capacity() const {
		return bufferCapacity;
	}

private:
	size_type startIndex;
	size_type nOfElements;
	size_type bufferCapacity;
	std::unique_ptr<char[]> values_memory;

	void checkNotFull() const {
		if (full()) {
			throw std::logic_error {"Buffer is full"};
		}
	}
	void checkNotEmpty() const {
		if (empty()) {
			throw std::logic_error {"Buffer is empty"};
		}
	}
	size_type getLastIndex() const {
		return (startIndex + nOfElements - 1) % bufferCapacity;
	}

	size_type getInsertIndex() const {
		return (startIndex + nOfElements) % bufferCapacity;
	}

	void copyElements(BoundedBuffer const & other) {
		auto nOfElementsAfterStartIndex = std::min(other.nOfElements, other.bufferCapacity - other.startIndex);

		std::cout << "Copying  " << nOfElementsAfterStartIndex << std::endl;
		std::copy_n(other.elements() + other.startIndex, nOfElementsAfterStartIndex, elements());
		if (nOfElementsAfterStartIndex < other.nOfElements) {
			std::copy_n(other.elements(), other.nOfElements - nOfElementsAfterStartIndex, elements() + nOfElementsAfterStartIndex - other.startIndex);
		}
	}

	void popAllElements() {
		while(!empty()) {
			pop();
		}
	}

	T* elements() const {
		return reinterpret_cast<T*>(values_memory.get());
	}

	static char* createElementsMemory(size_type capacity) {
		return new char[sizeof(T[capacity])];
	}
};

#endif /* BOUNDEDBUFFER_H_ */
