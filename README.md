Table of contents
=================
<!--ts-->
   * [About](#about)
   * [Quick Start](#quick-start)
   * [Dpcumentation](#documentation)
   * [Examples](#examples)
      * [Example 1: Generating Y-bus](#example-1-generating-y-bus)
      * [Example 2: Power flow analysis 1](#example-2-power-flow-analysis-1)
      * [Example 2: Power flow analysis 2](#example-3-power-flow-analysis-2)
<!--te-->

About
=====
‘psystem’ is a C++ library for solving power system related problems. It can be used for configuring a power system, analyzing stability, y-bus, and power-flow of the system.

Quick Start
===========
Download the latest release of “psystem” from github. The release will contain two files one is static library (with ‘.a’ extension) and the other is a header file (with ‘.h’ extension). Link your compiler with the static library and include the header file in your C++ code.

Documentation
=============
Visit the wiki page.

Examples
========
The following examples are made and compiled with Code::Blocks IDE. It is referred to run the projects using the specified IDE but other IDEs will also be able to run the code, but user needs to configure the project from scratch.

## Example 1: Generating Y-bus
## Example 2: Power Flow Analysis 1
![image](https://github.com/rifat-hossain/psystem/assets/35867913/914f60e5-4d31-47a1-a1d6-5921392d1e8b)

The following power system diagram shows all the necessary properties of the system. From the diagram we can say, Bus 1 is the slack bus, Bus 2 is a PQ and Bus 3 is a PV bus.

Step 1, creating Code::Blocks project

https://wiki.codeblocks.org/index.php/Creating_a_new_project

Step 2, linking ‘psystem’ library to the project.

Step 3, including the library header to your code,

Include the following lines of code at the beginning of the C++ file that you want to execute.
```c++
#include <iostream>
#include "psystem.h"
```

Step 4, initializing a power system,

In the `main` function add the following code
```c++
psystem ps;
```
>This will instantiate a power system environment to work with.
>
Step 5, creating buses,

```c++
ps.addBus(Bus(Bus::VD_BUS,1.05,0,true));
ps.addBus(Bus(Bus::PQ_BUS,-4,-2.5,true));
ps.addBus(Bus(Bus::PV_BUS,2,1.04,true));
```
>Parameters of Bus function is *bus type*, *1st variable*, *2nd variable* and *if it is in per unit*.
>From the code we can see, the first bus is a VD bus, the first variable is voltage which is given as 1.05, second variable, angle, is 0 radian and the 4th paramenter tells that they are provided as per unit.

Step 6, adding connections,

```c++
ps.addConn(Connection(1,2,0.02,0.04,1, true));
ps.addConn(Connection(1,3,0.01,0.03,1, true));
ps.addConn(Connection(2,3,0.0125,0.025,1, true));
```

Step 7, power-flow analysis,

```c++
ps.init_ybus();
ps.analyze_powerflow(0.03, 100000);
```

## Example 3: Power Flow Analysis 2
