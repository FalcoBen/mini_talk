#include <stdio.h>
#include <libc.h>

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


int main() {
    unsigned char buffer[4] = {"🈲"};
    int i = 0;
    while(i < 4)
    {
        print_bits(buffer[i]);
        write(1, "\n", 1);
        i++;
    }
    return 0;
}
