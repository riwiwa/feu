#include <stdio.h>
#include <stdlib.h>

void decrypt(FILE *encrypted, FILE *key, FILE *decrypted);

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    printf("ERROR: Specify an encrypted file along with a key (./decrypt [ENCRYPTED FILE] [KEY])");
  }

  // Open files for IO and check if they are accessible
  FILE *encrypted = fopen(argv[1], "r");
  FILE *key = fopen(argv[2], "r");

  if(encrypted == NULL)
  {
    printf("ERROR: Cannot access specified encrypted file"); 
  }
  if(key == NULL)
  {
    printf("ERROR: Cannot access specified key file"); 
  }

  FILE *decrypted = fopen("decrypted","w+");

  decrypt(encrypted, key, decrypted);

  fclose(encrypted);
  fclose(key);
  fclose(decrypted);
  return 0;
}

void decrypt(FILE *encrypted, FILE *key, FILE *decrypted)
{
  int encrypted_ch;
  while((encrypted_ch = fgetc(encrypted)) != EOF)
  {
    int key_ch = fgetc(key);
    int decrypted_ch = encrypted_ch ^ key_ch;
    fputc(decrypted_ch, decrypted);
  }
}
