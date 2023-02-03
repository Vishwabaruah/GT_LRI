# GT_LRI (Game Theoretic Link Relevence Index)

# Introduction:

This program calculates the LRI value of the genes in the microarray dataset. The dataset must have genes in rows and samples in columns. The method is suitable for a Case-Control microarray dataset. 

# Procedure:

1. First execute the new.py file
	* Enter the Input as the mt Filename as data.txt as provided here
	* Input the tissue Filename as control.txt

2. The above program will generate neu.txt file which will be used in the next program

3. Change the code in posval.cpp as follows
	* sd_col = 1393 ( assign the number of column of neu.txt file in line number 156)
  	* sd_row = 20545 ( assign the number of row of neu.txt file in number 156)

4. Now execute the posval.cpp file
	* Enter the number of nodes as the number of row of the neu.txt file
	* Enter the neu file name as neu.txt as provided here

# Contribution: 

Ankumon Sarmah, Vishwa Jyoti Baruah, Papori Neog Bora, Bhaswati Sarmah, Priyakshi Mahanta, Stefano Moretti, Rajnish Kumar, Surajit Borkotokey.

# Cite these articles

For more information and citing this method use follwing references.

1. [Baruah, V. J., Neog Bora, P., Sarmah, B., Mahanta, P., Sarmah, A., Moretti, S., ... & Borkotokey, S. (2022). Game-theoretic link relevance indexing on genome-wide expression dataset identifies putative salient genes with potential etiological and diapeutics role in colorectal cancer. Scientific Reports, 12(1), 13409.](https://doi.org/10.1038/s41598-022-17266-0)

2. [Neog Bora, P., Baruah, V. J., Borkotokey, S., Gogoi, L., Mahanta, P., Sarmah, A., ... & Moretti, S. (2020). Identifying the salient genes in microarray data: A novel game theoretic model for the co-expression network. Diagnostics, 10(8), 586.](https://doi.org/10.3390/diagnostics10080586)

