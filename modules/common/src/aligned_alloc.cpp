#include "common/aligned_alloc.h"

#ifdef WIN32
#include <malloc.h>
#endif

namespace common
{
    void* aligned_alloc(std::size_t alignment, std::size_t size)
    {
#ifdef WIN32
        return _aligned_malloc(size, alignment);
#else
        return std::aligned_alloc(alignment, size);
#endif
    }
}
