#include <cstdio>
#include <cstring>
#include <vector>
int const NN=4096;
using namespace std;
typedef union
{long code;
 struct
 {unsigned int Pos   :2;
  unsigned int Count :2;
  unsigned int Symb  :2;
  unsigned int Bit0  :2;
  unsigned int Bit1  :2;
  unsigned int Bit2  :2;
  unsigned int Bit3  :2;
 };
}State;
typedef union
{long code;
 struct
 {unsigned int Pos   :2;
  unsigned int Count :2;
  unsigned int Symb  :2;
  unsigned int Bit0  :2;
  unsigned int Bit1  :2;
  unsigned int Bit2  :2;
  unsigned int Bit3  :2;
  unsigned int Instr :3;
  unsigned int RBit0 :2;
  unsigned int RBit1 :2;
  unsigned int RBit2 :2;
  unsigned int RBit3 :2;
 };
}Instruction;

struct
{char s[NN];
 int len,whereRobot[2];
}String;
vector <Instruction> robot[2];
State state[2];
long cnt=0;
bool setBit(int n,char v,Instruction *instr)
{int w;
 switch (v)
 {case '?':{w=3;break;}
  case '0':{w=1;break;}
  case '1':{w=2;break;}
  default:return false;
 }
 switch(n)
 {case  3:{instr->Bit0=w;break;}
  case  4:{instr->Bit1=w;break;}
  case  5:{instr->Bit2=w;break;}
  case  6:{instr->Bit3=w;break;}
  case 10:{instr->RBit0=w;break;}
  case 11:{instr->RBit1=w;break;}
  case 12:{instr->RBit2=w;break;}
  case 13:{instr->RBit3=w;break;}
  default: return false;
 }
 return true;
}
bool codeInstr(const char *s,Instruction *instr)
{for (int i=0;s[i];i++)
  switch(i)
  {case  0:switch(s[i])
           {case 'I':{instr->Pos=0;continue;}
            case 'L':{instr->Pos=1;continue;}
            case 'R':{instr->Pos=2;continue;}
            case '?':{instr->Pos=3;continue;}
            default: return false;
           }
   case  1:switch(s[i])
           {case '?':{instr->Count=3;continue;}
            case 'O':{instr->Count=1;continue;}
            case 'T':{instr->Count=2;continue;}
            default: return false;
           }
   case  2:switch(s[i])
           {case '?':{instr->Symb=3;continue;}
            case 'A':{instr->Symb=1;continue;}
            case 'B':{instr->Symb=2;continue;}
            default: return false;
           }
   case  3 : case 4: case 5: case 6: case 10: case 11: case 12:
   case 13:{if (!setBit(i,s[i],instr)) return false;
            continue;
           }
   case  7:{if (s[i]!='-') return false;
            continue;
           }
   case  8:{if (s[i]!='>') return false;
            continue;
           }
   case  9:switch(s[i])
           {case 'L':{instr->Instr=1;continue;}
            case 'R':{instr->Instr=2;continue;}
            case 'S':{instr->Instr=3;continue;}
            case 'Y':{instr->Instr=4;return true;}
            case 'N':{instr->Instr=5;return true;}
            default: return false;
           }
   default:return false;
 }
 return true;
}
void showState(State st)
{switch (st.Pos)
 {case 0:{printf("I");break;}
  case 1:{printf("L");break;}
  case 2:{printf("R");break;}
  case 3:printf("?");
 }
 switch(st.Count)
 {case 3:{printf("?");break;}
  case 1:{printf("O");break;}
  case 2:printf("T");
 }
 switch(st.Symb)
 {case 3:{printf("?");break;}
  case 1:{printf("A");break;}
  case 2:printf("B");
 }
 switch(st.Bit0)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
 switch(st.Bit1)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
 switch(st.Bit2)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
 switch(st.Bit3)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
}
void showInstr(Instruction instr)
{State s;
 s.code=instr.code;
 showState(s);
 printf("->");
 switch (instr.Instr)
 {case 1:{printf("L");break;}
  case 2:{printf("R");break;}
  case 3:{printf("S");break;}
  case 4:{printf("Y");return;}
  case 5:{printf("N");return;}
 }
 switch(instr.RBit0)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
 switch(instr.RBit1)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
 switch(instr.RBit2)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
 switch(instr.RBit3)
 {case 3:{printf("?");break;}
  case 1:{printf("0");break;}
  case 2:printf("1");
 }
}
bool stateMatch(State state,Instruction instr,bool exact=true)
{if (state.Pos!=instr.Pos && instr.Pos!=3) return false;
 long currSt=(state.code & 0x3FFF),instrSt=(instr.code & 0x3FFF);
 if (exact) return currSt == instrSt;
 return (currSt & instrSt)==currSt;
}
bool getMatch(int robotNo,Instruction *next)
{//exact match
 for (auto i=robot[robotNo].begin();i!=robot[robotNo].end();i++)
  if (stateMatch(state[robotNo],*i)){*next=*i;return true;}
 //first pattern match
 for (auto i=robot[robotNo].begin();i!=robot[robotNo].end();i++)
  if (stateMatch(state[robotNo],*i,false)){*next=*i;return true;}
 //no match
 return false;
}
long readFile(const char *fname)
{long c=0;
 FILE *f=fopen(fname,"r");
 if (!f) return -1;//File not found
 char b[256];
 int r=-1;
 Instruction instr;
 while (!feof(f))
 {fgets(b,256,f);
  if (feof(f)) break;
  c=c+1;
  char *t=strpbrk(b,"\n\r");
  if (t) *t=0;
  if (!*b || *b=='%') continue;
  if (!strcmp(b,"Robot 1"))
  {if (r!=-1) {fclose(f);return c;}
   r=0;
   continue;
  }
  if (!strcmp(b,"Robot 2"))
  {if (r!=0) return c;
   r=1;
   continue;
  }
  if (!codeInstr(b,&instr)) {fclose(f);return c;}
  robot[r].push_back(instr);
 }
 fclose(f);
 if (r!=1) return -2;//Wrong file format
 return 0;//OK
}
bool checkString()
{int i;
 Instruction instr;
 char sInstr[16]="LT?0000->R0000";
 char *t=strpbrk(String.s,"\n\r");
 if (t) *t=0;
 printf("Processing string: %s\n",String.s);
 for (i=0;String.s[i];i++)
  if (String.s[i]!='A' && String.s[i]!='B') return false;
 if (i<2) return false;
 String.len=i;
 String.whereRobot[0]=String.whereRobot[1]=0;
 sInstr[2]=*String.s;
 codeInstr(sInstr,&instr);
 instr.Instr=0;
 state[0].code=state[1].code=instr.code;
 return true;
}
bool getString(FILE *f)
{fgets(String.s,NN,f);
 return checkString();
}
int exec(int robotNumber,Instruction instr)
{switch(instr.Instr)
 {case 1:{if (--String.whereRobot[robotNumber]<0) return -1;//Out of string
          break;
         }
  case 2:{if (++String.whereRobot[robotNumber]>=String.len) return -1;//Out of string
          break;
         }
  case 3:break;
  case 4:return 1;//YES announced
  case 5:return 2;//NO announced
  default:return -2;//Invalid instruction
 }
 state[robotNumber].Symb=String.s[String.whereRobot[robotNumber]]-'A'+1;
 if (String.whereRobot[robotNumber]==String.len-1)
  state[robotNumber].Pos=2;
 else if (!String.whereRobot[robotNumber])
       state[robotNumber].Pos=1;
      else state[robotNumber].Pos=0;
 if (instr.RBit0!=3) state[robotNumber].Bit0=instr.RBit0;
 if (instr.RBit1!=3) state[robotNumber].Bit1=instr.RBit1;
 if (instr.RBit2!=3) state[robotNumber].Bit2=instr.RBit2;
 if (instr.RBit3!=3) state[robotNumber].Bit3=instr.RBit3;
 return 0;
}
bool readInstr()
{int e=readFile("robots.txt");
 switch(e)
 {case 0:return true;
  case -1:{fprintf(stderr,"Instruction file not found\n");break;}
  case -2:{fprintf(stderr,"Invalid instruction file format\n");break;}
  default:fprintf(stderr,"Error reading instruction file, line #%d\n",e);
 }
 return false;
}
int identifyString(bool trace=false)
{Instruction instr;
 char buf[4];
 int r,e;
 for (unsigned long i=0;i<1000UL*(unsigned long)String.len;i++)
 {r=(i & 1);
  if (!i && trace)
  {printf("Before move # 1:\n");
   printf("Robot %d: Place=%d, State=",r+1,String.whereRobot[r]);
   showState(state[r]);
   printf("\nRobot %d: Place=%d, State=",r+2,String.whereRobot[r+1]);
   showState(state[r+1]);
   printf("\n");
  }
  if (trace) printf("Matching instruction for robot %d:",r+1);
  if (!getMatch(r,&instr)) return -3;//No valid instruction found
  if (trace) {showInstr(instr);
              printf("\n");
             }
  e=exec(r,instr);
  if (r)
  {state[0].Count=(String.whereRobot[0]==String.whereRobot[1])?2:1;
   state[1].Count=state[0].Count;
   if (trace)
   {printf("After move # %d:\n",++cnt);
    printf("Robot %d: Place=%d, State=",r,String.whereRobot[r-1]);
    showState(state[r-1]);
    printf("\nRobot %d: Place=%d, State=",r+1,String.whereRobot[r]);
    showState(state[r]);
    printf("\n---------Press ENTER------------\n");
    gets(buf);
   }
  }
  if (e) return e;
 }
 return -4;//Too many steps
}
//No input parameter - get the string from stdin, tracing OFF
//1 input parameter: if correct string - check it (tracong OFF), else tracing ON and get the string from stdin
//2 input parameters - check the first one as string, tracing ON
int main(int c,char **p)
{if(!readInstr()) return 0;
 bool trace=false;
 if (c>=2) {strcpy(String.s,p[1]);
            if (!checkString()) trace=true;
            else trace=c>2;
           }
 if (c<2 || (c==2 && trace))
 {printf("Input the string\n");
  if (!getString(stdin)) {fprintf(stderr,"Invalid input string\n");return 0;}
 }
 switch(identifyString(trace)) //identifyString(true) to trace the process
 {case -4:{fprintf(stderr,"Too many steps\n");return 0;}
  case -3:{fprintf(stderr,"No valid instruction found\n");return 0;}
  case -2:{fprintf(stderr,"Invalid instruction\n");return 0;}
  case -1:{fprintf(stderr,"Stepping out of string\n");return 0;}
  case  1:{printf("Fine\n");
           break;}
  case  2:{printf("Coarse\n");
           break;}
 }
 return 0;
}
