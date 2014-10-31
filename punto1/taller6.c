#include <math.h>

#include <stdio.h>
#include <stdlib.h>
float xprima(float x, float y);
float yprima(float x, float y);
void Runge_kutta(float x_old,float y_old,float t_old,float* x_new,float* y_new,float* t_new);


int main(int argc, char *argv[])
{
  float h=0.001;
  float min_x = 0.0;
  float max_x = 1.0;
  float n_points = (int)((max_x-min_x)/h);
 
  float *y;
  y = malloc(n_points* sizeof(float)); 
  float *x;


  x = malloc(n_points* sizeof(float)); 
  float *t;
  t = malloc(n_points* sizeof(float));  
  y[0]=atof(argv[2]);

  x[0]=atof(argv[1]);
  t[0]=0.0;
 
  int i;
  
  
   for (i=1;i<n_points;i++)
  {
    Runge_kutta(x[i-1], y[i-1], t[i-1],&x[i], &y[i], &t[i] );
    
  } 
 


 FILE *file;
 char nombre[1000];
 sprintf(nombre, "poblaciones_%d_%d.dat",(int)x[0],(int)y[0]);
 file= fopen(nombre, "w");
 for (i=1;i<n_points;i++)
  {
    fprintf(file,"%f %f  \n",y[i],x[i]);
  }
 fclose(file);
 }

 float yprima(float x, float y)
  { 
    return -30*y+x*y; 
  }
 float xprima(float x, float y)
  { 
    return 20*x-x*y; 
  }

 void Runge_kutta(float x_old,float y_old,float t_old,float* x_new,float* y_new,float* t_new)
 {
  float h=0.001;
  float k_1y,k_1x,y1,x1,k_2y,k_2x,y2,x2,k_3y,k_3x,y3,x3;
  float k_4y,k_4x,pendiente_y,pendiente_x;
  
    
    k_1y = yprima(x_old,y_old);
    k_1x= xprima(x_old,y_old);
    
    //primer paso
    
    y1 = y_old + (h/2.0) * k_1y;
    x1 = x_old + (h/2.0) * k_1x;
    k_2y = yprima(x1, y1);
    k_2x = xprima(x1, y1);
    
    //segundo paso
    
    y2= y_old + (h/2.0) * k_2y;
    x2= x_old + (h/2.0) * k_2x;
    k_3y = yprima(x2, y2);
    k_3x = xprima(x2, y2);
    
    
    //tercer paso
    
    y3 = y_old + h * k_3y;
    x3 = x_old + h * k_3x;
    k_4y = yprima(x3, y3);
    k_4x = xprima(x3, y3);
    
    //cuarto paso
    pendiente_y = (1.0/6.0)*(k_1y + 2.0*k_2y + 2.0*k_3y + k_4y);
    pendiente_x = (1.0/6.0)*(k_1x + 2.0*k_2x + 2.0*k_3x + k_4x);
    
    *t_new = t_old + h;
    *y_new = y_old + h * pendiente_y;
    *x_new= x_old + h * pendiente_x;
    
   
   }







