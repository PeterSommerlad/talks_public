## Slides for my NDC Techtown 2026 talk

[Slides](https://github.com/PeterSommerlad/talks_public/blob/main/NDC/NDCTechTown2026/intnotsafe.pdf)


# int != safe && int != ℤ

C++ integers suffer from potential inaccuracy in arithmetic operations as well as undefined behavior.

This talk shows the risks involved in inappropriate integer operations and the problems with integral promotion and the "usual arithmetic conversions" that in addition to the original operands types can further confuse programmers.

We will take a look at MISRA C++ guidelines with respect to integer arithmetic and operations and see where are their limitations in static analysis.

However, the power of C++ and new standard library features will allow us to implement safer alternatives. It might be a bit of art required to actually achieve syntactical nicety, efficient implementation and well-defined behavior when dealing with whole numbers and integers. 

Note: this talk will not include approaches for unlimited precision arithmetic that might be required for some domains.



* assess the risk of integer arithmetic quiz
* why are there hidden problems, shouldn't integers just wrap?
* what safety guidelines say
* options for dealing with inaccuracy (overflow)
* C++26: saturation arithmetic


# Safer C++ with MISRA-C++:2023 and beyond

The handouts for my workshop will be made available to participants only.

As a co-author of the MISRA-C++:2023 guidelines and contributor to ISO SC22 WG23 C++ vulnerabilities standard (24772-10) the trainer is in a unique position to provide insights into these safety standards while not being one of the tooling implementors.

You will learn how to write conforming C++ in a constructive way, instead of reacting to compliancy checker warnings. We will look at, for example,


* vulnerabilities of built-in integral types and how to sidestep those.
* using user-defined types to improve the design and decrease vulnerabilities of function interfaces.
* acknowledging vulnerabilities of pointer-like types and how to reduce the need for them.
* MISRA-compliant class design from Rule-of-Zero, Rule of DesDeMovA, Modern Rule-of-Three, to the Rule-of-Five/Six for General Manager types.
* specific vulnerabilities of concurrent code and how upcoming MISRA C++ might address them.
* MISRA-C++ guidelines intended to be deviated, so that such deviation is deliberate, thoughtful, and documented.
* plus more...


This is not a workshop addressing the most recent C++26 features, but cares for modern C++ in high quality and safety and security related setting. If you bring your own code examples and questions to discuss you can make the most out of this workshop and draw from Peter's four decades of experience as a developer and educator in providing developer guidance (First C++ guidelines published 1992), creating reliable software, and teaching software engineering.