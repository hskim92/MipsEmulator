int main()
{
	int i;
	int sum;

	i = 4;
	sum = foo(4);

	return sum;
}

int foo(int index)
{
	if (index == 1) return 1;
	else return index+foo(index-1);
}

