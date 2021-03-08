#include "Planet.h"

#include <chrono>
#include <iostream>
#include <utility>

template <typename Action>
std::chrono::milliseconds measure(Action action) {
	auto start = std::chrono::high_resolution_clock::now();
	auto const keepAlive = action(); //Keep the result alive to avoid measuring the destruction
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	return duration;
}


int main() {
	//Instantiation
	auto constructionAction = []{Planet<87000000> earth{}; return earth;};
	auto const constructionDuration = measure(constructionAction);
	std::cout << "Construction of Planet took: " << constructionDuration.count() << "ms\n";

	//Copying
	Planet<87000000> earth{};
	auto copyAction = [&]{auto copy{earth}; return copy;};
	auto const copyDuration = measure(copyAction);
	std::cout << "Copying of Planet took: " << copyDuration.count() << "ms\n";

	//Moving
	auto moveAction = [&]{auto moved{std::move(earth)}; return moved;};
	auto const moveDuration = measure(moveAction);
	std::cout << "Moving of Planet took: " << moveDuration.count() << "ms\n";
}
