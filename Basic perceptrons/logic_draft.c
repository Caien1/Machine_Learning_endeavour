#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ITTER 100000
typedef float set[3];
typedef struct
{
    float nand_w1;
    float nand_w2;
    float nand_b;

    float or_w1;
    float or_w2;
    float or_b;

    float and_w1;
    float and_w2;
    float and_b;

    float not_w1;
    float not_b;
} Xor;

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

set nor_gate[]={
{0,0,1},
{0,1,0},
{1,0,0},
{1,1,0},
};

set *train = xor_gate;
size_t train_count = 4;
float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}

float forward(Xor m, float x1, float x2)
{

    float a = sigmoidf(x1 * m.or_w1 + x2 * m.or_w2 + m.and_b);
    float b = sigmoidf(x1 * m.nand_w1 + x2 * m.nand_w2 + m.nand_b);
    float c  = sigmoidf(a * m.and_w1 + b * m.and_w2 + m.and_b);
   return c;
   // return sigmoidf(c * m.not_w1 + m.not_b );
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
    
    printf("\nand_w1: %f\n", m.nand_w1);
    printf("nand_w2: %f\n", m.nand_w2);
    printf("nand_b: %f\n", m.nand_b);

    printf("or_w1: %f\n", m.or_w1);
    printf("or_w2: %f\n", m.or_w2);

    printf("and_w1: %f\n", m.and_w1);
    printf("and_w2: %f\n", m.and_w2);
    printf("and_b: %f\n", m.and_b);
    printf("not_w: %f\n", m.not_w1);
    printf("not_b: %f\n", m.not_b);
}

Xor rand_xor(void)
{
    Xor m;
    m.nand_w1 = rand_float();
    m.nand_w2 = rand_float();
    m.nand_b = rand_float();

    m.or_w1 = rand_float();
    m.or_w2 = rand_float();
    m.or_b = rand_float();

    m.and_w1 = rand_float();
    m.and_w2 = rand_float();
    m.and_b = rand_float();

    m.not_w1=rand_float();
    m.not_b=rand_float();
    return m;
}
Xor finite_diffrence(Xor m, float esp)
{
    Xor g;
    float saved;
    float c = cost(m);

    saved = m.nand_w1;
    m.nand_w1 += esp;
    g.nand_w1 = (cost(m) - c) / esp;
    m.nand_w1 = saved;

    saved = m.nand_w2;
    m.nand_w2 += esp;
    g.nand_w2 = (cost(m) - c) / esp;
    m.nand_w2 = saved;

    saved = m.nand_b;
    m.nand_b += esp;
    g.nand_b = (cost(m) - c) / esp;
    m.nand_b = saved;

    saved = m.or_w1;
    m.or_w1 += esp;
    g.or_w1 = (cost(m) - c) / esp;
    m.or_w1 = saved;

    saved = m.or_w2;
    m.or_w2 += esp;
    g.or_w2 = (cost(m) - c) / esp;
    m.or_w2 = saved;

    saved = m.or_b;
    m.or_b += esp;
    g.or_b = (cost(m) - c) / esp;
    m.or_b = saved;

    saved = m.and_w1;
    m.and_w1 += esp;
    g.and_w1 = (cost(m) - c) / esp;
    m.and_w1 = saved;

    saved = m.and_w2;
    m.and_w2 += esp;
    g.and_w2 = (cost(m) - c) / esp;
    m.and_w2 = saved;

    saved = m.and_b;
    m.and_b += esp;
    g.and_b = (cost(m) - c) / esp;
    m.and_b = saved;

    saved = m.not_w1;
    m.not_w1 += esp;
    g.not_w1 = (cost(m)-c)/esp;
    m.not_w1= saved;

    saved = m.not_b;
    m.not_b += esp;
    g.not_b = (cost(m)-c)/esp;
    m.not_b = saved;
    return g;
}

Xor train_AI(Xor m, Xor g, float rate)
{
    m.and_w1 -= g.and_w1 * rate;
    m.and_w2 -= g.and_w2 * rate;
    m.and_b -= g.and_b * rate;
    
    m.or_w1 -= g.or_w1 * rate;
    m.or_w2 -= g.or_w2 * rate;
    m.or_b -= g.or_b * rate;
    
    m.nand_w1 -= g.nand_w1 * rate;
    m.nand_w2 -= g.nand_w2 * rate;
    m.nand_b -= g.nand_b * rate;

    m.not_w1 -= g.not_w1 *rate;
    m.not_b -= g.not_b * rate;

    return m;
}
int main()
{
    Xor m = rand_xor();
    float esp = 1e-1;
    float rate = 1e-1;

   printXor(m);
    printf("\nInitial Cost: %f", cost(m));
    printf("\n______________________________\n");

     for (size_t i = 0; i < 2; i++)
     {
        for (size_t j = 0; j < 2; j++)
        {
            printf("%zu ^ %zu  %f  \n",i,j,forward(m,i,j));
        }
        
     }

  for (size_t i = 0; i < ITTER; i++)
    {
    Xor g = finite_diffrence(m, esp);
    m=train_AI(m,g,rate);
    //printf("Cost: %f\n", cost(m));
    }
     
        printf("______________________________\n");
     printf("After training Cost: %f\n", cost(m));
   

     for (size_t i = 0; i < 2; i++)
     {
        for (size_t j = 0; j < 2; j++)
        {
            printf("%zu ^ %zu  %f  \n",i,j,forward(m,i,j));
        }
        
     }
     printXor(m);

}
