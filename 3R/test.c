#include <stdio.h>
#include "lili.h"

int inputs[] = {13, 17, 19, 23, 29, 31};

int main() 
{
	printf("remove() => %d\n", remove_element());
	print_lili();
	printf("insert(%d%s\n", insert_element(47), ")");
	print_lili();
	printf("insert(%d%s\n", insert_element(11), ")");
	print_lili();
	printf("insert(%d%s\n", insert_element(23), ")");
	print_lili();
	printf("insert(%d%s\n", insert_element(11), ")");
	print_lili();
	printf("remove() => %d\n", remove_element());
	print_lili();
	printf("remove() => %d\n", remove_element());
	print_lili();
	printf("insert(%d%s\n", insert_element(18), ")");
	print_lili();
	printf("insert(%d%s\n", insert_element(43), ")");
	print_lili();
}
