#include <stdio.h>
#include <stdlib.h>

void encrypt(FILE *in, FILE *out, FILE *key);

int main(int argc, char *argv[])
{
  // Check if no args are given
  if(argc < 2)
  {
    printf("ERROR: Too little arguments. Specify input file to be encrypted.\n");
    return 0;
  }

  // Check if too many args are given
  if(argc > 3)
  {
    printf("ERROR: Too many arguments.\n");
    return 0;
  }

  // Initialize variables
  FILE *in, *out, *key;

  // Open input file for reading
  in = fopen(argv[1], "r");

  // Check if a name was given for the output file
  if(argc == 3)
  {
    out = fopen(argv[2], "w");
  } else {
    out = fopen("output", "w");
  }

  // Check if input file is there
  if(in == NULL)
  {
    printf("Error while opening file\n");
    exit(1);
  }

  encrypt(in, out, key);

  // Cleanup and exit
  fclose(in);
  fclose(out);
  //fclose(key);
  return 0;
}

void encrypt(FILE *input, FILE *encrypted, FILE *key)
{
  int ch;

  // TODO: encrypt each character
  while(ch != EOF)
  {
    // read each character from the input
    ch = fgetc(input);
    // store current indexed character to output
    putc(ch, encrypted);
  }
}
