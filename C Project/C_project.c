#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
 struct Medicine{
   int id,price,quantity;
   char medicneName[100],Company[100],Mfg_Date[11],Exp_Date[11],info[5000];
  }m[100];
 struct info{
	  char symptoms[2][20];
	  char disease[50];
	  char mednames[150];
  }in[5];
 void PurchaseMedicine(int number);
 void EnterInfoAboutMedicine(int number);
 //void KnowInfoAboutMedicine(int number);
 void AddMedicineinStore(int number,struct Medicine m[]);
 void DeleteMedicineStore(int number);
 

int main()
 {
   int i,j,choice,number=0,c;
   for(i=0;i<100;i++)
   {
   m[i].id=0;
   m[i].price=0;
   m[i].quantity=0;
   strcpy(m[i].Mfg_Date,"");
  strcpy(m[i].Exp_Date,"");
   strcpy(m[i].medicneName,"");
   strcpy(m[i].Company,"");
   strcpy(m[i].info,"");
   }
	char sym[20];
	int flag=0;
	FILE *infile;
	infile = fopen("info.dat","r");
	printf("Enter the symptom \n");
	gets(sym);
	for(int i=0;i<2;++i)
	{
		while(fread(&in[i],sizeof(struct info),1,infile))
		{
			for (int j=0;j<2;++j){
				if(strcmp(sym,in[i].symptoms[j])==0){
					flag=1;
					printf("The details of the entered symptoms are\n");
					printf("The disease is : %s\n",in[i].disease);
					printf("The prescribed medicines are : %s\n",in[i].mednames);
				}
			}
		}
	}
	if(flag==0)
		printf("Consult Doctor\n");
	fclose(infile);
   do{
   printf("Enter\n1 - Purchase Medicine\n2 - Enter Information about a Medicine\n3 - Medicine Information\n4 - Add Medicine\n5 - Delete a Medicine\n");
   scanf("%d",&choice);
   switch(choice)
   {
    case 1:
    {
     PurchaseMedicine(number+1);
     break;
    }
     case 2:
    {
     EnterInfoAboutMedicine(number+1);
     break;
    }

      case 3:
      {
       KnowInfoAboutMedicine(number+1);
       break;
      }
      case 4:
      {
       ++number;
       AddMedicineinStore(number,m);
       break;
      }
      case 5:
      {
       DeleteMedicineStore(number+1);
       break;
      }

   }
     printf("To Continue with other Options Enter 1 Else any other number\n");
     scanf("%d",&c);
   }while(c==1);
   return 0;

 }
 void PurchaseMedicine(int number)
 {
	 FILE *infile;
	infile = fopen("med.dat", "r");
  int id,check,i,quantity,flag=0;
  char name[100];
  printf("Enter Name of Medicine\n");
  fflush(stdin);
   gets(name);
   for(i=0;i<number;i++)
   {
	    while(fread(&m[i],sizeof(struct Medicine),1,infile))
    if(strcmp(m[i].medicneName,name)==0)
    {
     flag=1;
     int c;
     printf("These are the details of Medicine\n");
     printf("Name=%s\nPrice=%d\nAvailable Quantity=%d\nCompany=%s\nMfg Date=%s\nExp Date=%s\n",m[i].medicneName,m[i].price,m[i].quantity,m[i].Company,m[i].Mfg_Date,m[i].Exp_Date);
      /*if(strcmp(m[i].info,"")==0)
      {
       printf("Medicine Review/Info=Not Available\n");
      }
      else
      {
       printf("Medicine Review/Info=%s\n",m[i].info);
      }
	  */
     printf("Do you want to purchase %s \nIf Yes Enter 1 else any other number\n",m[i].medicneName);
     fflush(stdin);
     scanf("%d",&c);
     if(c==1)
     {
      printf("Enter Quantity to Purchase\n");
      scanf("%d",&quantity);
      if(m[i].quantity>quantity)
      {
       printf("Total Price to be paid=%d\n",quantity*m[i].price);
      }
      else{
       printf("Please Enter quantity below Available Quantity\n");
      }
     }
     break;
    }
   }
   if(flag==0)
   {
    printf("Entered Name Not Found\n");
   }
   fclose(infile);
  }


 /*void EnterInfoAboutMedicine(int number)       
 {
  int i,flag=0,c;
  char name[100],info[100];
  printf("Enter Name of the medicine you want to Review or include Info\n");
  fflush(stdin);
  gets(name);
  for(i=0;i<number;i++)
  {
   if(strcmp(m[i].medicneName,name)==0)
   {
    flag=1;
    printf("These are the details of Medicine\n");
    printf("Name=%s\nPrice=%d\nAvailable Quantity=%d\nCompany=%s\nMfg Date=%s\nExp Date=%s\n",m[i].medicneName,m[i].price,m[i].quantity,m[i].Company,m[i].Mfg_Date,m[i].Exp_Date);
    if(strcmp(m[i].info,"")!=0)
    {
     printf("Review Already Available!\nIf you want to Add a Review Enter 1 else Any other number\n");
     fflush(stdin);
     scanf("%d",&c);
    }
    else
    {
     printf("Enter review(less than 100 Characters)\n");
     fflush(stdin);
     gets(m[i].info);
    }
    if(c==1)
    {
     printf("Enter review(less than 100 Characters)\n");
     fflush(stdin);
     gets(info);
     strcat(m[i].info,"; ");
     strcat(m[i].info,info);
    }

   }
  }
  if(flag==0)
  {
   printf("Entered Name Not Found\n");
  }
 }
 */
 /*void KnowInfoAboutMedicine(int number)
{	
	FILE *infile;
	infile = fopen("med.dat", "r");
   int i,flag=0;
  char name[100];
  printf("Enter Name of the medicine you want to see Review and Info\n");
  fflush(stdin);
  gets(name);
  for(i=0;i<number;i++)
  {
	  while(fread(&m[i],sizeof(struct Medicine),1,infile))
   if(strcmp(m[i].medicneName,name)==0)
   {
    flag=1;
    printf("These are the details of Medicine\n");
    printf("Name=%s\nPrice=%d\nAvailable Quantity=%d\nCompany=%s\nMfg Date=%s\nExp Date=%s\n",m[i].medicneName,m[i].price,m[i].quantity,m[i].Company,m[i].Mfg_Date,m[i].Exp_Date);
    if(strcmp(m[i].info,"")!=0)
    {
     printf("Review or Info=%s\n",m[i].info);
    }
    else
    {
     printf("Review or Info=Not Available\n");
    }
   }
  }
  if(flag==0)
  {
   printf("Entered Name Not Found\n");
  }
  fclose(infile);
  
 }
*/
 void AddMedicineinStore(int number,struct Medicine m[])
 
{ 
  FILE *outfile;
  outfile = fopen("med.dat", "a");
  char name[100];
  printf("Enter Medicine Id\n");
  scanf("%d",&(m[number].id));
  fflush(stdin);
  printf("Enter Medicine Name\n");
  fflush(stdin);
  gets(name);
  strcpy(m[number].medicneName,name);
  printf("Enter Company Name\n");
  fflush(stdin);
  gets(m[number].Company);
  printf("Enter Manufactured Date\n");
  fflush(stdin);
  gets(m[number].Mfg_Date);
  printf("Enter Expiry Date\n");
  fflush(stdin);
  gets(m[number].Exp_Date);
  printf("Enter Quantity\n");
  fflush(stdin);
  scanf("%d",&(m[number].quantity));
  printf("Enter Price\n");
  fflush(stdin);
  scanf("%d",&(m[number].price));
  strcpy(m[number].info,"");
  printf("Medicine with id %d Added Successfully\n",m[number].id);
  fwrite(&m[number],sizeof(struct Medicine),1,outfile);
  fclose(outfile);
                }			 

 void DeleteMedicineStore(int number)
 { 
  int id,i,flag=0,num;
  printf("Enter Id to be deleted\n");
  fflush(stdin);
  scanf("%d",&id);
  for(i=0;i<number;i++)
  {
   if(m[i].id==id)
   {
    flag=1;
    m[i].id=0;
    m[i].price=0;
    m[i].quantity=0;
    strcpy(m[i].medicneName,"");
    strcpy(m[i].Company,"");
    strcpy(m[i].Mfg_Date,"");
    strcpy(m[i].Exp_Date,"");
    strcpy(m[i].info,"");
    num=i;
    break;
   }
  }
  if(flag==1)
  {
   printf("Medicine with %d is Deleted Successfully\n",id);
  }
 }


