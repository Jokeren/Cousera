#include <cstdio>
#include "algorithm.h"

const char* file_name = "../data/web-Google.txt";

int main()
{
	pagerank::Algorithm	*algorithm = new pagerank::Algorithm(file_name);

	algorithm->run();

	return 0;
}

