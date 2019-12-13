#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include"inputoutput.c"

int main(int argc,char * argv[])
{
	int i,j;
	const char s1[15]={"bunny.input"};
	const char s2[15]={"mesh.csv"};
	int rows,cols;
	double *vertex_data;
	FILE *f1,*f2;
	    
    f1 = fopen(s1, "r");
    int vertex_num;
	vertex_data=ReadCSV(f1,&vertex_num,5);
	if (vertex_data==NULL)
	   printf("Read Failed in main!\n"); 
	for (i=0;i<0;i++)
	{
		for (j=0;j<5;j++)
		printf("%f ",vertex_data[i*5+j]);
		printf("\n");
	}
	
	int triangle_num=0;
	double * triangle_data=ReadCSV(f1,&triangle_num,4);
	
    f2 = fopen(s2, "w");
	WriteCSV(f2,vertex_data, triangle_data,vertex_num,triangle_num);
	if (vertex_data!=NULL)
	free(vertex_data);
	if (triangle_data!=NULL)
	free(triangle_data);
    fclose(f1);
    fclose(f2);
    return 0;	
}  
