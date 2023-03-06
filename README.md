Cache Simulation

The purpose of this program is to create a cache simulation and determine how parameters affect the hit rate of a cache. To create a new test simulation, simply type 
	cache.initParams(lineSize, cacheSize, linesPerSet, boolean)
	the boolean in this case represents the replacement method.
		0 = LRU 
		1 = FIFO
	There are already 205 tests automatically written in main. After each test, the 	parameters and hit rate result are printed to the console with '|' as a delimiter.
 
Compile and Run:
In order to compile this program, you will simply need to download and open these files in the code editor or program of your choice, such as VSC, VS, Intellij, etc. Ensure the code editor such as VSC is able to run c++ files by having gcc and MinGW-w64 via https://www.msys2.org/ which also provides other useful downloads such as GCC (for windows). For macOS have Clang. 