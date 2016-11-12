//stdio functions to replace: getc, fprintf, printf                                                                                                                                                       


#include <stdio.h>
#include <stdlib.h> //for qsort, malloc, realloc, free                                                                                                                                                    

//Create global variable to keep track                                                                                                                                                                    
int comparisons = 0;

/*                                                                                                                                                                                                        
The function frobcmp returns a negative value if a is smaller than b,                                                                                                                                     
a positive if a is bigger than b, and 0 if a and b are equal strings                                                                                                                                      
*/
int frobcmp(char const * a, char const * b)
{
  int i = 0;
  for (; a[i] != ' ' && b[i] != ' '; i++)
    {
      if ((a[i]^42) < (b[i]^42)) //a's current char is lesser than b's                                                                                                                                    
        {
          return -1;
        }

      else if ((a[i]^42) > (b[i]^42)) //a's current char is greater than b's                                                                                                                              
        {
          return 1;
        }
    }

  if(a[i] == ' '  && b[i] == ' ')
    {
      return 0;
    }
  else if (a[i] == ' ')
    {
      return -1;
    }
  else
    {
      return 1;
    }

}

int compr(void const * x, void const * y)
{
  comparisons++; 
  const char* a = *(const char **) x;
  const char* b = *(const char **) y;
  return frobcmp(a, b); 
}

//MAIN FUNCTION                                                                                                                                                                                           
int main ()
{
    
  //char c = getc(stdin);
  int wordMem = 1;
  int listMem = 1;
  size_t numChars = 0;
  size_t numWords = 0;
  char* word = NULL;
  char** wordList = NULL;
  char* fileSpace;
  
  //Use fstat to check if stdin is a file. If it is, allocate enough memory to hold the entire file. 
  //If the file has grown by the time you reach the end of this allocated memory, we allocate more memory just like in assignment 5.
  //Essentially, instead of starting by allocating some arbitrary amount of memory, start by allocating the size of the file. 
  //Then everything else stays the same.
  
  struct stat buf;
  const int STDIN_NUM = 0;
  
  //if fstat fails, quit
  if(fstat(STDIN_NUM, &buf) < 0)
    {
      fprintf(stderr, "sfrobu: fstat error");
      exit(1);
     }
   
   //otherwise, check if we're getting a regular file as input
   else if(S_ISREG(buf.std_mode))
    {
      fileSpace = (char*)malloc(buf.st_size * sizeof(char));
      if(read(0, fileSpace, buf.st_size) > 0)
        {
          for(size_t i=0; i < buf.st_size; i++)
          {
          }
        }
     }
  

  //a big outer loop to stay inside our file's bounds                                                                                                                                                     
  while (c != EOF)
    {
      if (word == NULL)
        {
          word = malloc(sizeof(char)*wordMem);
        }

      //store the first char from the file inside our individual word array                                                                                                                               
      word[numChars] = c;

      numChars++; //mark that we've added a char to the individual word                                                                                                                                   

      //if we've reached end of a word, store the word we just created into the list                                                                                                                      
      if (c == ' ')
        {
          //if this list is still empty, allocate memory for the incoming word FIRST                                                                                                                      
          if (wordList == NULL)
            wordList = malloc(sizeof(char*)*listMem);

          //store the newly minted word                                                                                                                                                                   
          wordList[numWords] = word;
          word = NULL; //ready to start a new word                                                                                                                                                        

          //reset                                                                                                                                                                                         
          numChars = 0;
          
          //acknowledge that we have another word                                                                                                                                                         
          numWords++;

          c = getc(stdin);

          //reset                                                                                                                                                                                         
          numChars = 0;
          wordMem = 1;
          continue;

        }

      //allocate fewer times by increasing memory  exponentially                                                                                                                                          
      if (numChars == wordMem)
       {
          wordMem *= 2;
          word = realloc(word, sizeof(char)*wordMem);
        }

      //now, grab the next char in the file and store in variable c                                                                                                                                       
      c = getc(stdin);


      if (numWords == listMem)
        {
          listMem *= 2;
          wordList = realloc(wordList, sizeof(char*)*listMem);
        }

      //if we've reached end of file, get outta here                                                                                                                                                      
      if (c == EOF && word != NULL)
        {
          word[numChars] = ' ';
          wordList[numWords] = word;
          word = NULL;
        }
    }


  //SORT the list    
    //because numWords is index in wordlist, add by 1                                                                                                                                                       
  qsort(wordList, numWords+1, sizeof(char*), compr);

  //Free memory taken up by the words AS YOU PRINT them to the screen                                                                                                                                     
  int freedomIndex = 0;
  for(; freedomIndex < numWords+1; freedomIndex++)
    {
      printf(wordList[freedomIndex]);
      free(wordList[freedomIndex]);
    }

  free(wordList);
  
  //if successful, print 
  fprintf(stderr, "Comparisons: %d\n", comparison);
  return 0;
}
