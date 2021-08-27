#include "bounded_buffer_content_suite_no_default.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include "n_times.h"
#include <stdexcept>
#include <vector>

using namespace cpp_advanced::times_literal;

namespace no_default_ctor {
struct NoDefaultCtor{
	NoDefaultCtor(int i):val{i}{}
	int val;
	operator int() const { return val;}
};


void test_buffer_is_not_empty_after_push_rvalue() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	ASSERTM("Buffer should not be empty after push", !buffer.empty());
}

void test_buffer_is_not_empty_after_push_lvalue() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	int const lvalue { 5 };
	buffer.push(lvalue);
	ASSERTM("Buffer should not be empty after push", !buffer.empty());
}

void test_buffer_is_empty_after_one_push_and_pop() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	buffer.pop();
	ASSERTM("Buffer should be empty after one push and pop", buffer.empty());
}

void test_buffer_of_size_two_is_full_after_two_pushs() {
	BoundedBuffer<NoDefaultCtor, 2> buffer { };
	2_times([&]() {buffer.push(5);});
	ASSERTM("Buffer of size two should be full after two pushs", buffer.full());
}

void test_buffer_size_is_one_after_push() {
	BoundedBuffer<NoDefaultCtor, 2> buffer { };
	buffer.push(1);
	ASSERT_EQUAL(1, buffer.size());
}

void test_buffer_size_is_fifty_after_fifty_pushs() {
	BoundedBuffer<NoDefaultCtor, 75> buffer { };
	50_times([&]() {buffer.push(5);});
	ASSERT_EQUAL(50, buffer.size());
}

void test_buffer_front_gets_element_of_push() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	ASSERT_EQUAL(5, buffer.front());
}

void test_buffer_back_gets_element_of_push() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	ASSERT_EQUAL(5, buffer.back());
}

void test_buffer_front_gets_first_element_of_pushs() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(1);
	buffer.push(2);
	ASSERT_EQUAL(1, buffer.front());
}

void test_buffer_back_gets_last_element_of_two_pushs() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(1);
	buffer.push(2);
	ASSERT_EQUAL(2, buffer.back());
}

void test_buffer_front_throws_after_push_pop() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	buffer.pop();
	ASSERT_THROWS(buffer.front(), std::logic_error);
}

void test_buffer_back_throws_after_push_pop() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	buffer.pop();
	ASSERT_THROWS(buffer.back(), std::logic_error);
}

void test_const_buffer_front_gets_element_of_push() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	auto const & constBuffer = buffer;
	ASSERT_EQUAL(5, constBuffer.front());
}

void test_const_buffer_back_gets_element_of_push() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	auto const & constBuffer = buffer;
	ASSERT_EQUAL(5, constBuffer.back());
}

void test_const_buffer_front_gets_first_element_of_pushs() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(1);
	buffer.push(2);
	auto const & constBuffer = buffer;
	ASSERT_EQUAL(1, constBuffer.front());
}

void test_const_buffer_back_gets_last_element_of_two_pushs() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(1);
	buffer.push(2);
	auto const & constBuffer = buffer;
	ASSERT_EQUAL(2, constBuffer.back());
}

void test_const_buffer_front_throws_after_push_pop() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	buffer.pop();
	auto const & constBuffer = buffer;
	ASSERT_THROWS(constBuffer.front(), std::logic_error);
}

void test_const_buffer_back_throws_after_push_pop() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	buffer.push(5);
	buffer.pop();
	auto const & constBuffer = buffer;
	ASSERT_THROWS(constBuffer.back(), std::logic_error);
}

void test_buffer_fronts_in_sequence_of_push_pop() {
	BoundedBuffer<NoDefaultCtor, 5> buffer { };
	std::vector<int> frontValues { }, expectedValues { 1, 1, 1, 2, 2, 3, 4, 4, 5 };
	buffer.push(1);
	frontValues.push_back(buffer.front());
	buffer.push(2);
	frontValues.push_back(buffer.front());
	buffer.push(3);
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.push(4);
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.push(5);
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	ASSERT_EQUAL(expectedValues, frontValues);
}

void test_buffer_wrap_around_behavior_front() {
	BoundedBuffer<NoDefaultCtor, 3> buffer { };
	std::vector<int> frontValues { }, expectedValues { 1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 5, 6, 7 };
	buffer.push(1);
	frontValues.push_back(buffer.front());
	buffer.push(2);
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.push(3);
	frontValues.push_back(buffer.front());
	buffer.push(4);
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.push(5);
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.push(6);
	frontValues.push_back(buffer.front());
	buffer.push(7);
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	buffer.pop();
	frontValues.push_back(buffer.front());
	ASSERT_EQUAL(expectedValues, frontValues);
}

void test_buffer_wrap_around_behavior_back() {
	BoundedBuffer<NoDefaultCtor, 3> buffer { };
	std::vector<int> backValues { }, expectedValues { 1, 2, 2, 3, 4, 4, 4, 5, 5, 6, 7, 7, 7 };
	buffer.push(1);
	backValues.push_back(buffer.back());
	buffer.push(2);
	backValues.push_back(buffer.back());
	buffer.pop();
	backValues.push_back(buffer.back());
	buffer.push(3);
	backValues.push_back(buffer.back());
	buffer.push(4);
	backValues.push_back(buffer.back());
	buffer.pop();
	backValues.push_back(buffer.back());
	buffer.pop();
	backValues.push_back(buffer.back());
	buffer.push(5);
	backValues.push_back(buffer.back());
	buffer.pop();
	backValues.push_back(buffer.back());
	buffer.push(6);
	backValues.push_back(buffer.back());
	buffer.push(7);
	backValues.push_back(buffer.back());
	buffer.pop();
	backValues.push_back(buffer.back());
	buffer.pop();
	backValues.push_back(buffer.back());
	ASSERT_EQUAL(expectedValues, backValues);
}

void test_buffer_after_swap_this_has_argument_content() {
	std::vector<int> frontValues { }, expectedValues { 1, 2, 3 };
	BoundedBuffer<NoDefaultCtor, 5> buffer { }, otherBuffer { };
	buffer.push(1);
	buffer.push(2);
	buffer.push(3);
	otherBuffer.swap(buffer);
	3_times([&]() {frontValues.push_back(otherBuffer.front()); otherBuffer.pop();});
	ASSERT_EQUAL(expectedValues, frontValues);
}

void test_buffer_after_swap_argument_has_this_content() {
	std::vector<int> frontValues { }, expectedValues { 1, 2, 3 };
	BoundedBuffer<NoDefaultCtor, 5> buffer { }, otherBuffer { };
	buffer.push(1);
	buffer.push(2);
	buffer.push(3);
	buffer.swap(otherBuffer);
	3_times([&]() {frontValues.push_back(otherBuffer.front()); otherBuffer.pop();});
	ASSERT_EQUAL(expectedValues, frontValues);
}
}
cute::suite make_suite_bounded_buffer_content_suite_no_default() {
	cute::suite s;
	s.push_back(CUTE(no_default_ctor::test_buffer_is_not_empty_after_push_rvalue));
	s.push_back(CUTE(no_default_ctor::test_buffer_is_not_empty_after_push_lvalue));
	s.push_back(CUTE(no_default_ctor::test_buffer_is_empty_after_one_push_and_pop));
	s.push_back(CUTE(no_default_ctor::test_buffer_of_size_two_is_full_after_two_pushs));
	s.push_back(CUTE(no_default_ctor::test_buffer_size_is_one_after_push));
	s.push_back(CUTE(no_default_ctor::test_buffer_size_is_fifty_after_fifty_pushs));
	s.push_back(CUTE(no_default_ctor::test_buffer_front_gets_element_of_push));
	s.push_back(CUTE(no_default_ctor::test_buffer_back_gets_element_of_push));
	s.push_back(CUTE(no_default_ctor::test_buffer_front_gets_first_element_of_pushs));
	s.push_back(CUTE(no_default_ctor::test_buffer_back_gets_last_element_of_two_pushs));
	s.push_back(CUTE(no_default_ctor::test_buffer_front_throws_after_push_pop));
	s.push_back(CUTE(no_default_ctor::test_buffer_back_throws_after_push_pop));
	s.push_back(CUTE(no_default_ctor::test_const_buffer_front_gets_element_of_push));
	s.push_back(CUTE(no_default_ctor::test_const_buffer_back_gets_element_of_push));
	s.push_back(CUTE(no_default_ctor::test_const_buffer_front_gets_first_element_of_pushs));
	s.push_back(CUTE(no_default_ctor::test_const_buffer_back_gets_last_element_of_two_pushs));
	s.push_back(CUTE(no_default_ctor::test_const_buffer_front_throws_after_push_pop));
	s.push_back(CUTE(no_default_ctor::test_const_buffer_back_throws_after_push_pop));
	s.push_back(CUTE(no_default_ctor::test_buffer_fronts_in_sequence_of_push_pop));
	s.push_back(CUTE(no_default_ctor::test_buffer_wrap_around_behavior_front));
	s.push_back(CUTE(no_default_ctor::test_buffer_wrap_around_behavior_back));
	s.push_back(CUTE(no_default_ctor::test_buffer_after_swap_this_has_argument_content));
	s.push_back(CUTE(no_default_ctor::test_buffer_after_swap_argument_has_this_content));
	return s;
}

