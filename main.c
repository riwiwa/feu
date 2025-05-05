#include <stdio.h>
#include <stdlib.h>

int main()
{
  char str[8];
  FILE* file_ptr;

  // Open file for reading
  file_ptr = fopen("file.txt", "r");

  // Check if file is there
  if(file_ptr == NULL)
  {
    printf("Error while opening file\n");
    exit(1);
  }

  // Store file contents in a string and print
  if(fgets(str, 8, file_ptr) != NULL)
  {
    puts(str);
  }
  fclose(file_ptr);
  return 0;
}
