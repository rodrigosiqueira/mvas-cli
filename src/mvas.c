#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "cli.h"
#include "vasHandler.h"
#include "segmentHandler.h"

int main(int argc, char ** argv)
{
  char * inputCommand = NULL;
  int action = 0;
  struct singleParameter * elements = NULL;

  commandList * currentCommands = typedCommand(argc, argv);
  if (!currentCommands)
  {
    return -1;
  }

  action = syntaxCommand(currentCommands);
  switch(action)
  {
    case LIST:
      printf("=== VAS ===\n");
      listVAS();
      printf("=== SEGMENTS ===\n");
      listSegment();
      break;
    case LIST_VAS:
      listVAS();
      break;
    case LIST_SEG:
      listSegment();
      break;
    case REMOVE:
      elements = currentCommands->head.tqh_first;
      // Ignore first element (it is 'r' or 'remove')
      elements = elements->pointers.tqe_next;
      for(; elements != NULL; elements = elements->pointers.tqe_next)
      {
        if (!strcmp(elements->parameter, "vid") ||
            !strcmp(elements->parameter, "v"))
        {
          removeVAS(elements->value);
          continue;
        }
        if (!strcmp(elements->parameter, "segment") ||
            !strcmp(elements->parameter, "s"))
        {
          removeSegment(elements->value);
          continue;
        }
      }
      break;
    default:
      printf("Wrong syntax or not implemented yet\n");
      break;
  }

  free(inputCommand);

  return 0;
}
