#include <unistd.h>
#include <stdio.h>

void print_bits(unsigned char octet)
{
	int i = 7;
	while(i >= 0)
	{
		if((octet >> i) & 1)
			write(1, "1", 1);
		else 
			write(1, "0", 1);
		i--;
	}
}


int main()
{
	char c = 'B'; /// 01000010
	print_bits(c);
}