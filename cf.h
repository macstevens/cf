/** cf.c

This file is C source code for parsing and manipulating a C-flat program
*/

#include <stdio.h>

typedef void *void_ptr;
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef long long int64;
typedef unsigned long long uint64;



typedef enum
{
    CF00_OT_OBJECT = 0,
    CF00_OT_PROCEDURE,

    CF00_OT_COUNT
} cf00_managed_object_type;

typedef enum
{
    CF00_RPCT_NONE = 0,
    CF00_RPCT_ARRAY_3,
    CF00_RPCT_LIST,
    CF00_RPCT_TREE,

    CF00_RPCT_COUNT
} cf00_reverse_pointer_container_type;

struct cf00_string_allocator;

typedef struct
{
    struct cf00_string_allocator *m_allocator;
    char *m_buffer;
    uint32 m_length;
    uint32 m_capacity;
} cf00_string;

typedef struct
{
    struct cf00_string_allocator *m_allocator;
    cf00_string *m_buffer;
    uint32 m_length;
    uint32 m_capacity;
} cf00_str_vec;

typedef enum { CF00_ALLOC_BLOCK_SIZE_A = 0x1FE0 } cf00_alloc_block_sz;

typedef struct
{
    uint8 m_raw_memory[CF00_ALLOC_BLOCK_SIZE_A];
    struct cf00_alloc_block_a *m_next_alloc_block;
} cf00_alloc_block_a; 

typedef struct
{
    struct cf00_alloc_block_a *m_alloc_block_chain;
    char *m_free_chain_char_buf_16;
    char *m_free_chain_char_buf_32;
    char *m_free_chain_char_buf_64;
    char *m_free_chain_char_buf_128;
    char *m_free_chain_char_buf_256;
    char *m_free_chain_char_buf_512;
    cf00_string *m_free_chain_string;
    cf00_string *m_free_chain_string_ptr_array_4;
    cf00_str_vec *m_free_chain_str_vec;
} cf00_string_allocator;

void cf00_init_string_allocator(cf00_string_allocator *a);
void cf00_clear_string_allocator(cf00_string_allocator *a);
char *cf00_allocate_char_buf_16(cf00_string_allocator *a);
char *cf00_allocate_char_buf_32(cf00_string_allocator *a);
char *cf00_allocate_char_buf_64(cf00_string_allocator *a);
char *cf00_allocate_char_buf_128(cf00_string_allocator *a);
char *cf00_allocate_char_buf_256(cf00_string_allocator *a);
char *cf00_allocate_char_buf_512(cf00_string_allocator *a);
cf00_string *cf00_allocate_string(cf00_string_allocator *a);
cf00_str_vec *cf00_allocate_str_vec(cf00_string_allocator *a);
void cf00_free_char_buf_16(cf00_string_allocator *a, char *buf);
void cf00_free_char_buf_32(cf00_string_allocator *a, char *buf);
void cf00_free_char_buf_64(cf00_string_allocator *a, char *buf);
void cf00_free_char_buf_128(cf00_string_allocator *a, char *buf);
void cf00_free_char_buf_256(cf00_string_allocator *a, char *buf);
void cf00_free_char_buf_512(cf00_string_allocator *a, char *buf);
void cf00_free_string(cf00_string_allocator *a, cf00_string *s);
void cf00_free_str_vec(cf00_string_allocator *a, cf00_str_vec *sv);


typedef void *cf00_void_ptr_array3[3];


typedef struct
{
    void *m_ptr;
    struct cf00_ptr_list_node *m_prev;
    struct cf00_ptr_list_node *m_next;
} cf00_ptr_list_node;

typedef struct
{
    void *m_cf00_ptr_list_node_allocator;
    cf00_ptr_list_node *m_head;
    uint32 m_size;
} cf00_ptr_list;

typedef struct 
{
    cf00_managed_object_type m_object_type;
    cf00_reverse_pointer_container_type m_rev_ptr_ctr_type;
    void *m_allocator;
    union
    {
        cf00_void_ptr_array3 m_rev_ptr_array_3;
        cf00_ptr_list m_rev_ptr_list;
        /* tree */
    };
} cf00_managed_object_data;



typedef struct
{
    cf00_managed_object_data m_object_data; /* must be first */

    
    
} cf00_procedure;



typedef struct
{
    /*  base time */
    /* enum {base_time_epoch, unix_1970_epoch} m_epoch */
    /* enum { seconds, milliseconds, microseconds, weeks, years } m_time_unit */
    int64 m_ticks;
} cf00_time;


typedef struct
{
    cf00_managed_object_data m_object_data; /* must be first */
    cf00_string m_file_name;
    cf00_str_vec m_relative_file_path;
    cf00_str_vec m_absolute_file_path;
    uint64 m_file_length;
    uint32 m_adler_32_sum;
    uint8 m_md5_sum[16];
    cf00_time m_modified_time;
    uint8 m_is_this_file;
    
  
} cf00_file_data;

typedef struct
{
    cf00_managed_object_data m_object_data; /* must be first */
    cf00_file_data *m_file_data;
    uint64 m_section_begin_pos;
    uint64 m_section_end_pos;   
  
} cf00_file_sub_section_a;


typedef struct
{
    cf00_managed_object_data m_object_data; /* must be first */
    cf00_file_data *m_file_data;
    uint64 m_section_begin_pos;
    uint64 m_section_end_pos;   
    cf00_string m_first_bytes;
    cf00_string m_last_bytes;
    uint32 m_begin_line_index;
    uint32 m_end_line_index;
    uint16 m_begin_line_offset;
    uint16 m_end_line_offset;
    uint32 m_adler_32_sum;
} cf00_file_sub_section_b;


typedef enum
{
    CF00_RT_NONE = 0,

    /* attribute (one-way relation, so to speak) */

    /* binary relation */
    CF00_RT_PREV_NEXT,
    CF00_RT_BEFORE_AFTER,

    /* ternary relation */

    /* n-way relation */

    CF00_RT_COUNT
} cf00_relation_type;


typedef struct
{
    cf00_managed_object_data m_object_data; /* must be first */
    cf00_relation_type m_relation_type; /* must be second */
    void *m_object_0;
} cf00_unary_relation;

typedef struct
{
    cf00_managed_object_data m_object_data; /* must be first */
    cf00_relation_type m_relation_type; /* must be second */
    void *m_object_0;
    void *m_object_1;
} cf00_binary_relation;


typedef struct
{
    cf00_managed_object_data m_object_data; /* must be first */
    cf00_relation_type m_relation_type; /* must be second */

    void *m_object_0;
    void *m_object_1;
    void *m_object_2;

} cf00_ternary_relation;








