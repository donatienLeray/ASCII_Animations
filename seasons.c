//Author @Dodo
#include <stdio.h>
#include <stdlib.h>
//needed for sleep()
#include <unistd.h>
//needed for mssleep()
#include <time.h>//also needed for getSeason()
#include <errno.h> 
//neede for waitpid() 
#include  <sys/types.h>
#include <sys/wait.h>
//for strcmp
#include <string.h>
 
int getSeason();
int mssleep(long);
void clear();

int winter(int i);
int spring(int i);
int summer(int i);
int autumn(int i);

int color=1;//color flag


int main(int argc, char *argv[]) {

    if (argc == 2)//argument exists
    {
        if (strcmp(argv[1],"-bw") == 0) color = 0;//if argument is -bw set color flag to false
    }

    int season = getSeason();//set season to current season
    int i= 0;// frame index
    int forkexists = 0;//fork flag = false
    int p;//fork

    //infinit for loop
    for(;;){

        //fork the programm if no fork exist
        // so we can have one process drawing th image and the other one looking for user input
        if (!forkexists)
        {
          p = fork(); 
          forkexists = 1;//set fork flag to true 
        }
        
        if (p == 0)// We're the child process
        {
            //return if user press enter
            if (getchar() == '\n') return 0;

        }
        else if (p > 0)// We're the parent process
        {
            switch (season)
            {
                case 0://WINTER
                    winter(i);//print frame i
                    i=(i+1)%7;//loop to next frame index
                    break;
                case 1://SPRING
                    spring(i);
                    i=(i+1)%15;
                    break;
                case 2://SUMMER
                    summer(i);
                    i=(i+1)%21;
                    break;
                case 3://AUTUMN
                    autumn(i);
                    i=(i+1)%7;
                    break;

                default:
                    break;
            }
            
        }
        else// We're the parent process, but child couldn't be created
        {
            return 1;
        }

        int wstatus;
        //if child processed ended becuase user pressed enter
        if (waitpid(0, &wstatus, WNOHANG))//WNOHANG is to not suspend execution of the thread if status is not immediately available
        {
            season = (season+1)%4;//loop to next season
            forkexists = 0;//set fork flag to false
            i= 0;//set frame idex to 0
        }   
        
    }

    return 0;

}

//returens for int corresponding to the current season: 0 for Winter, 1 for Spring, 2 for Summer and 3 for Autumn
int getSeason() {
    time_t t = time(NULL); //get current sysem time
    struct tm tm = *localtime(&t); 
    float value = (float)tm.tm_mon+1 + ((float)tm.tm_mday / 100);  // <month>.<day(2 digit)>    
    if (value < 3.21 || value >= 12.22) return 0;   // Winter
    if (value < 6.21) return 1; // Spring
    if (value < 9.23) return 2; // Summer
    return 3;   // Autumn
}

//Sleep for the requested number of milliseconds.
int mssleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}


// clears the terminal and reset colors
void clear() {
    printf("\x1b[0m");
    printf("\x1b[2J");
    printf("\x1b[H");
}

//formats and prints the asci txt files to the console
int printFile(char* filename){

    FILE *fptr;
    char c;

    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
            printf("Cannot open file \n");
            exit(0);
    }

    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {    
        
        if (color) //if color flag is true use color codes
        {
            switch (c)
            {
            case 'B': printf("\x1b[34m"); break;//Blue
            case 'b': printf("\x1b[94m"); break;//light blue
            case 'P': printf("\x1b[35m"); break;//Puple
            case 'G': printf("\x1b[32m"); break;//Green
            case 'g': printf("\x1b[92m"); break;//light Green
            case 'Y': printf("\x1b[93m"); break;//Yellow
            case 'S': printf("\x1b[90m"); break;//Grey
            case 'W': printf("\x1b[37m"); break;//White
            case 'O': printf("\x1b[33m"); break;//Orange
            case 'R': printf("\x1b[91m"); break;//RED
            case 'K': printf("\x1b[37m*"); break;//SNOWFLAKE
	        default: printf("%c",c); break;//print character
            }
        }
        else //if color flag is false rest colors
        {
            switch (c)
            {
            case 'B': printf("\e[m"); break;
            case 'b': printf("\e[m"); break;
            case 'P': printf("\e[m"); break;
            case 'G': printf("\e[m"); break;
            case 'g': printf("\e[m"); break; 
            case 'Y': printf("\e[m"); break;
            case 'S': printf("\e[m"); break;
            case 'W': printf("\e[m"); break;
            case 'O': printf("\e[m"); break;
            case 'R': printf("\e[m"); break;
            case '-': printf("\e[m "); break;
            case 'K': printf("\e[m*"); break;//SNOWFLAKE
	        default: printf("%c",c); break;//print character
            }
        }   
        
            c = fgetc(fptr);
    }
    printf("\x1b[0m");//reset colors
    fclose(fptr);
    return 0;
}

//printout the right frame for the winter animation 
int winter(int i){
    
    clear();
    switch(i)//showing frame according to frame indicator i
    {
	    case 0:  printFile("ASCII_ARTS/winter/01.txt"); break;
	    case 1:  printFile("ASCII_ARTS/winter/02.txt"); break;
	    case 2:  printFile("ASCII_ARTS/winter/03.txt"); break;
        case 3:  printFile("ASCII_ARTS/winter/04.txt"); break;
        case 4:  printFile("ASCII_ARTS/winter/05.txt"); break;
        case 5:  printFile("ASCII_ARTS/winter/06.txt"); break;
        case 6:  printFile("ASCII_ARTS/winter/07.txt"); break;
	    default: printf("wrong i"); break;
    }
    mssleep(400);//time (ms) one frame is shown 
    return 0;

} 

int spring(int i){

    clear();
    switch(i) 
    {
	    case 0:  printFile("ASCII_ARTS/spring/01.txt"); break;
        /*
	    case 1:  printFile("ASCII_ARTS/spring/02.txt"); break;
	    case 2:  printFile("ASCII_ARTS/spring/03.txt"); break;
        case 3:  printFile("ASCII_ARTS/spring/04.txt"); break;
        case 4:  printFile("ASCII_ARTS/spring/05.txt"); break;
        case 5:  printFile("ASCII_ARTS/spring/06.txt"); break;
        case 6:  printFile("ASCII_ARTS/spring/07.txt"); break;
        case 7:  printFile("ASCII_ARTS/spring/08.txt"); break;
        case 8:  printFile("ASCII_ARTS/spring/09.txt"); break;
        case 9:  printFile("ASCII_ARTS/spring/10.txt"); break;
        case 10: printFile("ASCII_ARTS/spring/11.txt"); break;
        case 11: printFile("ASCII_ARTS/spring/12.txt"); break;
        case 12: printFile("ASCII_ARTS/spring/13.txt"); break;
        case 13: printFile("ASCII_ARTS/spring/14.txt"); break;
        case 14: printFile("ASCII_ARTS/spring/01.txt"); break;
        */
	    default: printf("wrong i"); break;
    }
    
    mssleep(1000); 
    return 0;
}

int summer(int i){

    clear();
    switch(i) 
    {
	    case 0:  printFile("ASCII_ARTS/summer/01.txt"); break;
	    case 1:  printFile("ASCII_ARTS/summer/02.txt"); break;
	    case 2:  printFile("ASCII_ARTS/summer/03.txt"); break;
        case 3:  printFile("ASCII_ARTS/summer/04.txt"); break;
        case 4:  printFile("ASCII_ARTS/summer/05.txt"); break;
        case 5:  printFile("ASCII_ARTS/summer/06.txt"); break;
        case 6:  printFile("ASCII_ARTS/summer/07.txt"); break;
        case 7:  printFile("ASCII_ARTS/summer/08.txt"); break;
        case 8:  printFile("ASCII_ARTS/summer/09.txt"); break;
        case 9:  printFile("ASCII_ARTS/summer/10.txt"); break;
        case 10: printFile("ASCII_ARTS/summer/11.txt"); break;
        case 11: printFile("ASCII_ARTS/summer/12.txt"); break;
        case 12: printFile("ASCII_ARTS/summer/13.txt"); break;
        case 13: printFile("ASCII_ARTS/summer/14.txt"); break;
        case 14: printFile("ASCII_ARTS/summer/15.txt"); break;
        case 15: printFile("ASCII_ARTS/summer/01.txt"); break;
        case 16: printFile("ASCII_ARTS/summer/16.txt"); break;
        case 17: printFile("ASCII_ARTS/summer/15.txt"); break;
        case 18: printFile("ASCII_ARTS/summer/01.txt"); break;
        case 19: printFile("ASCII_ARTS/summer/16.txt"); break;
        case 20: printFile("ASCII_ARTS/summer/15.txt"); break;
	    default: printf("wrong i"); break;
    }
    mssleep(700); 
    return 0;
    
}

int autumn(int i){

    clear();
    switch(i) 
    {
	    case 0:  printFile("ASCII_ARTS/autumn/01.txt"); break;
        /*
	    case 1:  printFile("ASCII_ARTS/autumn/02.txt"); break;
	    case 2:  printFile("ASCII_ARTS/autumn/03.txt"); break;
        case 3:  printFile("ASCII_ARTS/autumn/04.txt"); break;
        case 4:  printFile("ASCII_ARTS/autumn/05.txt"); break;
        case 5:  printFile("ASCII_ARTS/autumn/06.txt"); break;
        case 6:  printFile("ASCII_ARTS/autumn/07.txt"); break;
        case 7:  printFile("ASCII_ARTS/autumn/08.txt"); break;
        case 8:  printFile("ASCII_ARTS/autumn/09.txt"); break;
        case 9:  printFile("ASCII_ARTS/autumn/10.txt"); break;
        case 10: printFile("ASCII_ARTS/autumn/11.txt"); break;
        case 11: printFile("ASCII_ARTS/autumn/12.txt"); break;
        case 12: printFile("ASCII_ARTS/autumn/13.txt"); break;
        case 13: printFile("ASCII_ARTS/autumn/14.txt"); break;
        case 14: printFile("ASCII_ARTS/autumn/01.txt"); break;
        */
	    default: printf("wrong i"); break;
    }
    mssleep(1000); 
    return 0;
    
}