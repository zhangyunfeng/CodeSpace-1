#include <iostream>
#include "CountId.hpp"


using namespace Ken;

void Usage(void)
{
	std::cout << "Usage: \n Command: ./CountId xmlpath \nLimit: id <= 9999999\nREADME: Find all id in xml file, then you can find all available ids,\n and check if repeat id existed" << std::endl;
	
}

void PrintVector(std::vector<int> ids)
{
	if (ids.empty()) {
		std::cout << "None" << std::endl;
		return;
		
	}
	std::vector<int>::iterator itBegin = ids.begin();
	std::vector<int>::iterator itEnd = ids.end();
	for (itBegin; itBegin != itEnd; itBegin++) {
		std::cout << *itBegin << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	if (argc < 2)  {
		Usage();
		return -1;
		
	}
	
	IdDiscriminator test(argv[1]);
	test.ParseXml();
	
	if (test.HaveRepetitiveids()) {
		std::cout << "========= Repetitive Ids below ========" << std::endl;
		
		std::vector<int> repetitiveids = test.GetRepetitiveIds();
		PrintVector(repetitiveids);
	}

	std::cout << "=========== Available Ids below ==========" << std::endl;
	
	std::vector<int> availableIds;
	availableIds.clear();
	availableIds = test.GetAvailableIdsInRange(10, 100);
	PrintVector(availableIds);
	
	return 0;
}
