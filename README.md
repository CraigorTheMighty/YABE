YABE - Yet Another Block Encoder
================================

GUI and command-line programs with regular C and OpenCL-based encoders for BC1-5 and ETC1/2 aimed at producing extreme quality output at reasonable performance.

Output images are saved as .ktx in the case of ETC1/2, and .ktx and/or .dds in the case of BC1-5. In the case of .dds, files will conform to DX9 DDS files when the format can be represented as a DX9 format in the interests of maximum compatibility, and a DX10 DDS file otherwise.

This started as a tiny project, then grew arms and legs, so please excuse the mess.

- Also, if you're hiring: I'm interested. ;)

Usage
=====

Run "YABE.exe" without any arguments in the command-line to get program usage information.

Run "YABE_GUI.exe" to run the GUI version of the program.

Quality / Performance
=====================

The encoders have 4 modes:

- Fast: very high-speed, but low quality
- Normal: reasonable speed, great quality
- High: slower, even better quality
- Best: very slow, best quality

The BC1 encoder at "high" quality setting typically beats RGBCX (https://github.com/richgel999/bc7enc) at hidden quality setting 19 _very slightly_ in PSNR. As far as I'm aware, RGBCX is currently one of if not _the_ highest-quality BC1 encoder out there, so there's not much room for improvement as most block encodings generated by RGBCX are already optimal. The quality improvement is of the order of 0.01 dB for "high", and 0.02 dB for "best".

The alpha-part of BC3, the BC4, and the BC5 encoders at "best" quality find the globally best encoding possible, and as such should always have equal or better quality in relation than MSE to any other encoder out there.

The ETC1 encoder at "normal" quality setting typically beats Crunch (https://github.com/Unity-Technologies/crunch/tree/unity) at "uber" quality in PSNR by 0.02 dB or so, but with considerably better performance. Again, as far as I'm aware, Crunch is the highest-quality ETC1 encoder out there. "High" provides about 0.05 dB improvement, and "best" provides up to around 0.1 dB improvement.

The encoders are fully multithreaded and under normal circumstances will occupy all cores/threads at 100% until encoding is completed.

On my system, Ryzen 9 5900X with 64GB DDR4-1333, Nvidia GTX 1060 3GB on this test suite of image (https://github.com/MohamedBakrAli/Kodak-Lossless-True-Color-Image-Suite/tree/master/PhotoCD_PCD0992):

|BC1 Encoder|Time|Average Quality (dB)|Hardware|
|---|---|---|---|
|RGBCX (Q=19)|63.77s|31.8105|CPU|
|YABE "High"|15.09s|31.8146|**GPU**|
|YABE "High"|39.95s|31.8146|CPU|
|YABE "Best"|21.88s|31.8212|**GPU**|
|YABE "Best"|95.64s|31.8212|CPU|

|ETC1 Encoder|Time|Average Quality (dB)|Hardware|
|---|---|---|---|
|Crunch (Q="Uber")|66.65s|32.6665|CPU|
|YABE "Normal"|10.76s|32.6845|**GPU**|
|YABE "Normal"|23.58s|32.6845|CPU|
|YABE "High"|16.64s|32.7391|**GPU**|
|YABE "High"|50.61s|32.7391|CPU|
|YABE "Best"|20.71s|32.7439|**GPU**|
|YABE "Best"|105.7s|32.7439|CPU|

I've yet to test against a state-of-the-art ETC2 encoder, but will update when I do. :)

Dependencies
============

Uses the DevIL library (https://openil.sourceforge.net/download.php) to load source images. DevIL is licensed under LGPL 2.1. The relevant headers, .libs, .dlls are included in this repository.

Uses libKTX (https://github.com/KhronosGroup/KTX-Software/releases/) to save .ktx outputs. libKTX is licensed under the Apache 2.0 license. The relevant headers, .libs, .dlls are included in this repository.

Includes the RBGCX encoder (https://github.com/richgel999/bc7enc) for the purposes of comparing output. Override the default BC1/4 encoders by adding "#define USE_RGBCX_ENCODER" to "dds.c". RGBCX is licensed under the MIT license / public domain license.

The project also contains a (currently unused) BC6 encoder, and a BC7 encoder from Richard Geldreich, Jr, which is licensed under the MIT license / public domain license.

Compiling
=========

I personally use Microsoft Visual Studio - Community Edition 2022 to build. I've not tested building using other tools or on other OS's, so your mileage may vary.

The code has two entry points: standard "main()" for command-line version, and "WinMain()" for GUI version. In Visual Studio, you can select between them by choosing either "console" or "Windows" under "subsystem" in the linker options.

You _SHOULD_ use a toolchain with OpenMP support that recognises the relevant #pragma statements in the source. The encoders will be _extremely_ slow if you do not have OpenMP support.

You will need to have an OpenCL SDK installed (e.g. https://github.com/KhronosGroup/OpenCL-SDK).

You will need to include the following .libs (included in this repository where possible):

- dbghelp.lib
- opengl32.lib
- DevIL.lib
- ILU.lib
- ILUT.lib
- ktx.lib
- opencl.lib

You must include the following .dlls in the same directory as the final executable (or where Windows can otherwise find them):

- DevIL.dll
- ILU.dll
- ILUT.dll
- ktx.dll

You _MUST NOT_ enable "warnings as errors". The library still has a lot of warnings (some legitimate), mostly regarding casting to smaller types, erroneous "potentially uninitialised variable referenced", and unreferenced function parameters. The (auto-generated) vector math source files do produce a lot of legitimate warnings, but for functions that're never used, so they can be safely ignored. I will likely fix these warnings at some point.

Notes Regarding OpenCL
======================

- The OpenCL encoders have been tested on an Nvidia GTX 1060 and RTX 3060, and integrated Intel HD Graphics. I'm a solo developer so unfortunately I generally don't have access to various different rigs to perform testing on, except when friends are being Helpful.

- The OpenCL encoders are _very_ complex, and have a habit of exposing the occasional weird driver/compiler bugs. The ETC encoder in particular is a verbatim text copy of the C++ version (with some #defines and whatnot providing abstraction between the two languages), so any bugs that appear in the OpenCL encoder should also be reproducible in the C++ version, which they generally aren't. As such I can only assume driver and/or compiler bugs.

- The first time the application is run in BCn or ETC mode on an OpenCL device, it will attempt to find reasonable parameters to run the OpenCL kernels with that codec on that device. This is currently coded to only allow parameters that result in the kernel for each codec completing within 250ms. On most Windows systems, the driver will reset if a kernel occupies the OpenCL device for >2000ms, which is the typical value of TdrDelay (https://learn.microsoft.com/en-us/windows-hardware/drivers/display/tdr-registry-keys). This should never happen under normal circumstances, but may be an issue for very old hardware.

- On some hardware (specifically Intel HD graphics), the driver doesn't appear to cache results of previous CL program builds, so even loading from a pre-compiled CL binary can result in a VERY long load for the application, up to 5 minutes, whereas on Nvidia/AMD hardware, loading from a binary typically only takes a few milliseconds (after the first time). This is mitigated in the GUI version by only loading the kernels once on start-up, but there's currently no workaround for the command-line version.

License
=======

MIT license. You can pretty much do what you like with this code, but please consider attributing me as the source.

Copyright (c) 2023 Craig Sutherland

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
