#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	FILE *fp1,*fp2,*fp3,*fp4;
	int MDTC,MNTC,MDTP,len,index,linenumber,count=0,X;
	char data[20],st[20],search[20];
	char ALA[20],mdt[20],c[20];
	fp1=fopen("pass2.txt","r");
	if (fp1==NULL)
	{
		printf("Cannot open file pass2");
		exit(0);
	}
	fp2=fopen("mdt.txt","r");
	if (fp2==NULL)
	{
		printf("Cannot open file mdt");
		exit(0);
	}
	fp3=fopen("output.txt","w");
	if (fp3==NULL)
	{
		printf("Cannot open file output ");
		exit(0);
	}
	fp4=fopen("mnt.txt","r");
	if (fp4==NULL)
	{
		printf("Cannot open file mnt ");
		exit(0);
	}
line1:
	if(fgets(data,20,fp1)!=NULL)
	{	
		int flag=0;
		fseek(fp4,2,SEEK_SET);
		fscanf(fp4,"%d",&MDTC);		
		fseek(fp4,1,SEEK_CUR);
		while((fgets(search,20,fp4)!=NULL)&&(flag==0))
		{		
			int i=0,j=0;
			while(search[i]!='\0')
			{
				if(search[i]=='&')
				{
					for(j=0;j<=i-1;j++)
					{
						st[j]=search[j];
					}
					break;
				}
				i++;
			}						
			len = strlen(st);
			if(strncmp(st,data,len)==0)
			{				
				flag=1;
				break;
			}			
			fseek(fp4,2,SEEK_CUR);
			fscanf(fp4,"%d",&MDTC);		
			fseek(fp4,1,SEEK_CUR);	
		}
		if(flag==1)
		{

			MDTP=MDTC;
			int k=0,j;
			for(j=len;data[j]!='\0';j++)
			{		
				if(data[j]!=',')
				{
					ALA[k]=data[j];		
					k++;
				}
			}		
			fseek(fp2,0,SEEK_SET);
			for(j=1;j<=MDTP;j++)
			{
				fseek(fp2,2,SEEK_CUR);
				fgets(mdt,20,fp2);
			}		
	line2:
			MDTP++;
			fseek(fp2,2,SEEK_CUR);
			fgets(mdt,20,fp2);	
			j=0;
			int p=0;
			while(mdt[j]!='\0')
			{						
				if(mdt[j]!='#')
				{
					c[p]=mdt[j];				
					p++;	
				}
				else
				{
					j++;
					index=(int)mdt[j];
					index=index-48;
					c[p]=ALA[index];					
					p++;				
				}
				j++;
			}
			char str1[]="MEND";
			if(strncmp(c,str1,4)==0)
			{
				goto line1;
			}
			else
			{
				fputs(c,fp3);
				goto line2;
			}				
		}
		else
		{
			fputs(data,fp3);
			char str2[]="END";
			if(strncmp(data,str2,3)==0)
			{
				printf("Pass 2 completed");
			}
			else
				goto line1;		
		}	
	}
}
