YABE - Yet Another Block Encoder
================================

Regular C and OpenCL-based encoders for BC1-5 and ETC1/2 aimed at producing extreme quality output at reasonable performance.

Dependencies
============

Uses the DevIL library (https://openil.sourceforge.net/download.php) to load source images. DevIL is licensed under LGPL 2.1. The relevant headers, .libs, .dlls are included in this repository.

Uses libKTX (https://github.com/KhronosGroup/KTX-Software/releases/) to save .ktx outputs. libKTX is licensed under the Apache 2.0 license. The relevant headers, .libs, .dlls are included in this repository.

Includes the RBGCX encoder (https://github.com/richgel999/bc7enc) for the purposes of comparing output. Enable by adding "#define USE_RGBCX_ENCODER" to "dds.c". RGBCX is licensed under the MIT license / public domain license.

The project also contains a (currently unused) BC6 encoder, and a BC7 encoder from Richard Geldreich, Jr, which is licensed under the MIT license / public domain license.

Compiling
=========

I personally use Microsoft Visual Studio - Community Edition 2022 to build. I've not tested building using other tools, so your mileage may vary.

You will need to have an OpenCL SDK installed (e.g. https://github.com/KhronosGroup/OpenCL-SDK).

You will also need to include the following .libs (included in this repository where possible):

dbghelp.lib
opengl32.lib
DevIL.lib
ILU.lib
ILUT.lib
ktx.lib
opencl.lib

You _MUST NOT_ enable "warnings as errors". The library still has a lot of warnings (some legitimate), mostly regarding casting to smaller types, erroneous "potentially uninitialised variable referenced", and unreferenced function parameters. The (auto-generated) vector math source files do produce a lot of legitimate warnings, but for functions that're never used, so they can be safely ignored. I will likely fix all the warnings at some point.

Quality / Performance
=====================

The BC encoders at "high" quality setting typically beat RGBCX at hidden quality setting 19 slightly in PSNR. As far as I'm aware, RGBCX is currently one of if not _the_ highest-quality BC1-5 encoder out there.

The ETC1 encoder at "normal" quality setting typically beats Crunch at uber quality in PSNR, but with considerably better performance. Again, as far as I'm aware, Crunch is the high-quality ETC1 encoder out there.

Notes Regarding OpenCL
======================

> The OpenCL encoders have been tested on an Nvidia GTX 1060. I'm a solo developer so unfortunately I generally don't have access to various different rigs to perform testing on.

> The OpenCL encoders are _very_ complex, and have a habit of exposing the occasional weird driver/compiler bugs. The ETC encoder in particular is a verbatim text copy of the C++ version (with some #defines and whatnot providing abstraction between the two languages), so any bugs that appear in the OpenCL encoder should also be reproducible in the C++ version, which they generally aren't. As such I can only assume driver and/or compiler bugs.

> On some hardware (specifically Intel), the driver doesn't appear to cache results of previous CL program builds, so even loading from a pre-compiled CL binary can result in a VERY long load for the application, up to 5 minutes, whereas on Nvidia/AMD hardware, loading from a binary typically only takes a few milliseconds after the first time. I currently have no plans to work around this, as the only approach I can think of to avoid this is to have the application be a persistent background process.


