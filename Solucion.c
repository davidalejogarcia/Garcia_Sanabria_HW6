#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define C 3E8
#define q 1.6E-19
#define m 1.67E-27
#define R_T 6.371E6
#define B 3E-5
#define m_MEV 938.27
#define PI 3.1415

double func_prime_1(double t,double *x,double v);
double func_prime_2(int i,double *x,double *v);
double norma(double v1,double v2, double v3);
double RungeKuttaFourthOrderStep(double *x, double *v, double t_old);


int main(int argc, char **argv){

  int n_points, i;
  double c, nu, sigma,  alpha, v_in, K;
  double *v,*x, *k1,  *t;

  K=atoi(argv[1]);

  alpha=2*PI*atoi(argv[2])/360;

  n_points=1E6+1;

  x = malloc(3 * sizeof(float));
  v = malloc(3 * sizeof(float));
  t = malloc(2 * sizeof(double));
  k1 = malloc(3 * sizeof(float));
  
  t[0] = 0.0;
  
  
  v_in=C*sqrt(1-pow((K/m_MEV+1),-2));
  
  alpha=PI/3;
  
  
  
  
  x[0]=2*R_T;
  x[1]=0;
  x[2]=0;

  v[0]=0;
  v[1]=v_in*sin(alpha);
  v[2]=v_in*cos(alpha);
 

  FILE *file;

  char filename[64];
  sprintf (filename, "trayectoria_%d_%d.dat", atoi(argv[1]), atoi(argv[2]));
 
  file=fopen(filename, "w");

  fprintf(file, "%f \t %f \t %f \t %f \n", t[0],  x[0], x[1],x[2] );
 
  for( i=1;i<n_points;i++){
   
    t[1] = RungeKuttaFourthOrderStep(x,v,t[0]);
    t[0]=t[1];
   
    fprintf(file, "%f \t %f \t %f \t %f \n", t[0],  x[0], x[1],x[2] );
  }
  

  
  return 0;
}

double func_prime_1(double t,double *x,double v){
  return v;
}

double func_prime_2(int i,double *x, double *v){
  
  double gamma,B1,B2,B3;
  double v1,v2,v3,x1,x2,x3;
  double r, a[3];

  x1=x[0];
  x2=x[1];
  x3=x[3];
  
  v1=v[0];
  v2=v[1];
  v3=v[2];

  r=norma(x1,x2,x3);

  B1=-(B*pow(R_T,3)/pow(r,5)) * (3*x1*x3);
  B2=-(B*pow(R_T,3)/pow(r,5)) * (3*x2*x3);
  B3=-(B*pow(R_T,3)/pow(r,5)) * (2*pow(x3,2)-pow(x1,2)-pow(x2,2));

  a[0]=(v2*B3-v3*B2);
  a[1]=(v3*B1-v1*B3);
  a[2]=(v1*B2-v2*B1);



  gamma=1/sqrt(1-(pow(norma(v1,v2,v3),2)/pow(C,2)));

  // printf("%f \t %f \t %f \t %f\n",v1, v2 ,v3, norma(v1,v2,v3)/C);
  //printf("%f \t %f \t %f \t \n",x1, x2 ,x3);
  

  
  return (q/(gamma*m))*a[i];
}

double norma(double v1,double v2, double v3){

  return sqrt(pow(v1,2)+pow(v2,2)+pow(v3,2));
}


double RungeKuttaFourthOrderStep(double *x, double *v, double t_old){
    
  double k_1_prime1[3], k_1_prime2[3], t1, x_1[3], v_1[3], h, t2, x_2[3], v_2[3], k_2_prime1[3], k_2_prime2[3], k_3_prime1[3], k_3_prime2[3], k_4_prime1[3], k_4_prime2[3], t3, x_3[3], v_3[3],average_k_1[3], average_k_2[3],t_new, x_new[3], v_new[3];


  h=1E-4;



  k_1_prime1[0] = func_prime_1(t_old,x, v[0]);
  k_1_prime2[0] = func_prime_2(0,x, v);

  k_1_prime1[1] = func_prime_1(t_old,x, v[1]);
  k_1_prime2[1] = func_prime_2(1,x, v);

  k_1_prime1[2] = func_prime_1(t_old,x, v[2]);
  k_1_prime2[2] = func_prime_2(2,x, v);
    
  //first step  
  t1 = t_old+ (h/2.0);

  x_1[0] = x[0] + (h/2.0) * k_1_prime1[0];
  v_1[0] = v[0] + (h/2.0) * k_1_prime2[0];

  x_1[1] = x[1] + (h/2.0) * k_1_prime1[1];
  v_1[1] = v[1] + (h/2.0) * k_1_prime2[1];

  x_1[2] = x[2] + (h/2.0) * k_1_prime1[2];
  v_1[2] = v[2] + (h/2.0) * k_1_prime2[2];

  k_2_prime1[0] = func_prime_1(t1, x_1, v_1[0]);
  k_2_prime2[0] = func_prime_2(0, x_1, v_1);

 
  k_2_prime1[1] = func_prime_1(t1, x_1, v_1[1]);
  k_2_prime2[1] = func_prime_2(1, x_1, v_1);

 
  k_2_prime1[2] = func_prime_1(t1, x_1, v_1[2]);
  k_2_prime2[2] = func_prime_2(2, x_1, v_1);

 
  //"second step"
  t2 = t_old + (h/2.0);

  x_2[0] = x[0] + (h/2.0) * k_2_prime1[0];
  v_2[0] = v[0] + (h/2.0) * k_2_prime2[0];

  x_2[1] = x[1] + (h/2.0) * k_2_prime1[1]; //
  v_2[1] = v[1] + (h/2.0) * k_2_prime2[1];

  x_2[2] = x[2] + (h/2.0) * k_2_prime1[2];
  v_2[2] = v[2] + (h/2.0) * k_2_prime2[2];

  k_3_prime1[0] = func_prime_1(t2, x_2, v_2[0]);
  k_3_prime2[0] = func_prime_2(0, x_2, v_2);

  
  k_3_prime1[1] = func_prime_1(t2, x_2, v_2[1]);
  k_3_prime2[1] = func_prime_2(1, x_2, v_2);

  
  k_3_prime1[2] = func_prime_1(t2, x_2, v_2[2]);
  k_3_prime2[2] = func_prime_2(2, x_2, v_2);  //Falta organizar v_2

    
    
    //"third step"
  t3 = t_old + h;

  x_3[0] = x[0] + h * k_3_prime1[0];
  v_3[0] = v[0] + h * k_3_prime2[0];

  x_3[1] = x[1] + h * k_3_prime1[1];
  v_3[1] = v[1] + h * k_3_prime2[1];

  x_3[2] = x[2] + h * k_3_prime1[2];
  v_3[2] = v[2] + h * k_3_prime2[2];

  k_4_prime1[0] = func_prime_1(t3, x_3, v_3[0]);
  k_4_prime2[0] = func_prime_2(0, x_3, v_3);

 
  k_4_prime1[1] = func_prime_1(t3, x_3, v_3[1]);
  k_4_prime2[1] = func_prime_2(1, x_3, v_3);

  
  k_4_prime1[2] = func_prime_1(t3, x_3, v_3[2]);
  k_4_prime2[2] = func_prime_2(2, x_3, v_3);


    
  // "fourth step"
  average_k_1[0] = (1.0/6.0)*(k_1_prime1[0] + 2.0*k_2_prime1[0] + 2.0*k_3_prime1[0] + k_4_prime1[0]);
  average_k_2[0] = (1.0/6.0)*(k_1_prime2[0] + 2.0*k_2_prime2[0] + 2.0*k_3_prime2[0] + k_4_prime2[0]);

  average_k_1[1] = (1.0/6.0)*(k_1_prime1[1] + 2.0*k_2_prime1[1] + 2.0*k_3_prime1[1] + k_4_prime1[1]);
  average_k_2[1] = (1.0/6.0)*(k_1_prime2[1] + 2.0*k_2_prime2[1] + 2.0*k_3_prime2[1] + k_4_prime2[1]);

  average_k_1[2] = (1.0/6.0)*(k_1_prime1[2] + 2.0*k_2_prime1[2] + 2.0*k_3_prime1[2] + k_4_prime1[2]);
  average_k_2[2] = (1.0/6.0)*(k_1_prime2[2] + 2.0*k_2_prime2[2] + 2.0*k_3_prime2[2] + k_4_prime2[2]);

  //printf("entro \t %f \t %f \t %f\n",  k_2_prime2[0], k_2_prime2[1] ,k_2_prime2[2]);

  //printf("entro \t %f \t %f \t %f\n", v_1[0], v_1[1] , v_1[2]);
    
  //Actualization
  t_new = t_old + h;

  x[0]=x[0] + h * average_k_1[0];
  v[0]=v[0] + h * average_k_2[0];
  
  x[1]=x[1] + h * average_k_1[1];
  v[1]=v[1] + h * average_k_2[1];

  x[2]=x[2] + h * average_k_1[2];
  v[2]=v[2] + h * average_k_2[2];
  
  

  return t_new;
}
