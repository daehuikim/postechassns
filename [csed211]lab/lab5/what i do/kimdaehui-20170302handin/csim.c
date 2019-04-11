// andrea0119
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <math.h>
#include "cachelab.h"

typedef unsigned long long int memoryAddress;


struct cacheParameter {      // 입력받는 캐시의 기본정보를 확인하는 것
	int s;
	int b;
	int E;
	int S;
	int B;
	int hits;
	int misses;
	int evicts;
};

struct setLine {          //한 라인 구조
	int latestUsed;
	int valid;
	memoryAddress tag;
	char *block;
};

struct cacheSet {    // 한 셋 구조
	struct setLine *lines;
};

struct cache {      // 한 캐쉬 구조
	struct cacheSet *sets;
};

struct cache initCache(long long numberOfSets, int numberOfLines, long long sizeOfBlock)
{    //입력받은 값들을 바탕으로 캐시를 메모리안에 할당한다.

	struct cache newCache;
	struct cacheSet set;
	struct setLine line;
	int indexOfSet;
	int indexOfLine;

	newCache.sets = (struct cacheSet*) malloc(sizeof(struct cacheSet) * numberOfSets); =

	for (indexOfSet = 0; indexOfSet < numberOfSets; indexOfSet++)
	{        //0의값으로 초기화해주는 단계이다

		set.lines = (struct setLine *) malloc(sizeof(struct setLine) * numberOfLines);
		newCache.sets[indexOfSet] = set;

		for (indexOfLine = 0; indexOfLine < numberOfLines; indexOfLine++)
		{
			line.latestUsed = 0;
			line.valid = 0;
			line.tag = 0;
			set.lines[indexOfLine] = line;
		}

	}

	return newCache;

}

void cleanFunction(struct cache myCache, long long numberOfSets, int numberOfLines, long long sizeOfBlock)
{     
	//메모리를 초기화해주는 함수
	int indexOfSet;
	for (indexOfSet = 0; indexOfSet < numberOfSets; indexOfSet++)
	{
		struct cacheSet set = myCache.sets[indexOfSet];

		if (set.lines != NULL) {
			free(set.lines);
		}

	}
	if (myCache.sets != NULL) {
		free(myCache.sets);
	}
}

int detectEmptyLine(struct cacheSet exampleSet, struct cacheParameter exampleParameter) {
	// vaild값을 조회해서 empty한 line인지 아닌지를 판별한다.

	int numberOfLines = exampleParameter.E;
	int index;
	struct setLine line;

	for (index = 0; index < numberOfLines; index++) {
		line = exampleSet.lines[index];
		if (line.valid == 0) {   
			return index;
		}
	}
	return -1;    
}

int detectEvictLine(struct cacheSet exampleSet, struct cacheParameter exampleParameter, int *usedLines) {
	// eviction을 판명하기 위해서 변수들을 초기화한 이후에 최근 사용된 라인을 확인한다.

	int numberOfLines = exampleParameter.E;
	int maxFreqUsage = exampleSet.lines[0].latestUsed;     
	int minFreqUsage = exampleSet.lines[0].latestUsed;	 
	int indexOfLine;

	for (indexOfLine = 1; indexOfLine < numberOfLines; indexOfLine++) {
		if (minFreqUsage > exampleSet.lines[indexOfLine].latestUsed) {
			minFreqUsage_index = indexOfLine;
			minFreqUsage = exampleSet.lines[indexOfLine].latestUsed;
		}

		if (maxFreqUsage < exampleSet.lines[indexOfLine].latestUsed) {
			maxFreqUsage = exampleSet.lines[indexOfLine].latestUsed;
		}
	}

	usedLines[0] = minFreqUsage;
	usedLines[1] = maxFreqUsage;
	return minFreqUsage_index;
}

struct cacheParameter accessTheCacheData(struct cache myCache, struct cacheParameter exampleParameter, memoryAddress address) {
	int indexOfLine;
	int checkFullCache = 0; 

	int numberOfLines = exampleParameter.E;
	int previousHit = exampleParameter.hits;

	int tagSize = (64 - (exampleParameter.s + exampleParameter.b));    //  t = m-s-b
	//변수들 선언, 초기화후에 입력받은 주소에서 필요한 값들을 추출해낸다.
	memoryAddress inputTag = address >> (exampleParameter.s + exampleParameter.b);
	unsigned long long temp = address << (tagSize);
	unsigned long long indexOfSet = temp >> (tagSize + exampleParameter.b);

	struct cacheSet exampleSet = myCache.sets[indexOfSet];

	for (indexOfLine = 0; indexOfLine < numberOfLines; indexOfLine++) {

		if (exampleSet.lines[indexOfLine].valid) {   

			if (exampleSet.lines[indexOfLine].tag == inputTag) {

				exampleSet.lines[indexOfLine].latestUsed++;  
				exampleParameter.hits++;    
			// 발리드하고 태그값이 같으면 hit
		}
		else if (!(exampleSet.lines[indexOfLine].valid) && (checkFullCache)) {
			checkFullCache = 0;	    // empty값이 있으면 Full하지 않은것을 체크
		}
		// 
	}

	if (previousHit == exampleParameter.hits) {   
		exampleParameter.misses++;    // hit되지 않고 나오면 miss
	}
	else {
		return exampleParameter;
	}
	int *usedLines = (int*)malloc(sizeof(int) * 2);
	int minFreqUsage_index = detectEvictLine(exampleSet, exampleParameter, usedLines);

	if (checkFullCache) //full cache가 hit되지 않을 경우 evict
	{
		exampleParameter.evicts++;
		exampleSet.lines[minFreqUsage_index].tag = inputTag;
		exampleSet.lines[minFreqUsage_index].latestUsed = usedLines[1] + 1;

	}

	else //그렇지 않으면은 empty에 tag적기
	{
		int empty_index = detectEmptyLine(exampleSet, exampleParameter);
		exampleSet.lines[empty_index].tag = inputTag;
		exampleSet.lines[empty_index].valid = 1;
		exampleSet.lines[empty_index].latestUsed = usedLines[1] + 1;
	}

	free(usedLines);
	return exampleParameter;
}

int main(int argc, char **argv)
{

	struct cache myCache;
	struct cacheParameter exampleParameter;
	bzero(&exampleParameter, sizeof(exampleParameter));  //처음에 0으로 초기화해준상태로 선언
	long long numberOfSets;
	long long sizeOfBlock;
	FILE *openTrace;
	char instructionInTraceFile;
	memoryAddress address;
	int size;
	char *trace_file;
	char c;
	//arg들을 입력받아서 파싱하는 부분이다.
	while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
	{
		switch (c)
		{
		case 's':
			exampleParameter.s = atoi(optarg);
			break;
		case 'E':
			exampleParameter.E = atoi(optarg);
			break;
		case 'b':
			exampleParameter.b = atoi(optarg);
			break;
		case 't':
			trace_file = optarg;
			break;
		case 'h':
			exit(0);
		default:
			exit(1);
		}
	}
	//set,line갯수를 2제곱으로 받아들이기
	numberOfSets = pow(2.0, exampleParameter.s);   /
	sizeOfBlock = pow(2.0, exampleParameter.b);  
	exampleParameter.hits = 0;
	exampleParameter.misses = 0;
	exampleParameter.evicts = 0;
	myCache = initCache(numberOfSets, exampleParameter.E, sizeOfBlock);

	//trace파일을 읽어들인다.
	openTrace = fopen(trace_file, "r");
	if (openTrace != NULL) {
		while (fscanf(openTrace, " %c %llx,%d", &instructionInTraceFile, &address, &size) == 3) {
			switch (instructionInTraceFile) {
			case 'I':
				break;
			case 'L':
				exampleParameter = accessTheCacheData(myCache, exampleParameter, address);
				break;
			case 'S':
				exampleParameter = accessTheCacheData(myCache, exampleParameter, address);
				break;
			case 'M':
				exampleParameter = accessTheCacheData(myCache, exampleParameter, address);
				exampleParameter = accessTheCacheData(myCache, exampleParameter, address);
				break;
			default:
				break;
			}
		}
	}

	printSummary(exampleParameter.hits, exampleParameter.misses, exampleParameter.evicts);
	cleanFunction(myCache, numberOfSets, exampleParameter.E, sizeOfBlock);
	fclose(openTrace);
	return 0;
}