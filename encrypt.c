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

  // Initialize variables and open files for IO
  FILE *in = fopen(argv[1], "r");

  if(in == NULL)
  {
    printf("Error while opening file\n");
    exit(1);
  }

  FILE *key = fopen("key","w+");
  FILE *out;


  // Check if a name was given for the encrypted output file, if not, create a file
  if(argc == 3)
  {
    out = fopen(argv[2], "w+");
  } else {
    out = fopen("encrypted", "w+");
  }

  encrypt(in, out, key);

  // Cleanup and exit
  fclose(in);
  fclose(out);
  fclose(key);
  return 0;
}

void encrypt(FILE *input, FILE *encrypted, FILE *key)
{
  int ch;
  FILE *urandom = fopen("/dev/urandom", "r");
  while((ch = fgetc(input)) != EOF)
  {
    int key_ch = fgetc(urandom);
    int encrypted_ch = ch ^ key_ch;
    fputc(encrypted_ch, encrypted);
    fputc(key_ch, key);
  }
}
