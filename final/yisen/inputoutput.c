#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void writeStrToFile(FILE* f, char* str) {
    int i, n;
    n = strlen(str);
    for (i = 0; i < n; i++) {
        fprintf(f, "%c", str[i]);
    }
}

double* ReadCSV(FILE* f1, int* n_rows, int n_cols, int kk) {
    if (f1 == NULL) {
        printf("Failed to open file!\n");
         return NULL;
    }
    char line[1000];
    int p, i, j,  len_line, index_mat=0, len_strNum = 0, count;
    float mat[200000], t;
    char strNum[100];
    double* data_ptr = NULL;
    
    fgets(line, 512, f1);
    *n_rows=strtol(line, (char **)NULL, 10);

	
    printf("lines of data %d \n",*n_rows);
 //   for (i=0;i<strlen(line);i++)
  //    printf("%c",line[i]);

    for (p=0; p<*n_rows*kk;p++)
	{
	    if (fgets(line, 512, f1) == NULL) {
	    	printf("error\n missing lines"); break;
		} 
        len_line = strlen(line);
        count=0;
        for (i = 0; i < len_line; i++) {
            if ((line[i] == ' ' || line[i] == '\n') && len_strNum > 0) {
                strNum[len_strNum] = '\0';
                t = strtod(strNum, NULL);
                mat[index_mat++] = t;
               // printf("%f ",t);
                count++;
                len_strNum = 0;
            } else {
                strNum[len_strNum++] = line[i];
            }
        }
        if (count!=n_cols) {
        	printf("Error: missing entry in line %d\n",p);
            
		}
    }

    if (index_mat == (*n_rows * n_cols*kk)) {
        data_ptr = (double*)calloc((*n_rows * n_cols*kk), sizeof(double));
        if (data_ptr != NULL) {
            for (i = 0; i < *n_rows * n_cols*kk; i++)
                data_ptr[i] = mat[i];
        } else
            printf("Failed when doing malloc\n");

    } else {
        printf("Failed to read file: missing enrty\n");
    }

    return data_ptr;
}

double* ReadCSV2(FILE* f1, double *r, int* n_rows, int n_cols) {
    if (f1 == NULL) {
        printf("Failed to open file!\n");
         return NULL;
    }
    char line[1000];
    int p, i, j,  len_line, index_mat=0, len_strNum = 0, count;
    float mat[200000], t;
    char strNum[100];
    double* data_ptr = NULL;
    
    fgets(line, 512, f1);
    fgets(line,512,f1);
    *r=strtod(line, (char **)NULL);
    fgets(line,512,f1);
    *n_rows=strtol(line, (char **)NULL, 10);

	
    printf("lines of data %d \n",*n_rows);
 //   for (i=0;i<strlen(line);i++)
  //    printf("%c",line[i]);

    for (p=0; p<*n_rows;p++)
	{
	    if (fgets(line, 512, f1) == NULL) {
	    	printf("error\n missing lines"); break;
		} 
        len_line = strlen(line);
        count=0;
        for (i = 0; i < len_line; i++) {
            if ((line[i] == ' ' || line[i] == '\n') && len_strNum > 0) {
                strNum[len_strNum] = '\0';
                t = strtod(strNum, NULL);
                mat[index_mat++] = t;
               // printf("%f ",t);
                count++;
                len_strNum = 0;
            } else {
                strNum[len_strNum++] = line[i];
            }
            
        }
        mat[index_mat++] = *r;
        if (count!=n_cols) {
        	printf("Error: missing entry in line %d\n",p);
            
		}
		//printf("%d\n",index_mat);
    }

    if (index_mat == (*n_rows * (n_cols+1))) {
        data_ptr = (double*)calloc((*n_rows * (n_cols+1)), sizeof(double));
        if (data_ptr != NULL) {
            for (i = 0; i < *n_rows* (n_cols+1); i++)
                data_ptr[i] = mat[i];
        } else
            printf("Failed when doing malloc\n");

    } else {
        printf("Failed to read file: missing enrty %d %d\n",*n_rows * (n_cols+1),index_mat);
    }

    return data_ptr;
}

void WriteCSV(FILE* f2,
              double* vertex_data,
              double* triangle_data,
              int vertex_num,
              int triangle_num) {
    if (f2 == NULL)
        printf("Failed to write file!\n");
    int cols_triangle=4,cols_vertex=5;
    int i, j, k;
    fprintf(f2,"%d\n",triangle_num);
    if (vertex_data != NULL && triangle_data!=NULL) {
        for ( k= 0; k < triangle_num; k++)
            for (i = 0; i < 3; i++) {
            	int index=triangle_data[k*cols_triangle+i+1];
            	for (j=0;j<3;j++) {
                    fprintf(f2, "%f ", vertex_data[index * cols_vertex + j]);
                }
               fprintf(f2, "\n");
            }
        
    } else {
        printf("Empty data to write\n");
    }
    
}
