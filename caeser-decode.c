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


int in(char c, char* s, int pos){
  // Assume everything is already in the same case
  int i;

  for(i = 0; i < pos; i++)
    if(c == s[i]) return 1;

  return 0;
}


void buildtable (char* key, char* decode){ // this changed from encode

  int length = strlen(key);
  fixkey(key); // fix the key, i.e., uppercase and remove whitespace and punctuation
  for(int k = 0; k < strlen(key); k++){
      for(int l = k+1; l < strlen(key); l++){
          if(key[k] == key[l]){
              key[l] = '-';
          }
      }
  }
  fixkey(key);
  char* encode = (char*)malloc(sizeof(char)*26);
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
      for(int m = 0; m < length; m++){
          if(key[m] == next){
              next += 1;
              m = 0;
          }
      }
      encode[index++] = next;
      if(index == 26){
          index = 0;
      }
  }
  // building up the original alphabet array
  char* alphabet = (char*)malloc(sizeof(char)*26);
  char firstChar = 'A';
  for(int a = 0; a < 26; a++){
      alphabet[a] = firstChar;
      firstChar += 1;
  }
  // using two for loops to generate the decode array from the encode array
  char inputChar = 'A';
  for(int q = 0; q < 26; q++){
      for(int p = 0; p < 26; p++){
          if(encode[p] == inputChar){
              decode[q] = alphabet[p];
              break;
          }
      }
      inputChar += 1;
  }


}

int main(int argc, char **argv){

  // first allocate some space for our translation table.

  char* decode = (char*)malloc(sizeof(char)*26); // this changed from encode
  char ch;

  if(argc != 2){
    fprintf(stderr,"format is: '%s' key", argv[0]);
    exit(1);
  }

  // Build translation tables, and ensure key is upcased and alpha chars only.

  buildtable(argv[1], decode); // this changed from encode

  // write the key to stderr (so it doesn't break our pipes)

  fprintf(stderr,"key: %s - %d\n", decode, strlen(decode));


  // the following code does the translations.  Characters are read
  // one-by-one from stdin, translated and written to stdout.

    ch = fgetc(stdin);
    while (!feof(stdin)) {
      if(isalpha(ch))          // only decrypt alpha chars
	fputc(decode[ch-'A'], stdout);
     else
	fputc(ch, stdout);
      ch = fgetc(stdin);      // get next char from stdin
    }
}
