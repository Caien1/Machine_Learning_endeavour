#include<stdio.h>
#include<stdlib.h>
#include<time.h>
float train[][2]={
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
    {5,10},
    {6,12},
    {7,14},
    {8,16},
    {9,18},
    {10,20},
};
#define COUNT sizeof(train)/sizeof(train[0])
float rand_float(){
    return (float) rand()/ (float) RAND_MAX;
}

float cost(float w ,float b){
  float result = 0.0f;
 

   for( size_t i=0 ;i<COUNT;i++){
    float x  = train[i][0];
    float guess = x*w +b; 
    float distance = guess - train[i][1]; 
    result += distance*distance;
  
  
   }
   result/= COUNT;
   return result;
}


int main(){ 
    srand(time(0));

    float w = rand_float()*10.0f;
    float b = rand_float()*2.0f;
   float esp = 1e-3;
   float rate = 1e-3;

 printf("\nw:%f b:%f Cost:%f   \n",w, b ,cost(w,b));
    //minimizing cost
   for( size_t i=0; i<10000;i++){
    float c = cost(w,b);
   float dcost = (cost(w + esp ,b)-c)/esp;
   float bias = (cost(w  , b + esp)-c)/esp;
    b-= rate*bias;
    w-=rate*dcost; 
   //printf("Cost: %f\n",cost(w,b));
   }

   printf("__AFTER MINIMIZATION OF COST__\n");
   printf("w:%f b:%f Cost:%f   \n",w, b ,cost(w,b));
   for (size_t i = 0; i <10; i++)
   {
        printf("value: %f \t  | original: %f \n",i*w+b,train[i][1]);
   }
   

    return 0;
}