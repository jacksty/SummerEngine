#include "stdafx.h"
#include "StackAllocator.h"
#include "Assert.h"

namespace SE
{
	namespace Memory
	{
		StackAllocator::StackAllocator(size_t bytes) :
			bufferStart((uintptr_t)malloc(bytes)),
			bufferEnd(bufferStart + bytes),
			stackHead(bufferStart)
		{
		}
		
		StackAllocator::~StackAllocator()
		{
			free((void*)bufferStart);
		}

		HeadMark StackAllocator::getHeadMark()
		{
			return HeadMark{ stackHead };
		}

		void* StackAllocator::allocHead(size_t bytes, size_t alignment)
		{
			ASSERT(alignment >= 1);
			ASSERT(alignment <= 128);
			ASSERT(alignment & (alignment - 1) == 0); // ensure that alignment is a power of 2

			uintptr_t alignedAddress;
			size_t alignedSize = bytes + alignment; // calculate size of block to be allocated
			size_t mask = alignment - 1;

#ifdef _DEBUG
			if (stackHead + alignedSize > bufferEnd)
				LOG_MANAGER->log("Memory cap reached in StackAllocator!", LogManager::LL_ERROR | LogManager::LL_DEBUG);
#endif

			// calculate offset needed to adjust address to required alignment
			uintptr_t misalignment = stackHead & mask;
			ptrdiff_t adjustment = alignment - misalignment;

			alignedAddress = stackHead + adjustment; // adjust the address
			stackHead += alignedSize; // move stackHead to the address of the new head

			return reinterpret_cast<void*>(alignedAddress);
		}

		void StackAllocator::popHead(HeadMark mark)
		{
#ifdef _DEBUG
			if (mark.mark < bufferStart || mark.mark > bufferEnd)
				LOG_MANAGER->log("Invalid HeadMark used to pop head of StackAllocator!", LogManager::LL_ERROR | LogManager::LL_DEBUG);
#endif
			stackHead = mark.mark;
		}


		DoubleEndedStackAllocator::DoubleEndedStackAllocator(size_t bytes) :
			StackAllocator(bytes),
			stackTail(bufferEnd)
		{
		}

		DoubleEndedStackAllocator::~DoubleEndedStackAllocator()
		{
			free((void*)bufferStart);
		}

		TailMark DoubleEndedStackAllocator::getTailMark()
		{
			return TailMark{ stackTail };
		}

		void* DoubleEndedStackAllocator::allocTail(size_t bytes, size_t alignment)
		{
			ASSERT(alignment >= 1);
			ASSERT(alignment <= 128);
			ASSERT(alignment & (alignment - 1) == 0); // ensure that alignment is a power of 2

			uintptr_t alignedAddress;
			size_t alignedSize = bytes + alignment; // calculate size of block to be allocated
			size_t mask = alignment - 1;

#ifdef _DEBUG
			if (alignedSize > stackTail - stackHead)
				LOG_MANAGER->log("Memory cap reached in DoubleEndedStackAllocator!", LogManager::LL_ERROR | LogManager::LL_DEBUG);
#endif

			stackTail -= alignedSize; // move stackTail to the address of the new head

			// calculate offset needed to adjust address to required alignment
			uintptr_t misalignment = stackTail & mask;
			ptrdiff_t adjustment = alignment - misalignment;
			alignedAddress = stackTail + adjustment; // adjust the address

			return reinterpret_cast<void*>(alignedAddress);
		}

		void* DoubleEndedStackAllocator::allocHead(size_t bytes, size_t alignment)
		{
			ASSERT(alignment >= 1);
			ASSERT(alignment <= 128);
			ASSERT(alignment & (alignment - 1) == 0); // ensure that alignment is a power of 2

			uintptr_t alignedAddress;
			size_t alignedSize = bytes + alignment; // calculate size of block to be allocated
			size_t mask = alignment - 1;

#ifdef _DEBUG
			if (alignedSize > stackTail - stackHead)
				LOG_MANAGER->log("Memory cap reached in DoubleEndedStackAllocator!", LogManager::LL_ERROR | LogManager::LL_DEBUG);
#endif

			// calculate offset needed to adjust address to required alignment
			uintptr_t misalignment = stackHead & mask;
			ptrdiff_t adjustment = alignment - misalignment;

			alignedAddress = stackHead + adjustment; // adjust the address
			stackHead += alignedSize; // move stackHead to the address of the new head

			return reinterpret_cast<void*>(alignedAddress);
		}

		void DoubleEndedStackAllocator::popTail(TailMark mark)
		{
#ifdef _DEBUG
			if (mark.mark < bufferStart || mark.mark > bufferEnd || mark.mark < stackHead)
				LOG_MANAGER->log("Invalid TailMark used to pop tail in DoubleEndedStackAllocator!", LogManager::LL_ERROR | LogManager::LL_DEBUG);
#endif
			stackTail = mark.mark;
		}
	}
}
