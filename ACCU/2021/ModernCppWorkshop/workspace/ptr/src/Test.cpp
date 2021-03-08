#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <experimental/memory>

static_assert(std::is_trivially_destructible_v<std::experimental::observer_ptr<int>>);




template<typename T>
struct ptr {
	constexpr ptr() noexcept = default;
	constexpr ptr(T *p) noexcept
	: _unwieldly_name{p}{}
	template<typename U
//	, std::enable_if< // 17
	> requires // 20
	std::is_nothrow_convertible_v<std::add_pointer_t<U>,std::add_pointer_t<T>>
	//>> // 17
	constexpr ptr(U *p) noexcept
	: _unwieldly_name{p}{}
constexpr	T* get() const noexcept { return _unwieldly_name;}
constexpr
auto
operator*() const noexcept
-> std::add_lvalue_reference_t<std::enable_if_t< // 17
//requires // 20+
not std::is_void_v<std::remove_cv<T>>
, T>> //17
{ return *get();} // should we throw on nullptr?
constexpr explicit operator bool() const noexcept { return get() != nullptr; }

friend constexpr auto
operator<(ptr const &l, ptr const &r){
	return std::less<T*>{}(l.get(),r.get());
}
private: T* _unwieldly_name{};
};

template<typename T>
ptr(T*) -> ptr<T>;

// ensure optimal

static_assert(std::is_trivially_copyable_v<ptr<int>>);
static_assert(std::is_trivially_destructible_v<ptr<int>>);
static_assert(sizeof(int*) == sizeof(ptr<int>));

// not compiling: static_assert(1+ptr<int>{nullptr});

int to_take_address_from{42};

// not compiling: static_assert(42 == ptr{&to_take_address_from}[0]);

void deduction_construction_test() {
	ptr pi{&to_take_address_from};
	ASSERT_EQUAL(&to_take_address_from, pi.get());
}

void dereference_operator(){
	ptr pi{&to_take_address_from};
	ASSERT_EQUAL(to_take_address_from,*pi);
}


void defaultconstructed_evaluates_to_false(){
	ASSERT(not ptr<int>{});
}
void valid_ptr_evaluates_to_true(){
	ASSERT(ptr{&to_take_address_from});
}

struct B {
	virtual ~B()=default;
};

struct S:B {
};

void check_convertability_works(){
	S x{};
	ptr<B> pb{&x};
	ASSERT_EQUAL(pb.get(),&x);
}
void convertability_fails(){
	B b{};
//	ptr<S> pb(&b); // downcast
//	ptr<int> pbi(&b);
//	ptr<B> pib(&to_take_address_from);

}
void convertible_to_void_works(){
	ptr<void const> p{&to_take_address_from};
	ASSERT_EQUAL(p.get(),&to_take_address_from);
}





bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(deduction_construction_test));
	s.push_back(CUTE(dereference_operator));
	s.push_back(CUTE(defaultconstructed_evaluates_to_false));
	s.push_back(CUTE(valid_ptr_evaluates_to_true));
	s.push_back(CUTE(check_convertability_works));
	s.push_back(CUTE(convertability_fails));
	s.push_back(CUTE(convertible_to_void_works));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
