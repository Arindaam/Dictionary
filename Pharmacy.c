#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include <locale.h>

struct Medicine{
  int id,price,quantity;
  char medicneName[100],Company[100],Exp_Date[11],info[500];
}m;

struct info{
	char symptoms[5][40];
	char disease[50];
	char mednames[3][25];
}inn;

void PurchaseMedicine();
int KnowInfoAboutMedicine();
void AddMedicineinStore();
void expired();
char name[100];
 
int main(){
  int j,choice,c;
  char sym[20];
	int flag=0;
	FILE *infile;
	infile = fopen("info.dat","r");
	printf("Enter the symptom \n");
	gets(sym);
	
	while(fread(&inn,sizeof(struct info),1,infile)){
		for (int j=0;j<5;++j){
			if(strcmp(sym,inn.symptoms[j])==0){
				flag++;
				printf("The details of the entered symptoms are\n");
				printf("The disease is : %s\n",inn.disease);
        int k=0;
        for(k;k<3;k++){
          if(!inn.mednames[k][0]){
            break;
          }
          printf("The prescribed medicines are : %s\n",inn.mednames[k]);
          
        }     
			}
      if(!inn.symptoms[j][0]){
        break;
      }
		}
	}

	if(flag!=1){
		printf("Consult Doctor\n");
  }
	fclose(infile);
  do{
    expired();
    printf("Enter\n1 - Purchase Medicine\n2 - Medicine Information\n3- Add Medicine \n");
    scanf("%d",&choice);
    switch(choice){
      case 1:{
        PurchaseMedicine();
        break;
      }

      case 2:{
        KnowInfoAboutMedicine();
        break;
      }
	
      case 3:{
        AddMedicineinStore();
        break;
      }
    }
    printf("To Continue with other Options Enter 1 Else any other number\n");
    scanf("%d",&c);
  }
  while(c==1);
  return 0;
}

void AddMedicineinStore(){

  FILE *outfile;
  outfile = fopen("med.dat", "a");
  
  printf("Enter Medicine Id\n");
  scanf("%d",&m.id);
  fflush(stdin);
  
  printf("Enter Medicine Name\n");
  fflush(stdin);
  scanf("%s",m.medicneName);
  
  printf("Enter Company Name\n");
  fflush(stdin);
  scanf("%s",m.Company);
  
  printf("Enter Expiry Date\n");
  fflush(stdin);
  scanf("%s",m.Exp_Date);
  
  printf("Enter Quantity\n");
  fflush(stdin);
  scanf("%d",&m.quantity);
  
  printf("Enter Price\n");
  fflush(stdin);
  scanf("%d",&m.price);

  printf("Enter Medicine Info\n");
  fflush(stdin);
  scanf("%s",m.info);
  
  printf("Medicine with id %d Added Successfully\n",m.id);
  fwrite(&m,sizeof(struct Medicine),1,outfile);
  fclose(outfile);
}			 

void PurchaseMedicine(){
	int reqd;
  int quantity=KnowInfoAboutMedicine();
  printf("Total available quality=%d \n",quantity);
  FILE *infile;
	infile = fopen("med.dat", "r");
  printf("Enter quantity reqd: \n");
  scanf("%d",&reqd);
  if(quantity<reqd){
    printf("We dont have enough stock");
    fclose(infile);
  }
  else{   
    FILE *fpt = fopen("temp.dat", "w");
    int count=0;
    while(fread(&m,sizeof(struct Medicine),1,infile) && count!=reqd){
      if(strcmp(m.medicneName,name)==0){
        if(m.quantity> reqd-count){
          m.quantity=m.quantity-reqd+count;
          printf("%d is quantity left of %s \n",m.quantity,m.Company);
          count=reqd;
          fwrite(&m,sizeof(struct Medicine),1,fpt);
        }
        else{
          count=count+m.quantity;
          printf("%s company is exhausted \n",m.Company);
          m.quantity=0;
        }
      }
      else{
         fwrite(&m,sizeof(struct Medicine),1,fpt); 
      }
    }
    fcloseall();
    remove("med.dat");
    rename("temp.dat","med.dat");
  }    
}


int KnowInfoAboutMedicine(){	    
	FILE *infile;
	infile = fopen("med.dat", "r");
  int flag=0;
  printf("Enter Name of the medicine\n");
  fflush(stdin);
  scanf("%s",name);
  printf("\n These are the details of Medicine\n\n");
  while(fread(&m,sizeof(struct Medicine),1,infile)){
    if(strcmp(m.medicneName,name)==0){
      printf("Name=%s\nPrice=%d\nAvailable Quantity=%d\nCompany=%s\nExp Date=%s\nInfo:\n%s\n",m.medicneName,m.price,m.quantity,m.Company,m.Exp_Date,m.info);
      flag+=m .quantity;
      printf("\n");
    }
  }
  if(flag==0){
   printf("Entered Name Not Found\n");
  } 
  fclose(infile);
  return(flag);
}

void expired(){
    char buf[100];
    time_t t;
    struct tm *timeptr,curr,exp_date;
    t = time(NULL);
    timeptr = localtime(&t);
    strftime(buf,sizeof(buf), "%a %m/%d/%Y %r", timeptr);
    FILE* infile=fopen("med.dat","r");
    FILE* fpt = fopen("temp.dat", "w"); 
    while(fread(&m,sizeof(struct Medicine),1,infile)){   
    	if (strptime(buf, "%a %m/%d/%Y %r",&curr) == NULL || strptime(m.Exp_Date, "%d/%m/%Y",&exp_date) == NULL){
        printf("\nstrptime failed\n");
	    }
    	else{
		    if(curr.tm_year < exp_date.tm_year || ( curr.tm_year == exp_date.tm_year && curr.tm_mon < exp_date.tm_mon )){
          fwrite(&m,sizeof(struct Medicine),1,fpt);
		    }
	    }
    }
    fcloseall();
    remove("med.dat");
    rename("temp.dat","med.dat");
}


 


