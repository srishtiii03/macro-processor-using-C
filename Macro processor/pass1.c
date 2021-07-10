#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	FILE *fp1,*fp2,*fp3,*fp4;
	int MDTC,MNTC;
	char data[20],st[20];
	fp1=fopen("input.txt","r");
	if (fp1==NULL)
	{
		printf("Cannot open file input");
		exit(0);
	}
	MDTC=1;
	MNTC=1;
	fp2=fopen("mdt.txt","w");
	if (fp2==NULL)
	{
		printf("Cannot open file mdt");
		exit(0);
	}
	fp3=fopen("pass2.txt","w");
	if (fp3==NULL)
	{
		printf("Cannot open file pass2 ");
		exit(0);
	}
	fp4=fopen("mnt.txt","w");
	if (fp4==NULL)
	{
		printf("Cannot open file mnt ");
		exit(0);
	}
line1:
	if(fgets(data,20,fp1)!=NULL)
	{	
		char str1[] = "MACRO";
		if(strncmp(data,str1,5)==0)
		{
			if(fgets(data,20,fp1)!=NULL)
			{
				strcpy(st,data);
				
				fprintf(fp4,"%d\t%d\t%s",MNTC,MDTC,data);
				MNTC++;
				char ALA[20];
				int i=0,j=0;
				while(st[i]!='\0')
				{
					if(st[i]=='&')
					{
						ALA[j]=st[++i];
						j++;
					}
					i++;
				}
				fprintf(fp2,"%d\t%s",MDTC,data);
				MDTC++;	
			line2:	
				if(fgets(data,20,fp1)!=NULL)
				{
					strcpy(st,data);					
					int i=0,k;
					while(st[i]!='\0')
					{						
						if(st[i]=='&')
						{		
							st[i]='#';
							i++;
							int q=47;
							for(k=0;k<=j-1;k++)        
							{	
								q++;						
								if(ALA[k]==st[i])
									break;
							}
							char c =(char)q;
							st[i]=c;
						}
						i++;
					}
					fprintf(fp2,"%d\t%s",MDTC,st);
					MDTC++;
					char str2[]="MEND";
					if(strncmp(data,str2,4)==0)
						goto line1;
					else
						goto line2;					
				}					
			}
		}
		else
		{
			fputs(data,fp3);
			char str3[]="END";
			if(strncmp(data,str3,3)==0)
			{
				printf("Pass 1 completed");
				exit(0);
			}
			else
				goto line1;					
		}
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	return 0;
}
