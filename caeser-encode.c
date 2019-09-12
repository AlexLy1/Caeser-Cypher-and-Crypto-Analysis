#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char upcase(char ch){
  if(islower(ch))
    ch -= 'a' - 'A';
  return ch;
}

char* fixkey(char* s){
  int i, j;
  char plain[26]; // assume key < length of alphabet, local array on stack, will go away!

  for(i = 0, j = 0; i < strlen(s); i++){
    if(isalpha(s[i])){
      plain[j++] = upcase(s[i]);
    }
  }
  plain[j] = '\0';
  return strcpy(s, plain);
}

void buildtable (char* key, char* encode){
  int length = strlen(key);
  //printf("first: %s\n", key);
  fixkey(key); // fix the key, i.e., uppercase and remove whitespace and punctuation
  //printf("second: %s\n", key);
  for(int k = 0; k < strlen(key); k++){
      for(int l = k+1; l < strlen(key); l++){
          if(key[k] == key[l]){
              key[l] = '-';
          }
      }
  }
  //printf("third: %s\n", key);
  fixkey(key);
  //printf("fourth: %s\n", key);
  int index = length -1;
  int indexOfKey = 0;
  char next = key[strlen(key)-1];
  for(int i = 0; i < 26; i++){
      encode[index] = key[indexOfKey];
      index++;
      indexOfKey++;
      if(index == 26){// if index reach the end of the array, set the index to the start
          index = 0;
      }
      if(indexOfKey == strlen(key)){// all char in key has already been place into encode array
          break;
      }
  }
  // for keep going to fill up the encode array
  for(int j = 0; j < 26-strlen(key); j++){
      next = next + 1;
      if(next > 90){
          next = 'A';
      }
      // for checking repreated char
      for(int m = 0; m < length; m++){
          if(key[m] == next){
              next += 1;
              m = -1;
          }
      }
      // put into the encode table
      encode[index++] = next;
      // reach to the end, back to the start
      if(index == 26){
          index = 0;
      }
  }
}

int main(int argc, char **argv){

  // first allocate some space for our translation table.

  char* encode = (char*)malloc(sizeof(char)*27);
  encode[26] = '\0';
  char ch;

  if(argc != 2){
    printf("format is: '%s' key", argv[0]);
    exit(1);
  }

  // Build translation tables, and ensure key is upcased and alpha chars only.

  buildtable(argv[1], encode);

  // write the key to stderr (so it doesn't break our pipes)

  fprintf(stderr,"key: %s - %d\n", encode, strlen(encode));

  // the following code does the translations.  Characters are read
  // one-by-one from stdin, translated and written to stdout.

  ch = fgetc(stdin);
  while (!feof(stdin)) {
    if(isalpha(ch)){        // only encrypt alpha chars
      ch = upcase(ch);      // make it uppercase
      fputc(encode[ch-'A'], stdout);
    }else
      fputc(ch, stdout);
    ch = fgetc(stdin);      // get next char from stdin
  }
}
