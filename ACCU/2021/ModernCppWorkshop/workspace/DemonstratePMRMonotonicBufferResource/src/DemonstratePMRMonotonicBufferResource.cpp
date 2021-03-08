#include <iostream>
#include <memory_resource>
#include <array>
#include <cstddef>
#include <numeric>
#include <cstdint>
#include <iterator>
#include <algorithm>
#include <new>


namespace {
	std::array<std::byte,1000> myheap{};
}

int use_vector_with_pmr_resource(){
	using namespace std::pmr;
	monotonic_buffer_resource mybuf{
		 myheap.data()
		,myheap.size()
		,null_memory_resource()};
	polymorphic_allocator<std::byte> const myalloc { &mybuf };
	vector<int64_t> v{myalloc};
	try {
		generate_n(std::back_inserter(v),1000,[i=0]()mutable{return i++;});
	} catch (std::bad_alloc const &) {
		// ignore here
	}

	return std::accumulate(begin(v),end(v),0);
}

using namespace std;

int main() {
	cout << use_vector_with_pmr_resource() << '\n';
}
