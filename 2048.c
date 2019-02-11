#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void IniciarJogo(int z, int tabuleiro[][z]);
void Jogo(int x, int y, int tabuleiro[][y]);
void MostrarTabuleiro(int x, int y, int tabuleiro[][y]);
void NovaJogada(int z, int tabuleiro[][z]);
void MoverDireita(int x, int y, int tabuleiro[][y]);
void MoverEsquerda(int x, int y, int tabuleiro[][y]);
void MoverCima(int x, int y, int tabuleiro[][y]);
void MoverBaixo(int x, int y, int tabuleiro[][y]);
void SomaDireita(int x, int y, int tabuleiro[][y]);
void SomaEsquerda(int x, int y, int tabuleiro[][y]);
void SomaCima(int x, int y, int tabuleiro[][y]);
void SomaBaixo(int x, int y, int tabuleiro[][y]);
int FimJogo(int x, int y, int tabuleiro[][y]);
int TestaSoma(int x, int y, int tabuleiro[][y]);
int Score = 0; //variáveis globais - pontuação
int HighScore = 0; //pontuação máxima

int main()
{
    int tabuleiro[4][4] = {{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}, {-1,-1,-1,-1}};

    Jogo(4,4, tabuleiro);

    return 0;
}



void Jogo(int x, int y, int tabuleiro[][y])
{
    int seta, fim = 0;
    IniciarJogo(y, tabuleiro);
    while (!fim)
    {
        MostrarTabuleiro(x, y, tabuleiro);
        seta = getch();
        switch(seta)
        {
            case 72: // cima
                MoverCima(x, y, tabuleiro);
                SomaCima(x, y, tabuleiro);
            break;

            case 80: // baixo
                MoverBaixo(x, y, tabuleiro);
                SomaBaixo(x, y, tabuleiro);
            break;

            case 75: // esquerda
                MoverEsquerda(x, y, tabuleiro);
                SomaEsquerda(x, y, tabuleiro);
            break;

            case 77: // direita
                MoverDireita(x, y, tabuleiro);
                SomaDireita(x, y, tabuleiro);
            break;

            case 114: // tecla 'r'
                fim = 3;
            break;

            default:
            break;

        }
        if(fim != 3)
            fim = FimJogo(x, y, tabuleiro);
    }

    MostrarTabuleiro(x, y, tabuleiro);
    if (fim == 2) {
        HighScore = Score;
        Score = 0;
        printf("\n\n\t\t\x7You win.\n");
        Jogo(x,y, tabuleiro);
    }
    else if (fim == 1)
    {
        HighScore = Score;
        Score = 0;
        printf("\n\n\t\t\x7Game over.\n");
        Jogo(x,y, tabuleiro);
    }
    else if (fim == 3) //reseta o jogo
    {
        HighScore = Score;
        Score = 0;
        Jogo(x,y,tabuleiro);
    }
}

int FimJogo(int x, int y, int tabuleiro[][y])
{
    int i, j;

    for(i=0; i<x; i++)
    {
        for(j=0; j<y; j++)
        {
          if (tabuleiro[i][j] == 2048)
            return 2;
          else if(tabuleiro[i][j] == -1)
            return 0;
        }
    }
    return TestaSoma(x, y, tabuleiro);
}

int TestaSoma(int x, int y, int tabuleiro[][y])
{
    int i, j;

      for(i=0; i<x-1; i++)
         {
             for(j=0; j<y; j++)
           {
            if(tabuleiro[i][j] == tabuleiro[i+1][j] && tabuleiro[i][j]>0)
                return 0;
            }
        }

     for(i=0; i<x; i++)
    {
        for(j=y-1; j>=1; j--)
        {
            if(tabuleiro[i][j] == tabuleiro[i][j-1] && tabuleiro[i][j]>0)
                return 0;
        }
    }

    return 1;
}

void IniciarJogo(int z, int tabuleiro[][z])
{
   time_t t;
   srand((unsigned) time(&t));
   int i, j, k=0;

   for(i=0;i<4;i++)
   {
       for(j=0;j<4;j++)
       {
           tabuleiro[i][j] = -1;
       }

   }

   while(k<2)
    {
        i = rand() % 4;
        j = rand() % 4;
        if(tabuleiro[i][j]!=2)
        {
            tabuleiro[i][j] = 2;
            k++;
        }
    }
}

void MostrarTabuleiro(int x, int y, int tabuleiro[][y])
{
     int i, j;

    system("cls");
    printf("\n2048.c\n");
    printf("\nHigh Score: %d\n", HighScore);
    printf("Your Score: %d\n\n", Score);

     for(i=0; i<x; i++)
    {
        printf("\t\t\t\t ---------------\n");
        //printf("\x1b"); <- seta da esquerda
        printf("\t\t\t\t|");
        for(j=0; j<y; j++)
        {
          if (tabuleiro[i][j] != -1 && tabuleiro[i][j] < 10)
            printf("  %d|", tabuleiro[i][j]);
          else if (tabuleiro[i][j] != -1 && tabuleiro[i][j] < 100)
            printf(" %d|", tabuleiro[i][j]);
          else if (tabuleiro[i][j] != -1 && tabuleiro[i][j] < 1000)
            printf("%d|", tabuleiro[i][j]);
          else
            printf("   |");
        }
        printf("\n");
    }
    printf("\t\t\t\t ---------------\n");
    printf("\nUse as setas do teclado para jogar.\nAperte 'r' para reiniciar o jogo.");

}

void NovaJogada(int z, int tabuleiro[][z])
{
   time_t t;
   srand((unsigned) time(&t));

   int i, j, n, k=0;
   for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if(tabuleiro[i][j] == -1)
              while(k<1)
                {
                    i = rand() % 4;
                    j = rand() % 4;
                    if(tabuleiro[i][j] < 0)
                    {
                        n = rand() % 10 + 1;
                        if (n<=5)
                        {
                            tabuleiro[i][j] = 2;
                            k++;
                        }
                        else
                        {
                            tabuleiro[i][j] = 4;
                            k++;
                        }

                    }
                }
        }
    }

}

void MoverDireita(int x, int y, int tabuleiro[][y])
{
       int i, j, contador=0;
       while(contador<12)
      {
          contador = 0;
          for(i=0; i<x; i++)
         {
             for(j=y-1; j>=1; j--)
           {
                if(tabuleiro[i][j]==-1 && tabuleiro[i][j-1]!=-1)
                {
                     tabuleiro[i][j] = tabuleiro[i][j-1];
                     tabuleiro[i][j-1] = -1;
                }
                 else
                     contador++;
            }
          }
       }
}

void MoverEsquerda(int x, int y, int tabuleiro[][y])
{
       int i, j, contador=0;
       while(contador<12)
      {
          contador = 0;
          for(i=0; i<x; i++)
         {
             for(j=0; j<y-1; j++)
           {
                if(tabuleiro[i][j]==-1 && tabuleiro[i][j+1]!=-1)
                {
                     tabuleiro[i][j] = tabuleiro[i][j+1];
                     tabuleiro[i][j+1] = -1;
                }
                 else
                     contador++;
            }
          }
       }

}

void MoverCima(int x, int y, int tabuleiro[][y])
{
       int i, j, contador=0;
       while(contador<12)
      {
          contador = 0;
          for(i=0; i<x-1; i++)
         {
             for(j=0; j<y; j++)
           {
                if(tabuleiro[i][j]==-1 && tabuleiro[i+1][j]!=-1)
                {
                     tabuleiro[i][j] = tabuleiro[i+1][j];
                     tabuleiro[i+1][j] = -1;
                }
                 else
                     contador++;
            }
          }
       }
}

void MoverBaixo(int x, int y, int tabuleiro[][y])
{
       int i, j, contador=0;
       while(contador<12)
      {
          contador = 0;
          for(i=x-1; i>=1; i--)
         {
             for(j=0; j<y; j++)
           {
                if(tabuleiro[i][j]==-1 && tabuleiro[i-1][j]!=-1)
                {
                     tabuleiro[i][j] = tabuleiro[i-1][j];
                     tabuleiro[i-1][j] = -1;
                }
                 else{
                     contador++;
                 }
            }
          }
       }
}

void SomaDireita(int x, int y, int tabuleiro[][y])
{
    int i, j;

    for(i=0; i<x; i++)
    {
        for(j=y-1; j>=1; j--)
        {
            if(tabuleiro[i][j] == tabuleiro[i][j-1] && tabuleiro[i][j]>0)
                {
                     tabuleiro[i][j] += tabuleiro[i][j-1];
                     Score += tabuleiro[i][j];
                     tabuleiro[i][j-1] = -1;
                }
        }
    }
    MoverDireita(x,y,tabuleiro);
    NovaJogada(y, tabuleiro);
}

void SomaEsquerda(int x, int y, int tabuleiro[][y])
{
    int i, j;

    for(i=0; i<x; i++)
    {
        for(j=0; j <= y-1; j++)
        {
            if(tabuleiro[i][j] == tabuleiro[i][j+1] && tabuleiro[i][j]>0)
                {
                     tabuleiro[i][j] += tabuleiro[i][j+1];
                     Score += tabuleiro[i][j];
                     tabuleiro[i][j+1] = -1;
                }
        }
    }
    MoverEsquerda(x,y,tabuleiro);
    NovaJogada(y, tabuleiro);
}

void SomaCima(int x, int y, int tabuleiro[][y])
{
    int i, j;

      for(i=0; i<x-1; i++)
         {
             for(j=0; j<y; j++)
           {
            if(tabuleiro[i][j] == tabuleiro[i+1][j] && tabuleiro[i][j]>0)
                {
                     tabuleiro[i][j] += tabuleiro[i+1][j];
                     Score += tabuleiro[i][j];
                     tabuleiro[i+1][j] = -1;
                }
        }
    }
    MoverCima(x,y,tabuleiro);
    NovaJogada(y, tabuleiro);
}

void SomaBaixo(int x, int y, int tabuleiro[][y])
{
    int i, j;

      for(i=x-1; i>=1; i--)
         {
             for(j=0; j<y; j++)
           {
            if(tabuleiro[i][j] == tabuleiro[i-1][j] && tabuleiro[i][j]>0)
                {
                     tabuleiro[i][j] += tabuleiro[i-1][j];
                     Score += tabuleiro[i][j];
                     tabuleiro[i-1][j] = -1;
                }
        }
    }
    MoverBaixo(x,y,tabuleiro);
    NovaJogada(y, tabuleiro);
}

