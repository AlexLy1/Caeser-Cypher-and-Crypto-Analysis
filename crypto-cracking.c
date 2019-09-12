#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TEXT_SIZE 200000  // Note, the longer the text the more likely you will get a good 'decode' from the start.
#define ALEN 26         // Number of chars in ENGLISH alphabet
#define CHFREQ "ETAONRISHDLFCMUGYPWBVKJXQZ" // Characters in order of appearance in English documents.
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

char upcase(char ch){
  if(islower(ch))
    ch -= 'a' - 'A';
  return ch;
}

void splitText(int, char*, char**);
char mapping(char*, char);
void frequencyAnalysis(char*, char*);



int main(int argc, char **argv){

  // first allocate some space for our input text (we will read from stdin).

  char* text = (char*)malloc(sizeof(char)*TEXT_SIZE+1);
  char ch;
  int n, i;

  if(argc > 1 && (n = atoi(argv[1])) > 0); else{ fprintf(stderr,"Malformed argument, use: crack [n], n > 0\n"); exit(-1);} // get the command line argument n

  // Now read TEXT_SIZE or feof worth of characters (whichever is smaller) and convert to uppercase as we do it.
  // Added: changed to count frequencies as we read it in

  for(i = 0, ch = fgetc(stdin); i < TEXT_SIZE && !feof(stdin); i++, ch = fgetc(stdin)){
    text[i] = (ch = (isalpha(ch)?upcase(ch):ch));
  }
  text[i] = '\0'; // terminate the string properly.

  for(int keyLen = 1; keyLen <= n; keyLen++){
    //for(int keyLen = 1; keyLen <= n; keyLen++){
      if(keyLen == 1){
        char* freOrder = malloc(sizeof(char)*26);
        // freOrder stores the frequency of this texts
        frequencyAnalysis(text, freOrder);
        char* output = malloc(sizeof(char)*TEXT_SIZE + 1);
          printf("order: %s\n", freOrder);
        for(int i = 0; i < strlen(text); i++){
          char c = mapping(freOrder, text[i]);
          fprintf(stdout, "%c", c);
        }
      }
      else{
        // allocate space for splitedText 2D array
        char** splitedText = (char**)malloc(sizeof(char*)*keyLen);
        for(int i = 0; i < keyLen; i++){
          splitedText[i] = (char*)malloc(sizeof(char)*(TEXT_SIZE/keyLen) + 1);
        }
        // allocate space for output text 2D array
        char** outText = (char**)malloc(sizeof(char*)*keyLen);
        for(int i = 0; i < keyLen; i++){
          outText[i] = (char*)malloc(sizeof(char)*(TEXT_SIZE/keyLen) + 1);
        }
        // split the text to corresponding number of subtext
        splitText(keyLen, text, splitedText);
        for(int row = 0; row < keyLen; row++){
          char* freOrder = malloc(sizeof(char)*26);
            // apply frequency analysis on each sub text
          frequencyAnalysis(splitedText[row], freOrder);
          for(int col = 0; col < strlen(splitedText[row]); col++){
              // change the mapping with the english orginal char then put them into output text
            char c = mapping(freOrder, splitedText[row][col]);
            outText[row][col] = c;
          }
        }
        //merge and output 
        int row = 0;
        int col = 0;
        for(int i = 0; i < strlen(text); i++){
          fprintf(stdout, "%c", outText[row][col]);
          row++;
          if(row == keyLen){
            row = 0;
            col++;
          }
        }
      }
  }

  return 0;
}

char mapping(char* frequency, char c){
  if(!isalpha(c)){
    return c;
  }
  int index = 0;
  for(int i = 0; i < 26; i++){
    if(c == frequency[i]){
      index = i;
      break;
    }
  }
  return CHFREQ[index];
}

// for spliting the test according to the possible key length
void splitText(int n, char* text, char** splitText){
  int trackIndex = 0;
  int inputIndex = 0;
  for(int j = 0; j < strlen(text); j++){
    splitText[trackIndex][inputIndex] = text[j];
    trackIndex++;
    if(trackIndex == n){
      trackIndex = 0;
      inputIndex++;
    }
  }
}

void frequencyAnalysis(char* text, char* order){
  // get frequency of this text
  int frequency[26];
  for(int i = 0; i < 26; i++){
    frequency[i] = 0;
  }
  for(int i = 0; i < strlen(text); i++){
    for(int j = 0; j < 26; j++){
      if(isalpha(text[i]) && text[i] == ALPHABET[j]){
        frequency[j]++;
        break;
      }
    }
  }

  for(int i = 0; i < 26; i++){
    int maxIndex = i;
    for(int j = 0; j < 26; j++){
      if(frequency[j] > frequency[maxIndex]){
        maxIndex = j;
      }
    }
      printf("char: %c frequency: %d\n", ALPHABET[maxIndex], frequency[maxIndex]);
    order[i] = ALPHABET[maxIndex];
    frequency[maxIndex] = -1;
  }
}
