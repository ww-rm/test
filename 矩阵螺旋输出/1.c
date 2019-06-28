#include <stdio.h>
#include <math.h>

int main()
{
	int matrix[100][100];
	int m;
	int n;
	int count = 0;
	int end = 0;
	scanf("%d%d", &m, &n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
	}
	int x = 0;
	while ((!end) && m != 1 && n != 1)
	{
		if (count < m * n)
		{
			for (int k = x; k < n - 1 - x; k++)
			{
				printf("%d ", matrix[x][k]);
				count++;
				if (count == m * n)
				{
					break;
				}
			}
		}
		if (count < m * n)
		{
			for (int k = x; k < m - 1 - x; k++)
			{
				printf("%d ", matrix[k][n - 1 - x]);
				count++;
				if (count == m * n)
				{
					break;
				}
			}
		}
		if (count < m * n)
		{
			for (int k = x; k < n - 1 - x; k++)
			{
				printf("%d ", matrix[m - 1 - x][n - 1 - k]);
				count++;
				if (count == m * n)
				{
					break;
				}
			}
		}
		if (count < m * n)
		{
			for (int k = x; k < m - 1 - x; k++)
			{
				printf("%d ", matrix[m - 1 - k][x]);
				count++;
				if (count == m * n)
				{
					break;
				}
			}
		}
		x++;
		if (count >= m * n)
		{
			break;
		}
	}
	if (m == 1)
	{
		for (int i = 0; i <= n - 1; i++)
		{
			printf("%d", matrix[0][i]);
			if (i != n - 1)
			{
				printf(" ");
			}
		}
	}
	else if (n == 1)
	{
		for (int i = 0; i <= m - 1; i++)
		{
			printf("%d", matrix[i][0]);
			if (i != m - 1)
			{
				printf(" ");
			}
		}
	}
	return 0;
}