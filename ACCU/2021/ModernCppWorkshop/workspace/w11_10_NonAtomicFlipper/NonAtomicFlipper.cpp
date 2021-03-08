#include <iostream>
#include <thread>
#include <iomanip>
#include <ios>

//-m32 Needs 32-Bit Compiler!

struct Flipper {
	void flip() {
		while (true) {
			value = ~value;
		}
	}
	auto get() const {
		return value;
	}
private:
	long long value { 0 };
};

int main(int argc, char **argv) {
	Flipper flipper { };
	std::thread flipperThread { [&] {
		flipper.flip();
	} };
	std::cout << std::hex;
	while (true) {
		auto tmp = flipper.get();
		if (tmp != 0ll && tmp != ~0ll) {
			std::cout << "Surprise! Value is 0x" << std::setw(sizeof(tmp) * 2) << std::setfill('0') << tmp << std::endl;
		}
	}
	flipperThread.join();
}
