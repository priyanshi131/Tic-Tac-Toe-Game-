#include<iostream>
#include<conio.h>
#include<fstream>
#include<dos.h>
#include<iomanip>
#include<windows.h>
#include<time.h>
#include<wtypes.h>


typedef unsigned __LONG32 DWORD;
#define delay      Sleep
#define gotoxy     gotoXY
#define clrscr()   system("CLS")
#define random(x)  rand()%x
#define DATE_TIME  TIME_DATE
#define pause()    system("pause")
#define wait()     pause()

using namespace std;
int h;
int w;


struct GAME
{
    int grid[3][3];
    int token;
    int row,column;
    int moves;
}G,C;

enum COLORS{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,GRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE};

void GET_CONSOLE_SIZE(int & HEIGHT_H, int & WIDTH_W)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WIDTH_W = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    HEIGHT_H = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void SetColors(int FOREGROUND,int BACKGROUND)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(FOREGROUND+(BACKGROUND*16)));
}

void gotoXY(int X_AXIS,int Y_AXIS)
{
    COORD coordinates;

    coordinates.X=X_AXIS;
    coordinates.Y=Y_AXIS;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}


void GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    HWND hDesktop =  GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

void ConsoleSize(int i,int x_axis=0,int y_axis=0,int horizontal_buffer=0,int vertical_buffer=0)
{
        HWND hWnd = GetConsoleWindow();
        typedef HWND WINAPI(*GetConsoleWindowT)(void);
        GetConsoleWindowT GetConsoleWindow;
        HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
        GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib,TEXT("GetConsoleWindow"));
        if(GetConsoleWindow == NULL)
             exit(0);
        if(i==0)
        {
            GetDesktopResolution(horizontal_buffer,vertical_buffer);
            MoveWindow(hWnd,0,0,horizontal_buffer,vertical_buffer,TRUE);
        }
        else if(i==1)
        {
            MoveWindow(hWnd,x_axis,y_axis,horizontal_buffer,vertical_buffer,TRUE);
        }

}

void resizeWindow(int x_axis,int y_axis,int horizontal_buffer,int vertical_buffer)
{
    ConsoleSize(1,x_axis,y_axis,horizontal_buffer,vertical_buffer);
}

void MaximiseWindow()
{
    resizeWindow(0,0,0,0);
    ConsoleSize(0);
}

void SHOWMOVE(char op='o')
{

       if(C.token==1)
         SetColors(10,12);
       else
         SetColors(5,10);

        if(C.grid[C.row-1][C.column-1]==9||op=='l')
        {
/******************************************************************************************************************************
                                                    ROW : 1 START
*******************************************************************************************************************************/
          if(C.column==1&&C.row==1)
                    for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(c+w*0.5-15,r+h*0.5-6);

                           cout<<" ";
                       }

          if(C.column==2&&C.row==1)
                     for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(10+c+w*0.5-15,r+h*0.5-6);
                           cout<<" ";
                       }

          if(C.column==3&&C.row==1)
                     for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(20+c+w*0.5-15,r+h*0.5-6);
                           cout<<" ";
                       }

/******************************************************************************************************************************
                                                    ROW : 1 END
*******************************************************************************************************************************/

/******************************************************************************************************************************
                                                    ROW : 2 START
*******************************************************************************************************************************/


           if(C.column==1&&C.row==2)
                     for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(c+w*0.5-15,4+r+h*0.5-6);

                           cout<<" ";
                       }
           if(C.column==2&&C.row==2)
                    for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(10+c+w*0.5-15,4+r+h*0.5-6);

                           cout<<" ";
                       }
           if(C.column==3&&C.row==2)
                    for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(20+c+w*0.5-15,4+r+h*0.5-6);
                           cout<<" ";
                       }
/******************************************************************************************************************************
                                                    ROW : 2 END
*******************************************************************************************************************************/

/******************************************************************************************************************************
                                                    ROW : 3 START
*******************************************************************************************************************************/

           if(C.row==3&&C.column==1)
                for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(c+w*0.5-15,8+r+h*0.5-6);
                           cout<<" ";
                       }

           if(C.row==3&&C.column==2)
                    for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(10+c+w*0.5-15,8+r+h*0.5-6);
                           cout<<" ";
                       }

           if(C.row==3&&C.column==3)
                    for(int r=0;r<3;r++)
                        for(int c=0;c<9;c++)
                       {
                           gotoXY(20+c+w*0.5-15,8+r+h*0.5-6);
                           cout<<" ";
                       }
            }
/******************************************************************************************************************************
                                                    ROW : 3 END
*******************************************************************************************************************************/

}

void LOADGAME()
{
     int r,c,bk;
     bk=C.token;
     SetColors(1,14);
     system("CLS");
     char grid[20][31]=
                        {   "         |         |         ",
                            "         |         |         ",
                            "         |         |         ",
                            "---------+---------+---------",
                            "         |         |         ",
                            "         |         |         ",
                            "         |         |         ",
                            "---------+---------+---------",
                            "         |         |         ",
                            "         |         |         ",
                            "         |         |         "
                        };

                        for(int c=0;c<11;c++)
                        {
                            gotoXY(w*0.5-15,c+h*0.5-6);
                            cout<<grid[c];
                        }

     for(r=0;r<3;r++)
     {
         for(c=0;c<3;c++)
         {
             if(C.grid[r][c]==1)
             {
                 C.row=r+1;
                 C.column=c+1;
                 C.token=C.grid[r][c];
                 SHOWMOVE('l');
             }
             if(C.grid[r][c]==0)
             {
                 C.row=r+1;
                 C.column=c+1;
                 C.token=C.grid[r][c];
                 SHOWMOVE('l');
             }
         }
     }

     C.token=bk;
}

int msg()
{


    char ch;


          char MSG[][30]=   {
                                "1.NEW GAME           ",
                                "2.LOAD GAME          ",
                                "3.EXIT               ",
                                "CHOICE NUMBER [ ]\b\b"
                            };
           do{


                       SetColors(RED,BLACK);/**SET MSG COLOUR TO (RED,BLACK)*/
                       system("CLS");

                   for(int r=0;r<4;r++)/**TO SHOW THE ABOVE MSG*/
                   {
                       gotoXY(w*0.5-15,r+h*0.5-4);
                       printf("%s",MSG[r]);
                    }
                    ch=getche();

                    switch(ch)
                    {


                      case '1':/**IF THE PLAYER WANTS NEW GAME */
                      {
                            system("CLS");
                            system("COLOR F0");
                            cout<<"\n\n\n\n\n\n\n";
                            cout<<setw(80)<<"LOADING.....";
                                for(int x=0;x<3;x++)
                                {
                                    cout<<"\b ";
                                    Sleep(1000);
                                    cout<<"\b.";
                                    Sleep(500);
                                 }
                                system("CLS");
                                SetColors(1,14);
                                system("CLS");
                                char grid[20][31]=
                                                    {   "         |         |         ",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "---------+---------+---------",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "---------+---------+---------",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "         |         |         "
                                                    };

                                        for(int i=0;i<3;i++)
                                         {
                                            for(int j=0;j<3;j++)
                                                C.grid[i][j]=9;
                                        }
                                        for(int c=0;c<11;c++)
                                        {
                                            gotoXY(w*0.5-15,c+h*0.5-6);
                                            cout<<grid[c];
                                        }
                                               return 1;

                        }


                      case '2':/**IF THE PLAYER WANTS TO PLAY SAVED GAME*/
                          {
                            system("CLS");
                            system("COLOR F0");
                            cout<<"\n\n\n\n\n\n\n";
                            cout<<setw(80)<<"LOADING.....";
                                for(int x=0;x<3;x++)
                                {
                                    cout<<"\b ";
                                    Sleep(1000);
                                    cout<<"\b.";
                                    Sleep(500);
                                 }
                              system("CLS");

                              SetColors(1,14);
                              system("CLS");
                              char grid[20][31]=
                                                    {   "         |         |         ",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "---------+---------+---------",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "---------+---------+---------",
                                                        "         |         |         ",
                                                        "         |         |         ",
                                                        "         |         |         "
                                                    };

                                        for(int i=0;i<3;i++)
                                         {
                                            for(int j=0;j<3;j++)
                                                C.grid[i][j]=9;
                                        }
                                        for(int c=0;c<11;c++)
                                        {
                                            gotoXY(w*0.5-15,c+h*0.5-6);
                                            cout<<grid[c];
                                        }
                                        return 0;
                          }


                      case '3':/**IF THE PLAYER WANTS EXIT GAME*/
                          {
                                        exit(0);
                          }

                      default:/**IF THE PLAYER ENTERS WRONG INDEX NUMBER*/
                          {
                                          SetColors(BLACK,WHITE);/**SET MSG COLOUR TO (BLACK,WHITE)*/
                                          system("CLS");
                                          gotoXY(w*0.5-20,h*0.25);
                                          cout<<"\a!!WRONG CHOICE NUMBER ENTER AGAIN!!";
                                          Sleep(1000);
                          }
                    }

              }while(1);
}



void GETMOVE()
{
    char ch;

   do
    {

        ch=getch();
        if(ch==0||ch==-32)
        {
            ch=getche();

               switch(ch)
               {

               case 72:
                    C.row--;
                    if(C.row<1)
                    C.row=3;

                   break;
               case 80:
                   C.row++;
                   if(C.row>3)
                    C.row=1;

                   break;
               case 77:
                    C.column++;
                   if(C.column>3)
                    C.column=1;


                   break;
               case 75:
                   C.column--;
                   if(C.column<1)
                    C.column=3;
                   break;

               }

                gotoXY(w*0.5-15+(C.column-1)*10,h*0.5-6+(C.row-1)*4);

            }

           else if(ch==27)
            {
                char t=27;
                char mmsg[][50]=
                {
                    "1.SAVE                 ",
                    "2.SAVE AND EXIT        ",
                    "3.CONTINUE             ",
                    "4.EXIT                 ",
                    "CHOICE NUMBER   [ ]\b\b"
                };
                char op;
                int I=0;

               do
                {
                    SetColors(14,0);
                    system("CLS");

                for(int r=0;r<5;r++)
                   {
                       gotoXY(w*0.5-15,r+h*0.5-4);
                       printf("%s",mmsg[r]);
                   }

                fflush(stdin);
                op=getche();

                switch(op)
                {
                  case '1':
                   {
                       fstream file;
                       file.open("GAMEDATA.DAT",ios::binary|ios::out);
                       if(!file)
                       {
                           file.close();
                           file.open("GAMEDATA.DAT",ios::binary|ios::app);
                           file.close();
                           file.open("GAMEDATA.DAT",ios::binary|ios::out);
                       }
                       file.write((char*)&C,sizeof(C));
                       file.close();
                       LOADGAME();
                       I=1;
                       break;

                   }
                   case '2':
                   {
                       fstream file;
                       file.open("GAMEDATA.DAT",ios::binary|ios::out);
                       if(!file)
                       {
                           file.close();
                           file.open("GAMEDATA.DAT",ios::binary|ios::app);
                           file.close();
                           file.open("GAMEDATA.DAT",ios::binary|ios::out);
                       }
                       file.write((char*)&C,sizeof(C));
                       file.close();
                       exit(0);
                   }
                    case '3':
                    {
                            LOADGAME();
                            I=1;
                            break;
                    }


                    case '4':
                        exit(0);

                    default:
                         {
                          SetColors(BLACK,WHITE);/**SET MSG COLOUR TO (BLACK,WHITE)*/
                          system("CLS");
                          gotoXY(w*0.5-20,h*0.25);
                          cout<<"!!WRONG CHOICE NUMBER ENTER AGAIN!!";
                          Sleep(1000);
                          system("CLS");
                         }

                }

               }while(I==0);
               ch=t;
            }

    }while(ch!=13);
}

int CHECKMOVE()
{
    int r,c,sum=0,s=0,s1=0;

           for(r=0;r<3;r++)
           {
              sum+=C.grid[r][r] ;
              s+=C.grid[r][2-r];
           }

                if(sum==3||s==3)
                 {
                     return 1;

                  }
                else if(sum==0||s==0)
                  {
                     return(0);

                  }
        sum=0,s=0,s1=0;

           for(r=0;r<3;r++)
           {
              sum+=C.grid[0][r] ;
              s+=C.grid[1][r];
              s1+=C.grid[2][r];
           }

                 if(sum==3||s==3||s1==3)
                 {
                     return 1;

                  }
                else if(sum==0||s==0||s1==0)
                  {
                     return(0);

                  }

          sum=0,s=0,s1=0;

           for(r=0;r<3;r++)
           {
              sum+=C.grid[r][0] ;
              s+=C.grid[r][1];
              s1+=C.grid[r][2];
           }

                if(sum==3||s==3||s1==3)
                 {
                     return 1;

                  }
                else if(sum==0||s==0||s1==0)
                  {
                     return(0);

                  }

          return 5;

}



void ma_in()
{
      C.column=1;
      C.row=1;
      C.token=1;
      int i=msg();

          if(i)
          {
               C.moves=1;
               while(C.moves!=10)
               {

                    GETMOVE();
                    SHOWMOVE();

                    if(C.grid[C.row-1][C.column-1]==9)
                    {

                        C.grid[C.row-1][C.column-1]=C.token;
                        C.moves++;
                        C.token=!C.token;
                    }

                    int c=CHECKMOVE();

                    if(C.moves==10&&c==5)
                    {

                        SetColors(BLACK,WHITE);
                        system("CLS");
                        cout<<"GAME DRAW";

                       for(int i=0;i<3;i++)
                         {
                            for(int j=0;j<3;j++)
                                C.grid[i][j]=9;
                        }
                        getch();
                        ma_in();

                    }
                       else if(c==1)
                       {
                            SetColors(BLACK,WHITE);
                            system("CLS");
                        cout<<"1 wins";
                           for(int i=0;i<3;i++)
                         {
                            for(int j=0;j<3;j++)
                                C.grid[i][j]=9;
                        }
                        getch();
                        ma_in();
                        }
                       else if(c==0)
                       {
                           SetColors(BLACK,WHITE);
                           system("CLS");
                           cout<<"0 wins";
                           for(int i=0;i<3;i++)
                         {
                            for(int j=0;j<3;j++)
                                C.grid[i][j]=9;
                         }
                        getch();
                        ma_in();
                       }


               }
          }
          else
          {
                    fstream file;
                    file.open("GAMEDATA.DAT",ios::binary|ios::in|ios::out);
                    if(!file)
                    {
                        system("CLS");
                        gotoXY(w*0.5-11,h*0.25);
                        cout<<"~NO GAME SAVED~";
                        getch();
                        system("CLS");
                        ma_in();
                    }
                    else
                    {

                        file.read((char*)&G,sizeof(G));
                        file.close();
                        C=G;
                        LOADGAME();
                        C=G;
                        while(C.moves!=10)
                               {

                                   GETMOVE();
                                   SHOWMOVE();
                                    if(C.grid[C.row-1][C.column-1]==9)
                                    {
                                        C.grid[C.row-1][C.column-1]=C.token;
                                        C.moves++;
                                        C.token=!C.token;
                                    }
                                    int c=CHECKMOVE();
                                    if(C.moves==10&&c==5)
                                    {

                                        SetColors(0,WHITE);
                                        system("CLS");
                                        cout<<"GAME DRAW";
                                        getch();
                                        ma_in();

                                    }
                                else if(c==1)
                                    {
                                        SetColors(BLACK,WHITE);
                                        system("CLS");
                                        cout<<"1 wins";
                                        getch();
                                        ma_in();

                                    }
                                else if(c==0)
                                    {

                                        SetColors(BLACK,WHITE);
                                        system("CLS");
                                        cout<<"0 wins";
                                        getch();
                                        ma_in();

                                    }


                               }

                    }

          }
}

int main()
{

  MaximiseWindow();
  GET_CONSOLE_SIZE(h,w);
  char op;
        ma_in();
    getch();
    return 0;
}
