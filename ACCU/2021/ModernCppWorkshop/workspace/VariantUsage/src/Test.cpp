#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "pssst.h"

#include <sstream>

#include <string>
#include <variant>

enum class errorcode {
	ok, failed_input
};

std::variant<std::string, errorcode> inputName(std::istream & in) {
  std::string name{};
  if (in >> name) return name;
  return errorcode::failed_input;
}


void failing_input() {
	std::istringstream input{};
	auto const res = inputName(input);
	ASSERT_EQUAL(1,res.index());
	ASSERT_EQUAL(errorcode::failed_input, std::get<errorcode>(res));
	ASSERT_THROWS(std::get<0>(res),std::bad_variant_access);
}
void successful_input() {
	std::istringstream input{"Peter"};
	auto const res = inputName(input);
	ASSERT_EQUAL(0,res.index());
	ASSERT_EQUAL("Peter", std::get<std::string>(res));
	ASSERT_THROWS(std::get<errorcode>(res),std::bad_variant_access);
}

// now for polymorphism variant
namespace polyvariant {
using namespace Pssst;

struct Width: strong<int,Width>, Out<Width>{};
struct Height: strong<int,Height>, Out<Height>{};
struct Radius: strong<int,Radius>, Out<Radius>{};

using screen=std::ostream;

struct rect{
	rect(Width w, Height h):
		width{w},height{h}{}
	Width width;
	Height height;
};
void draw(rect const &r, screen& on){
	on << "rectangle:" << r.width << "," << r.height;
}

struct circle{
	circle(Radius r):
		radius{r}{}
	Radius radius;
};
void draw(circle const &c, screen& on){
	on << "circle:" << c.radius;
}
void draw(char const *const &s,screen&os){
	os << "string:"<< s;
}
void draw(int i,screen &os){ // make ints a special case
	os << "an_int:"<<i;
}


struct composite;
using widget = std::variant<rect,circle,composite,int,char const *>;
using widgets=std::vector<widget>;
// helper for visitor, did not make it into C++17
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void draw(widget const &w,screen & on);

struct composite{
	void add(widget w){
		content.emplace_back(std::move(w));
	}
	friend void draw(composite const &c, screen &on){
		on << "{ ";
		for(widget const &drawable : c.content){
			draw(drawable,on);
			on << ',';
		}
		on << " }";
	}
private:
	widgets content{};
};
void draw(widget const &w,screen & on){
	visit(overloaded{
	  [&on](int const &i){ draw(i,on);},
	  [&on](char const *s){ draw(s,on);},
	  [&on](rect const &r){ draw(r,on);},
	  [&on](circle const &c){ draw(c,on);},
	  [&on](composite const &co){ draw(co,on);}
	},w);
}


void testRect(){
	std::ostringstream out{};
	widget r{rect{Width{2},Height{4}}};
	draw(r,out);
	ASSERT_EQUAL("rectangle:2,4",out.str());
}

void testCircle(){
	std::ostringstream out{};
	widget c{circle{Radius{4}}};
	draw(c,out);
	ASSERT_EQUAL("circle:4",out.str());
}
void testComposite(){
	std::ostringstream out{};
	composite c{};
	c.add(circle(Radius{42}));
	c.add(rect(Width{4},Height{2}));
	c.add(circle(Radius{4}));
	c.add(42);
	c.add("a c string");
	widget w{c};
	draw(w,out);
	ASSERT_EQUAL("{ circle:42,rectangle:4,2,circle:4,an_int:42,string:a c string, }",out.str());
}


}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(failing_input));
	s.push_back(CUTE(successful_input));
	s.push_back(CUTE(polyvariant::testRect));
	s.push_back(CUTE(polyvariant::testCircle));
	s.push_back(CUTE(polyvariant::testComposite));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
