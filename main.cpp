#include "Cache.h"

int main() {
    Cache cache;
	//init params (line, cache, assoc, replacement method)
	//replace: 0 = LRU.	
	//         1 = FIFO
	int testNum = 0;
	cout << "==============FA Examples==============\n";
	cout << "Test Num|Line sz|Cache sz|/|Replace|Hit Rate\n";
	for (int i = 4; i < 7; i++){//2^4 , 2^5, 2^7 
		for(int j = 10; j < 15; j++){//2^10 , 2^11, 2^12, 2^13, 2^14 
			cache.initParams(pow(2, i), pow(2, j), pow(2, j)/pow(2, i), 0);
			cout << testNum << " | " << pow(2, i) << " | " <<  pow(2, j) << " | / | " << "LRU | " << cache.hitRate << "\n";
			//cout << testNum << "|" << pow(2, i) << "|" <<  pow(2, j) << "|" << (pow(2, j)/pow(2, i)) << "|0|\n" ;
			testNum++; 
			cache.initParams(pow(2, i), pow(2, j), pow(2, j)/pow(2, i), 1); 	
			cout << testNum << " | " << pow(2, i) << " | " <<  pow(2, j) << " | / | " << " FIFO | " << cache.hitRate << "\n";
			//cout << testNum << "|" << pow(2, i) << "|" <<  pow(2, j) << "|" <<(pow(2, j)/pow(2, i)) << "|1|\n" ;
			testNum++;	
		}
	}
	
	cout << "==============DM Examples==============\n";
	cout << "Test num|Line sz|Cache sz|/|/|Hit Rate\n";
	for (int i = 4; i < 7; i++){//2^4 , 2^5, 2^7 
		for(int j = 10; j < 15; j++){//2^10 , 2^11, 2^12, 2^13, 2^14 
			cache.initParams(pow(2, i), pow(2, j), 1, 0);
			cout << testNum << " | " << pow(2, i) << " | " <<  pow(2, j) << " | / | / | " << cache.hitRate << "\n"; 
			//cout << testNum << "|" << pow(2, i) << "|" <<  pow(2, j)  << "|1|0|\n" ;
			testNum++; 
			//replacement method doesnt matter for DM 		
		}
	} 
	
	cout << "==============N-Way Set Associative Examples==============\n";
	cout << "Test num|Line sz|Cache sz|LinesPerSet|Replace|Hit Rate\n";

	for (int h = 1; h < 7; h++){
		for (int i = 4; i < 7; i++){//2^4 , 2^5, 2^7 
			for(int j = 10; j < 15; j++){//2^10 , 2^11, 2^12, 2^13, 2^14 
				if (pow(2, j) / pow(2, i) > pow(2, h)){
					/*numLines > Lines Per set , because numSets = numLines / linesPerSet 
						if numLines <= linesPerSet , then numSets is <= 1 which defeats the purpose of n-way 
					*/
					cache.initParams(pow(2, i), pow(2, j), pow(2, h), 0);
					cout << testNum << " | " << pow(2, i) << " | " <<  pow(2, j) << " | " << pow(2, h) << "-way | LRU | " << cache.hitRate << "\n";
					//cout << testNum << "|" << pow(2, i) << "|" <<  pow(2, j) << "|" << pow(2, h) << "|0|\n";
					testNum++; 
					cache.initParams(pow(2, i), pow(2, j), pow(2, h), 1);
					cout << testNum << " | " << pow(2, i) << " | " <<  pow(2, j) << " | " <<  pow(2, h) << "-way | FIFO | " << cache.hitRate << "\n"; 
					//cout << testNum << "|" << pow(2, i) << "|" <<  pow(2, j) << "|" << pow(2, h) << "|1|\n";
					testNum++;	
				}
			}
		}
	}


	//needed averages
	// int div = 0;
	// float lAvg = 0;
	// float FAvg = 0;
	
	// for (int h = 1; h < 7; h++){
	// 	for(int j = 10; j < 15; j++){//2^10 , 2^11, 2^12, 2^13, 2^14 
	// 		for (int i = 4; i < 7; i++){//2^4 , 2^5, 2^7 
	// 			if (pow(2, j) / pow(2, i) > pow(2, h)){
	// 				/*numLines > Lines Per set , because numSets = numLines / linesPerSet 
	// 					if numLines <= linesPerSet , then numSets is <= 1 which defeats the purpose of n-way 
	// 				*/
	// 				cache.initParams(pow(2, i), pow(2, j), pow(2, h), 0);
	// 				//cout << testNum << " | " << pow(2, i) << " | " <<  pow(2, j) << " | " << pow(2, h) << "-way | LRU | " << cache.hitRate << "\n";
	// 				//cout << testNum << "|" << pow(2, i) << "|" <<  pow(2, j) << "|" << pow(2, h) << "|0|\n";
	// 				lAvg += cache.hitRate;

	// 				testNum++; 
	// 				cache.initParams(pow(2, i), pow(2, j), pow(2, h), 1);
	// 				//cout << testNum << " | " << pow(2, i) << " | " <<  pow(2, j) << " | " <<  pow(2, h) << "-way | FIFO | " << cache.hitRate << "\n"; 
	// 				//cout << testNum << "|" << pow(2, i) << "|" <<  pow(2, j) << "|" << pow(2, h) << "|1|\n";
	// 				FAvg += cache.hitRate;
	// 				testNum++;	

	// 				div++;
	// 			}
	// 		}
	// 		lAvg /= div; 
	// 		FAvg /=div;
	// 		cout << pow(2,j) << "|" << pow(2, h) << "-way | LRU | " << lAvg << "\n";
	// 		cout << pow(2,j) << "|" << pow(2, h) << "-way | FIFO | " << FAvg << "\n";
	// 		div = 0;
	// 		lAvg = 0;
	// 		FAvg = 0;

	// 	}
	// }
}

