#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
// a struct to read and write 
struct person  
{ 
        char symptoms[5][40];
	char disease[50];
	char mednames[3][25];
};
int main() 
{ 
    FILE *outfile; 
    outfile = fopen ("info.dat", "w"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 
  
    struct person input1 = {{"blackheads","cysts","whiteheads"}, "acne", {"benzoyl peroxide","Azelaic acid"}};
    struct person input2 = {{"stomach pain","nausea","jaundice","indigestion"}, "acute pancreatitis", {"Acetaminophen","Tramadol"}};
    struct person input3 = {{"wheezing","coughing"}, "asthma", {"Albuterol","Metaproterenol"}};
    struct person input4 = {{"spots"}, "chickenpox", {"acyclovir"}};
    struct person input5 = {{"stomach pain","bloated","foul-smelling stool"}, "constipation", {"Enulose","Kristalose"}};
    struct person input6 = {{"thirsty","tired","weightloss","blurred vision","urinating friendly"}, "diabetes", {"metformin","meglitinides"}};  
    

    // write struct to file 
	fwrite (&input1, sizeof(struct person), 1, outfile); 
	fwrite (&input2, sizeof(struct person), 1, outfile); 
	fwrite (&input3, sizeof(struct person), 1, outfile); 
	fwrite (&input4, sizeof(struct person), 1, outfile); 
	fwrite (&input5, sizeof(struct person), 1, outfile); 
	fwrite (&input6, sizeof(struct person), 1, outfile);       
    if(fwrite != 0)  
        printf("contents to file written successfully !\n"); 
    else 
        printf("error writing file !\n"); 	
  
    // close file 
    fclose (outfile); 
  
    return 0; 
} 
