# GT_LRI

# Introduction:
This program calculate the LRI value of microarray dataset with genes in rows and sample in columns

# Procedure:

1. First execute the new.py file
	a)Enter the Input as the mt Filename as data.txt as provided here
	b)input the tissue Filename as control.txt

2. The above program will generate neu.txt file which will be used in the next program

3. Change the code in posval.cpp as follows

	  * sd_col = 1393 ( assign the number of column of neu.txt file in line number 156)
  	* sd_row = 20545 ( assign the number of row of neu.txt file in number 156)

4. Now execute the posval.cpp file
	a)Enter the number of nodes as the number of row of the neu.txt file
	b)Enter the neu file name as neu.txt as provided here

# Contribution: 

Ankumon Sarmah, Vishwa Jyoti Baruah, Papori Neog Bora, Bhaswati Sarmah, Priyakshi Mahanta, Stefano Moretti, Rajnish Kumar, Surajit Borkotokey.
