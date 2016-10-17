#include <windows.h>
#include <iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

void play();//play game
void empty(char table[][9][3] );//empty table and mark trine table
void emptySmallTable(char table[][9][3],char tableNum);//empty small table ,small table = trine table
bool fullSmallTable(char table[][9][3],char tableNum);//if full small table return true else return false
bool fullTable(char table[][9][3]);//if full sudoku table return true else false
bool setNumber(char table[][9][3] , int l , int c , char num );//if set number in sudoku table return true else false
bool searchLine(char table[][9][3] , int l , int c , char num);//if exit number in line return false else return true
bool searchCloumn(char table[][9][3] , int l , int c,char num) ;//if exit number in cloumn return false else return true
bool searchTableTrine(char table[][9][3] , int l , int c , char num);//if exit number in trine table return false else return true
void complate(char table[][9][3], char tableNum);//full soduku table
void status(char table[][9][3]);//status game and clear random number 
void print(char table[][9][3]);//print table

/////////////////
char backC;//shomare jadvale setai addai ke ba addad set shode barabare va dar ye cloumn  
char backL;//shomare jadvale setai addai ke ba addad set shode barabare va dar ye line
char backT;//shomare jadvale setai addai ke ba addad set shode barabare va dar ye table
////////////////

//#####Main#####
int main()
{
	// Change the window title:
    SetConsoleTitle(TEXT("Sudoku"));
	char select;
	do
	{

		system("cls");
		system("color F0");
			
		cout<<"\n\n                     \4\4 Welcome to Sudoku \4\4\n ";
		cout<<"\n\n\n   Are you play game?\n\n   1:Play                    OTH:Exit \n   ";
		cin>>select ;
		system("cls");

		if(select=='1')
			 play();//play game
		else
			break;
	}while(true);
}
//#####End Main#####

//define play
void play()
{
	char table[9][9][3],num;
	int l, c;
	
	empty(table);//empty table
	status(table);//status game
	//do-while full table
	do{
		system("cls");
		system("color F1");
		print(table);//print

		//end while , full table
		if(fullTable(table)==true)
			break;

		//get number 
		cout<<"\n\n         Line: ";
		cin>>l;
		cout<<"         Column: ";
		cin>>c;
		cout<<"         Enter number: ";
		cin>>num;

		//number must 1 to 9
		if( l<1 || l>9 || c<1 || c>9 || num<49 || num>57)
		{
			system("color C");
			cout<<"\n         ERORR:my dear user please enter number 1 to 9\n               OK!!!!!\n         ";
			system("pause");
			continue;
		}
		
		//number set in table
		setNumber(table,--l,--c,num);	

	}while(true);

	system("color A");
	cout<<"\n\n                      \3\3\3You Win\3\3\3 \n\n                      tnx :x ";  
	system("pause");
}

//define empty
void empty(char table[][9][3])
{
	char t=1;
	char em=(char)0xB0;

	//empty array and mark small table 
	for(int i=0;i<9;i++)
	{
		t='1';
		if(i>=3 && i<6)
			t='4';
		else if(i>=6 && i<9)
			t='7';

		for(int j=0;j<9;j++)
		{
			if(j==3 ||j==6 )
				t++;
			if(t%2==0)
				em=(char)0xB2;
			else
				em=(char)0xB0;
			table[i][j][1]=t;
			table[i][j][0]=em;
		}
	}
	
	//empty table[][][2] 
	 for(int i=0 ; i<9 ; i++)
		 for(int j=0 ; j<9 ; j++)
			 table[i][j][2]=NULL;
}
//end empty

//define empty small table
void emptySmallTable(char table[][9][3],char tableNum)
{
	char emp=(char)0xB0;
	if(tableNum % 2==0)
		emp=(char)0xB2;

	for(int i=0;i<9;i++)
		for(int j=0; j<9; j++)
			if(table[i][j][1]==tableNum)
				table[i][j][0] = emp;

}
//end empty small table

//define full small table
bool fullSmallTable(char table[][9][3],char tableNum)
{
	system("cls");
	system("color F2");
	cout<<"\n\n\n                       \5\5   LODING \5" ;
	for(int i=0;i<9;i++)
	{
		cout<<"\n                       \5\5\5\5\5\n                       " ;
		for(int j=0; j<9; j++)
		{
				if(table[i][j][1]==tableNum)
				{
					cout<<"\5\5\5\5";
					if(table[i][j][0]==(char)0xB0 || table[i][j][0]==(char)0xB2)
					{
						cout<<"\5\5\5";
						return false;
					}
				}
		}
	}
	return true;
}
//end full small table

//define full table
bool fullTable(char table[][9][3])
{
	for(int i=0;i<9;i++)
		for(int j=0; j<9; j++)
			if(table[i][j][0]==(char)0xB0 || table[i][j][0]==(char)0xB2)
				return false;

	return true;
}
//end full table

//define set number
bool setNumber(char table[][9][3],int l ,int c ,char num)
{
	if((searchLine(table , l , c , num)==false) || (searchCloumn(table, l ,c ,  num)==false) || (searchTableTrine(table , l, c, num)==false))
		return false;

	if(table[l][c][2] == 'X' )//for user dont change number in table
		return false;

	table[l][c][0]=num;//set number
	return true;
}
//end set number

//define search line
bool searchLine(char table[][9][3],int l,int c,char num)
{
	for(int i=0;i<9;i++)
	{
		if(table[l][i][0] ==	num)//exit num in line
		{
			backL = table[l][i][1];
			return false;
		}
	}

	backL = '0';
	return true;
}
//end search line

//define search cloumn
bool searchCloumn(char table[][9][3] , int l ,int c, char num)
{
	for(int i=0;i<9;i++)
	{
		if(table[i][c][0]==num)//exit num in cloumn
		{
			backC = table[i][c][1];
			return false;
		}
	}

	backC='0';
	return true;
}
//end search cloumn

//define search table trine
bool searchTableTrine(char table[][9][3] , int l , int c , char num)
{
		for(int i=0 ; i<9 ; i++)
			for(int j=0 ; j<9 ; j++)
				if( table[i][j][1] == table[l][c][1] )
					if( table[i][j][0] == num )//exit num in table trine
					{
						backT = table[i][j][1];
						return false;
					}

	backT='0';
	return true;
}
//end search table trine


//define complate
void complate (char table[][9][3],char tableNum)
{
	char randNum;
	int randL,randC;//rand num and line and cloumn
	srand(time(NULL)*100000);

		switch(tableNum)
		{//switch
		//table 1
		case '1':

			for(int i=0;i<1000;i++)
			{//for1
				randL = rand()%3;
				randC = (rand()/100)%3;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum) ;
			}//for1
			break;
		case '2':
		//table2
			for(int i=0;i<1000;i++)
			{//for 2
				randL = rand()%3 ;
				randC = ((rand()/100)%3) + 3;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum) ;
			}//for 2
			break;
		case '3':
		//table 3
			for(int i=0;i<1000;i++)
			{//for 3
				randL = rand()%3 ;
		 		randC = ((rand()/100)%3) + 6;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum) ;
			}//for 3
			break;
		case '4':
		//table 4
			for(int i=0;i<1000;i++)
			{//for 4
				randL = (rand()%3) +3 ;
				randC = ((rand()/100)%3) ;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum) ;
			}//for 4
			break;
		case '5':
		//table 5	
			for(int i=0;i<1000;i++)
			{//for 5
				randL = (rand()%3) +3 ;
				randC = ((rand()/100)%3) + 3 ;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum);
			}//for 5
			break;
		case '6':
		//table 6
			for(int i=0;i<1000;i++)
			{//for 6
				randL = (rand()%3) +3 ;
				randC = ((rand()/100)%3) + 6 ;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum);
			}//for 6
			break;
		case '7':
		//table 7
			for(int i=0;i<1000;i++)
			{//for 7
				randL = (rand()%3) + 6 ;
				randC = ((rand()/100)%3)  ;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum) ;
			}//for 7
			break;
		case '8':
		//table 8
			for(int i=0;i<1000;i++)
			{//for 8
				randL = (rand()%3) + 6 ;
				randC = ((rand()/100)%3) +3  ;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum) ;
			}//for 8
			break;
		case '9':		
		//table 9
			for(int i=0;i<1000;i++)
			{//for 9
				randL = (rand()%3) + 6 ;
				randC = ((rand()/100)%3) +6  ;
				randNum = rand()%9 + 49;
				setNumber(table,randL,randC,randNum) ;
			}//for 9
			break;
	}//switch

	if(fullTable(table))//end function
		return;
	if(fullSmallTable(table,tableNum))//if table full goto next table
	{
		do
			tableNum++;
		while(fullSmallTable(table,tableNum));//if next table full goto next and ... 

		complate(table , tableNum);//Recursive
	}
	else//if dont full small table 
	{
		emptySmallTable(table,tableNum);//this table is empty
		
		//table back is empty
		if(backL != '0')//line 
		{
			emptySmallTable(table,backL);
			complate(table,backL);//Recursive
		}
		else if(backC != '0')//cloumn
		{
			emptySmallTable(table,backC);
			complate(table,backC);//Recursive
		}
		else//small table
		{
			emptySmallTable(table,backT);
			complate(table,backT);//Recursive
		}
	}
	return; 
}
//end complate

//define statuse
void status (char table[][9][3])
{
	system("color F0");
	
	char sta;//status
	int mark=0;//dgree for loop
	int randL,randC;//rand line and cloumn

	system("cls");
	cout<<"\n\n\n\n          Please enter statuse game :\n          1.*\n          2.**\n          3.***\n          4.****\n          ";
	cin>>sta;

	switch(sta)
	{
	case '1'://*
		mark=50;
		break;
	case '2'://**
		mark=60;
		break;
	case '3'://***
		mark=70;
		break;
	case '4'://****
		mark=80;
		break;
	default://must enter 1 to 4
		system("color C");
		cout<<"\n         ERORR:my dear user please enter number 1 to 4\n               OK!!!!!\n         ";
		system("pause");
		status(table);
		break;
	}
	
	complate(table , '1');//complate 

	srand(time(NULL)*100000);

	for(int i=0 ; i<mark ; i++)//clear rand number
	{
		randL = (rand()%9)  ;
		randC = (((rand()/100))%9)  ;

		if(table[randL][randC][1] % 2 == 0)
			table[randL][randC][0] = (char)0xB2;
		else
			table[randL][randC][0] = (char)0xB0;
	}

	//number of separate user program number
	for(int i=0; i<9; i++)
		for(int j=0; j<9;j++)
			if(table[i][j][0] != (char)0xB0 && table[i][j][0] != (char)0xB2)
				table[i][j][2] = 'X';

	system("pause");
}
//end statuse

//define print
void print(char table[][9][3])
{
	//mark cloumn 
	cout<<"\n\n\n\n           1   2   3   4   5   6   7   8   9"
		<<"\n         \x00C9";

	//up line table
	for(int i=0;i<2;i++)
		cout<<"\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CB";
	cout<<"\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00BB";

	//table
		for(int i=0;i<9;i++)
		{//for 1
			cout<<"\n        "<<i+1<<"\x00BA ";// num line ||

			for(int j=0; j<9; j++)  
			{//for 2
				if(j==8 || (j+1)%3==0)
					cout<<table[i][j][0]<<" \x00BA ";//num table ||
				else
					cout<<table[i][j][0]<<" \x00B3 ";//num table |
			}//for 2
	
			//under line array
			switch(i)
			{//switch
			//Separation Table
			case 2:
			case 5:
				cout<<"\n         \x00CC";//angle 2
				for(int i=0;i<2;i++)
					cout<<"\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CE";
			cout<<"\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00B9";
				
			break;

			//end line
			case 8:
				cout<<"\n         \x00C8";//angle 3
				for(int i=0;i<2;i++)
					cout<<"\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CA";
				cout<<"\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00CD\x00BC";
				break;

			//under line 
			default:
				cout<<"\n         \x00BA";//angle 1
				for(int i=0;i<9;i++)
				{//for 3
					if(i==8 || (i+1)%3==0 )
						cout<<"\x00c4\x00c4\x00c4\x00BA";
					else
						cout<<"\x00c4\x00c4\x00c4\x00C5";
				}//for 3

			}//switch
	}//for1
}