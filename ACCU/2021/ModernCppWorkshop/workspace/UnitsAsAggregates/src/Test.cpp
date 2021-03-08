#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"


namespace Psst{


template<typename B, template<typename...>class T>
struct bind2{
	template<typename A, typename ...C>
	using apply=T<A,B,C...>;
};
template<typename A, template<typename...>class T>
struct bind1{
	template<typename ...B>
	using apply=T<A,B...>;
};

template <typename U, template <typename ...> class ...BS>
struct ops:BS<U>...{};


template <typename V, typename TAG>
struct Unit {
	static_assert(std::is_object_v<V>,"must keep real values");
	V val;
};



template <typename U>
struct is_unit{
	template<typename T>
	static char test(decltype(T::val)*);
	template<typename T>
	static long long test(...);
	static inline constexpr bool value=sizeof(test<U>(nullptr))==sizeof(char);
};

template<typename U>
constexpr inline  bool is_strong_v=is_unit<U>::value;


static_assert(!is_strong_v<int>,"int is no unit");
namespace _____testing_____{
struct bla:Unit<int,bla>{};
static_assert(is_strong_v<bla>,"bla is a unit");
}

// ops templates

template <typename U>
struct Inc{
	friend constexpr auto operator++(U &rv) noexcept {
		return ++rv.val;
	}
	friend constexpr auto operator++(U &rv,int) noexcept {
		auto res=rv;
		++rv;
		return res;
	}
};


template <typename U>
struct Eq{
	friend constexpr bool
	operator==(U const &l, U const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		return l.val == r.val;
	}
	friend constexpr bool
	operator!=(U const &l, U const& r) noexcept {
		return !(l==r);
	}
};
template <typename U, typename V>
struct EqWithImpl{
	friend constexpr bool
	operator==(U const &l, V const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		static_assert(!std::is_same_v<U,V>,"can not be applied to identical types");
		if constexpr(is_strong_v<V>)
			return l.val == r.val;
		else
			return l.val == r;
	}
	friend constexpr bool
	operator==(V const &l, U const& r) noexcept {
		return r == l;
	}
	friend constexpr bool
	operator!=(U const &l, V const& r) noexcept {
		return !(l==r);
	}
	friend constexpr bool
	operator!=(V const &l, U const& r) noexcept {
		return !(r==l);
	}
};

template <typename W>
using EqWith=bind2<W,EqWithImpl>;

template <typename U>
struct Cmp{
	friend constexpr bool
	operator<(U const &l, U const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		return l.val < r.val;
	}
	friend constexpr bool
	operator>(U const &l, U const& r) noexcept {
		return r < l;
	}
	friend constexpr bool
	operator<=(U const &l, U const& r) noexcept {
		return !(r < l);
	}
	friend constexpr bool
	operator>=(U const &l, U const& r) noexcept {
		return !(l < r);
	}
};
template <typename U, typename V>
struct CmpWithImpl{
	friend constexpr bool
	operator<(U const &l, V const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		static_assert(!std::is_same_v<U,V>,"can not be applied to identical types");
		if constexpr(is_strong_v<V>)
			return l.val < r.val;
		else
			return l.val < r;
	}
	friend constexpr bool
	operator<(V const &l, U const& r) noexcept {
		static_assert(is_strong_v<U>,"can only be applied to units");
		static_assert(!std::is_same_v<U,V>,"can not be applied to identical types");
		if constexpr(is_strong_v<V>)
			return l.val < r.val;
		else
			return l < r.val;
	}
	friend constexpr bool
	operator>(U const &l, V const& r) noexcept {
		return r > l;
	}
	friend constexpr bool
	operator>(V const &l, U const& r) noexcept {
		return r > l;
	}
	friend constexpr bool
	operator<=(U const &l, V const& r) noexcept {
		return !(r > l);
	}
	friend constexpr bool
	operator<=(V const &l, U const& r) noexcept {
		return !(r > l);
	}
	friend constexpr bool
	operator>=(U const &l, V const& r) noexcept {
		return !(l < r);
	}
	friend constexpr bool
	operator>=(V const &l, U const& r) noexcept {
		return !(l < r);
	}
};
template <typename W>
using CmpWith=bind2<W,CmpWithImpl>;


template <typename U>
struct Add {
	friend constexpr U&
	operator+=(U& l, U const &r) noexcept {
		l.val += r.val;
		return l;
	}
	friend constexpr U
	operator+(U l, U const &r) noexcept {
		return l+=r;
	}
};

template <typename U>
struct Out {
	friend std::ostream&
	operator<<(std::ostream &l, U const &r) {
		return l << r.val;
	}
};

struct WaitC:Unit<unsigned,WaitC>, ops<WaitC,Out,Add,Inc,Eq,EqWith<unsigned>::apply>
{
};
static_assert(is_strong_v<WaitC>,"should be a unit");
static_assert(sizeof(WaitC)==sizeof(unsigned),"works?");
static_assert(std::is_trivial_v<WaitC>,"standard layout");
}

void testAWaitCounterUnit(){
	using namespace Psst;
	WaitC wc{42};
	++wc;
	ASSERT_EQUAL(43u,wc);
	ASSERT(wc!=42u);
	ASSERT_EQUAL(WaitC{43},wc);
}
void testAddingWaitCounter(){
	using namespace Psst;
	WaitC wc{42};
	wc += WaitC{42u};
	wc = wc + wc;
	ASSERT_EQUAL(168u,wc);
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testAWaitCounterUnit));
	s.push_back(CUTE(testAddingWaitCounter));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
