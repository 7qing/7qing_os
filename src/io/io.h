#ifndef IO__H__
#define IO__H__

unsigned char insb(unsigned short port);
unsigned short insw(unsigned short port);

void outb(unsigned short port, unsigned char val);
void outb(unsigned short port, unsigned short val);
#endif