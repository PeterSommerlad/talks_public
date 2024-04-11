# ACCU 2024 

## Workshop: "Resilient C++ - Mitigate C++ Vulnerabilities" [slides](ResilienntCpp.pdf)

Safer C++ through guidelines, idioms and libraries

C++ programmers suffer from its super power of backward compatibility, deficiencies in language and standard library design, as well as its complexity. Fortunately, there exist collections of C++ vulnerabilities with their mitigations and guidelines to make your own code less prone to pitfalls caused by using the language and its standard library. This workshop will show you where to look for pitfalls, as well as highlight specific ones and provides concrete guidance or even libraries to use for your own C++ design and code to follow, so that your code becomes safer. It is inspired by the author's work on the MISRA-C++ guidelines and the collection of C++ vulnerabilities in the context of ISO SC22 WG23.

Writing safe and secure code suffers from the language's vulnerabilities. Knowing C++ vulnerabilities and potential mitigations is a first step to write better code. Fortunately there exist guidelines and collections of potential programming pitfalls to draw from. Those might recommend to not use a language feature or use it in a specific way. While this might not absolutely be possible, each violation of such guidelines should be well thought of. Also using dedicated libraries help with sidestepping some problems, such as the woes of implicit conversions of built-int types.
Outline

*    provide a mental model for C++ type design and use
*    demonstrate libraries that help circumventing language pitfalls
*    give examples of C++ vulnerabilities with mitigation hints
*    highlight some MISRA-C++ guidelines applicable beyond the safety realm
*    show some idioms and coding guidelines making your code less vulnerable
*    indicate where to look for further learning, such as ISO WG23, MISRA-C++, CERT, and Core Guidelines
*    notes when to think about violating a guideline consciously and how to convince that you didn't open up to a C++ vulnerabiliy




## Talk: Safer C++ with MISRA-C++:2023


MISRA guidelines and corresponding static analysis tooling exist to foster programming practices that are considered important for safety-critical systems, especially in the automotive industry.

In application areas where human live or capital is at risk, safe and secure code is a must, but even in other domains the internal quality of C++ programs is an important factor for programmers' effectiveness. Adhering to MISRA-C++ can help to achieve better internal quality, reducing the risk of undefined behavior and portability issues through implementation-defined behavior.

Since the original MISRA-C++:2008 guidelines that addressed C++03, five new C++ standards were released. While inherently conservative, an update to the MISRA-C++ guidelines was prepared and is released in 2023 adressing C++17.

This talk will give an overview of why and what MISRA-C++:2023 attempts to achieve as well as demonstrate some example MISRA-C++ rules and how modern C++ design already fulfils them.
Some seemingly surprising guidelines are shown and explained, why such "unachievalbe" guidelines exist and the rationale behind those guidelines that one seemingly must violate.
For example, an advisory guideline forbids to write your own loops, except for a few cases, which sounds ridiculous on first sight. The talk will show a few cases how to work around but also tells you not to sweat it to hard, but reminds you that getting loop statements correct is really hard.