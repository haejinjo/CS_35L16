//This version of tr takes buffered input and output                                                                      

#include <stdio.h>
#include <string.h>


int containsDuplicates(char* cstr)
{
  //create an array to represent a comprehensive chart of ASCII chars                                                     
  //initialize all spaces to 0 aka false                                                                                  
  int asciiHash[256] = {0};

  //looping through the cstring argument once makes efficiency O(N)!!! <3                                                 
  int i = 0;
  int charNum = 0;
  for(; i < strlen(cstr); i++)
    {
      charNum = cstr[i]; //automatically translates char to its ascii representation when stored in int                   

      //if this particular char has already been marked in our rudimentary hash table...                                  
      if (asciiHash[charNum] != 0)
        {
          //return true, it contains duplicates                                                                           
          return 1;
        }

      else
        asciiHash[charNum] = 1; //mark that we've "seen" this current char already                                        
    }

  //saw no duplicates in this cstring                                                                                     
  return 0;

}


//TRANSLATOR FUNCTION IMPLEMENTATION                                                                                      
char translator(char in, char* from, char* to)
{
  int i = 0;
  for (; i < strlen(from); i++)
    {

      //if input char is a match with this char in the first argument                                                     
      //overwrite it to the appropro char from the second argument                                                        
      if (in == from[i])
        {
          return to[i]; //return translated char                                                                          
        }
   }

  //if no translation took place, just return the original char                                                           
      return in;
}

//MAIN FUNCTION                                                                                                           
int main (int argc, char* argv[])
{
  if (argc == 0) //tell user THEY NEED OPERANDS                                                                           
    {
      fprintf(stderr,  "tr2b: missing operands");
      return 1;
    }
  else if (argc > 3) //tell user which operand is the first to violate the acceptable number                              
    {
      fprintf(stderr, "%s %s %s",  "tr2b: extra operand `", argv[3], "'\n");
      return 1;
    }
  else if (argc == 2) //tell user they forgot an operand after the last one entered                                       
    {
      fprintf(stderr, "%s %s %s", "tr2b: missing operand after `", argv[1], "'\n");
      return 1;
    }
  else if (strlen(argv[1]) != strlen(argv[2]))
    {
fprintf(stderr, "%s", "tr2b: operands must be byte strings of the same length\n");
      return 1;
    }
  else if (containsDuplicates(argv[1])) //only concerned with the "from" argument                                         
    {
      fprintf(stderr, "%s", "tr2b: first operand must not contain duplicate bytes\n");
    }

char input_char = getchar();
char output_char;
  //loop through each char in the given file, break out once we reach the end                                             
  while(input_char != EOF)
    {
      output_char = translator(input_char, argv[1], argv[2]);
      putchar(output_char);
      input_char = getchar();
    }

  return 0;
}
