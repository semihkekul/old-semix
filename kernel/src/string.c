#include <stddef.h>
#include <stdint.h>
#include "../include/system.h"
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
/*
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
 
}
*/
void *memset(void* dst, char val, size_t count)
{
 	char *p = (char *)dst;

	for (; count != 0; --count)
		*p++ = val;

    return dst;
}
/*
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{

}
*/

int strcmp(const char* s1, const char* s2)
{
	size_t idx = 0;
	char val = 0;
	do{
		if(s1[idx] == '\0' && s2[idx] == '0')
		{
			val = 0;
			break;
		}
		else if(s1[idx] == '\0') 
		{
			val = -1;
			break;
		} 
		else if(s2[idx] == '\0')
		{
			val = 1;
			break;
		}
		val = s1[idx] - s2[idx];
	} 
	while(1);
	return val;
}
