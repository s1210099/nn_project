/*************************************************************/
/* C-program for self-organized learning of Kohonen network  */
/*                                                           */
/* The purpose here is to find the representatives of p      */
/* clusters in the pattern space. If you can provide the     */
/* the training samples x, and speicify the number p, you    */
/* can use this program easily                               */
/*                                                           */
/*  1) Number of input : I                                   */
/*  2) Number of neurons: M                                  */
/*  3) Number of training patterns: P                        */
/*                                                           */
/* This program is produced by Qiangfu Zhao.                 */
/* You are free to use it for educational purpose            */
/*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  I             4
#define  M             3
#define  P             150
#define  alpha         0.5
#define  n_update      20

double w[M][I];
double x[P][I]={
  {5.1,3.5,1.4,0.2},
  {4.9,3.0,1.4,0.2},
  {4.7,3.2,1.3,0.2},
  {4.6,3.1,1.5,0.2},
  {5.0,3.6,1.4,0.2},
  {5.4,3.9,1.7,0.4},
  {4.6,3.4,1.4,0.3},
  {5.0,3.4,1.5,0.2},
  {4.4,2.9,1.4,0.2},
  {4.9,3.1,1.5,0.1},
  {5.4,3.7,1.5,0.2},
  {4.8,3.4,1.6,0.2},
  {4.8,3.0,1.4,0.1},
  {4.3,3.0,1.1,0.1},
  {5.8,4.0,1.2,0.2},
  {5.7,4.4,1.5,0.4},
  {5.4,3.9,1.3,0.4},
  {5.1,3.5,1.4,0.3},
  {5.7,3.8,1.7,0.3},
  {5.1,3.8,1.5,0.3},
  {5.4,3.4,1.7,0.2},
  {5.1,3.7,1.5,0.4},
  {4.6,3.6,1.0,0.2},
  {5.1,3.3,1.7,0.5},
  {4.8,3.4,1.9,0.2},
  {5.0,3.0,1.6,0.2},
  {5.0,3.4,1.6,0.4},
  {5.2,3.5,1.5,0.2},
  {5.2,3.4,1.4,0.2},
  {4.7,3.2,1.6,0.2},
  {4.8,3.1,1.6,0.2},
  {5.4,3.4,1.5,0.4},
  {5.2,4.1,1.5,0.1},
  {5.5,4.2,1.4,0.2},
  {4.9,3.1,1.5,0.1},
  {5.0,3.2,1.2,0.2},
  {5.5,3.5,1.3,0.2},
  {4.9,3.1,1.5,0.1},
  {4.4,3.0,1.3,0.2},
  {5.1,3.4,1.5,0.2},
  {5.0,3.5,1.3,0.3},
  {4.5,2.3,1.3,0.3},
  {4.4,3.2,1.3,0.2},
  {5.0,3.5,1.6,0.6},
  {5.1,3.8,1.9,0.4},
  {4.8,3.0,1.4,0.3},
  {5.1,3.8,1.6,0.2},
  {4.6,3.2,1.4,0.2},
  {5.3,3.7,1.5,0.2},
  {5.0,3.3,1.4,0.2},
  {7.0,3.2,4.7,1.4},
  {6.4,3.2,4.5,1.5},
  {6.9,3.1,4.9,1.5},
  {5.5,2.3,4.0,1.3},
  {6.5,2.8,4.6,1.5},
  {5.7,2.8,4.5,1.3},
  {6.3,3.3,4.7,1.6},
  {4.9,2.4,3.3,1.0},
  {6.6,2.9,4.6,1.3},
  {5.2,2.7,3.9,1.4},
  {5.0,2.0,3.5,1.0},
  {5.9,3.0,4.2,1.5},
  {6.0,2.2,4.0,1.0},
  {6.1,2.9,4.7,1.4},
  {5.6,2.9,3.6,1.3},
  {6.7,3.1,4.4,1.4},
  {5.6,3.0,4.5,1.5},
  {5.8,2.7,4.1,1.0},
  {6.2,2.2,4.5,1.5},
  {5.6,2.5,3.9,1.1},
  {5.9,3.2,4.8,1.8},
  {6.1,2.8,4.0,1.3},
  {6.3,2.5,4.9,1.5},
  {6.1,2.8,4.7,1.2},
  {6.4,2.9,4.3,1.3},
  {6.6,3.0,4.4,1.4},
  {6.8,2.8,4.8,1.4},
  {6.7,3.0,5.0,1.7},
  {6.0,2.9,4.5,1.5},
  {5.7,2.6,3.5,1.0},
  {5.5,2.4,3.8,1.1},
  {5.5,2.4,3.7,1.0},
  {5.8,2.7,3.9,1.2},
  {6.0,2.7,5.1,1.6},
  {5.4,3.0,4.5,1.5},
  {6.0,3.4,4.5,1.6},
  {6.7,3.1,4.7,1.5},
  {6.3,2.3,4.4,1.3},
  {5.6,3.0,4.1,1.3},
  {5.5,2.5,4.0,1.3},
  {5.5,2.6,4.4,1.2},
  {6.1,3.0,4.6,1.4},
  {5.8,2.6,4.0,1.2},
  {5.0,2.3,3.3,1.0},
  {5.6,2.7,4.2,1.3},
  {5.7,3.0,4.2,1.2},
  {5.7,2.9,4.2,1.3},
  {6.2,2.9,4.3,1.3},
  {5.1,2.5,3.0,1.1},
  {5.7,2.8,4.1,1.3},
  {6.3,3.3,6.0,2.5},
  {5.8,2.7,5.1,1.9},
  {7.1,3.0,5.9,2.1},
  {6.3,2.9,5.6,1.8},
  {6.5,3.0,5.8,2.2},
  {7.6,3.0,6.6,2.1},
  {4.9,2.5,4.5,1.7},
  {7.3,2.9,6.3,1.8},
  {6.7,2.5,5.8,1.8},
  {7.2,3.6,6.1,2.5},
  {6.5,3.2,5.1,2.0},
  {6.4,2.7,5.3,1.9},
  {6.8,3.0,5.5,2.1},
  {5.7,2.5,5.0,2.0},
  {5.8,2.8,5.1,2.4},
  {6.4,3.2,5.3,2.3},
  {6.5,3.0,5.5,1.8},
  {7.7,3.8,6.7,2.2},
  {7.7,2.6,6.9,2.3},
  {6.0,2.2,5.0,1.5},
  {6.9,3.2,5.7,2.3},
  {5.6,2.8,4.9,2.0},
  {7.7,2.8,6.7,2.0},
  {6.3,2.7,4.9,1.8},
  {6.7,3.3,5.7,2.1},
  {7.2,3.2,6.0,1.8},
  {6.2,2.8,4.8,1.8},
  {6.1,3.0,4.9,1.8},
  {6.4,2.8,5.6,2.1},
  {7.2,3.0,5.8,1.6},
  {7.4,2.8,6.1,1.9},
  {7.9,3.8,6.4,2.0},
  {6.4,2.8,5.6,2.2},
  {6.3,2.8,5.1,1.5},
  {6.1,2.6,5.6,1.4},
  {7.7,3.0,6.1,2.3},
  {6.3,3.4,5.6,2.4},
  {6.4,3.1,5.5,1.8},
  {6.0,3.0,4.8,1.8},
  {6.9,3.1,5.4,2.1},
  {6.7,3.1,5.6,2.4},
  {6.9,3.1,5.1,2.3},
  {5.8,2.7,5.1,1.9},
  {6.8,3.2,5.9,2.3},
  {6.7,3.3,5.7,2.5},
  {6.7,3.0,5.2,2.3},
  {6.3,2.5,5.0,1.9},
  {6.5,3.0,5.2,2.0},
  {6.2,3.4,5.4,2.3},
  {5.9,3.0,5.1,1.8}};

  double y[M];

  /*************************************************************/
  /* Print out the result of the q-th iteration                */
  /*************************************************************/
  void PrintResult(int q)
  { int m, i;

    printf("\n\n");
    printf("Results in the %d-th iteration: \n", q);
    for(m=0; m<M; m++)
    { for(i=0; i<I; i++)
      printf("%5f ",w[m][i]);
      printf("\n");
    }
    printf("\n\n");
  }

  /*************************************************************/
  /* The main program                                          */
  /*************************************************************/
  main()
  { int m, m0, i, p, q;
    double norm, s, s0;


    /* Initialization of the connection weights */

    for(m=0; m<M; m++)
    { norm=0;
      for(i=0; i<I; i++)
      { w[m][i] = (double)(rand()%10001)/10000.0 - 0.5;
        norm += w[m][i]*w[m][i];
      }
      norm = sqrt(norm);
      for(i=0; i<I; i++)
      w[m][i] /= norm;
    }
    PrintResult(0);

    /* Unsupervised learning */

    for(q=0; q < n_update; q++)
    { for(p=0; p<P; p++)
      { s0 = 100000;
        for(m=0; m<M; m++)
        { s = 0;
          for(i=0; i<I; i++)
          s += (w[m][i]-x[p][i])*(w[m][i]-x[p][i]);
          // s += w[m][i]*x[p][i];

          s+=sqrt(s);
          if(s < s0)
          { s0 = s;
            m0 = m;
          }
        }

        for(i=0; i<I; i++)
        w[m0][i] += alpha*(x[p][i] - w[m0][i]);

        norm = 0;
        for(i=0; i<I; i++)
        norm += w[m0][i]*w[m0][i];

        norm = sqrt(norm);
        for(i=0; i<I; i++)
        w[m0][i] /= norm;
      }
      PrintResult(q);
    }

    /* Classify the training patterns */

    for(p=0; p<P; p++)
    { s0 = 10000;
      for(m=0; m<M; m++)
      { s = 0;
        for(i=0; i<I; i++)
        // s += w[m][i]*x[p][i];
        s = (w[m][i]-x[p][i])*(w[m][i]-x[p][i]);

        s+=sqrt(s);
        if(s < s0)
        { s0 = s;
          m0 = m;
        }
      }
      printf("%d\t%d\n",p,m0);
    }
  }
