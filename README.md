# deframework 2.0 - Editor and Runtime
Newschool Demo Editor for Windows

This is an editor to create unrestricted file size demos for the demoscene.

![alt text](https://github.com/JohnnyJimJams/deframework/blob/master/deframework.jpg)

# Building

* Build as x86 only, x64 is not set up yet.

It contains all dependencies, should build out of the box with MS Visual Studio 2017 Community.

# Code design

The editor is used to create and edit demos, and can will spit out a demo as a single file executable.

The code is split into two main concepts

1) Runtime (Maths, OpenGL, loaders, etc)
   Major class: Demo

2) Editor (Imgui and editor code)
   Major Class: Editor

This document could really use some love, but see the TODO.txt for a brain dump of what's left to do, what's been done and bugs.
https://raw.githubusercontent.com/JohnnyJimJams/deframework/master/TODO.txt

