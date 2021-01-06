#include <chrono>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

const int BUFFER_SIZE = 81920;

int main(int argc, char *argv[])
{
 	char buffer[BUFFER_SIZE]; // default buffer as in c# for apple-to-apple comparison
	int64_t totalBytesRead = 0;
	
	std::cout << "Testing file: " << argv[1] << std::endl;
 
    auto start = std::chrono::steady_clock::now();
 
	// Read all file
	FILE * fp;

	fp = fopen(argv[1], "rb");
	if(fp == NULL) {
		std::cerr << "Unable to open file" << std::endl;
		return 1;
	}
	
	auto startAfterFopen = std::chrono::steady_clock::now();
	
	int64_t bytesRead;
	do {
		bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, fp);
		totalBytesRead += bytesRead;
	} while(bytesRead == BUFFER_SIZE);
	
	fclose(fp);
    auto end = std::chrono::steady_clock::now();
	
	double secondsElapsed = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count())/1000000.0;
	double secondsElapsedAfterOpen = (std::chrono::duration_cast<std::chrono::microseconds>(end - startAfterFopen).count())/1000000.0;
	
	std::cout << "After open:  " << totalBytesRead << " bytes (" << totalBytesRead / 1024.0 / 1024.0 << " MB) copied, " << secondsElapsedAfterOpen << " s, " << (totalBytesRead / secondsElapsedAfterOpen / 1024 / 1024) << " MB/s" << std::endl;
	
	std::cout << "Before open: " << totalBytesRead << " bytes (" << totalBytesRead / 1024.0 / 1024.0 << " MB) copied, " << secondsElapsed << " s, " << (totalBytesRead / secondsElapsed / 1024 / 1024) << " MB/s" << std::endl;
	
	std::cout << "Diff in milliseconds=" << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) - std::chrono::duration_cast<std::chrono::milliseconds>(end - startAfterFopen)).count() << std::endl;

	return(0);
}