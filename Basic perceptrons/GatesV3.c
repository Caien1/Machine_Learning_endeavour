#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ITTER 5000
typedef float set[3];
typedef struct
{
    float xor_ona[3][3];

} Xor;

size_t size = 3;

set xor_gate[] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};
set and_gate[] = {
    {0, 0, 0},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 1},
};
set nand_gate[] = {
    {0, 0, 1},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};
set or_gate[] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};

set exor_gate[] = {
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 1},
};

set nor_gate[] = {
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 0},
};

set *train = NULL;
size_t train_count = 4;

float matrixMul(float x[], float y[])
{
    float sum = 0.0f;
    float temp[3];
    size_t size = 3;
    for (size_t i = 0; i < size; i++)
    {
        sum += x[i] * y[i];
    }

    return sum;
}

float sigmoidf(float x)
{
    // return relu(x);
    return sinf(x);
  //  return 1.f / (1.f + expf(-x));
}


float forward(Xor m, float x1, float x2)
{
    //use some sort of matrix multiplication instead of this

    float a = sigmoidf(x1 * m.xor_ona[0][0] + x2 * m.xor_ona[0][1] + m.xor_ona[0][2]);
    float b = sigmoidf(x1 * m.xor_ona[1][0] + x2 * m.xor_ona[1][1] + m.xor_ona[1][2]);
    float c = sigmoidf(a * m.xor_ona[2][0] + b * m.xor_ona[2][1] + m.xor_ona[2][2]);
    return c;
}
float cost(Xor m)
{
    float result = 0.0f;

    for (size_t i = 0; i < train_count; i++)
    {

        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = forward(m, x1, x2);
        float d = y - train[i][2];
        result += d * d;
    }
    result /= train_count;
    return result;
}
float rand_float()
{
    return (float)rand() / (float)RAND_MAX;
}

void printXor(Xor m)
{
    printf("\tW1\t\t W2\t\t b \n");
    for (size_t i = 0; i < 3; i++)
    {

        if (i == 0)
            printf("1)Or\t");
        else if (i == 1)
            printf("2)Nand\t");
        else
            printf("3)OR\t");
        for (size_t j = 0; j < 3; j++)
        {
            printf("%f\t", m.xor_ona[i][j]);
        }

        printf("\n");
    }
}

Xor rand_xor(void)
{
    Xor m;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            m.xor_ona[i][j] = rand_float();
        }
    }

    return m;
}

Xor finite_diffrence(Xor m, float esp)
{
    Xor g;
    float saved;
    float c = cost(m);
    int i = 0;
    int j = 0;
    for (size_t i = 0; i < 3; i++)
    {
        /* code */
        for (size_t j = 0; j < 3; j++)
        {
            /* code */
            saved = m.xor_ona[i][j];
            m.xor_ona[i][j] += esp;
            g.xor_ona[i][j] = (cost(m) - c) / esp;
            m.xor_ona[i][j] = saved;
        }
    }
    //  printXor(g);

    return g;
}

Xor train_AI(Xor m, Xor g, float rate)
{
    // printXor(g);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            m.xor_ona[i][j] -= g.xor_ona[i][j] * rate;
        }
    }
    return m;
}
int main()
{
    srand(9);
    Xor m = rand_xor();

    float esp = 1e-1;
    float rate = 1e-1;
    int option = 99;
    char sign;
    do
    {
        printf("Enter options:\n0)TO exit\t1)XOR\t2)AND\n3)OR\t\t4)NAND\t5)Exor\n Your choice : ");
        scanf("%d", &option);
        switch (option)
        {
        case 0:
            return 0;
            break;
        case 1:
            train = xor_gate;
            break;
        case 2:
            train = and_gate;
            break;
        case 3:
            train = or_gate;
            break;
        case 4:
            train = nand_gate;
            break;
        case 5:
        train = exor_gate;break;
            default:
            return 0;
        }
    } while (option == 99);
    printf("______________________________\n");
    printf("Cost intial:%f\n", cost(m));

    for (size_t i = 0; i < ITTER; i++)
    {
        Xor g = finite_diffrence(m, esp);
        m = train_AI(m, g, rate);
    }
    printf("______________________________\n");

    printf("Cost Final:%f\n", cost(m));

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            printf("%zu  %zu  %f  \n", i, j, forward(m, i, j));
        }
    }
}
