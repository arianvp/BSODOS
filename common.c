#include "common.h"

inline void outb(u16int _port, u8int _value)
{
    asm volatile("outb %1, %0" : : "dN" (_port), "a" (_value));
}

inline u8int inb(u16int _port)
{
   u8int ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (_port));
   return ret;
}

inline u16int inw(u16int _port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (_port));
   return ret;
} 

inline u32int inl(u16int _port)
{
   u32int ret;
   asm volatile ("inl %1, %0" : "=a" (ret) : "dN" (_port));
   return ret;
} 
