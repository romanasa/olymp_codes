#include <cstdio>
#include <cstring>
#include <vector>
int const NN=16768;//4096;
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
bool readInstr(const char *fname)
{int e=readFile(fname);
 switch(e)
 {case 0:return true;
  case -1:{fprintf(stderr,"Instruction file not found\n");break;}
  case -2:{fprintf(stderr,"Invalid instruction file format\n");break;}
  default:fprintf(stderr,"Error reading instruction file, line #%d\n",e);
 }
 return false;
}
int identifyString()
{Instruction instr;
 char buf[4];
 int r,e;
 for (unsigned long i=0;i<1000UL*(unsigned long)String.len;i++)
 {r=(i & 1);
  if (!getMatch(r,&instr)) return -3;//No valid instruction found
  e=exec(r,instr);
  if (r)
  {state[0].Count=(String.whereRobot[0]==String.whereRobot[1])?2:1;
   state[1].Count=state[0].Count;
  }
  if (e) return e;
 }
 return -4;//Too many steps
}
int main(int parN,char **par)
{//par[1] - in file path
 //par[2] - sol file - dummy
 //par[3] - res file
 char res[4],*q,*t;
 Instruction instr;
 char sInstr[16]="LT?0000->R0000";
 int ans,lin=0,i=0;
 double score=0;
 bool err=false;
 if (parN<3){printf("Not enough parameters.\nUsage: checker <(path to the )file, containing tests> <dummy (sol file)> <(path to the )res file>");
             return 0;
            }
 if(!readInstr(par[3])) {printf("0\n");
                         fprintf(stderr,"No result file\n");
                         return 0;
                        }
 FILE *f=fopen(par[1],"r");
 if (!f){printf("Testfile %s not found\n",par[1]);return 0;}
 lin=0;
 while (!feof(f))
 {fgets(String.s,NN,f);
  t=strpbrk(String.s,"\n\r");
  if (t) *t=0;
  lin++;
  if (*String.s=='%')
  {if (i && !err) score+=0.1;
   i++;//test number
   err=false;
   continue;
  }
  fgets(res,4,f);
  lin++;
  if (err) continue;
  if (*res=='Y') ans=1;
  else if (*res=='N') ans=2;
       else {err=true;
             printf("Incorrectly read test %d, line %d, res %c\n",i,lin,res);//should not happen
             break;
            }
  String.len=strlen(String.s);
  String.whereRobot[0]=String.whereRobot[1]=0;
  sInstr[2]=*String.s;
  codeInstr(sInstr,&instr);
  instr.Instr=0;
  state[0].code=state[1].code=instr.code;
  int r=identifyString();
  switch(r)
  {case -4:{fprintf(stderr,"Too many steps\n");err=true;break;}
   case -3:{fprintf(stderr,"No valid instruction found\n");err=true;break;}
   case -2:{fprintf(stderr,"Invalid instruction\n");err=true;break;}
   case -1:{fprintf(stderr,"Stepping out of string\n");err=true;break;}
   case  1:{err=(ans!=1);break;}
   case  2:err=(ans!=2);
  }
           //next information should not be sent to the competitor
  if (err) {//fprintf(stderr,"Error in test %d, line %d\n",i,lin);
            //fprintf(stderr,"Author: %d, program result: %d\n",res,r);
           }
 }
 fclose(f);
 if (!err) score+=0.1;
 printf("%0.2f\n",score);
 return 0;
}