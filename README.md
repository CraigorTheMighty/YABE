YABE - Yet Another Block Encoder
================================

Regular C and OpenCL-based encoders for BC1-5 and ETC1/2 aimed at producing extreme quality output at reasonable performance.

Uses the DevIL library (https://openil.sourceforge.net/download.php) to load source images.

Also includes the RBGCX encoder (https://github.com/richgel999/bc7enc) for the purposes of comparing output. Enable by adding 
"#define USE_RGBCX_ENCODER" to "dds.c".

The BC encoders at "high" quality setting typically beat RGBCX at hidden quality setting 19 slightly in PSNR.

The ETC1 encoder at "normal" quality setting typically beats Crunch at uber quality in PSNR, but with considerably better 
performance.

OpenCL encoders have been tested on Nvidia GTX 1060.

The OpenCL encoders are very complex, and have a habit of exposing the occasional weird driver/compiler bugs. I add workarounds
to these where I can.

On some hardware (notably Intel), the driver doesn't appear to cache results of previous CL program builds, so even loading 
from a pre-compiled binary can result in VERY long load for the application, up to 5 minutes, whereas on Nvidia/AMD hardware, 
loading from binary typically takes a few milliseconds. I currently have no plans to fix this, as the only approach to avoid 
this is to have the application be a persistent background process.
