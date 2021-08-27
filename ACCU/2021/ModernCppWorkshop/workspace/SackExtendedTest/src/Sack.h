#ifndef SACK_H_
#define SACK_H_
#include <vector> // implementation detail, might change...
#include <random>
#include <stdexcept>
#include <initializer_list>
#include <iterator>

template <typename T,
    template<typename...> typename container=std::vector>
class Sack
{
	using SackType=container<T>;
	using size_type=typename SackType::size_type;
	SackType theSack{};
	using difference_type=typename SackType::difference_type;
	inline static std::mt19937 randengine{std::random_device{}()};
	using rand=std::uniform_int_distribution<difference_type>;

public:
	Sack()=default;
	template <typename ITER>
	Sack(ITER b, ITER e):theSack(b,e){}
	Sack(std::initializer_list<T> il):theSack(il){}
	bool empty() const { return theSack.empty() ; }
	size_type size() const { return theSack.size();}
	void putInto(T const &item) { theSack.insert(theSack.end(),item);}
	T getOut(){
		if (empty()) throw std::logic_error{"empty Sack"};
		auto iter=theSack.begin();
		difference_type index = rand{0,static_cast<difference_type>(size())}(randengine);
		std::advance(iter,index);
		T retval{*iter};
		theSack.erase(iter);
		return retval;
	}
	template <typename Elt>
	explicit operator std::vector<Elt>() const {
		return std::vector<Elt>(theSack.begin(),theSack.end());
	}
	template <typename Elt=T>
	std::vector<Elt> asVector() const {
		return std::vector<Elt>(theSack.begin(),theSack.end());
	}
};
template <typename T>
Sack<T> makeSack(std::initializer_list<T> list){
	return Sack<T>{list};
}
template <typename T>
Sack<T> makeSack1(std::initializer_list<T> list){
	Sack<T> sack { };
	for (auto it=list.begin(); it != list.end(); ++ it)
		sack.putInto(*it);
	return sack;
}
template <typename T>
Sack<T> makeSack2(std::initializer_list<T> list){
	Sack<T> sack { };
	for (auto const &elt:list)
		sack.putInto(elt);
	return sack;
}
template <typename T>
Sack<T> makeSack3(std::initializer_list<T> list){
	return Sack<T>(list.begin(),list.end());
}
template <template<typename...> class container,typename T>
Sack<T,container> makeOtherSack(std::initializer_list<T> list){
	return Sack<T,container>{list};
}


#endif /*SACK_H_*/
