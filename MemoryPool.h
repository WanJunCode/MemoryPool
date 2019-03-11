#ifndef _MEMORYPOOL_H  
#define _MEMORYPOOL_H  
#include <stdlib.h>

#define MINUNITSIZE 64  
#define ADDR_ALIGN 8  
#define SIZE_ALIGN MINUNITSIZE  

struct memory_chunk;
// sizeof = 24
typedef struct memory_block  
{  
    size_t count;  
    size_t start;  
    memory_chunk* pmem_chunk;       // 记录所绑定的 chunk  
}memory_block;

// 可用的内存块结构体  
// 双链表，每个节点有一个 memory_block
// sizeof = 24
typedef struct memory_chunk  
{  
    memory_block* pfree_mem_addr;  
    memory_chunk* pre;  
    memory_chunk* next;  
}memory_chunk;

// 内存池结构体  sizeof(80)
typedef struct MEMORYPOOL  
{  
    void *memory;                               // 实际可使用内存地址  
    size_t size;                                // 可分配内存大小
    memory_block* pmem_map;                     // 第二部分指针 ，内存映射表
    memory_chunk* pfree_mem_chunk;              // 内存块 双链表
    memory_chunk* pfree_mem_chunk_pool;         // 可用内存块池 双链表
    size_t mem_used_size;                       // 记录内存池中已经分配给用户的内存的大小
    size_t mem_map_pool_count;                  // 记录链表单元缓冲池中剩余的单元的个数，个数为0时不能分配单元给pfree_mem_chunk
    size_t free_mem_chunk_count;                // 可使用 内存双链表个数
    size_t mem_map_unit_count;                  // 单元个数
    size_t mem_block_count;                     // 一个 mem_unit 大小为 MINUNITSIZE  
}MEMORYPOOL, *PMEMORYPOOL;  

/************************************************************************/  
/* 生成内存池 
 * pBuf: 给定的内存buffer起始地址 
 * sBufSize: 给定的内存buffer大小 
 * 返回生成的内存池指针 
/************************************************************************/  
PMEMORYPOOL CreateMemoryPool(void* pBuf, size_t sBufSize);  
/************************************************************************/  
/* 暂时没用 
/************************************************************************/  
void ReleaseMemoryPool(PMEMORYPOOL* ppMem) ;   
/************************************************************************/  
/* 从内存池中分配指定大小的内存  
 * pMem: 内存池 指针 
 * sMemorySize: 要分配的内存大小 
 * 成功时返回分配的内存起始地址，失败返回NULL 
/************************************************************************/  
void* GetMemory(size_t sMemorySize, PMEMORYPOOL pMem) ;  
  
/************************************************************************/  
/* 从内存池中释放申请到的内存 
 * pMem：内存池指针 
 * ptrMemoryBlock：申请到的内存起始地址 
/************************************************************************/  
void FreeMemory(void *ptrMemoryBlock, PMEMORYPOOL pMem) ;  
  
#endif //_MEMORYPOOL_H  