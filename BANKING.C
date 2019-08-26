#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<conio.h>
#include<graphics.h>

union REGS in,out;
void AddUser();
void MainScreen();
void ShowUser();
void Transaction();
void RemoveUser();
void main()
{
	MainScreen();
	getch();
}
void MainScreen()
{

	int  ch,xc,yc,button,a;
	int gd,gm,f,z;
	gd=DETECT;
	initgraph(&gd,&gm,"");

	setcolor(RED);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR,4);
	outtextxy(150,10,"Banking Mangement System");

	in.x.ax=1;
	int86(0x33,&in,&out);
	setcolor(CYAN);
	gotoxy(33,8);
	printf("Show Users");
	rectangle(200,100,400,140);
	gotoxy(33,12);
	printf("Add Users");
	rectangle(200,160,400,200);
	gotoxy(33,16);
	printf("Transactions");
	rectangle(200,220,400,260);
	gotoxy(33,19);
	printf("Remove Users");
	rectangle(200,280,400,320);
	gotoxy(33,23);
	printf("Exit");
	rectangle(200,340,400,380);
	while(1)
	{

		in.x.ax=3;
		int86(0x33,&in,&out);
		button=out.x.bx;
		xc= out.x.cx;
		yc= out.x.dx;


		if(button==1)
		{
			if(xc>200&&xc<400&&yc>100&&yc<140) //Show User
			{
				a=1;
				break;


			}
			if(xc>200&&xc<400&&yc>160&&yc<200) //Add User
			{
				a=2;
				break;

			}
			if(xc>200&&xc<400&&yc>220&&yc<260) //Transaction
			{
				a=3;
				break;


			}
			if(xc>200&&xc<400&&yc>280&&yc<320) //Remove User
			{
				a=4;
				break;


			}
			if(xc>200&&xc<400&&yc>340&&yc<380) //Exit
			{
				exit(0);
			}



		}
	}



	switch(a)
	{
		case(1):ShowUser(); break;
		case(2):AddUser();  break;
		case(3):Transaction(); break;
		case(4):RemoveUser(); break;
		case(5):break;
	}
}
void AddUser()
{
	FILE *fp;
	char ch,fname[20],lname[20],gen[20];
	int age,balance,account_no;
	fp = fopen("data.txt","a");
	system("cls");
	printf("Enter First Name:");
	scanf("%s",fname);
	printf("Enter Last Name:");
	scanf("%s",lname);
	printf("Enter Gender:");
	scanf("%s",gen);
	printf("Enter age:");
	scanf("%d",&age);
	printf("Enter opening balance:");
	scanf("%d",&balance);
	printf("Enter Account number:");
	scanf("%d",&account_no);

	fprintf(fp,"\n%s %s %s %d %d %d",fname,lname,gen,age,balance,account_no);
	printf("\nRecord added Successfully!!");
	getch();
	fclose(fp);
	MainScreen();

}
void ShowUser()
{
	FILE *fp;
	char ch,fname[20],lname[20],gen[20];
	int age,balance,account_no;
	fp = fopen("data.txt","r");
	system("cls");
	if(fp!=	NULL)
	{
		while(!feof(fp))
		{
			fscanf(fp,"%s%s%s%d%d%d",fname,lname,gen,&age,&balance,&account_no);
			printf("First Name:%s",fname);
			printf("\nLast Name:%s",lname);
			printf("\ngen:%s",gen);
			printf("\nage:%d",age);
			printf("\nbalance:%d",balance);
			printf("\nAccount Number:%d\n\n",account_no);
		}
	}
	else
	{
	printf("No Active Users");
	}
	getch();
	fclose(fp);
	MainScreen();

}
void Transaction()
{
	FILE *fp,*tem;
	char ch,fname[20],lname[20],gen[20];
	int age,balance;
	int choice,acc_no,flag=0,account_no,amount;
	system("cls");
	printf("\n\t\t\tEnter account_number:");
	scanf("%d",&acc_no);
	system("cls");
	fp = fopen("data.txt","ab+");
	tem =fopen("temp.txt","w+");
	//tem = fopen("temp.c","w");
	system("cls");
	while(!feof(fp))
	{
		fscanf(fp,"%s%s%s%d%d%d",fname,lname,gen,&age,&balance,&account_no);
		if(acc_no==account_no)
		{
			printf("\n\t\t\tSelect a Transaction\n\n1.Credit\n2.Debit\n3.Show Balance\n");
			scanf("%d",&choice);
			if(choice==1||choice==2)
			{
				printf("\nenter the amount for transaction:");
				scanf("%d",&amount);
			}
			switch(choice)
			{
				case(1):
				{
				      balance = balance+amount;
				      break;
				}
				case(2):
				{
					if(amount<balance)
					{
						balance = balance-amount;
					}
					else
					{
					printf("Not sufficient amount!!");
					}
					getch();
					break;
				}
				case(3):
				{
					printf("\nBalance:%d\n",balance);
					getch();
				}
			}
			flag=1;
		}
		fprintf(tem,"\n%s %s %s %d %d %d",fname,lname,gen,age,balance,account_no);

	}
	if(flag==0)
	{
		printf("\n\n\t\t\tAccount number not found!!");
		getch();
	}
	fclose(fp);
	fclose(tem);
	remove("data.txt");
	rename("temp.txt","data.txt");
	MainScreen();
}
void RemoveUser()
{
	FILE *fp,*tem;
	int acc_no,account_no,age,balance,flag=0;
	char  fname[20],lname[20],gen[20];
	system("cls");
	printf("\n\t\t\tEnter account_number:");
	scanf("%d",&acc_no);
	system("cls");
	fp = fopen("data.txt","ab+");
	tem =fopen("temp.txt","w+");
	system("cls");
	while(!feof(fp))
	{
		fscanf(fp,"%s%s%s%d%d%d",fname,lname,gen,&age,&balance,&account_no);
		if(acc_no!=account_no)
		{
		fprintf(tem,"\n%s %s %s %d %d %d",fname,lname,gen,age,balance,account_no);
		}
		else
		{
			flag=1;
		}

	}
	if(flag==0)
	{
		printf("\n\n\t\t\tAccount number not found!!");
		getch();
	}
	fclose(fp);
	fclose(tem);
	remove("data.txt");
	rename("temp.txt","data.txt");
	MainScreen();
}
