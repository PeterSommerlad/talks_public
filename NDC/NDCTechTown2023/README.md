# Safer C++ with MISRA-C++ 2023

[Slides for my talk](https://github.com/PeterSommerlad/NDC/NDCTechTown2023/Safer C++ with MISRA-C++.pdf)

MISRA guidelines and corresponding static analysis tooling exist to foster programming practices that are considered important for safety-critical systems, especially in the automotive industry.
C++
Embedded
Software Design
Security

In application areas where human live or capital is at risk, safe and secure code is a must, but even in other domains the internal quality of C++ programs is an important factor for programmers' effectiveness. Adhering to MISRA-C++ can help to achieve better internal quality, reducing the risk of undefined behavior and portability issues through implementation-defined behavior.

Since the original MISRA-C++ 2008 guidelines that addressed C++03, five new C++ standards were released. While inherently conservative, an update to the MISRA-C++ guidelines was prepared and is (about to be) released in 2023 adressing C++17.

This talk will give an overview of why and what MISRA-C++ attempts to achieve as well as demonstrate some example MISRA-C++ rules and how modern C++ design already fulfils them.
Some seemingly surprising guidelines are shown and explained, why such "unachievalbe" guidelines exist and the rationale behind those guidelines that one seemingly must violate.
For example, an advisory guideline forbids to write your own loops, except for a few cases, which sounds ridiculous on first sight. The talk will show a few cases how to work around but also tells you not to sweat it to hard, but reminds you that getting loop statements correct is really hard.
