// Calculates 15-th Fibonacci number

int Fib(int);

int main()
{
	int res = 0;
	res = Fib(15);
	return res;
}

int Fib(int n)
{
	if (n <= 2) return 1;
	else {
		return Fib(n-1) + Fib(n-2);
	}
}
