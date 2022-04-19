#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<malloc.h>
#include<string.h>
//#include<unistd.h>
#include<time.h>
#include<omp.h>
#include<stdbool.h>

unsigned int nodes, link1 = 0, cnodes = 0;
int **neu;
int** mat;
double** final;



float convert(char* a)
{
	char ch;
	float val, b;
	int len, k, dot, mode, b1;
	len = strlen(a);

	val = 0;
	mode = 10;
	k = 0;
	dot = 0;

	while (k != len)
	{

		ch = a[k];

		if (ch != '.' && dot == 0)
		{
			val = 10 * val + (ch - '0');
		}

		if (ch == '.')
		{
			dot = 1;
		}

		if (ch != '.' && dot == 1)
		{
			val = val + ((float)(ch - '0') / mode);
			mode = mode * 10;
		}

		k++;
	}
	return val;
}

void take()
{
	char c, ch[100], file[20];
	int i, j, k, col1, row = 0, col = 0;
	FILE* fp;

	printf("enter the neu file name\n");
	scanf("%s", file);
	fp=fopen(file, "r");
	c = fgetc(fp);
	i = 0;
	k = 0;
	j = 0;
	while (c != EOF)
	{
		if (c == ' ')
		{
			//printf("%s ",ch);
			neu[row][col] = convert(ch);
			//if (neu[row][col] == 1)
			//	link1++;
			i = 0;
			k++;
			memset(ch, 0, 100);
			col++;
		}
		else
		{
			if (c == '\n')
			{

				//neu[row][col] = ch[0] - '0';
				neu[row][col] =convert(ch);
				//printf("%d\n",neu[row][col]);
				//if (neu[row][col] == 1)
				//	link1++;
				memset(ch, 0, 100);

				col = 0;
				row++;
				j++;
				k = 0;
				i = 0;
			}
			else
			{
				ch[i] = c;
				i++;
			}
		}

		c = fgetc(fp);

	}


	fclose(fp);
}
void game()
{
	double sum = 0, totsum = 0;
	int i, j, count = 0;

	for (i = 0;i < nodes;i++)
	{
		for (j = 0;j < nodes;j++)
		{
			if (mat[i][j] != 0 && i != j)
			{
				sum = sum + (double)(1.0 / mat[j][nodes]);
				count++;
				//printf("%lf\n",sum);
			}
		}
		if (sum != 0)
			sum = sum + 1;
		//printf("%lf ",sum);
		sum = sum / (cnodes * 2);
		final[i][0] = sum;
		final[i][1] = i;
		//printf("%lf %d\n",sum,count);
		totsum = totsum + sum;
		sum = 0;
		count = 0;

	}
	printf("totsum=%lf", totsum);
}
int main()
{
	int i, j, k = 0, t;
	
	
	unsigned int sd_col = 00000, sd_row = 11111;
	double total_time;
	clock_t start,end;
	//printf("%d",omp_get_max_threads());
	printf("enter the no of nodes");
	scanf("%d", &nodes);

	
	neu = (int **)malloc(nodes * sizeof(int*));

	for (i = 0; i < nodes; i++)
	{
		neu[i] = (int*)malloc((sd_col) * sizeof(int));

	}

	take();
	
	/*for (i = 0; i <  nodes; i++)
	{
	 for (j = 0; j <sd_col; j++)
	 {
		 printf("%d ",neu[i][j]);
		}
	 printf("\n");
	}*/
	printf("one\n");
	mat = (int**)malloc(nodes * sizeof(int*));

	for (i = 0; i < nodes; i++)
	{
		mat[i] = (int*)malloc(nodes * sizeof(int));

	}
	printf("two\n");

	start = clock();
	
	for (i = 0; i <  nodes; i++)
	{
	 for (j = 0; j <nodes; j++)
	 {
		 mat[i][j]=0;
		}
	 
	}
omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel shared(nodes,mat)
	{
		
		#pragma omp for
		for (int i = 0;i < nodes;i++)
		{
			
#pragma omp parallel //firstprivate(i,num1,num2,sumx,sumy,sumxsq,sumysq,deno1,deno2,temp) shared(mat,nodes)
			{
				double num1 = 0, num2 = 0, sumx = 0, sumy = 0, sumxsq = 0, sumysq = 0;
				double deno1 = 0, deno2 = 0,temp=0;
				#pragma omp for
				for (int j = 0;j < nodes;j++)
				{
					if (i != j)
					{

						for (int k = 0;k < sd_col;k++)
						{
							num1 = num1 + neu[i][k] * neu[j][k];
							sumx = sumx + neu[i][k];
							sumy = sumy + neu[j][k];
							sumxsq = sumxsq + pow(neu[i][k], 2);
							sumysq = sumysq + pow(neu[j][k], 2);
						}
						num1 = sd_col * num1;
						num2 = sumx * sumy;
						deno1 = sqrt(sd_col * sumxsq - pow(sumx, 2));
						deno2 = sqrt(sd_col * sumysq - pow(sumy, 2));
						if (deno1 * deno2 != 0)
							temp = double((num1 - num2) / (deno1 * deno2));
						if (temp > 0.9)
							mat[i][j] = 1;
						else
							mat[i][j] = 0;
					}
					//printf("%lf\n",temp);
					num1 = num2 =sumx =  sumy =  sumxsq =  sumysq = deno1 =  deno2 = temp=0;
			
				}
				
				//printf("%d %d\n", i, j);
			}
			
		}

	}
	
	end = clock();
	printf("time is =%lf\n", (double)(end - start) / (double)CLOCKS_PER_SEC);
	
	FILE *fp;


if((fp=fopen("test.txt", "wb"))==NULL) {
    printf("Cannot open file.\n");
}

for(i=0;i<nodes;i++) {
for(j=0;j<nodes;j++) {
    fprintf(fp,"%d ",mat[i][j]);
}
fprintf(fp,"\n");}

fclose(fp);
printf("mat first value %d",mat[0][0]);
	
	printf("three\n");
	
	
	int count = 0;
	for (i = 0; i < nodes; i++)
	{
		for (j = 0;j < nodes;j++)
		{
			if (mat[i][j] == 1)
				count++;
		}
		mat[i][nodes] = count;
		if (count == 0)
			cnodes++;
		count = 0;
	}
	cnodes = nodes - cnodes;
	final = (double**)malloc(nodes * sizeof(double*));

	for (i = 0; i < nodes; i++)
	{
		final[i] = (double*)malloc(2 * sizeof(double));

	}
	printf("four\n");
	game();
	printf("five\n");
	/*for (i = 0; i <  nodes; i++)
	{
	 for (j = 0; j <=nodes; j++)
	 {
		 printf("%d ",mat[i][j]);
		}
	 printf("\n");
	}*/

	 //link1=(link1)/2;
	//printf("link is %d\n ",link1);





//start=clock();
//end=clock();
//printf("time is =%lf\n",(double)(end-start)/(double)CLOCKS_PER_SEC);
double temp=0;
	for (i = 0;i < nodes - 1;i++)
	{
		for (j = 0;j < nodes - i - 1;j++)
		{
			if (final[j][0] > final[j + 1][0])
			{
				temp = final[j][0];
				final[j][0] = final[j + 1][0];
				final[j + 1][0] = temp;

				t = final[j][1];
				final[j][1] = final[j + 1][1];
				final[j + 1][1] = t;
			}

		}
	}

	printf("six\n");

	double sum = 0;
	for (i = 0;i < nodes;i++)
	{
		printf("%d=%lf\n", (int)(final[i][1] + 1), final[i][0]);
		sum = sum + final[i][0];
	}

	printf("sum is %f", sum);
	getch();
	return(0);
}


