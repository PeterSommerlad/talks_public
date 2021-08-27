#ifndef SACK_H_
#define SACK_H_
#include <vector> // implementation detail, might change...
#include <random>
#include <stdexcept>
template <typename T>
class Sack
{
	using SackType=std::vector<T>;
	using size_type=typename SackType::size_type;
	SackType theSack{};

	inline static std::mt19937 randengine{std::random_device{}()};
	using rand=std::uniform_int_distribution<size_type>;
public:
	bool empty() const { return theSack.empty() ; }
	size_type size() const { return theSack.size();}
	void putInto(T const &item) { theSack.push_back(item);}
	T getOut() ;
	template <typename Elt = T>
	explicit operator std::vector<Elt>() const {
		return std::vector<Elt>(theSack.begin(),theSack.end());
							// () to avoid initializer_list ctor
	}
};
template <typename T>
inline T Sack<T>::getOut(){
		if (empty()) throw std::logic_error{"empty Sack"};
		auto index = rand{0u,size()}(randengine);
		T retval{theSack.at(index)};
		theSack.erase(theSack.begin()+index);
		return retval;
}
#include <initializer_list>
template <typename T>
Sack<T> makeSack(std::initializer_list<T> list){
	Sack<T> sack;
	for (auto it=list.begin(); it != list.end(); ++ it)
		sack.putInto(*it);
	return sack;
}

#endif /*SACK_H_*/
