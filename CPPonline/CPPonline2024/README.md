# Talk: Vulnerable C++

Slides/Handout for my talk at [C++Online](https://cpponline.uk/) 2024 are [here](TalkVulnerableCpp_cpponline2024.pdf).

## Abstract

Programming languages contain features that could cause code to behave badly. Either by creating hazards in safety critical software, or by creating entry points for attacks in security-critical software.

ISO SC22 WG23 working group collects common language vulnerabilities and provides standards that map the common vulnerabilities to specific programming languages and their mitigations.

This talk will give an overview of typical vulnerabilities and will demonstrate examples on how C++ maps to those generic vulnerabilities and how the upcoming standard 24772-10 provides advice for mitigation.

<hr/>

# Workshop: Safer C++ with MISRA-C++:2023

Handout for my workshop at [C++Online](https://cpponline.uk/) 2024 will be [here](WorkshopSaferCppWithMISRA.pdf).


## Abstract

C++ programmers suffer from the language's complexity as well as from its "super power" of backward compatibility that manifests known and sometimes lesser known deficiencies in language and standard library design.

In application areas where human live or capital is at risk, safe and secure code is a must, but even in other domains the internal quality of C++ programs is an important factor for programmers' effectiveness.

Writing safe and secure code is hard, and requires to circumvent undefined behavior and also portability issues, when development and target platforms differ. Knowing C++ vulnerabilities and potential mitigations is a first step to write better code. Fortunately, there exist guidelines and collections of potential programming pitfalls to draw from. Those might recommend to not use a language feature or use it in a specific way. Often enforced by static analysis tools, such guidance and tooling falls short when applied as an afterthought.

Also, guidelines might be formulated in a way that require you to violate them to achieve the goals of a system. Each deviation from such guidelines should be well thought of, must be documented for safety critical systems, and at best becomes tightly encapsulated.

Using dedicated libraries can help with sidestepping some of the vulnerability problems, such as the woes of implicit conversions of built-in integer types.

This workshop will show you where to look for pitfalls, as well as highlight specific ones and provides concrete design guidance and some libraries to use for your own C++ design and code to follow, so that your code becomes safer and less risky.

### Outline

*  Properties of Safe and Secure Code
*  Origins and Evolution of Guidelines
*  From "Dos and Don'ts" to Design
*  Conscious Class Design
*  Value Values
*  Flavors of Manager Types
*  Strong Types (optional)
*  Integer types without UB and overhead (optional)
*  Understand Relationship Risks
*  Putting Plain Pointers away
*  AMA (ask me anything)
