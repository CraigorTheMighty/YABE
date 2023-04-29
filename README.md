YABE - Yet Another Block Encoder
================================

Regular C and OpenCL-based encoders for BC1-5 and ETC1/2 aimed at producing extreme quality output at reasonable performance.

Dependencies
============

Uses the DevIL library (https://openil.sourceforge.net/download.php) to load source images. DevIL is licensed under LGPL 2.1. The relevant headers, .libs, .dlls are included in this repository.

Uses libKTX (https://github.com/KhronosGroup/KTX-Software/releases/) to save .ktx outputs. libKTX is licensed under the Apache 2.0 license. The relevant headers, .libs, .dlls are included in this repository.

Includes the RBGCX encoder (https://github.com/richgel999/bc7enc) for the purposes of comparing output. Enable by adding "#define USE_RGBCX_ENCODER" to "dds.c". RGBCX is licensed under the MIT license / public domain license.

Quality / Performance
=====================

The BC encoders at "high" quality setting typically beat RGBCX at hidden quality setting 19 slightly in PSNR. As far as I'm aware, RGBCX is currently one of if not the highest-quality BC1-5 encoder out there.

The ETC1 encoder at "normal" quality setting typically beats Crunch at uber quality in PSNR, but with considerably better performance. Again, as far as I'm aware, Crunch is the high-quality ETC1 encoder out there.

Notes Regarding OpenCL
======================

The OpenCL encoders have been tested on an Nvidia GTX 1060. I'm a solo developer so unfortunately I generally don't have access to various different rigs to perform testing on.

The OpenCL encoders are _very_ complex, and have a habit of exposing the occasional weird driver/compiler bugs. The ETC encoder in particular is a verbatim text copy of the C++ version (with some #defines and whatnot providing abstraction between the two languages), so any bugs that appear in the OpenCL encoder should also be reproducible in the C++ version, which they generally aren't. As such I can only assume driver and/or compiler bugs.

On some hardware (specifically Intel), the driver doesn't appear to cache results of previous CL program builds, so even loading from a pre-compiled CL binary can result in a VERY long load for the application, up to 5 minutes, whereas on Nvidia/AMD hardware, loading from a binary typically only takes a few milliseconds after the first time. I currently have no plans to work around this, as the only approach I can think of to avoid this is to have the application be a persistent background process.
