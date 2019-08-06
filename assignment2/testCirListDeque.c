#include "cirListDeque.h"
#include <stdio.h>

int main()
{
	struct cirListDeque* q = createCirListDeque();
	
	printf("front elements \n"); 
	for(int i = 0; i<5; i++)
	{
		addFrontCirListDeque(q, (TYPE)i);
		printf("%g \n", frontCirListDeque(q));
	}

	printf("back elements \n"); 
	for(int i = 5; i < 10; i++)
	{
		addBackCirListDeque(q, (TYPE)i);
		printf("%g \n", backCirListDeque(q));
	}

	printf("front element = %g \n", frontCirListDeque(q));
 	
	printf("back element =  %g \n", backCirListDeque(q));
	
	printf("remove front and back element \n");	

	removeFrontCirListDeque(q);
	printf("front element = %g \n", frontCirListDeque(q));

	removeBackCirListDeque(q);
	printf("back element =  %g \n", backCirListDeque(q));
		
	
	int flag = isEmptyCirListDeque(q);
	printf("flag = %d \n", flag);

	printf("Linked List elements: \n");
	printCirListDeque(q);

	freeCirListDeque(q);
	return 0;
}
