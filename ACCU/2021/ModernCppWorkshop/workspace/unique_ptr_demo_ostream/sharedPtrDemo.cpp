#include <memory>
#include <fstream>
#include <sstream>

enum class to { string, file};

std::unique_ptr<std::ostream> os_factory(to mode){
    if (mode == to::string)
        return std::make_unique<std::ostringstream>();
    else
        return std::make_unique<std::ofstream>("hello.txt");
}


int main(){
	auto out = os_factory(to::file);
	if (out) (*out) << "hello world\n";
	auto fileout = os_factory(to::string);
	if (fileout) (*fileout) << "Hello, world!\n";
	fileout.reset(); // clears unique_ptr, deallocates stream object
}
