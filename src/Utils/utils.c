#include <stdlib.h>

void limparTela()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
