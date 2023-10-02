// C Program for Iterative Tower of Hanoi
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

// A structure to create the stack
struct Stack
{
unsigned capacity;
int top;
int *array;
};

// stack of finite capacity.
struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack =
		(struct Stack*) malloc(sizeof(struct Stack));
	stack -> capacity = capacity;
	stack -> top = -1;
	stack -> array =
		(int*) malloc(stack -> capacity * sizeof(int));
	return stack;
}


int isFull(struct Stack* stack)
{
return (stack->top == stack->capacity - 1);
}


int isEmpty(struct Stack* stack)
{
return (stack->top == -1);
}


void push(struct Stack *stack, int item)
{
	if (isFull(stack))
		return;
	stack -> array[++stack -> top] = item;
}


int pop(struct Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack -> array[stack -> top--];
}

//Function to show the movement of disks from source to destination using auxiliary rods
void moveDisk(char fromPeg, char toPeg, int disk)
{
	printf("Move the disk %d from \'%c\' to \'%c\'\n",
		disk, fromPeg, toPeg);
}

// Function to implement valid movement between two rods

void moveDisksBetweenTwoRods(struct Stack *from,
			struct Stack *to, char A, char C)
{
	int rod1TopDisk = pop(from);
	int rod2TopDisk = pop(to);

	// When rod 1 is empty
	if (rod1TopDisk == INT_MIN)
	{
		push(from, rod2TopDisk);
		moveDisk(C, A, rod2TopDisk);
	}

	// When rod 2 pole is empty
	else if (rod2TopDisk == INT_MIN)
	{
		push(to, rod1TopDisk);
		moveDisk(A, C, rod1TopDisk);
	}

	// When top disk of rod 1 > top disk of rod 2
	else if (rod1TopDisk > rod2TopDisk)
	{
		push(from, rod1TopDisk);
		push(from, rod2TopDisk);
		moveDisk(C, A, rod2TopDisk);
	}

	// When top disk of rod 1 < top disk of rod 2
	else
	{
		push(to, rod2TopDisk);
		push(to, rod1TopDisk);
		moveDisk(A, C, rod1TopDisk);
	}
}

//Function to implement Tower of Hanoi
void toH(int no_of_disks, struct Stack
			*from, struct Stack *_using,
			struct Stack *to)
{
	int i, total_num_of_moves;
	char A = 'A', C= 'C', B = 'B';

	//If the number of disks is even, then interchange destination auxiliary 
	if (no_of_disks % 2 == 0)
	{
		char temp = C;
		C = B;
		B = temp;
	}
	total_num_of_moves = pow(2, no_of_disks) - 1;

	
	for (i = no_of_disks; i >= 1; i--)
		push(from, i);

	for (i = 1; i <= total_num_of_moves; i++)
	{
		if (i % 3 == 1)
		moveDisksBetweenTwoRods(from, to, A, C);

		else if (i % 3 == 2)
		moveDisksBetweenTwoRods(from,_using, A, B);

		else if (i % 3 == 0)
		moveDisksBetweenTwoRods(_using, to, B, C);
	}
}

int main()
{
	
	unsigned no_of_disks;
	printf("Enter number of disks");
	scanf("%d", &no_of_disks);

	struct Stack *from, *_using, *to;

	// Create three stacks of size 'no_of_disks'
	
	from = createStack(no_of_disks);
	_using = createStack(no_of_disks);
	to = createStack(no_of_disks);

	toH(no_of_disks, from,_using,to);
	return 0;
}

