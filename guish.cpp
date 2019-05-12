//*********************************************************
//
// MEHMET OZKAN
// Foundation of Operating Systems
// Project #1: New Island Shell - Writing Your Own Shell
// October 11, 2017
// Instructor: Dr. Ajay K. Katangur
//*********************************************************


//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <cstdlib>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <ctime>
#include <fcntl.h>


//*********************************************************
//
// Extern Declarations
//
//*********************************************************
using namespace std;




extern "C"
{
  extern char **gettoks();
} 

int cc_counter=0;
int quit_counter=0;
int stop_counter=0;

//********************************************************************
//
// Ctrl C Handling Function
//
// This function performs handling SIGINT signal and counts how many times occured.
// In this purpose, pointer based multi-dimensional array used to show history of the commands.
//
// Value Parameters
// ----------------
// signo	int		Number of signal 
//
// Local Variables
// ---------------
// cc_counter  int	Counter of SIGINT interrupts


void cc_handler( int signo )
{
  	
  cc_counter++;
 
 
}

//********************************************************************
//
// Ctrl \ Handling Function
//
// This function performs handling SIGQUIT signal and counts how many times occured.
// In this purpose, pointer based multi-dimensional array used to show history of the commands.
//
// Value Parameters
// ----------------
// signo	int		Number of signal 
//
// Local Variables
// ---------------
// quit_counter  int	Counter of SIGQUIT interrupts

void quit_handler( int signo )
{
	
  quit_counter++;
   
}

//********************************************************************
//
// Ctrl C Handling Function
//
// This function performs handling SIGTSTP signal and counts how many times occured.
// In this purpose, pointer based multi-dimensional array used to show history of the commands.
//
// Value Parameters
// ----------------
// signo	int			Number of signal 
//
// Local Variables
// ---------------
// stop_counter  int	Counter of SIGTSTP interrupts

void stop_handler( int signo )
{
  stop_counter++;
  
  
}

//********************************************************************
//
// Displaying History Function
//
// This function performs displaying the last 10 commands from user when typing "hist".
// In this purpose, pointer based multi-dimensional array used to show history of the commands.
//
// Value Parameters
// ----------------
// history[] char	pointer based array to show history of the commands 
//
// Local Variables
// ---------------
// i		int		History index variable
// j 		int		Commands's character variable
// k		int		Commands's string variable
//
//*******************************************************************

void showhist(char** history[]) 
{
	cout<<"****History of last 10 commands by user****"<<endl;
	
  for (int i = 0; history[i] != NULL && i<10;i++)
	{
    cout << "Mr.Command"<<"[" << i<<"]" << ":";
	
    for (int j = 0; history[i][j] != NULL; j++)
	{
      if (j > 0)
	  {
        cout << " ";
      }
      for (int k = 0; history[i][j][k] != NULL; k++)
	  {
        cout << history[i][j][k];
      }
    }
    cout << endl;
  }
}



//********************************************************************
//
// History Adding Function
//
// This function performs adding last 10 commands from user into history array.
// In this purpose, pointer based multi-dimensional array used to store the commands.
//
// Value Parameters
// ----------------
// history[]	char	pointer based array to store commands
// 
// Reference Parameters
// --------------------
// cmnds    char     The location of the commands
//
// Local Variables
// ---------------
// index	   int		 History index variable
// stringsize  int		 Commands's string variable
// chrctrsize  int		 Commands's character variable
//
//*******************************************************************

void historyadding(char** history[], char** &cmnds)
{
	int index = 0;
	int stringsize = 0;
	int chrctrsize = 0; 
	
	  if (history[9] != NULL)
	  {
		for(int i = 0; i<9; i++)			
		{
		history[i]=history[i+1];
		}
	  }
	 
	  history[9]=NULL;
	  
	  while (history[index] != NULL)
	  {
		index++; 
	  }
	 	  
	  while (cmnds[stringsize] != NULL)
		  
	  stringsize++;
	  stringsize += 1;
	  history[index] = new char* [stringsize];
	  
	  for (int i = 0; i <stringsize; i++)
	  {
		if (i == stringsize - 1)
		{
		  history[index][i] = NULL;
		}
		else
		{
		 
		 while (cmnds[i][chrctrsize] != NULL)
			  
		chrctrsize++;
		chrctrsize += 1;
		history[index][i] = new char [chrctrsize];
		  
		for (int j = 0; j <chrctrsize; j++)
		  {
			history[index][i][j] = cmnds[i][j];
		  }
		}
	  }
	  
	  
	  
}

//*********************************************************
//
// Main Function
//
//*********************************************************
int main( int argc, char *argv[] )
{
		
	//local variables
	int ii;
	char **toks;
	char** history[10];
	int retval;
	int indxlast;
	int histindx;
	
	//******Time variables to get time******//
	time_t now = time(0);
	char* dt = ctime(&now);
        
     
	//initialize local variables
	ii = 0;
	toks = NULL;
	retval = 0;
	indxlast = 0;
	
//*****Initializing the history[i] array***//
	for (int i=0; i <10; i++)
	 {
		history[i] = NULL;
	 }
  
//******Signal Handling and calling the handler functions for each signals******//
	signal( SIGINT, cc_handler);
	signal( SIGQUIT, quit_handler);
	signal( SIGTSTP, stop_handler);
	  
	  
	 
// main (infinite) loop
     while( true )
{
//******Time variables to get current time******//

	 time_t now = time(0);
	 char* dt = ctime(&now);
	 
	 cout<<"[By.MehmetOzkan][Type your command and hit enter]"<<dt<<"->";
	 
	 toks = gettoks();
	  
	 if( toks[0] != NULL)
{
	 
//********************************************************************
// Implementation of the history while getting commands from the user 
//
// Saving the commands in the history array and, calling the historyadding and showhist functions to print history
//
// Local Variables
// ---------------
// indxlast     int		Last index number in history array
// histindx		int		Index of history array
 
//******When user types "r ", assign the index of the history to last command from the user before "r"****** 
      while (!strcmp( toks[0], "r" ))
	  {
        if (toks[1] == NULL)
		{
          
          while(history[indxlast] != NULL && indxlast <10)
		{
            indxlast++;
        }
          indxlast--;
          if (indxlast >= 0)
		  {
            toks = history[indxlast];
          }
        }
        else
		{
			
//******When user types "r n(number)", assign the index of n to index of the history for tracking last nth commands******

       if(toks[1][1] == NULL)
		{
           
		   histindx = (int)(toks[1][0] - '0');  //*******module %10 doesn't work proparly and then using ASCI table gave a good result********
			
			if (histindx >= 0 && histindx < 10)
		{
            if (history[histindx] != NULL)
			{
			toks = history[histindx];
			}
            else
			{
            perror("Please try another history index"); //****If there isn't any command with specific nth number in the history, type accurate index.
            break;
			}
        }
            else
		{
              
            perror("Please try another history index"); //*******If the number of nth command is other than a number [0,9], type accurate index.
            break;
        }
        }
          else									 //*******If the number of nth command is more than one digit, gives error to the user to retype accurate index.
		{
		    perror("Please try another history index between [0,9]");
            break;
        }
        }
			
		}

      if (!strcmp( toks[0], "r" ) )
	  {
		 
        continue;
	  }
	   
//******If the command is "hist", add "hist" command in the history and call the showhist function to display the history******//
 
      else if(!strcmp( toks[0], "hist" ) )
	  {
			historyadding(history, toks); //Firstly save hist command in history
			showhist(history);			  //Display history with last command of "hist"
      }
	  
	  else
	  {
        historyadding(history, toks);
		
//******If the command is "exit", terminate the program and print how many times interrupts occured from SIGINT,SIGQUIT and SIGTSTP signals******//	
	
		if(!strcmp( toks[0], "exit" ))
	  {
		  
		  cout << "Control C received: " <<cc_counter<< endl;
		  cout << "Control / received: " <<quit_counter<< endl; 
		  cout << "Control Z received: " <<stop_counter<< endl; 
		  
		exit(0);
		
	  } 
	  }
	  
}	

//*********Creating Fork() function to create a process*******//  
	    
		pid_t pid, wpid;
	    int status; 
		pid = fork();
		

			
//********************************************************************
// I/O Redirection Procedure
//
// This procedure performs replacing standard input with input file and standard output with output file
// by finding where '<' or '>' occurs in the command by user.In this purpose, dup2() functions are used in each I/O redirections.
//
// Local Variables
// ---------------
// fd1  int		File descriptor
// fd2	int		File descriptor
// jj	int		Tokens increment

//*******Creating process when the pid is 0 **********////////////
	    if (pid == 0) 
		{

int fd1,fd2;
        
    for(int jj=0;toks[jj]!=NULL;jj++)
    {
		
		if(!strcmp(toks[jj],">"))
        {      
            
            fd2 = open(toks[jj+1] , O_WRONLY | O_CREAT| O_APPEND, 0777);
			           
                
			 dup2(fd2, 1); 
			 toks[jj+1]=NULL;
			 toks[jj]=NULL;
			 close(fd2);
        }  
	}
	for(int jj=0;toks[jj]!=NULL;jj++){
		
        if(!strcmp(toks[jj],"<"))
        {     
			
            fd1 = open(toks[jj+1], O_RDONLY);
		
			dup2(fd1, 0);		
			toks[jj+1]=NULL;
			toks[jj]=NULL;
			close(fd1);
			
        }               

     }     
	 
//*****Execute process after the child process and then exit*****///    
    	execvp(*toks,toks);
		perror("execvp");
		exit(EXIT_FAILURE);
		
		
	     } 
		 else if (pid < 0) 
		 {
			 printf("fork() failed!\n");
			exit(1);
		
	     } 
////*****Parent Process to wait child process terminate and get status of child process***////
		 else  
		{
		  while (!(wait(&status) == pid)) ; 
		
		}
		
		

     

  // return to calling environment
}
		return( retval );
}
  
  

	

  
  
  

  



