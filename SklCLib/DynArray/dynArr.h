#ifndef _DYNARR_H_
#define _DYNARR_H_
typedef unsigned long long uint64_t;

/*
Memory layout
uint64_t   capacity = number elements that can be held
uint64_t   length   = number of elements currently contained
uint64_t   stride   = size of each element in bytes
void*      elements
*/

typedef enum {
    DARRAY_CAPACITY,
    DARRAY_LENGTH,
    DARRAY_STRIDE,
    DARRAY_FILED_LENGTH
} _darray_data;

void* _darray_create(uint64_t length, uint64_t stride);
void _darray_destroy(void* array);

uint64_t _darray_field_get(void* array, uint64_t field);
void _darray_field_set(void* array, uint64_t field, uint64_t value);

void* _darray_resize(void* array);

void* _darray_push(void* array, const void* value_ptr);
void _darray_pop(void* array, void* dest);

void* _darray_pop_at(void* array, uint64_t index, void* dest);
void* _darray_insert_at(void* array, uint64_t index, void* value_ptr);

#define DARRAY_DEFAULT_CAPACITY 1
#define DARRAY_RESIZE_FACTOR 2

#define darray_create(type) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define darray_reserve(type, capacity) \
    _darray_create(capacity, sizeof(type))

#define darray_destroy(array) _darray_destroy(array);

#define darray_push(array, value)           \
    {                                       \
        typeof(value) temp = value;         \
        array = _darray_push(array, &temp); \
    }
// NOTE: could use __auto_type for temp abovr, but intelisense
// for VSCode flafs it as an unknown type, typeof() seems to 
// work just fint, though. Both are GNU extensions. 

#define darray_pop(array, value_ptr) \
    _darray_pop(array, value_ptr)

#define darray_insert_at(array, index, value)           \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _darray_insert_at(array, index, &temp); \
    }

#define darray_pop_at(array, index, value_ptr) \
    _darray_pop_at(array, index, value_ptr)

#define darray_clear(arrat) \
    _darray_field_set(array, DARRAY_LENGTH, 0)

#define darray_capacity(array) \
    _darray_field_get(array, DARRAY_CAPACITY)

#define darray_length(array) \
    _darray_field_get(array, DARRAY_LENGTH)

#define darray_stride(array) \
    _darray_field_get(array, DARRAY_STRIDE)

#define darray_length_set(array, value) \
    _darray_field_set(array, DARRAY_LENGTH, value)

#endif //_DYNARR_H_