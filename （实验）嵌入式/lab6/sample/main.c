#define  N	6
int main(void)
{
	unsigned char c[6] = {1,2,3,4,5,6};
	unsigned char x[6] = {4,8,9,3,5,1};
	unsigned char i,f;

	for (i=0, f=0; i<N; i++)
	{
		f = f + c[i]*x[i];
	}

	return 0;
}