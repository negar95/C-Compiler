#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<string>
FILE *fptr,*eptr;
int attribute;
int token;
int s,idcounter,line=1,tedad,kooft;
int current_state,state[3][30][20];
char *x,*cast;
int braceCounter=0;
void word(void);
void wmain(void);
void wchar(void);
void wbool(void);
void wvoid(void);
void wnull(void);
void wtrue(void);
void wint(void);
void wmax(void);
void wfloat(void);
void wif(void);
void woperator(void);
void numbers(void);
void identifier(void);
void gettoken(void);
void error(void);
void errorID(void);
void errorNUM(void);
void errorCH(int a);
void read (void);
void read1(void);
void getAssemblyCode(void);
void setSymbolTable(void);
void geterror(void);
void setcast(void);
void upto(void);
void spaceblock(void);

struct id
{
	int index;
	char *name;
	char *type;
	int value;
	struct id *next;
}first,*current;
void word(void)
{
if(*x==' '||*x=='\n'||*x==NULL)
	return;
else if(*x==39)//'
	{
		if(s!=3)
			errorCH(1);
		
		else if(*(x+s-1)!=39)
			errorCH(2);
		token=1;
		attribute=16;
	}
else if(*x=='"')
	{
		if(s<=2)
			errorCH(1);
		else if(*(x+s-1)!='"')
		attribute=15;
		token=1;
	}
	

else if(s==4)
	{
	switch(*x)
	{
	case 'm':
		wmain();
		break;
	case 'c':
		wchar();
		break;
	case 'b':
		wbool();
		break;
	case 'v':
		wvoid();
		break;
	case 'n':
		wnull();
		break;
	case 't':
		wtrue();
		break;
	default:
		identifier();
	}
	}//end of s=4

else if(s==3)
	{
		switch(*x)
		{
		case 'm':
			wmax();
			break;
		case 'i':
			wint();
			break;
		default:
			identifier();

		}
	}//end of s=3
else if(s==5)
	{
	if(*x=='f')
		wfloat();
	else
		identifier();
	}//end of s=5
else if(s==2)
	{
	if(*x=='i')
		wif();
	else if((*x>'A'&&*x<'Z')||(*x>'a'&&*x<'z'))//alphabet
		identifier();
	else if(*x>'0'&&*x<'9')//number
		numbers();
	else if(*x=='-')//negative num
		numbers();
	else
		woperator();
	}//end of s=2
else if(s==1)
	{
	if((*x>='A'&&*x<='Z')||(*x>='a'&&*x<='z'))
		identifier();
	else if(*x>='0'&&*x<='9')
		numbers();
	else
		woperator();
	}//end of(s=1
else
	identifier();
}
void wmain(void)
{
	const char *wm="main";
	if(!strcmp(x,wm))
	{
	attribute=0;
	token=0;
	}
	else
		identifier();
}//token=0
void wchar(void)
{
	const char *wm="char";

	if(!strcmp(x,wm))
	{
		attribute=4;
		token=0;
	}
	else
		identifier();
}
void wbool(void)
{
	const char *wm="bool";
	if(!strcmp(x,wm))
	{
	attribute=5;
	token=0;
	}
	else
		identifier();
}
void wvoid(void)
{
	const char *wm="void";
	if(!strcmp(x,wm))
	{
	attribute=8;
	token=0;
	}
	else
		identifier();
}
void wnull(void)
{
	const char *wm="NULL";
	if(!strcmp(x,wm))
	{
	attribute=9;
	token=0;
	}
	else
		identifier();
}
void wtrue(void)
{
	const char *wm="TRUE";
	if(!strcmp(x,wm))
	{
	attribute=10;
	token=0;
	}
	else
		identifier();
}
void wint(void)
{
	const char *wm="int";
	
	if(!strcmp(x,wm))
	{
	attribute=2;
	token=0;
	}
	else
		identifier();
}
void wmax(void)
{ 
	const char *wm="max";
	const char *wm1="min";
	
	if(!strcmp(x,wm))
	{
	attribute=6;
	token=0;
	}
	else if(!strcmp(x,wm1))
	{
	attribute=7;
	token=0;
	}
	else
		identifier();
	}
void wfloat(void)
{
	const char *wm="float";
	const char *wm1="FALSE";
	if(!strcmp(x,wm))
	{
	attribute=3;
	token=0;
	}
	else if(!strcmp(x,wm1))
	{
	attribute=11;
	token=0;
	}
	else
		identifier();
	}
void wif(void)
{
	const char *wm="if";
	
	if(!strcmp(x,wm))
	{
	attribute=1;
	token=0;
	}
	else
		identifier();
}

void woperator(void)
{
	if(s==1)
	{
		switch(*x)
		{
			case '!':
				attribute=0;
				token=1;
				break;
			case '=':
				attribute=1;
				token=1;
				break;
			case '>':
				attribute=2;
				token=1;
				break;
			case '<':
				attribute=3;
				token=1;
				break;
			case '|':
				attribute=4;
				token=1;
				break;
			case '&':
				attribute=5;
				token=1;
				break;
			case '+':
				attribute=6;
				token=1;
				break;
			case '-':
				attribute=7;
				token=1;
				break;
			case '*':
				attribute=8;
				token=1;
				break;
			case '/':
				attribute=9;
				token=1;
				break;
			case '(':
				attribute=10;
				token=1;
				break;
			case ')':
				attribute=11;
				token=1;
				break;
			case '{':
				attribute=12;
				token=1;
				break;
			case '}':
				attribute=13;
				token=1;
				break;
			case ';':
				attribute=14;
				token=1;
				break;
			case ',':
				attribute=17;
				token=1;
				break;
			default:
				identifier();
		}
	}
	else if(s==2)
	{
		switch(*x)
		{
				
			case '!':
				if(*(x+1)=='=')
				{
				attribute=18;
				token=1;
				}
				else identifier();
		
				break;
			case '=':
				if(*(x+1)=='=')
				{
				attribute=19;
				token=1;
				}
				else identifier();
				break;
			case '>':
				if(*(x+1)=='=')
				{
				attribute=20;
				token=1;
				}
				else identifier();
				break;
			case '<':
				if(*(x+1)=='=')
				{
				attribute=21;
				token=1;
				}
				else identifier();
				break;
			case '|':
				if(*(x+1)=='=')
				{
				attribute=22;
				token=1;
				}
				else if(*(x+1)=='|')
				{
					attribute=29;
					token=1;
				}
				else identifier();
				break;
		case '&':
			if(*(x+1)=='=')
			{
			attribute=23;
			token=1;
			}
			else if(*(x+1)=='&')
			{
			attribute=28;
			token=1;
			}
			else identifier();
			break;
		case '+':
			if(*(x+1)=='=')
			{
			attribute=24;
			token=1;
			}
			else identifier();
			break;
		case '-':
			if(*(x+1)=='=')
			{
			attribute=25;
			token=1;
			}
			else identifier();
			break;
		case '*':
			if(*(x+1)=='=')
			{
			attribute=26;
			token=1;
			}
			else identifier();
			break;
		case '/':
			if(*(x+1)=='=')
			{
			attribute=27;
			token=1;
			}
			else identifier();
			break;
		default:
			identifier();
			}
	}
} 
void numbers(void)
{
	int k=0;
	while(*(x+k)<='9'&&*(x+k)>='0')
		k++;
	if(*(x+k)!='.'&&k!=s)
		errorNUM();
	else if(k!=s)
	{
		k++;
	while(*(x+k)<='9'&&*(x+k)>='0')
		k++;
	}
	if(k==s)
		tedad++;
		
	else errorNUM();
	attribute=tedad;
	token=2;
}
void identifier(void)//token=3
{
	int k=0;
	while((*(x+k)<='z'&&*(x+k)>='a')||(*(x+k)<='Z'&&*(x+k)>='A'))//{a,b,...}||{A,B,...}
		k++;
	if(k!=0)
	{
		while(*(x+k)>='0'&&*(x+k)<='9')
			k++;
		if(k!=s)//checking last char..
			errorID();
		token=3;
		idcounter++;
		attribute=idcounter;
	}
	else if((*(x)>48&&*(x)<58)||*x=='-')
		numbers();
	else
	{
		token=3;
		idcounter++;
		attribute=idcounter;
		errorID(); 
	}
}

void gettoken(void)
{
	state[token][attribute][0]=-1;
	state[token][attribute][1]=-1;
	state[token][attribute][2]=-4;
	state[token][attribute][3]=-9;//required ')'
	state[token][attribute][4]=-10;//required '{'
	state[token][attribute][2]=-1;
	state[token][attribute][5]=-2;//required id,if,variable definitions
	state[token][attribute][6]=-4;//required:'('
	state[token][attribute][7]=-5;//wrong if expression:
	state[token][attribute][8]=-5;//
	state[token][attribute][9]=-5;//
	state[token][attribute][10]=-3;//required id
	state[token][attribute][11]=-7;//expected a ';'
	state[token][attribute][12]=-3;
	state[token][attribute][13]=-6;
	state[token][attribute][14]=-7;
	state[token][attribute][15]=-3;
	state[token][attribute][16]=-8;//missed ';'
	state[token][attribute][17]=-4;
	state[token][attribute][18]=-3;
	state[token][attribute][19]=-9;
	

	state[0][8][0]=1;
	state[0][0][1]=2;
	state[0][1][5]=6;
	state[0][2][5]=10;
	state[0][3][5]=10;
	state[0][4][5]=10;
	state[0][5][5]=10;
	state[0][6][9]=17;
	state[0][7][9]=17;
	state[0][10][9]=3;
	state[0][11][9]=3;
	state[0][6][12]=17;
	state[0][7][12]=17;
	state[0][10][12]=14;
	state[0][11][12]=14;
	state[0][10][15]=16;
	state[0][11][15]=16;

	state[2][attribute][7]=8;
	state[2][attribute][9]=3;
	state[2][attribute][12]=14;
	state[2][attribute][15]=16;
	state[2][attribute][18]=19;

	state[3][attribute][5]=13;
	state[3][attribute][7]=8;
	state[3][attribute][9]=3;
	state[3][attribute][10]=11;
	state[3][attribute][12]=14;
	state[3][attribute][15]=16;
	state[3][attribute][18]=19;

	state[1][10][2]=3;
	state[1][11][3]=4;
	state[1][12][4]=5;
	state[1][13][5]=5;
	state[1][12][5]=5;
	state[1][10][6]=7;
	state[1][2][8]=9;
	state[1][3][8]=9;
	state[1][20][8]=9;
	state[1][21][8]=9;
	state[1][4][8]=9;
	state[1][5][8]=9;
	state[1][18][8]=9;
	state[1][19][8]=9;
	state[1][28][8]=9;
	state[1][29][8]=9;
	state[1][1][11]=12;
	state[1][14][11]=5;
	state[1][17][11]=10;
	state[1][15][12]=11;
	state[1][16][12]=11;
	state[1][1][13]=12;
	state[1][24][13]=15;
	state[1][25][13]=15;
	state[1][26][13]=15;
	state[1][27][13]=15;
	state[1][6][14]=12;
	state[1][7][14]=12;
	state[1][8][14]=12;
	state[1][9][14]=12;
	state[1][14][14]=5;
	state[1][17][14]=10;
	state[1][14][16]=5;
	state[1][10][17]=18;
	state[1][11][19]=14;
	state[1][17][19]=18;
}

void setcast(void)
{
	static int indexincreaser=-1;
	kooft=0;
	if(current_state==10)
	{
		if(token==0)
		{
			cast=(char*)malloc(sizeof(char));
			strcpy(cast,x);
		}
		spaceblock();
		read1();
		if(current_state>0&&kooft==0)
		{
			current=&first;
			while(current->next!=NULL&&strcmp(current->name,x)!=0)
				current=current->next;
			if(current->next==NULL&&strcmp(current->name,x)!=0)
			{
				indexincreaser++;
				
				current->next =(struct id *)malloc(sizeof(struct id));
				current=current->next;
				current->index = indexincreaser;
				current->name=(char*)malloc(sizeof (char));
				current->type =(char*)malloc(sizeof (char));
				strcpy(current->name,x);
				strcpy(current->type,cast);
				current->next=NULL;
			}
			else if(strcmp(current->name,x)==0)
			{
				fprintf(eptr,"line %d error:'%s' : redefinition, different basic types",line,x);
				while(current->next!=NULL)
					current=current->next;
			}
		}
		spaceblock();
	}
}
void error(void)
{
	if(current_state>=0)
		return;
	else if(current_state==-1)
		fprintf(eptr,"line %d error:begin expression is not valid\n",line);
	else if(current_state==-2)
		fprintf(eptr,"line %d error:required:id,if,variable definitions,'{'  found:%s\n",line,x);
	else if(current_state==-3)
		fprintf(eptr,"line %d error:required:id found:%s\n",line,x);
	else if(current_state==-4)
		fprintf(eptr,"line %d error:required:'('  found:%s\n",line,x);
	else if(current_state==-5)
		fprintf(eptr,"line %d error:if condition is not valid\n",line);
	else if(current_state==-6)
		fprintf(eptr,"line %d error:expexted an expression\n",line);
	else if(current_state==-7)
		fprintf(eptr,"line %d error:expected a ';' before '%s'\n",line,x);
	else if(current_state==-8)
		fprintf(eptr,"line %d error:missing ';'\n",line);
	else if(current_state==-9)
		fprintf(eptr,"line %d error:erquired:')'  found:%s\n",line,x);
	else if(current_state==-10)
		fprintf(eptr,"line %d error:required:'{'  before '%s'\n",line,x);

}
void errorID(void)
{
	fprintf(eptr,"line %d error:expected:identifier,identifier is not valid\n",line);
	kooft=-1;
}
void errorNUM(void)
{
	fprintf(eptr,"line %d error:ecpected:number, the number is not valid!\n",line);
	kooft=-1;
}
void errorCH(int a)
{
	if (a==1)
		fprintf(eptr,"line %d error:expected:char, invalid number of characters in constant\n",line);
	else if (a==2)
		fprintf(eptr,"line %d error:expected:' or \" , missing ' or \" \n",line);
	kooft=-1;
}
void upto(void)
{
static int counter1=0;
if(current_state<0)
	{
	if(current_state==-5)
	{
		while(*x!='{' && !feof(fptr) && *x!='}')
		{
			*x=fgetc(fptr);
			if(*x=='\n')
				line++;
		}
		if(*x=='{')
			counter1++;
		if(*x=='}')
			counter1--;
		while(counter1>0 && !feof(fptr))
		{
			*x = fgetc(fptr);
			if( *x=='{' )
				counter1++;
			if( *x == '}' )
				counter1--;
			if(*x=='\n')
				line++;
		}
		current_state = 5;
	}

else if(current_state==-7)
	{
		if(*(x+s)=='\n')
			line--;
		fseek(fptr,0-s-1,SEEK_CUR);
		
		current_state=5;
	}
else
	{
		if(*x==';')
			current_state=5;
		while(*x!=';'&&*x!='}'&&!feof(fptr) )
		{
			
			*x = fgetc(fptr);
			if(*x=='\n')
				line++;
			current_state = 5;
		}
	}
	}
}

void read(void)
{
	*x=fgetc(fptr);
	s=0;
	while(*x!=' '&&*x!='\n'&&!feof(fptr))
	{
		x++;
		s++;
		*x=fgetc(fptr);
		if(*x=='\n')
			fseek(fptr,-1,SEEK_CUR);
	}
	*x=NULL;
	x-=s;
	word();
	gettoken();	
	
	
	if(token==1&&attribute==12)
		braceCounter++;
	else if(token==1&&attribute==13)
		braceCounter--;

	/*if(current_state==12)
			{
				if(token==3&&attribute>0)
				{
					current=&first;
					while(current->next!=NULL)
					{
						if(current->next->name==attribute)
							idv*=(current->next->value);
						current=current->next;
					}
				}
				else if (token==2)
					idv*=0;
			}*/
	
	
	current_state=state[token][attribute][current_state];
	setcast();
	error();
	upto();

	
	if(!feof(fptr))
	{
		*x=fgetc(fptr);
		while(*x==' '||*x=='\n')
		{
			if(*x=='\n')
				line++;
			if(!feof(fptr))
				*x=fgetc(fptr);			
		}
			
		fseek(fptr,-1,SEEK_CUR);
	}
}
void read1(void)
{
	*x=fgetc(fptr);
	s=0;
	while(*x!=' '&&*x!='\n'&&!feof(fptr))
	{
		x++;
		s++;
		*x=fgetc(fptr);
		if(*x=='\n')
			fseek(fptr,-1,SEEK_CUR);
	}
	*x=NULL;
	x-=s;
	word();
	gettoken();
	
	current_state=state[token][attribute][current_state];
	//upto();
	//setcast();
	
}
void spaceblock(void)
{
	if(!feof(fptr))
		{
			*x=fgetc(fptr);
			while(*x==' '||*x=='\n')
			{
				if(*x=='\n')
					line++;
				if(!feof(fptr))
					*x=fgetc(fptr);			
			}
			
			fseek(fptr,-1,SEEK_CUR);
		}
}

void geterror(void)
{
	if((eptr=fopen("error.txt","w"))==NULL)
		printf("file could not be found\n");
	else
	{
		if((fptr=fopen("new.txt","r"))==NULL)
			printf("file could not be found\n");
		else
			while(!feof(fptr))
				read();
	}
}

void getAssemblyCode(void)
{
	int asstoken1=0,asstoken2=0,assline=0,asssigntoken=0,asslineif=0,s1;
	int assindex,assindex1,assindex2;
	char *assid,*assid1,*assid2,*asssign;
	line=1;
	kooft=0;
	current_state=0;

	FILE *assptr;
	assptr=fopen("Assembly Code.txt","w+");
	fseek(fptr,0,SEEK_SET);
	
	while(!feof(fptr))
	{
		*x=fgetc(fptr);
		s=0;
		while(*x!=' '&&*x!='\n'&&!feof(fptr))
		{
			x++;
			s++;
			*x=fgetc(fptr);
		}
		*x=NULL;
		x-=s;
		word();
		gettoken();
		if(current_state==10&&token==3)
		{
			assid=(char*)malloc(sizeof(char));
			strcpy(assid,x);
			while(current->next!=NULL && strcmp(assid1,current->name)!=0)
				current=current->next;
			assindex=current->index;
			while(current->next!=NULL)
				current=current->next;
		}//save 'a' in int a

		current_state=state[token][attribute][current_state];
		//spaceblock();
		if(current_state==12)
		{
			while(*x!=';')
				read1();
			if(current_state>0 && kooft!=-1 )
			{
				while(*x!='=')
				{
					fseek(fptr,-2,SEEK_CUR);
					*x=fgetc(fptr);
					if(*x=='\n')
					line--;
				}
				current_state=12;
				//seen '='
				spaceblock();
				//assid1 handle
				read1();
				asstoken1=token;
				assid1=(char*)malloc(sizeof(char));
				strcpy(assid1,x);
				getch();
				read1();
				asssign=(char*)malloc(sizeof(char));
				strcpy(asssign,x);
				if(current_state==12)//for detecting operator
				{
					//assid2 handle
					read1();
					asstoken2=token;
					assid2=(char*)malloc(sizeof(char));
					strcpy(assid2,x);
					//assindex1 handle
					current=&first;
					if((*assid1<='z'&&*assid1>='a')||(*assid1<='Z'&&*assid1>='A'))
					{
						while(current->next!=NULL&&strcmp(assid1,current->name)!=0)
							current=current->next;
						assindex1=current->index;
					}
					//assindex2 handle
					current=&first;
					if((*assid2<='z'&&*assid2>='a')||(*assid2<='Z'&&*assid2>='A'))
					{
						while(current->next!=NULL&&strcmp(assid2,current->name)!=0)
							current=current->next;
						assindex2=current->index;
						while(current->next!=NULL)
							current=current->next;
					}
					switch (*asssign)
					{
					case'+':
						if(asstoken1==2)
						{
							if(asstoken2==2)
							{
								fprintf(assptr,"move $t(%d),%s\naddi $t(%d),%s\n",assindex,assid1,assindex,assid2);	
								assline+=2;
							}
							else if(asstoken2==3)
							{
								fprintf(assptr,"move $t(%d),%s\nadd $t(%d),$t(%d),$t(%d)\n",assindex,assid1,assindex,assindex,assindex2);
								assline+=2;
							}
						}
						else if(asstoken1==3)
						{
							if(asstoken2==2)
							{
								fprintf(assptr,"move $t(%d),%s\nadd $t(%d),$t(%d),$t(%d)\n",assindex,assid2,assindex,assindex,assindex1);
								assline+=2;
							}
							else if(asstoken2==3)
							{
								fprintf(assptr,"add $t(%d),$t(%d),$t(%d)\n",assindex,assindex1,assindex2);
								assline++;
							}
						}
						break;
				//___________________________________________________________________________________________________________________________
					case'-':
						if(asstoken1==2)
						{
							if(asstoken2==2)
								fprintf(assptr,"move $a0,%s\nmove $t(%d),%s\nsub $t(%d),$a0,$t(%d)",assid1,assindex,assid2,assindex,assindex);
							else if(asstoken2==3)
								fprintf(assptr,"move $t(%d),%s\nsub $t(%d),$t(%d),$t(%d)",assindex,assid1,assindex,assindex,assindex2);
						}
						else if(asstoken1==3)
						{
							if(asstoken2==2)
								fprintf(assptr,"move $t(%d),$t(%d)\nsubi $t(%d),%s",assindex,assindex1,assindex,assid2);
							else if(asstoken2==3)
								fprintf(assptr,"sub $t(%d),$t(%d),$t(%d)",assindex,assindex1,assindex2);
						}
						break;
				//___________________________________________________________________________________________________________________________
					case'*':
						if(asstoken1==2)
						{
							if(asstoken2==2)
								fprintf(assptr,"move $a0,%s\nmove $t(%d),%s\nmult $t(%d),$a0,$t(%d)",assid1,assindex,assid2,assindex,assindex);
							else if(asstoken2==3)
								fprintf(assptr,"move $a0,%s\nmove $t(%d),$t(%d)\nmult $t(%d),$a0,$t(%d)",assid1,assindex,assindex2,assindex,assindex);
						}
						else if(asstoken1==3)
						{
							if(asstoken2==2)
								fprintf(assptr,"move $a0,%s\nmove $t(%d),$t(%d)\nmult $t(%d),$a0,$t(%d)",assid2,assindex,assindex1,assindex,assindex);
							else if( asstoken2 ==3)
								fprintf(assptr,"mult $t(%d),$t(%d),$t(%d)",assindex,assindex1,assindex2);
						}
						break;
				//___________________________________________________________________________________________________________________________
					case'/':
						if(asstoken1==2)
						{
							if(asstoken2==2)
								fprintf(assptr,"move $a0,%s\nmove $t(%d),%s\ndiv $t(%d),$a0,$t(%d)",assid1,assindex,assid2,assindex,assindex);
							else if(asstoken2==3)
								fprintf(assptr,"move $a0,%s\ndiv $t(%d),$a0,$t(%d)",assid1,assindex,assindex2);
						}
						else if(asstoken1==3)
						{
							if(asstoken2==2)
								fprintf(assptr,"move $a0,%s\ndiv $t(%d),$t(%d),$a0",assid2,assindex,assindex1);
							else if(asstoken2==3)
								fprintf(assptr,"div $t(%d),$t(%d),$t(%d)",assindex,assindex1,assindex2);
						}
						break;
					
					}	
				}
				else if(strcmp(asssign,";")==0)
				{
					if((*assid1<='z'&&*assid1>='a')||(*assid1<='Z'&&*assid1>='A'))
					{
						current=&first;
						while(current->next!=NULL&&strcmp(assid1,current->name)!=0)
							current=current->next;
						assindex1=current->index;
					}
					if(asstoken1==2||asstoken1==1)
					{
						fprintf(assptr,"move $t(%d),%s\n",assindex,assid1);
						assline++;
					}
					else if(asstoken1==3)
					{
						fprintf(assptr,"move $t(%d),$t(%d)\n",assindex,assindex1);
						assline++;
					}
					else if(asstoken1==0)
					{
						if(strcmp(assid1,"TRUE")==0)
						{
							fprintf(assptr,"move $t(%d), 1\n",assindex);
							assline++;
						}
						else if(strcmp(assid1,"FALSE")==0)
						{
							fprintf(assptr,"move $t(%d), 0\n",assindex);
							assline++;
						}
					}
					
				}
				else if(strcmp(asssign,"(")==0)
				{
					if(strcmp(assid1,"max"))
					{
						read1();
						asstoken1=token;
						assid1=(char*)malloc(sizeof(char));
						strcpy(assid1,x);
						read1(); //read ','
						read1();
						asstoken2=token;
						assid2=(char*)malloc(sizeof(char));
						strcpy(assid2,x);
						//assindex1 handle
						current=&first;
						if((*assid1<='z'&&*assid1>='a')||(*assid1<='Z'&&*assid1>='A'))
						{
							while(current->next!=NULL&&strcmp(assid1,current->name)!=0)
								current=current->next;
							assindex1=current->index;
						}
						//assindex2 handle
						current=&first;
						if((*assid2<='z'&&*assid2>='a')||(*assid2<='Z'&&*assid2>='A'))
						{
							while(current->next!=NULL&&strcmp(assid2,current->name)!=0)
								current=current->next;
							assindex2=current->index;
							while(current->next!=NULL)
								current=current->next;
						}
						if(asstoken1==2)
						{
							if(asstoken2==2)
							{
								fprintf(assptr,"move $a0, %s\nmove $a1,%s\nsub $a2, $a0, $a1\nbltz $a0, %d+3\nmove $t(%d), $a0\nj %d+2\nmove $t(%d), $a1\n",assid1,assid2,assline,assindex,assline+3,assindex);
								assline+=7;
							}
							else if(asstoken2==3)
							{
								fprintf(assptr,"move $a0, %s\nsub $a2, $a0, $t(%d)\nbltz $a2, %d+3\nmove $t(%d), $a0\nj %d+2\nmove $t(%d), $t(%d)\n",assid1,assindex2,assline,assindex,assline+3,assindex,assindex2);
								assline+=6;
							}
						}
						else if(asstoken1==3)
						{
							if(asstoken2==2)
							{
								fprintf(assptr,"move $a0, %s\nsub $a2, $a0, $t(%d)\nbltz $a2, %d+3\nmove $t(%d), $a0\nj %d+2\nmove $t(%d),$t(%d)\n",assid2,assindex1,assline,assindex,assline+3,assindex,assindex1);
								assline+=6;
							}
							else if(asstoken2==3)
							{
								fprintf(assptr,"move $a0, 4\nsub $a2, $t(%d), $t(%d)\nbltz $a2, %d+3\nmove $t(%d), $t(%d)\nj %d+2\nmove $t(%d), $t(%d)\n",assindex2,assindex1,assline,assindex,assindex2,assline+3,assindex,assindex1);
								assline+=6;
							}
						}
					}//end of max
					else if(strcmp(assid1,"min"))
					{
						read();
						asstoken1=token;
						assid1=(char*)malloc(sizeof(char));
						strcpy(assid1,x);
						read();//read ','
						read();
						asstoken2=token;
						assid2=(char*)malloc(sizeof(char));
						strcpy(assid2,x);//assindex1 handle
						current=&first;
							while(current->next!=NULL&&strcmp(assid1,current->name)!=0)
								current=current->next;
							assindex1=current->index;
						//assindex2 handle
						current=&first;
							while(current->next!=NULL&&strcmp(assid2,current->name)!=0)
								current=current->next;
							assindex2=current->index;
							while(current->next!=NULL)
								current=current->next;
						if(asstoken1==2)
						{
							if(asstoken2==2)
							{
								fprintf(assptr,"move $a0, %s\nmove $a1,%s\nsub $a2, $a0, $a1\nbltz $a2, %d+3\nmove $t(%d), $a1\nj %d+2\nmove $t(%d), $a0\n",assid1,assid2,assline,assindex,assline+3,assindex);
								assline+=7;
							}
							else if(asstoken2==3)
							{
								fprintf(assptr,"move $a0, %s\nsub $a2, $a0, $t(%d)\nbltz $a2, %d+3\nmove $t(%d), $t(%d)\nj %d+2\nmove $t(%d), $a0\n",assid1,assindex2,assline,assindex,assindex2,assline+3,assindex);
								assline+=6;
							}
						}
						else if(asstoken1==3)
						{
							if(asstoken2==2)
							{
								fprintf(assptr,"move $a0, %s\nsub $a2, $a0, $t(%d)\nbltz $a2, %d+3\nmove $t(%d), $t(%d)\nj %d+2\nmove $t(%d),$a0\n",assid2,assindex1,assline,assindex,assindex1,assline+3,assindex);
								assline+=6;
							}
							else if(asstoken2==3)
							{
								fprintf(assptr,"move $a0, 4\nsub $a2, $t(%d), $t(%d)\nbltz $a2, %d+3\nmove $t(%d), $t(%d)\nj %d+2\nmove $t(%d), $t(%d)\n",assindex2,assindex1,assline,assindex,assindex1,assline+3,assindex,assindex2);
								assline+=6;
							}
						}
					}//end of min
				}//end of max&min
			}
		}//int x=2+a;
		else if(current_state==6)
		{
			spaceblock();
			read1();
			if(current_state>0&&kooft!=-1)//'(' seen
			{
				spaceblock();
				read1();
				if(current_state>0&&kooft!=-1)
				{
					asstoken1=token;
					assid1=(char*)malloc(sizeof(char));
					strcpy(assid1,x);
					spaceblock();
					read1();
					if(current_state>0&&kooft!=-1)
					{
						asssigntoken=attribute;
						spaceblock();
						read1();
						if(current_state>0&&kooft!=-1)
						{
							asstoken2=token;
							assid2=(char*)malloc(sizeof(char));
							strcpy(assid2,x);
							current=&first;
							//assindex1 handle
								while(current->next!=NULL&&strcmp(assid1,current->name)!=0)
									current=current->next;
								assindex1=current->index;
							//assindex2 handle
							current=&first;
								while(current->next!=NULL&&strcmp(assid2,current->name)!=0)
									current=current->next;
								assindex2=current->index;
								while(current->next!=NULL)
									current=current->next;
								spaceblock();
							read1();
							if(current_state>0&&kooft!=-1)
							{
								spaceblock();
								read1();
								if(current_state>0&&kooft!=-1)
								{
									switch(asssigntoken)
									{
									case 19://'=='
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"bne $t(%d),$t(%d), %c+1\n",assindex1,assindex2,200);
												assline++;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"bne $t(%d), %s, %c+1\n",assindex1,assid2,200);
												assline++;
											}
										}
										else if(asstoken1==2)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"bne %s,$t(%d), %c+1\n",assid1,assindex2,200);
												assline++;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"bne %s,%s,%c+1\n",assid1,assid2,200);
												assline++;
											}
										}
										break;
									case 18://'!='
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"beq $t(%d),$t(%d), %c+1\n",assindex1,assindex2,200);
												assline++;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"beq $t(%d), %s, %c+1\n",assindex1,assid2,200);
												assline++;
											}
										}
										else if(asstoken1==2)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"beq %s,$t(%d), %c+1\n",assid1,assindex2,200);
												assline++;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"beq %s,%s,%c+1\n",assid1,assid2,200);
												assline++;
											}
										}
										break;
									case 20://'>='
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"sub $a0, $t(%d), $t(%d)\nbltz $a0, %c+1\n",assindex1,assindex2,200);
												assline+=2;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a0, %s\nsub $a1, $t(%d), $a0\nbltz $a1, %c+1\n",assid2,assindex1,200);
												assline+=3;
											}
										}
										break;
									case 2://'>'
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"sub $a0, $t(%d), $t(%d)\nblez $a0, %c+1\n",assindex1,assindex2,200);
												assline+=2;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a0, %s\nsub $a1, $t(%d), $a0\nblez $a1, %c+1\n",assid2,assindex1,200);
												assline+=3;
											}
										}
										break;
									case 21://'<='
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"sub $a0, $t(%d), $t(%d)\nbltz $a0, %c+1\n",assindex2,assindex1,200);
												assline+=2;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a0, %s\nsub $a1, $a0, $t(%d)\nbltz $a1, %c+1\n",assid2,assindex1,200);
												assline+=3;
											}
										}
										break;
									case 3://'<'
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"sub $a0, $t(%d), $t(%d)\nblez $a0, %c+1\n",assindex2,assindex1,200);
												assline+=2;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a0, %s\nsub $a1, $a0, $t(%d)\nblez $a1, %c+1\n",assid2,assindex1,200);
												assline+=3;
											}
										}
										break;
									case 28://'&&'
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"and $a0, $t(%d), $t(%d)\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assindex1,assindex2,200);
												assline+=3;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a2, %s\nand $a0, $t(%d), $a2\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assid2,assindex1,200);
												assline+=4;
											}
										}
										break;
									case 5://'&'
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"and $a0, $t(%d), $t(%d)\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assindex1,assindex2,200);
												assline+=3;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a2, %s\nand $a0, $t(%d), $a2\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assid2,assindex1,200);
												assline+=4;
											}
										}
										break;
									case 29://'||'
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"or $a0, $t(%d), $t(%d)\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assindex1,assindex2,200);
												assline+=3;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a2, %s\nor $a0, $t(%d), $a2\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assid2,assindex1,200);
												assline+=4;
											}
										}
										break;
									case 4://'|'
										if(asstoken1==3)
										{
											if(asstoken2==3)
											{
												fprintf(assptr,"or $a0, $t(%d), $t(%d)\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assindex1,assindex2,200);
												assline+=3;
											}
											else if(asstoken2==2)
											{
												fprintf(assptr,"move $a2, %s\nor $a0, $t(%d), $a2\nmove $a1, 0\nbeq $a0, $a1, %c+1\n",assid2,assindex1,200);
												assline+=4;
											}
										}
										break;
									}
								}
							}//after ')' con
						}//after id2 con
					}//after sign con
				}//after id1 con
			}//after '(' con
		}//end of if condition
		upto();
		spaceblock();
	}
}

void setSymbolTable(void)
{
	FILE *stptr;
	stptr=fopen("symbol table.txt","w");
	current=first.next->next;
	fprintf(stptr,"index\tname\ttype\tvalue\n\n");
	while(current->next != NULL)
	{
		fprintf(stptr,"%d\t%s\t%s\tvalue\n",current->index,current->name ,current->type );
		current=current->next ;
	}
	fprintf(stptr,"%d\t%s\t%s\tvalue\n",current->index,current->name ,current->type );

}

int main()
{
	braceCounter=0;
	current=&first;
	current->next =(struct id *)malloc(sizeof(struct id));
	first.next=current->next;
	first.next->name=" ";
	first.name=" ";
	current->next->next=NULL;
	x=(char*)malloc(sizeof(char));
	geterror();
	setSymbolTable();
	getAssemblyCode();
	if(braceCounter<3)
		fprintf(eptr,"missing '}'");
}