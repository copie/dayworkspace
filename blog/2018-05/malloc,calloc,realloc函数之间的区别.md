# malloc,calloc,realloc 函数之间的区别

在 C 语言中内存可以分为五个区域: 堆, 栈, 全局/静态存储区, 常量存储区和自由存储区.
栈区(stack): 函数执行时, 局部变量, 函数形参, 和临时变量都是在栈区获得内存,由编译器自动完成的, 函数执行结束时这些存储单元自动被释放.栈内存的分配运算内置于处理器指令集中,效率很高,但分配的内存容量有限;
堆区(heap): 一般由程序员分配释放, 若程序员不释放, 则可能会引起内存泄漏(memory leak), C 标准函数库提供了许多函数来实现对堆上内存管理其中就包括:
malloc函数, calloc函数, realloc函数和free函数, 使用这些函数需要包含头文件stdlib.h.

## malloc()函数

动态内存分配(dynamic memory allocation), 从堆区分配指定字节(byte)的内存.

    void* malloc (size_t size);

其中形参size为需要分配的内存字节数, 分配成功的话, 函数返回已分配内存的首地址; 反之, 返回NULL.

需要注意的是, 函数的返回值类型是 void *, 所以在使用 malloc() 时通常需要进行强制类型转换, 将 void 型指针转换成我们需要的类型, 例如：

    int *p = (int *)malloc(sizeof(int)*10); // 分配10个int类型的内存空间

另外, 通过该函数分配得到的内存空间是未被初始化的, 内存的值是未知的. 因此, 一般在使用该内存空间之前, 要调用另一个函数memset()来将其初始化为0.

    void *memset(void *p, int c, size_t n);

其中, 形参p为所操作的内存空间的首地址, c为赋给每个字节的值, n为操作内存空间的字节数; memset()函数是以字节为单位进行赋值的, 所赋值的范围是0x00～0xFF. 若想要对一个double或int型的数组赋值时, 就特别需要注意. memset()函数也是一种对较大的结构体或数组进行清零的比较快的方法.

    memset(a, 0, 20) //把一个char a[20]清零

```C
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char *p = NULL;
    p = (char *)malloc(sizeof(char)*13);
    if(p == NULL)
    {
        printf("不能够获得足够的内存");
        return -1;
    }
    strcpy(p,"Hello World!\0");
    printf("%s\n",p); 
}
```

## calloc()函数

calloc()函数与malloc()函数的功能相类似, 都是从堆内存中分配空间.

    void* calloc (size_t num, size_t size);

calloc() 在内存中动态地分配了 num*size 个字节长度的连续内存空间, 并且每个字节的值都初始化为0.

返回值与malloc()函数类似, 可以参考malloc()函数.

calloc()函数与malloc函数的一个显著不同时是, calloc()得到的内存空间是经过初始化的, 其内容全为0, calloc()函数适合为数组申请空间, 可以将size设置为数组元素的空间长度, 将n设置为数组的容量.

```C
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char *p = NULL;
    int i;
    p = (char *)calloc(13,sizeof(char));
    if(p == NULL)
    {
        printf("不能够获得足够的内存");
        return -1;
    }
    strcpy(p,"Hello World!\0");
    printf("%s\n",p); 
    for(i = 0; i< 13; i++)
    {
        putchar(p[i]);
    }
    putchar('\n');
}
```

## realloc() 函数

realloc()函数的功能比malloc()函数和calloc()函数的功能更为丰富, 可以实现内存分配和内存释放的功能, 其原型为：

    void* realloc (void* ptr, size_t size);

其中ptr必须为需要重新分配的堆内存空间指针, 即由malloc函数、calloc函数或realloc函数分配空间的指针; size 为新的内存空间的大小, size 可比原来的大或者小, 还可以不变. 当 malloc()、calloc() 分配的内存空间不够用时, 就可以用 realloc() 来调整已分配的内存.  
+ 如果 ptr 为 NULL, 它的效果和 malloc() 相同, 即分配 size 字节的内存空间.  
+ 如果 size 的值为 0, 那么 ptr 指向的内存空间就会被释放, 但是由于没有开辟新的内存空间, 所以会返回空指针; 类似于调用 free().  
+ realloc()函数可以对给定的指针所指的空间进行扩大或者缩小, 无论是扩张或是缩小, 原有内存的中内容将保持不变. 当然, 对于缩小, 则被缩小的那一部分的内容会丢失. realloc()并不保证调整后的内存空间和原来的内存空间保持同一内存地址. 相反, realloc()函数返回的指针很可能指向一个新的内存地址;  
+ 我们知道realloc()函数是从堆上分配内存的, 当扩大一块内存空间时, realloc()会试图直接从堆上现存的数据后面的那些字节中获得附加的字节, 如果能够满足, 函数直接返回的指针不变; 如果数据后面的字节不够, 那么就会使用堆区第一个足够大小的可用内存空间, 现存的数据然后就被拷贝至新的位置, 而老块则放回到堆上. 这句话传递的一个重要的信息就是数据可能被移动. 
```C
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char *p = NULL;
    char *p1 = NULL;
    int i;
    p = (char *)calloc(13,sizeof(char));
    p1 = (char *)calloc(13,sizeof(char));
    
    if(p == NULL)
    {
        printf("不能够获得足够的内存");
        return -1;
    }
    strcpy(p,"Hello World!\0");
    strcpy(p1,"Hello World!\0");
    printf("%s\n",p);
    p = (char *)realloc(p,25);
    strcat(p,p1);
    printf("%s\n",p);
    p = (char *)realloc(p,0);
    printf("%p\n",p);    
    
}
```