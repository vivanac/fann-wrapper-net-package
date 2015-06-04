# fann-wrapper-net-package
Develop package for [FANN] library with .NET [wrapper] and boost

## Instructions

1. Boost
  * Download [boost] 1.58 and unzip it to repo's boost_1_58_0 folder
  * Go to repo's boost_1_58_0 folder then run bootstrap.bat and afterwards b2.exe from cmd
2. Native Fann library
  * Open solution native fann lib in \native\VS2013\fann.sln
  * In configuration manager select "Release" and "x64" platform
  * Build release
3. Wrapper Fann.net 
  * Open wrapper fann-net in \wrapper\Fann.Net.sln
  * In configuration manager select "Release" and "x64" platform (make sure that all projects have x64 and not win32 or anyCPU)
  * Build release
4. After that you are ready to use x64 fann .net wrapper around native fann 2.2.

### Important

In case your project is using FANN wrapper and returns FileNotFoundException you probably forgot to copy FANN wrapper dependencies (fanndouble.dll, fannfixed.dll and fannfloat.dll) on path with fann.net.dll. You can make postbuild action to copy this files to $(TargetDir) folder.

[boost]:http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.7z/download
[FANN]: http://leenissen.dk/fann/wp/
[wrapper]: http://leenissen.dk/fann/wp/2011/02/native-c-net-wrapper-for-fann-released/
