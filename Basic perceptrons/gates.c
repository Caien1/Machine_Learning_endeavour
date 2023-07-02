#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <time.h>
typedef float set[3];

// OR-gate
set or_gate[] = {
{0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};

set and_gate[] =
{
{0,0,0},
{0,1,0},
{1,0,0},
{1,1,1},
};

set nand_gate[] ={
{0,0,1},
{0,1,1},
{1,0,1},
{1,1,0},

};
set nor_gate[]={
{0,0,1},
{0,1,0},
{1,0,0},
{1,1,0},
};
set *train= nor_gate;

#define COUNT sizeof(or_gate) / sizeof(or_gate[0])



float sigmoidf( float x){
    return 1.f / (1.f + expf(-x));

}



float cost(float w1, float w2 ,float b)
{
    float result = 0.0f;

    for (size_t i = 0; i < COUNT; i++)
    {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf((x1 * w1) + (x2 * w2)+b);
        float d = y - train[i][2];
        result += d * d;
    }
    result /= COUNT;
    return result;
}



float rand_float()
{
    return (float)rand() / (float)RAND_MAX;
}


int main(int argc, char const *argv[])
{
    srand(time(0));
    float b =rand_float();
    float w1 = rand_float();
    float w2 = rand_float();
    printf("Cost: %f  w1:%f  w2:%f \n", cost(w1, w2,b),w1,w2);
   
    
        
    float esp = 1e-1;
    float rate = 1e-1;
    for (int i = 0; i < 1000*1000; i++)
    {
        float c = cost(w1, w2,b);
      //printf("w1:%f  w3:%f c:%f \n", w1,w2,c);
        float w1_cost = (cost(w1 + esp, w2,b) - c) / esp;
        float w2_cost = (cost(w1, w2 + esp,b) - c) / esp;
        float bias = (cost(w1,w2,b+esp)-c)/esp;
        w1 -= rate * w1_cost;
        w2 -= rate * w2_cost;
        b -= rate * bias;
    }

printf("w1: %f w2:%f, b:%f cost:%f \n", w1, w2,b, cost(w1, w2,b));
    for (size_t i = 0; i < 2; i++)
    
    {
        for ( size_t j = 0; j < 2; j++)
        {
            printf ("%u | %u  %f\n",i,j,sigmoidf(i*w1+j*w2 +b));
            
        }
        
    }
    

    return 0;
}
