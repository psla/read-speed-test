#include <chrono>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

const int BUFFER_SIZE = 81920;

int main(int argc, char *argv[])
{
 	char buffer[BUFFER_SIZE]; // default buffer as in c# for apple-to-apple comparison
	long totalBytesRead = 0;
 
    auto start = std::chrono::steady_clock::now();
 
	// Read all file
	FILE * fp;

	fp = fopen(argv[0], "r");
	auto startAfterFopen = std::chrono::steady_clock::now();
	
	long bytesRead;
	do {
		bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, fp);
		totalBytesRead += bytesRead;
	} while(bytesRead == BUFFER_SIZE);
	
	fclose(fp);
    auto end = std::chrono::steady_clock::now();
	
	double secondsElapsed = (std::chrono::duration_cast<std::chrono::microseconds>(end - start).count())/1000000.0;
	std::cout << totalBytesRead << " bytes (" << totalBytesRead / 1024.0 / 1024.0 << " MB) copied, " << secondsElapsed << " s, " << (totalBytesRead / secondsElapsed / 1024 / 1024) << " MB/s";
	return(0);
}