#include <vector>
#include <initializer_list>
#include "cache_link.h"

void ConstructPagesVectorByInitializer_list(std::vector<Page>& vecPages, std::initializer_list<int> page_init_list) // NOTE: use c++11
{
	for (auto it = page_init_list.begin(); it != page_init_list.end(); it++) {
		vecPages.push_back(Page(*it));
	}
}

int main(int argc, char const *argv[])
{
	Cache_FIFO<Page> cache_fifo(6);

	std::vector<Page> pages_needed;
	pages_needed.clear();
	ConstructPagesVectorByInitializer_list(pages_needed, 
	{ 1, 2, 3, 4, 5, 6, 3, 8, 4, 34, 1, 22, 3, 5, 7, 6, 3, 5 });
	
	
	cache_fifo.RequestPages(pages_needed);
	return 0;
}
