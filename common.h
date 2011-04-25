#ifndef _COMMON_H_
#define _COMMON_H_

typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

extern inline void outb(u16int _port, u8int _value)__attribute__((always_inline));
extern inline u8int inb(u16int _port)__attribute__((always_inline));
extern inline u16int inw(u16int _port)__attribute__((always_inline));
extern inline u32int inl(u16int _port) __attribute__((always_inline));
#endif
