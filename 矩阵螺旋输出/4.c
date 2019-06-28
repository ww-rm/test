#include <stdio.h>

void space(int, int);

int main()
{
    int matrix[100][100];
    int m;
    int n;
    scanf("%d%d", &m, &n);
    int mix = ((m >= n) ? n : m);
    int opration = 2 * mix - 1 + (m > n); //操作方向描述变量
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    int counter = 0;
    for (int i = 0; i <= 2 * m; i++)
    {
        switch (i % 4)
        {
        case 0:
        {
            for (int a = (i / 4); a < (n - i / 4 - 1); a++)
            {
                printf("%d", matrix[i / 4][a]);
                counter++;
                if (counter >= m * n)
                {
                    break;
                }
                space(counter, m * n);
            }
            break;
        }
        case 1:
        {
            for (int a = (i / 4); a < (m - i / 4 - 1); a++)
            {
                printf("%d", matrix[a][n - i / 4 - 1]);
                counter++;
                if (counter >= m * n)
                {
                    break;
                }
                space(counter, m * n);
                if (m % 2 == 1 && counter == m * n - 1)
                {
                    printf("%d", matrix[a][m - i / 4 - 1]);
                }
            }
            break;
        }
        case 2:
        {
            for (int a = n - 1 - i / 4; a > i / 4; a--)
            {
                printf("%d", matrix[m - i / 4 - 1][a]);
                counter++;
                if (counter >= m * n)
                {
                    break;
                }
                space(counter, m * n);
            }
            break;
        }
        case 3:
        {
            for (int a = m - 1 - i / 4; a > i / 4; a--)
            {
                printf("%d", matrix[a][i / 4]);
                counter++;
                if (counter >= m * n)
                {
                    break;
                }
                space(counter, m * n);
            }
            break;
        }
        }
        if (counter >= m * n)
        {
            break;
        }
    }
    return 0;
}

void space(int a, int b)
{
    if (a != b)
    {
        printf(" ");
    }
}