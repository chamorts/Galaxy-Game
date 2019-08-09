#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <conio.h>

using namespace std;

#define IZQUIERDA 75
#define DERECHA   77

char avion_l1[]={' ',' ',' ', '*',' ',' ',' ',0};
char avion_l2[]={' ',' ','*', '*','*',' ',' ',0};
char avion_l3[]={' ','*',' ', '*',' ','*',' ',0};

char explocion_l1[]={' ',' ','*','*',' ',' ',' ',0};
char explocion_l2[]={' ','*','*','*','*',' ',' ',0};
char explocion_l3[]={' ',' ','*','*',' ',' ',' ',0};

char explocion_r1[]={'*',' ','*','*',' ','*',' ',0};
char explocion_r2[]={' ','*','*','*','*',' ',' ',0};
char explocion_r3[]={'*',' ','*','*',' ','*',' ',0};

char borrar_avion[]={' ',' ',' ',' ',' ',' ',' ',0};

int Num_vidas = 3;
int Corazones = 3;
int ix = 40;
int iy = 19;

int y = 8 , x = 12;
int yy = 12 , xx = 17;
int x1 = 58 , y1 = 6;
int x2 = 70 , y2 = 9;

int i,v;

int dd=0;
bool disparo = false;
int xb;

int repeticion = 0 , nivel = 1;
bool condicion = false;

void gotoxy(int x , int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);

}

void vidas(int vi)
{
    gotoxy(2,1); printf("VIDAS %d",vi);
}

void Barra_Salud(int n)
{
    gotoxy(72,1); printf(" ");
    gotoxy(73,1); printf(" ");
    gotoxy(74,1); printf(" ");

    for(v = 0 ; v < n ; v++)
    {
         gotoxy(72+v ,1);
         printf("%c",3);
    }
}

void Explocion(void)
{
    gotoxy(ix,iy); puts(explocion_l1);
    gotoxy(ix,iy+1); puts(explocion_l2);
    gotoxy(ix,iy+2); puts(explocion_l3);

    Sleep(380);

    gotoxy(ix,iy); puts(explocion_r1);
    gotoxy(ix,iy+1); puts(explocion_r2);
    gotoxy(ix,iy+2); puts(explocion_r3);

    Sleep(380);

    gotoxy(ix,iy); puts(avion_l1);
    gotoxy(ix,iy+1); puts(avion_l2);
    gotoxy(ix,iy+2); puts(avion_l3);

}

void jugar(void)
{
   if(!disparo) xb = ix;
   gotoxy(xb+3 , iy + dd); printf("*");
// Asteroide
   gotoxy(x,y); printf("%c",2);
   gotoxy(xx,yy); printf("%c",2);
   gotoxy(x1,y1); printf("%c",2);
   gotoxy(x2,y2); printf("%c",2);

   Sleep(70);

   gotoxy(x,y); printf(" ");
   gotoxy(xx,yy); printf(" ");
   gotoxy(x1,y1); printf(" ");
   gotoxy(x2,y2); printf(" ");

   gotoxy(xb+3 , iy + dd); printf(" ");
   if(disparo == true) dd--;
   if(iy + dd < 5 ){
    dd =0;
    disparo = false;
   }

   if (y > 20 || x == xb+3 && iy + dd <= y)
   {
       y = 4;
       x = (rand() % 70) +6;

       if (y == 4)
        condicion = false;

   }
   if (yy > 20 || xx == xb+3 && iy + dd <= yy)
   {
       yy = 4;
       xx = (rand() % 70) +6;
   }
   if (y1 > 20 || x1 == xb+3 && iy + dd <= y1)
   {
       y1 = 4;
       x1 = (rand() % 70) +6;
   }
   if (y2 > 20 || x2 == xb+3 && iy + dd <= y2)
   {
       y2 = 4;
       x2 = (rand() % 70) +6;
   }
// Mover Nave
if(kbhit())
{
    unsigned char tecla = getch();

    switch (tecla)
    {
    case IZQUIERDA:

        if( ix > 4)
        {
            gotoxy(ix,iy); puts(borrar_avion);
            gotoxy(ix,iy+1); puts(borrar_avion);
            gotoxy(ix,iy+2); puts(borrar_avion);

            ix -=2;

            gotoxy(ix,iy); puts(avion_l1);
            gotoxy(ix,iy+1); puts(avion_l2);
            gotoxy(ix,iy+2); puts(avion_l3);
        }
        break;

    case DERECHA:

        if( ix < 70)
        {
            gotoxy(ix,iy); puts(borrar_avion);
            gotoxy(ix,iy+1); puts(borrar_avion);
            gotoxy(ix,iy+2); puts(borrar_avion);

            ix +=2;

            gotoxy(ix,iy);puts(avion_l1);
            gotoxy(ix,iy+1);puts(avion_l2);
            gotoxy(ix,iy+2);puts(avion_l3);
        }
        break;

    case 'd':
            disparo = true;
            break;
    }
}
// Impacto Asteroide
if( ( x > ix && x<ix + 6 && y == iy-1) || ( xx > ix && xx<ix + 6 && yy == iy-1)
    || ( x1 > ix && x1<ix + 6 && y1 == iy-1) || ( x2 > ix && x2<ix + 6 && y2 == iy-1) )
    {
        Corazones --;
        Barra_Salud(Corazones);
        printf("\a");
    }

            gotoxy(ix,iy);puts(avion_l1);
            gotoxy(ix,iy+1);puts(avion_l2);
            gotoxy(ix,iy+2);puts(avion_l3);

if(!Corazones)
{
    Num_vidas--;
    vidas(Num_vidas);
    Explocion();
    Corazones = 3;

    Barra_Salud(Corazones);
}

// Niveles
if(!condicion)
{
    repeticion ++;
    condicion = true;
}

if(repeticion == 10)
{
    nivel++;
    gotoxy(35,1); printf("NIVEL %i",nivel);

    gotoxy(ix,iy); puts(borrar_avion);
    gotoxy(ix,iy+1); puts(borrar_avion);
    gotoxy(ix,iy+2); puts(borrar_avion);

    iy -= 2;

    gotoxy(ix,iy); puts(avion_l1);
    gotoxy(ix,iy+1); puts(avion_l2);
    gotoxy(ix,iy+2); puts(avion_l3);

    repeticion = 0;

}
   y++;
   yy++;
   y1++;
   y2++;
}


int main()
{
    system("color 03");
    cout<<"\n\n\n\n\t\t\t***********************************************\n";
    cout<<"\t\t\t|                 GALAXY GAME                 |\n";
    cout<<"\t\t\t|                                             |\n";
    cout<<"\t\t\t|          Creado por Gabriel Corporan        |\n";
    cout<<"\t\t\t|              Matricula 2017-1865            |\n";
    cout<<"\t\t\t***********************************************\n\n\n";
    cout<<"\n\n\t\t\t\tPulse una tecla para continuar\n\n\n\n\n\n\n\n";
    cout<<"\n\n\t\t\t\tPulse la tecla D para Disparar\n";
    cout<<"\n\n\t\t\t\tPulse Flechas para mover la Nave\n";
			system("pause>null");
			system("cls");

    PlaySound(TEXT("Jungle.wav"), NULL,SND_ASYNC);

    vidas(Num_vidas);
    Barra_Salud(Corazones);
    gotoxy(35,1); printf("NIVEL %i",nivel);

    gotoxy(ix,iy);puts(avion_l1);
    gotoxy(ix,iy+1);puts(avion_l2);
    gotoxy(ix,iy+2);puts(avion_l3);

    while(Num_vidas> 0 && nivel <= 6)
        jugar();


    gotoxy(20,15); printf(" GAME OVER ");

    Sleep(200);
    system("pause");

    return 0;
}
