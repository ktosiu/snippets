#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cassert>

const size_t allocator_page_size = 32768;

struct allocator_page
{
    allocator_page* next_page;
    size_t offset;
    char data[allocator_page_size];
};

struct allocator_state
{
    allocator_page* current;
};

void* allocate_new_page_data(size_t size)
{
    size_t extra_size = (size > allocator_page_size) ? size - allocator_page_size : 0;
    return malloc(sizeof(allocator_page) + extra_size);
}

void* allocate_oob(allocator_state* state, size_t size)
{
    allocator_page* page = (allocator_page*)allocate_new_page_data(size);
    page->next_page = state->current;
    state->current = page;
    page->offset = size;
    return page->data;
}

void* allocate(allocator_state* state, size_t size)
{
    if(state->current->offset + size <= allocator_page_size)
    {
        void* result = state->current->data + state->current->offset;
        state->current->offset += size;
        return result;
    }
    return allocate_oob(state, size);
}

int main()
{
    allocator_state state;
    allocator_page init_page;
    state.current = &init_page;
    void* pbuf = allocate(&state, 10);
    assert(pbuf);
    return 0;
}
