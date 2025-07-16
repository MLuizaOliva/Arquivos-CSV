#include <stdlib.h>
#include <stdio.h>

void limparTela()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void pausarTela()
{
  limparBuffer();
  printf("\nPressione Enter para continuar...");
  getchar();
}
