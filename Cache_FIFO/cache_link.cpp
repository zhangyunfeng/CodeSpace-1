#ifndef CACHE_LINK_CPP
#define CACHE_LINK_CPP


#include <string>
#include <vector>
#include <iterator>
#include "cache_link.h"



template<typename T>
Cache_FIFO<T>::Cache_FIFO(const int nPages) : 
	number_pages(nPages), head(NULL)
{
	InitCacheLink();
}

template<typename T>
Cache_FIFO<T>::~Cache_FIFO()
{
	ReleaseCacheLink();
}

template<typename T>
void Cache_FIFO<T>::InitCacheLink(void)
{
	cache_page_link<T>* current_page = NULL;
	current_page = new cache_page_link<T>();
	head = current_page ;
	for (int i = 0; current_page && i < number_pages-1; ++i) {
		current_page->next = new cache_page_link<T>();
		current_page = current_page->next;
	}
	detector = head; 
}

template<typename T>
void Cache_FIFO<T>::AddNewPageToCacheFromMemory(const T& page)
{
	cache_page_link<T>* swapout_page = GetSwapPage();
	if (swapout_page) { 
		swapout_page->data = page;
	}
}

template<typename T>
bool Cache_FIFO<T>::IsPageExisted(const T& page_)
{
	cache_page_link<T>* head_temp = head;
	while (head_temp) {
		if (page_ == head_temp->data) 
			return true;
		head_temp = head_temp->next;
	}
	return false;
}

template<typename T>
cache_page_link<T>* Cache_FIFO<T>::GetSwapPage(void)
{
	cache_page_link<T>* need_swaped_page = NULL;
	if (detector && detector->next) {
		detector = detector->next;
	} else {
		detector = head;
	}
	need_swaped_page = detector;

	return need_swaped_page;
}

template<typename T>
void Cache_FIFO<T>::OutputCachePageLink(void) const
{
	cache_page_link<T>* head_temp = head;
	while (head_temp){
		std::cout << head_temp->data << " ";
		head_temp = head_temp->next;
	}
	std::cout << std::endl;
}

template<typename T>
void Cache_FIFO<T>::ReleaseCacheLink(void)
{
	cache_page_link<T>* current_page = head;
	while (current_page) {
		head = current_page->next;
		delete current_page;
		current_page = head;
	}
}

template<typename T>
void Cache_FIFO<T>::RequestPages(std::vector<T>& pages_needed)
{
	//需要执行的pages， 如果cache中有就从cache中直接取出执行
	//如果某个page没有，就从内存中获取放到cache中
	typename std::vector<T>::iterator itBegin = pages_needed.begin();
	typename std::vector<T>::iterator itEnd = pages_needed.end();
	for (itBegin; itBegin != itEnd; itBegin++, OutputCachePageLink()) {
		if (IsPageExisted(*itBegin)) {
			continue;
		}
		AddNewPageToCacheFromMemory(*itBegin);
		//OutputCachePageLink();
	}
}


#endif // CACHE_LINK_CPP

