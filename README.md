# MicroJava Compiler

A compiler for **MicroJava**, a small statically typed, Java-like language used as a
case study in compiler construction. This project implements the full pipeline:
lexical analysis, parsing, semantic analysis (context conditions), symbol table
management, and code generation for a stack-based virtual machine.

The language definition and the reference architecture follow the MicroJava
specification in H. Mössenböck, *Compiler Construction: Fundamentals and
Applications* (Appendices A and B).

## Table of Contents

- [Features](#features)
- [Status](#status)
- [Requirements](#requirements)
- [Building](#building)
- [Usage](#usage)
- [Project Layout](#project-layout)
- [Compiler Architecture](#compiler-architecture)
- [Language Overview](#language-overview)
- [Semantic Checks](#semantic-checks)
- [Implementation Limits](#implementation-limits)
- [Example Program](#example-program)
- [Testing](#testing)
- [Error Reporting](#error-reporting)
- [Known Limitations](#known-limitations)
- [References](#references)
- [License](#license)

## Features

- Hand-written scanner with `//` line comments and whitespace filtering
- Recursive-descent parser producing the MicroJava AST
- Scoped symbol table with hiding and declare-before-use enforcement
- Full static type checking: type equality, compatibility, assignment compatibility
- Context-condition checking for every grammar production
- Code generation for a stack machine with automatic jump-label patching
- Bytecode decoder for inspecting generated `.obj` files
- Single-pass compilation with error recovery and a global error counter

## Status

| Component                | Status |
|--------------------------|--------|
| Scanner                  | ✅     |
| Parser                   | ⬜     |
| Symbol table (`Tab`)     | ⬜     |
| Type system (`Struct`)   | ⬜     |
| Semantic analysis        | ⬜     |
| Code generator (`Code`)  | ⬜     |
| Decoder                  | ⬜     |
| Virtual machine (`Run`)  | ⬜     |

<!-- TODO: ⬜ should be replaced with ✅ -->

---

## Requirements

- C++ compiler gcc/clang

---

## Building

With Makefile:

```bash
make 