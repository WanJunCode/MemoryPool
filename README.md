# MemoryPool
内存池 使用 c 编写

参考链接
https://blog.csdn.net/yuanchunsi/article/details/78497624

将buffer分为四部分，第1部分是mem_pool结构体；第2部分是内存映射表；第3部分是内存chunk结构体缓冲区；第4部分是实际可分配的内存区。

第1部分的作用是可以通过该mem_pool结构体控制整个内存池。

第2部分的作用是记录第4部分，即实际可分配的内存区的使用情况。表中的每一个单元表示一个固定大小的内存块（block），多个连续的block组成一个chunk。

第3部分是一个mem_chunk pool，其作用是存储整个程序可用的mem_chunk结构体。其中pmem_block指向该chunk在内存映射表中的位置，others表示其他一些域，不同的实现对应该域的内容略有不同。

第4部分就是实际可以被分配给用户的内存。
整个内存池管理程序除了这四部分外，还有一个重要的内容就是 memory chunk set。虽然其中的每个元素都来自mem_chunk pool，但是它与mem_chunk pool的不同之处在于其中的每个memory chunk中记录了当前可用的一块内存的相关信息。而mem_chunk pool中的memory chunk的内容是无定以的。可以这样理解mem_chunk pool与memory chunk set：mem_chunk pool是为memory chunk set分配内存的“内存池”，只是该“内存池”每次分配的内存大小是固定的，为mem_chunk结构体的大小。内存池程序主要是通过搜索这个memory chunk set来获取可被分配的内存。在memory chunk set上建立不同的数据结构就构成了不同的内存池实现方法，同时也导致了不同的搜索效率，直接影响内存池的性能，本文稍后会介绍两种内存池的实现。
memory chunk set 就是逻辑上的可使用内存块

使用映射表的目的是为了更加快的从 第四部分找到对应的地址。
第三部分 内存池 逻辑结构使用双链表，直观的显示可用的内存块以及内存块大小。