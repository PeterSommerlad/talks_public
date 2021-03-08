#include "httplib.h"

#include <algorithm>

#include <future>
#include <iostream>
#include <iterator>


void printHeaders(std::ostream & out, httplib::Headers const & headers) {
	out << "Headers: " << '\n';
	std::transform(std::begin(headers), std::end(headers), std::ostream_iterator<std::string>{out, "\n"}, [] (auto const & header) {
		return header.first + ": " + header.second;
	});
}


int main() {
    httplib::Client cli("www.w3.org", 80);
    auto fetchUrl = [&] (std::string_view url) {
		return cli.Get(url.data());
	};
    auto future = std::async(std::launch::async, fetchUrl, "/");
    std::cout << "Do something else...\n";
    auto result = future.get();
    if (result) {
    	printHeaders(std::cout, result->headers);
    }
}

