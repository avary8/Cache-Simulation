## Cache Simulation

Read full report: [download](https://raw.githubusercontent.com/avary8/Cache-Simulation/19af857e5f5152f5a445fce98bf78fedae6ebe83/cache_report.pdf) to utilize links in pdf.  
Or [no download](https://github.com/avary8/Cache-Simulation/blob/main/cache_report.pdf) 

The purpose of this program is to create a cache simulation and determine how parameters affect the hit rate of a cache.   
  
To create a new test simulation, type: `cache.initParams(lineSize, cacheSize, linesPerSet, boolean)` into main.cpp
 - the boolean in this case represents the replacement method.
 	- 0 = LRU
 	- 1 = FIFO
      
  There are already 205 tests automatically written in main. After each test, the parameters and hit rate result are printed to the console with '|' as a delimiter.
