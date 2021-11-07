#include "Resources\StackAllocator.h"
#include <xmemory>

StackAllocator::StackAllocator(uint64_t maxSize)
{
	_top = malloc(maxSize);
	_bottom = _top;
}

StackAllocator::~StackAllocator()
{
	free(_bottom);
	_top = nullptr;
	_bottom = nullptr;
}

void* StackAllocator::Alloc(uint64_t size)
{
	void* ptr = _top;
	_top = static_cast<char*>(_top) + size;
	return ptr;
}

StackAllocator::Marker StackAllocator::GetMarker()
{
	return reinterpret_cast<Marker>(_top);
}

void StackAllocator::FreeToMarker(StackAllocator::Marker marker)
{
	// Only change the unused memory to 0 when running debug.
	// Todo: Maybe replace the _DEBUG define with something else.
#ifdef _DEBUG
	for (uint64_t i = (uint64_t)_top; i >= marker; i--)
	{
		char* c = (char*)i;
		*c = 0;
	}
#endif // _DEBUG
	_top = reinterpret_cast<void*>(marker);
}

void StackAllocator::Clear()
{
	FreeToMarker(reinterpret_cast<uint64_t>(_bottom));
}