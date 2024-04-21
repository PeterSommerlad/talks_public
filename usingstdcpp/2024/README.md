Here you can find the slides/handouts for my workshop and talk at using std::c++ 2024.

# Keynote: The new MISRA-C++:2023 Safety Guidelines

MISRA guidelines and corresponding static analysis tooling exist to foster programming practices that are considered important for safety-critical systems, especially in the automotive industry.
In application areas where human live or capital is at risk, safe and secure code is a must, but even in other domains the internal quality of C++ programs is an important factor for programmers' effectiveness. Adhering to MISRA-C++ can help to achieve better internal quality, reducing the risk of undefined behavior and portability issues through implementation-defined behavior.

Since the original MISRA-C++ 2008 guidelines that addressed C++03, five new C++ standards were released. While inherently conservative, an update to the MISRA-C++ guidelines that the presenter contributed to was released in 2023 adressing C++17.

This talk will give an overview of why and what MISRA-C++:2023 attempts to achieve as well as demonstrate some example MISRA-C++:2023 rules and how contemporary C++ design already fulfils them.

Some seemingly surprising guidelines are shown and explained, why such "unachievalbe" guidelines exist and the rationale behind those guidelines that one seemingly must violate.

# Workshop: [Contemporary Design for Safer C++]([https://github.com/PeterSommerlad/talks_public/tree/main/usingstdcpp/2024](https://github.com/PeterSommerlad/talks_public/blob/main/usingstdcpp/2024/Workshop_Contemporary%20Design%20for%20Safer%20C%2B%2B.pdf)/)



C++ programmers suffer from the language's complexity as well as from its "super power" of backward compatibility that manifests known and sometimes lesser known deficiencies in language and standard library design.

In application areas where human live or capital is at risk, safe and secure code is a must, but even in other domains the internal quality of C++ programs is an important factor for programmers' effectiveness.

Writing safe and secure code is hard, and requires to circumvent undefined behavior and also portability issues, when development and target platforms differ. Knowing C++ vulnerabilities and potential mitigations is a first step to write better code. Fortunately, there exist guidelines and collections of potential programming pitfalls to draw from. Those might recommend to not use a language feature or use it in a specific way. Often enforced by static analysis tools, such guidance and tooling falls short when applied as an afterthought.

This tutorial demonstrates C++ techniques and design practices that proactively circumvent critical parts of C++ but still allow for good performance and clean code.

Using dedicated libraries can help with sidestepping some of the vulnerability problems, such as the woes of implicit conversions of built-in integer types.

This tutorial will show you where to look for pitfalls, as well as highlight specific ones and provides concrete design guidance and some libraries to use for your own C++ design and code to follow, so that your code becomes safer and less risky.
