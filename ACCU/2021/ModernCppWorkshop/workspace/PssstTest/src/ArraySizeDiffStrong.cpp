#include "ArraySizeDiffStrong.h"
#include "cute.h"
#include "pssst.h"

#include <algorithm>

#include <cstddef>
#include <iterator>
#include <stdexcept>

namespace test {
using namespace Pssst;
struct Size: strong<size_t,Size>,ops<Size,Order,Additive,Out> {
};
struct Diff: strong<std::ptrdiff_t,Diff>,ops<Diff,Order,Additive,Out>{};

template <typename T, size_t N>
struct array{
	T a[N];
	using size_type=Size;
	using value_type=T;
	using difference_type=Diff;
	using reference=value_type&;
	using const_reference= value_type const&;
	using pointer=value_type*;
	using const_pointer=const value_type*;
	using iterator=pointer;
	using const_iterator=const_pointer;
	using reverse_iterator=std::reverse_iterator<iterator>;
	using const_reverse_iterator=std::reverse_iterator<const_iterator>;
	constexpr pointer data() { return a;}
	constexpr const_pointer data() const { return a;}
	constexpr reference at( size_type pos ) { if (pos < size()) return a[pos]; throw std::out_of_range{"array::at"};}
	constexpr const_reference at( size_type pos ) const { if (pos < size()) return a[pos]; throw std::out_of_range{"array::at"};}
	constexpr reference operator[]( size_type pos ) { return a[pos];}
	constexpr const_reference operator[]( size_type pos ) const { return a[pos]; }
	constexpr reference front() { return *a;}
	constexpr const_reference front() const{ return *a;}
	constexpr reference back() { return a[N-1];}
	constexpr const_reference back() const{ return a[N-1];}
	constexpr iterator begin() noexcept{return a;}
	constexpr const_iterator begin() const noexcept {return a;}
	constexpr const_iterator cbegin() const noexcept {return a;}
	constexpr iterator end() noexcept {return a+N;}
	constexpr const_iterator end() const noexcept {return a+N;}
	constexpr const_iterator cend() const noexcept {return a+N;}
	constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end());}
	constexpr const_reverse_iterator  rbegin() const noexcept { return const_reverse_iterator(end());}
	constexpr const_reverse_iterator  crbegin() const noexcept { return const_reverse_iterator(end());}
	constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin());}
	constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin());}
	constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin());}
	constexpr bool empty() const noexcept {return N !=0;}
	constexpr size_type size() const noexcept { return size_type{N};}
	constexpr size_type max_size() const noexcept { return size();}
	constexpr void fill( const T& value ) { std::fill(begin(),end(),value);}
	constexpr void swap( array& other ) noexcept(std::is_nothrow_swappable<T>::value){ std::swap_ranges(begin(), end(), other.begin());}
};
template <class T, class... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;


}
cute::suite make_suite_ArraySizeDiffStrong() {
	cute::suite s { };
	return s;
}
