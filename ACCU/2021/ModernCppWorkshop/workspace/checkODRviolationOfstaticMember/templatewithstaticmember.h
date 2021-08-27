#ifndef TEMPLATEWITHSTATICMEMBER_H_
#define TEMPLATEWITHSTATICMEMBER_H_
template <typename T>
struct staticmember{
	inline static int dummy{sizeof(T)};
};
#endif /* TEMPLATEWITHSTATICMEMBER_H_ */
