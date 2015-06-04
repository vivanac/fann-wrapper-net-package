This source code depends on 
	FANN - available from http://leenissen.dk/fann/wp/
	Boost - available from http://www.boost.org
	Visual Studio 2012 
	
To Use....

Both Debug and Release builds of Fann.Net.dll are included in the respective directories plus the FANN dependency dlls (fanndouble.dll,fannfixed.dll,fannfloat.dll)
. Add Fann.Net.dll to your references and keep the other dependency dlls in the root directory of your application. Documentation on usage to come...	
	
	
To Build......	
	
	
1) Download Fann 2.2 and Boost <= 1.55.0
2) Create clone of this repo
3) open the solution with vs 2012
4) Set up your boost include path and Fann include path,also set fann librarie's binaries (fanndouble.lib,fannfixed.lib,fannfloat.lib) as additional 
   dependencies in the linker's input tab.And finally add paths to Fann's binary directory (usually bin) in the linkers general tab to the additional
   library directories
5) Build

There is also an XOR test project included in .\Fann.Net.Xor.Test\...


