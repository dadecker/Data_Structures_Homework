#include <cassert>
#include <iostream>
#include <cstdlib>
#include "dlUtils.h"
#include "MemoryManager.h"

MemoryManager::MemoryManager(unsigned int memtotal): memsize(memtotal)
{
   baseptr = new unsigned char[memsize];
   blockdata dummyBlock(0,false,0);
   blockdata originalBlock(memsize,true,baseptr);
   header = new dlNode<blockdata>(dummyBlock,nullptr,nullptr);
   trailer = new dlNode<blockdata>(dummyBlock,nullptr,nullptr);
   header->next = new dlNode<blockdata>(originalBlock,header,trailer);
   trailer->prev = header->next;
}

MemoryManager::~MemoryManager()
{
  delete [] baseptr;
  clearList(header);
}

void MemoryManager::showBlockList() 
{
  printDlList(header,trailer,"->");
}

void MemoryManager::splitBlock(dlNode<blockdata> *p, unsigned int request)
{
	unsigned char * newBlockPtr = p->info.blockptr + request;
	blockdata blockdata1(request,false,p->info.blockptr);
	blockdata blockdata2(p->info.blocksize - request,true,newBlockPtr);
	insertAfter(trailer,p->prev,blockdata1);
	p->info = blockdata2;
}

unsigned char * MemoryManager::malloc(unsigned int request)
{
	dlNode<blockdata> *p = header->next;
	while(p != trailer)
	{
		if(p->info.free == true && p->info.blocksize > request)
		{
			splitBlock(p,request);
			return p->prev->info.blockptr;
		}
		
		if(p->info.free == true && p->info.blocksize == request)
		{
			p->info.free = false;
			return p->info.blockptr;
		}
		
		p = p->next;
	}
	return NULL;	

}

void MemoryManager::mergeForward(dlNode<blockdata> *p)
{
	if(p->next->info.free == true)
	{	
		blockdata newBlock(p->info.blocksize + p->next->info.blocksize, true, p->info.blockptr);
		p->next->info.blockptr = NULL;
		p->info = newBlock;
		deleteNext(header,trailer,p);
		
	}
}

void MemoryManager::mergeBackward(dlNode<blockdata> *p)
{ 
	if(p->prev->info.free == true)
	{
		blockdata newBlock(p->prev->info.blocksize + p->info.blocksize, true, p->prev->info.blockptr);
		p->info.blockptr = NULL;
		p->prev->info = newBlock;
		deleteNode(header,trailer,p);

	}

}

void MemoryManager::free(unsigned char *ptr2block)
{
	dlNode<blockdata>* p = header->next;
	unsigned char * newBlockptr;
	while(p != trailer)
	{
		if(p->info.blockptr == ptr2block)
		{
			p->info.free = true;
			ptr2block = NULL;
			newBlockptr = p->prev->info.blockptr + p->prev->info.blocksize;
			mergeForward(p);
			mergeBackward(p);
			return;		
		}
		p = p->next;
	}
	std::cout << "exiting because the pointer was not found"<< std::endl;
	std::exit(0);
}

