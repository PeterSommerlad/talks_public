
#include <iostream>

template<typename...Types>
void printAll(std::ostream & out,
			  Types const &...all) {
     (out  << ... << all);
}



template<typename First, typename...Types>
void printAllSep(std::ostream & out,
		      First const & first,
			  Types const &...rest) {
  out << first;
  if (sizeof...(Types)) {
     (out  << ... << ((out << ", "), rest));
  }
}

int main() {
	printAll(std::cout, 1,2,3,"hello",' ',"world!\n");
	printAllSep(std::cout, 1,2,3,"hello",' ',"world!\n");
}
