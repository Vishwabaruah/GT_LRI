#**mat;
#float *in_sum;
#**mat1;


#int **neu;
#int *tissue;
Max1=0;min1=0;tot_sum=0;
num1=0;num2=0;sumx=0;sumy=0;sumxsq=0;sumysq=0;deno1=0;deno2=0;
i=0;j=0;k=0;m=0;n=0;sc=0;tc=0;cnt=0;
sup=0;opp=0;

mtfilename = input("Input the data Filename: ");
tissuefilename=input("input the control Filename:  ");
	
f = open(tissuefilename, 'r')
file_contents =f.read()
tissue = file_contents.splitlines()
f.close()

print(tissue[0]);

tis=len(tissue);
print(tis);

#with open(mtfilename) as textFile:
 #   mt = [float(line.split()) for line in textFile]

with open(mtfilename) as file:
    mt = [[float(digit) for digit in line.split()] for line in file]

    
pos_count, neg_count = 0, 0

for num in tissue: 
 
    if num == 'normal': 
        pos_count += 1
  
    if num == 'tumor': 
        neg_count += 1

sd_row=sr_row=len(mt);
sd_col=neg_count;
sr_col=pos_count;

print("sd_row=",sd_row,"sd_col=",sd_col,"sr_row=",sr_row,"sr_col=",sr_col);

rows, cols = (sd_row, sd_col) 
sd = [[0] * cols for i in range(rows)]

neu = [[0] * cols for i in range(rows)]
#rows, cols = (sd_row, sd_row) 
#mat = [[0] * cols for i in range(rows)]
#mat1 = [[0] * cols for i in range(rows)] 

rows, cols = (sr_row, sr_col) 
sr = [[0] * cols for i in range(rows)]

r_row=0;
d_row=0;

#def column(matrix, i):
#    return [row[i] for row in matrix]

for i in range(len(tissue)):
        if tissue[i]=='normal':
            for j in range(sr_row):
                    sr[j][r_row]=mt[j][i];
            r_row=r_row+1;   
        if tissue[i]=='tumor':
            for j in range(sd_row):
                    sd[j][d_row]=mt[j][i];      
            d_row=d_row+1;

import numpy as np
#print(np.matrix(sr));


for i in range(sd_row):#loop depend on sd_row
        max1=min1=sr[i][0];
        for j in range(sr_col):
            if sr[i][j]>max1:
                max1=sr[i][j];
            if sr[i][j]<min1:
                min1=sr[i][j];	    
        for n in range(sd_col):			
            if sd[i][n]>=min1 and sd[i][n]<=max1:
                neu[i][n]=0;
            else:
                neu[i][n]=sd[i][n];
				
#print(np.matrix(neu));
mat = np.matrix(neu)
with open('neu.txt','wb') as f:
    for line in mat:
        np.savetxt(f, line, fmt='%d')


# # del sd
# # del sr
# # import gc
# # gc.collect()

# rows, cols = (sd_row, sd_row) 
# #mat = [[0] * cols for i in range(rows)]
# #mat1 = [[0] * cols for i in range(rows)] 
# mat1 = np.zeros((rows,cols), dtype=bool)
# import math;
# print("one")
# #myfile = open('outfile.txt', 'w')
# temp=0
# for i in range(sd_row):
#     for j in range(sd_row):
#         if i!=j:
#             for k in range(sd_col):
#                 num1=num1+neu[i][k]*neu[j][k];
#                 sumx=sumx+neu[i][k];
#                 sumy=sumy+neu[j][k];
#                 sumxsq=sumxsq+pow(neu[i][k],2);
#                 sumysq=sumysq+pow(neu[j][k],2);
#             num1=sd_col*num1;
#             num2=sumx*sumy;
#             deno1=math.sqrt(sd_col*sumxsq-pow(sumx,2));
#             deno2=math.sqrt(sd_col*sumysq-pow(sumy,2));
#             if deno1*deno2!=0:
#                 temp=(num1-num2)/(deno1*deno2);
#             if temp>0.9:
#                 mat1[i,j]=1;
#             else:
#                 mat1[i,j]=0;
#         num1=num2=sumx=sumy=sumxsq=sumysq=deno1=deno2=0;
#     #print(i,j)

# #myfile.close()
# import numpy as np 
# mat = np.matrix(mat1)
# with open('outfile.txt','wb') as f:
#     for line in mat:
#         np.savetxt(f, line, fmt='%d')

  
# # print(np.matrix(mat));
# #print(np.matrix(mat1));
