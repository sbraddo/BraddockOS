#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract (int a, int b);
int multiply (int a, int b);
int divide (int a, int b);
int finish (int a, int b);
typedef int (*Operation) (int a, int b);
int inputInt;

int main (void)
{
	/* IMPLEMENT ME: Insert your algorithm here */
	int a = 6;
	int b = 3;
	int rVal;
	Operation operations[5] = {&add, &subtract, &multiply, &divide, &finish};
	while (1){
			printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): ");
			scanf("%d", &inputInt);
			rVal = (*operations[inputInt])(a, b);
			printf("x = %d\n", rVal);
	}
	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { 
	printf ("Adding 'a' and 'b'\n"); 
	return a + b; 
	}

int subtract (int a, int b){
	printf("Subtracting 'a' and 'b'\n");
	return a - b;
}

int multiply (int a, int b){
	printf("Multiplying 'a' and 'b'\n");
	return a * b;
}

int divide (int a, int b){
	printf("Dividing 'a' and 'b'\n");
	return a / b;
}

int finish (int a, int b){
	exit(0);
}
