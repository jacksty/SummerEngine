#pragma once
#include "stdafx.h"

#define MEMORY_UNALIGNED 1


namespace SE
{
	namespace Memory // The Memory namespace should only ever be accessed externally by MemoryManager
	{
		// HeadMark and TailMark are simply wrappers meant to prevent confusion when determining which side a mark came from.
		typedef struct HeadMark final
		{
			const uintptr_t mark;
		} HeadMark;
		typedef struct TailMark final
		{
			const uintptr_t mark;
		} TailMark;


		/////////////////////////////////////////////////////////////////////////////////////////
		class StackAllocator
		{
			// ATTRIBUTES
		protected:
			/// The address in memory where the buffer belonging to this stack begins.
			const uintptr_t bufferStart;
			/// The address in memory where the buffer belonging to this stack ends.
			const uintptr_t bufferEnd;

			/// Pointer to the beginning of the most recent element added to the head.
			uintptr_t stackHead;

			// CONSTRUCTORS / DESTRUCTORS
		public:
			StackAllocator(size_t bufferSize);
			virtual ~StackAllocator();

			// METHODS
		public:
			/// Allocate and push a block of memory of the given size to the head of the stack.
			virtual void* allocHead(size_t bytes, size_t alignment = MEMORY_UNALIGNED);
			/// Get a mark pointing to the current head of the stack. Can be used to deallocate everything pushed to the head after this point in time.
			HeadMark getHeadMark();
			/// Deallocate all memory pushed to the head after mark was taken.
			void popHead(HeadMark mark);
		};


		/////////////////////////////////////////////////////////////////////////////////////////
		class DoubleEndedStackAllocator : public StackAllocator
		{
			// ATTRIBUTES
		protected:
			/// Pointer to the beginning of the most recent element added to the tail.
			uintptr_t stackTail;

			// CONSTRUCTORS / DESTRUCTORS
		public:
			DoubleEndedStackAllocator(size_t bufferSize);
			~DoubleEndedStackAllocator() override;

			// METHODS
		public:
			/// Allocate and push a block of memory of the given size to the head of the stack.
			void* allocHead(size_t bytes, size_t alignment = MEMORY_UNALIGNED) override;
			/// Allocate and push a block of memory of the given size to the tail of the stack.
			void* allocTail(size_t bytes, size_t alignment = MEMORY_UNALIGNED);
			/// Get a mark pointing to the current tail of the stack. Can be used to deallocate everything pushed to the tail after this point in time.
			TailMark getTailMark();
			/// Deallocate all memory pushed to the tail after mark was taken.
			void popTail(TailMark mark);
		};
	}
}
