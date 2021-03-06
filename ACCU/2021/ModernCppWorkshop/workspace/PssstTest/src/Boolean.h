#ifndef SRC_BOOLEAN_H_
#define SRC_BOOLEAN_H_

#include "pssst.h"

namespace Pssst {
// a better bool?
template <typename B>
struct BooleanOps {
	// attempt shortcut version

	friend constexpr B
	operator || (B const &l, B const &r){
		// no shortcut! but no side effect here useful.
		auto const &[vl]=l;
		auto const &[vr]=r;
		return B{vl || vr};
	}
	template <typename C> // requires is_invocable_r_v<bool,C const&>
	friend constexpr
	std::enable_if_t<std::is_invocable_r_v<bool,C const &>, B >
	operator || (B const &l, C const &r){
		return l?l:B{static_cast<bool>(r())};
	}
	friend constexpr B
	operator && (B const &l, B const &r){
		// no shortcut! but no side effect here useful.
		auto const &[vl]=l;
		auto const &[vr]=r;
		return B{vl && vr};
	}
	template <typename C> // requires is_invocable_r_v<bool,C const&>
	friend constexpr 
	std::enable_if_t<std::is_invocable_r_v<bool,C const &>,B>
	operator && (B const &l, C const &r){
		return l?B{static_cast<bool>(r())}:l;
	}
	friend constexpr B
	operator !(B const &l){
		auto const &[vl]=l;
		return B{! vl};
	}
};
struct Bool:BooleanOps<Bool>, Eq<Bool,Bool> {

	constexpr Bool() noexcept=default;
	constexpr explicit Bool(bool const b) noexcept :
			val { b } {
	}
	constexpr explicit operator bool() const {
		return val;
	}
	bool val{};
};
static_assert(std::is_trivially_copyable_v<Bool>);
static_assert(std::is_trivially_destructible_v<Bool>);

// comparisons with our non-integral Bool as result
template <typename U>
using OrderB = Order<U,Bool>;
template <typename U>
using EqB = Eq<U,Bool>;

}



#endif /* SRC_BOOLEAN_H_ */
