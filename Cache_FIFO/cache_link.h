#ifndef CACHE_LINK_H
#define CACHE_LINK_H

#include <iostream>
#include <vector>
#include <iterator>

class Page
{
public:
	Page() : data(0)
	{

	}
	Page(const int data_) : data(data_)
	{

	}
	Page(const Page& t) : data(0)
	{
		this->data = t.data;
	}

	Page& operator = (const Page& page)
	{
		this->data = page.data;
		return *this;
		
	}

	/* bool operator== (const Page& lpage, const Page& rpage) */
	/* { */
	/* 	return (lpage == const_cast<Page&>(rpage)) */
	/* } */

	friend bool operator== (const Page& lpage, const Page& rpage)
	{
		return (lpage.data == rpage.data);
		
	}

	friend std::ostream& operator << (std::ostream& os, const Page& page)
	{
		os << page.data;
		return os;
	}
public:
	int data;
};

template <typename T>
struct cache_page_link
{
	cache_page_link() : 
		next(NULL), pre(NULL)
	{
	}

	T data;
	cache_page_link* next;
	cache_page_link* pre;
};

template<typename T>
class Cache_FIFO
{
public:
	Cache_FIFO(const int nPages);
	~Cache_FIFO();
	void InitCacheLink(void);

	//从内存中将page放置到cache中
	void AddNewPageToCacheFromMemory(const T& page);
	bool IsPageExisted(const T& page);
	cache_page_link<T>* GetSwapPage(void);
	void OutputCachePageLink(void) const;
	void ReleaseCacheLink(void);
	void RequestPages(std::vector<T>& pages_needed);
private:
	cache_page_link<T>* head;
	cache_page_link<T>* detector;
	const int number_pages;
};


#include "cache_link.cpp"    //c++ 不支持模板的声明和实现分开在不同的文件中

#endif // CACHE_LINK_H
