#include <unistd.h>


void print_bit(unsigned char octet)
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

int main(int ac , char **av)
{
	if(ac == 2)
	{
		print_bit(av[1][0]);
	}
	return 0;
}