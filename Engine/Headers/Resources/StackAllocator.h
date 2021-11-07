#pragma once
#include <stdint.h>
#include "API.h"

// A StackAllocator is a block of contignious memory.
// Like the actual stack it allows for objects to be stored in a LIFO manner, which makes it ideal for loading/unloading levels.
// The implementation seen here is largly based on the Game Engine Architecture book by Jason Gregory.
class StackAllocator
{
public:
	typedef uint64_t Marker;

	ENGINE_API explicit StackAllocator(uint64_t  maxSize);
	ENGINE_API ~StackAllocator();
	// Allocate a chunk of memory on the stack.
	ENGINE_API void* Alloc(uint64_t size);
	void* AllocAligned(uint64_t  size, uint64_t align);
	// Returns the current stack top ptr as marker.
	ENGINE_API Marker GetMarker();
	ENGINE_API void FreeToMarker(Marker marker);
	ENGINE_API void Clear();
private:
	void* _top;
	void* _bottom;
};
