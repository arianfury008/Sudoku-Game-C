/* Sudoku Game program with C */

/* TEAM MEMEBERS:
 * Arian khatiban
 * Zahra mahmoodi
*/


/* Reference:
 * Sudoku Programming With C book by Giulio Zambon
 * Sudoku : https://en.wikipedia.org/wiki/Sudoku
 * https://www.tutorialspoint.com/
*/

/* Project Information:
 * registration and login
 * Share
 * Menu
 * Helper
 * Timer
 * Solve Sudoku
 * Score And High Score
 * Level
 * reset
 * RealTime checking
 * Exit
*/



// Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// our method for sudoku
int login ();
void registration (void);
int menu();
int solved_sudoku(int *board[36][36], int solutions);
int checking_invalid_numbers(int *copy[36][36], int row, int col);
void printboard(int *board[36][36]);

// struct for our player data
struct loginStruct
{
    char name[30];
    char username[30];
    char password[20];
    int Score;
    int HighestScore;
    int CurrentLevel;
};


//Note: We can use system("ClS") if we use External Terminal (above Clion Check External Terminal Then every where I used this method Replace it With system("ClS")) :
//but Clion "system("ClS")" Doesn't work beacuse that I Wrote this method !
void clearscr ( void )
{
    for ( int i = 0; i < 50; i++ ) // 50 is arbitrary
        printf("\n");
}

// Proprities
// we use pointer below
int *dataTables[36][36];
int *temporary2[36][36];

int sudoku_borad_row = 9, column_board = 9, nonetsize = 3; // Row 9 Column 9 : 9*9
int row, col;
int currentLevel;

/* main function and others functions */
int main(){

    int option;
    printf("\n\nTEAM MEMEBERS : Arian khatiban , Zahra mahmoodi\n\n");
    printf("Press '1' to Register\nPress '2' to Login\n\n");
    scanf("%d",&option);
    getchar();           // catching newline.
    while(option != 1 && option != 2){
        printf("Press '1' to Register\nPress '2' to Login\n\n");
        scanf("%d",&option);
        getchar();
    }
    if(option == 1)
    {
        registration();
    }

    else if(option == 2)
    {
        int lo = login();
        while(lo == 0){
            lo = login();
        }
    }

    // Game Started !!!
    option = menu();
    while (option == 0){
        option = menu();
    }
    if(option == 1) {
        // Now You Enter The Sudoku Level
        clearscr();
        char command[80];
        int i, j, k, invalidNumber; // for check our situation
        int num1, num2, num3, temporary;


        for (row = 0; row < 36; row++)
            for (col = 0; col < 36; col++)
                dataTables[row][col] = 0;

        getchar();
        clock_t start = clock();
        start = clock();
        while(1) // Infinite loop
        {
            clock_t end = clock();
            float seconds = (float)(end - start) / CLOCKS_PER_SEC;
             // Level 1
            if(currentLevel == 1){
                dataTables[2][2] = 3;
                dataTables[4][4] = 8;
                dataTables[8][1] = 2;
            }
            // Level 2
            if(currentLevel == 2){
                dataTables[2][2] = 3;
                dataTables[4][5] = 8;
                dataTables[8][1] = 2;
                dataTables[8][4] = 7;
                dataTables[6][3] = 5;
            }
            // Level 3
            if(currentLevel == 3){
                dataTables[2][2] = 3;
                dataTables[4][5] = 8;
                dataTables[8][1] = 2;
                dataTables[8][4] = 7;
                dataTables[6][3] = 5;
                dataTables[6][5] = 1;
                dataTables[6][9] = 6;

            }
            // Level 4
            if(currentLevel == 4){
                dataTables[2][2] = 3;
                dataTables[4][5] = 8;
                dataTables[8][1] = 2;
                dataTables[8][4] = 7;
                dataTables[6][3] = 5;
                dataTables[9][5] = 1;
            }
            // Level 5
            if(currentLevel == 5){
                dataTables[2][2] = 3;
                dataTables[4][5] = 8;
                dataTables[8][1] = 2;
                dataTables[8][4] = 7;
                dataTables[6][3] = 5;
                dataTables[1][1] = 1;
                dataTables[1][3] = 3;
            }

            printboard(dataTables);
            int hour = (seconds/3600);

            int min = (seconds -(3600*hour))/60;

            int sec = (seconds -(3600*hour)-(min*60));
            printf(("\nTime : %d:%d:%d\n"),hour,min,sec);
            printf("\nEnter your command (Press 'help' for see Available commands): ");
            fgets(command, sizeof(command), stdin);
            command[strlen(command)-1] = '\0'; // Strlen is used for calculate the length of string . // /0 is reffered to as null character
            invalidNumber = 1; // first we set invalid to true (1)
            num1 = 0;
            num2 = 0;
            num3 = 0;



            for (j = 0; j < strlen(command); j++)
            {
                if ( command[j] == ',' )
                {
                    for (k = j+1; k < strlen(command); k++)
                    {
                        if ( command[k] == ',' )
                        {
                            invalidNumber = 0; // Now our num is valid (0) check later
                            break;
                        }
                    }
                    break;
                }
            }


            for (i = 0; i < strlen(command); i++)
                command[i] = tolower( command[i]); // The tolower() function takes an uppercase alphabet and convert it to a lowercase character. if you got error Please add #include <ctype.h> .


            if (strcmp("exit", command) == 0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
            {
                printf("Thank you for Playing.\n\n");
                exit(0);
            }


            else if (strcmp("help", command) == 0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
            {
                printf("\nThis is the help menu. Available commands:\n\n");
                printf("Entering a number, then a comma, then another number, then another comma, then a final number. example : 1,1,5 \n");
                printf("reset - resets the board\n");
                printf("finish - when your board is finished and completed you must check the final result to go to the next level (Get score too)\n");
                printf("solve - solves the entered sudoku problem every time you use this commend will decrease 10 score from you (HELPER).\n");
                printf("unsolve - unsolves the recently solved sudoku problem (BACK).\n");
                printf("menu - menu of the game\n");
                printf("exit - exits the game.\n");
                getchar();
            }

            else if (strcmp("reset", command) == 0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
            {
                printf("Board has been reset\n");
                sudoku_borad_row = 9;
                column_board = 9;
                nonetsize = 3;

                for (row = 0; row < 36; row++)
                    for (col = 0; col < 36; col++)
                        dataTables[row][col] = 0;
                // Level 1
                if(currentLevel == 1){
                    dataTables[2][2] = 3;
                    dataTables[4][4] = 8;
                    dataTables[8][1] = 2;
                }
                // Level 2
                if(currentLevel == 2){
                    dataTables[2][2] = 3;
                    dataTables[4][5] = 8;
                    dataTables[8][1] = 2;
                    dataTables[8][4] = 7;
                    dataTables[6][3] = 5;
                }
                // Level 3
                if(currentLevel == 3){
                    dataTables[2][2] = 3;
                    dataTables[4][5] = 8;
                    dataTables[8][1] = 2;
                    dataTables[8][4] = 7;
                    dataTables[6][3] = 5;
                    dataTables[6][5] = 1;
                    dataTables[6][9] = 6;

                }
                // Level 4
                if(currentLevel == 4){
                    dataTables[2][2] = 3;
                    dataTables[4][5] = 8;
                    dataTables[8][1] = 2;
                    dataTables[8][4] = 7;
                    dataTables[6][3] = 5;
                    dataTables[9][5] = 1;
                }
                // Level 5
                if(currentLevel == 5){
                    dataTables[2][2] = 3;
                    dataTables[4][5] = 8;
                    dataTables[8][1] = 2;
                    dataTables[8][4] = 7;
                    dataTables[6][3] = 5;
                    dataTables[1][1] = 1;
                    dataTables[1][3] = 3;
                }

                printboard(dataTables);
            }

            else if (strcmp("solve", command) == 0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
            {
                FILE *log; // The C library function FILE
                char username[30],password[20];
                int score , highestScore;
                int currentLevel;
                struct loginStruct l;

                log = fopen("login.txt","r"); // "r" Mode : Opens a file for reading. The file must exist.

                while(fread(&l,sizeof(l),1,log)) // Read from file
                {
                    strcpy(username, l.username); // The C library function copies the string pointed
                    strcpy(password, l.password); // The C library function copies the string pointed
                    highestScore = l.HighestScore;
                    score = l.Score - 10;
                    currentLevel = l.CurrentLevel;
                }
                fclose(log); // close file

                if(score >= 0){
                    log=fopen("login.txt","w");// create and open file // "w" mode : Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
                    if (log == NULL)
                    {
                        fputs("Error at opening File!", stderr); // if log not been created so return null we should send error then close program
                        exit(1);
                    }

                    strcpy(l.username, username); // The C library function copies the string pointed
                    strcpy(l.password, password); // The C library function copies the string pointed
                    l.HighestScore = highestScore;
                    l.Score = score;
                    l.CurrentLevel = currentLevel;


                    fwrite(&l,sizeof(l),1,log); // Write to file
                    fclose(log); // close file

                    int numberofsolutions = solved_sudoku(dataTables, 0);

                    switch(numberofsolutions)
                    {
                        case -1:
                            printf("\nBroken board.\n");
                            break;
                        case 0:
                            printf("\nNo solution.\n");
                            break;
                        case 1:
                            printf("\n%d solution.\n", numberofsolutions);
                            break;
                        default:
                            printf("\n%d solutions.\n", numberofsolutions);

                    }
                }
                else
                {
                    printf("You need more Score (10)");
                    getchar();
                }

            }

            else if (strcmp("unsolve", command) == 0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
            {
                for (row = 0; row < 36; row++)
                    for (col = 0; col < 36; col++)
                        dataTables[row][col] = temporary2[row][col];

                printboard(dataTables);
            }

            else if(strcmp("menu",command) == 0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
            {
                sudoku_borad_row = 9;
                column_board = 9;
                nonetsize = 3;

                for (row = 0; row < 36; row++)
                    for (col = 0; col < 36; col++)
                        dataTables[row][col] = 0;
                clearscr();
                int op = menu();
                start = clock();
                while(op == 0){
                    op = menu();
                    start = clock();
                }
            }

            else if(strcmp("finish",command) == 0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
            {
                int isDone = 1;
                for(int row = 0; row < 9;row++)
                    for (int col = 0; col < 9; col++) {
                        if (dataTables[row][col] == 0) {
                            isDone = 0;
                        }
                    }

                        if(isDone == 1)
                        {
                            int hour = (seconds/3600);

                            int min = (seconds -(3600*hour))/60;

                            int sec = (seconds -(3600*hour)-(min*60));
                            printf(("\nTime : %d:%d:%d\n"),hour,min,sec);
                            printf("Well Played !!! you going to next level and you got 100 score. Press Enter please");
                            getchar();
                            FILE *log; // The C library function FILE
                            char username[30],password[20];
                            int score , highestScore;
                            int currentLevel;
                            struct loginStruct l;

                            log = fopen("login.txt","r"); // "r" Mode : Opens a file for reading. The file must exist.

                            while(fread(&l,sizeof(l),1,log)) // Read from file
                            {
                                strcpy(username, l.username); // The C library function copies the string pointed
                                strcpy(password, l.password); // The C library function copies the string pointed
                                highestScore = l.HighestScore + 100;
                                score = l.Score + 100;
                                currentLevel = l.CurrentLevel + 1;
                            }
                            fclose(log); // close file


                            log=fopen("login.txt","w");// create and open file // "w" mode : Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
                            if (log == NULL)
                            {
                                fputs("Error at opening File!", stderr); // if log not been created so return null we should send error then close program
                                exit(1);
                            }

                            strcpy(l.username, username); // The C library function copies the string pointed
                            strcpy(l.password, password); // The C library function copies the string pointed
                            l.HighestScore = highestScore;
                            l.Score = score;
                            l.CurrentLevel = currentLevel;


                            fwrite(&l,sizeof(l),1,log); // Write to file
                            fclose(log); // close file

                            sudoku_borad_row = 9;
                            column_board = 9;
                            nonetsize = 3;

                            for (row = 0; row < 36; row++)
                                for (col = 0; col < 36; col++)
                                    dataTables[row][col] = 0;
                            clearscr();
                            int op = menu();
                            start = clock();
                            while(op == 0){
                                op = menu();
                                start = clock();
                            }
                        }
                        else{
                            printf("Your sudoku have wrong number . check it again !");
                        }
                    }


            else if (invalidNumber == 0) // Player input is acceptable
            {

                for ( i = 0; i < j; i++)
                    num1 = 10*num1 + (command[i] - '0'); // Row

                for ( i = j+1; i < k; i++)
                    num2 = 10*num2 + (command[i] - '0'); // Columns

                for ( i = k+1; i < strlen(command); i++)
                    num3 = 10*num3 + (command[i] - '0'); // Final number


                if ( num1 <= 0 || num2 <= 0 || num3 < 0 || num1 > 36 || num2 > 36 ){
                    printf("ERROR, the board is only a max of 36x36.\n");
                    getchar();
                }
                else
                {
                    if (num1 > sudoku_borad_row || num2 > column_board || num3 > column_board){
                        printf("\nOff the board. Input not accepted.\n");
                        getchar();
                    }
                    else
                    {
                        (dataTables[num1-1][num2-1]) = num3;
                        if(checking_invalid_numbers(dataTables, num1 -1, num2 -1) == 1){
                            printf("\nLook carefully at the table, you are doing wrong !!!\n");
                            (dataTables[num1-1][num2-1]) = 0;
                        }
                        else
                        (dataTables[num1-1][num2-1]) = num3; //user not counting from 0

                    }
                }

            }

            else // Player input isn't acceptable
            {
                printf("Invalid input.\n");
                getchar();
            }
        }

    }

    return 1;
}

// menu of the game :
int menu(){
    clearscr();  // Be sure To read Note Above I told why I go this Way !!!
    struct loginStruct loginInfo;
    FILE *log; // The Standard Function
    int option = 0;

    log = fopen("login.txt","r"); // "r" mode : open exits file
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr); // stderr : the standard error message
        exit(1);
    }


    fread(&loginInfo,sizeof(loginInfo),1,log); // Read data from file inside Project file


    printf("Welcome %s Your Score Is %d and Highest Score is %d\nCurrent Level : %d/5\n\n(For Start game Press 1)\n(What is Sudoku ?(Helper) press 2)\n(For Share profile press 3)\n(For Exit game press 4)\n"
            ,loginInfo.name,loginInfo.Score ,loginInfo.HighestScore,loginInfo.CurrentLevel);
    currentLevel = loginInfo.CurrentLevel;
    scanf("%d",&option);
    while(option != 1 && option != 2 && option != 3 && option != 4){
        printf("\nWrong Button Please Press 1 or 2 or 3 or 4\n");
        scanf("%d",&option);
        getchar();
    }

    if(option == 1){
      return 1;
    }
    else if(option == 2){
        clearscr();
        option = 0;
        printf("Sudoku (originally called Number Place) is a logic-based,combinatorial number-placement puzzle. In classic Sudoku, the objective is to fill a 9 × 9 grid with digits so that each column, each row, and each of the nine 3 × 3 subgrids that compose the grid (also called \"boxes\", \"blocks\", or \"regions\") contain all of the digits from 1 to 9. The puzzle setter provides a partially completed grid, which for a well-posed puzzle has a single solution.\n"
               "\n"
               "French newspapers featured variations of the Sudoku puzzles in the 19th century, and the puzzle has appeared since 1979 in puzzle books under the name Number Place.However, the modern Sudoku only began to gain widespread popularity in 1986 when it was published by the Japanese puzzle company Nikoli under the name Sudoku, meaning \"single number\". It first appeared in a U.S. newspaper, and then The Times (London), in 2004, thanks to the efforts of Wayne Gould, who devised a computer program to rapidly produce unique puzzles.");
        printf("\n\n\n Press 1 to Back : ");
        scanf("%d",&option);
        while(option != 1){
            printf("\n\n\n Just Press 1 to Back : ");
            scanf("%d",&option);
        }
        if(option == 1){
            return 0;
        }
    }
    else if(option == 3){
        clearscr();
        option = 0;
        printf("share this text: Hi my friend Let's compete with each other in Sudoku game . my current Level is %d and Highest Score is %d. Are you ready to compete? :)",loginInfo.CurrentLevel,loginInfo.HighestScore);
        getchar();
        getchar();
        return 0;
    }
    else if(option == 4){
        exit(1);
    }
    else
    {
        return 0;
    }
}

// registration (Save data in text file)
void registration(void)
{
    FILE *log; // The C library function FILE

    log=fopen("login.txt","w");// create and open file // "w" mode : Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr); // if log not been created so return null we should send error then close program
        exit(1);
    }


    struct loginStruct l;

    printf("\nWelcome to Sudoku game Before you Play, We need to enter some details for registration.\n\n");
    printf("\nEnter Name:\n");
    scanf("%s",l.name);

    printf("\nNow please choose a username and password for system login.\nEnsure the username is no more than 30 characters long.\nEnsure your password is at least 8 characters long and contains lowercase, uppercase, numerical and special character values.\n");

    printf("\nEnter Username:");
    scanf(" %s",l.username);
    printf("Enter Password:");
    scanf("%s",&l.password);

    l.Score = 20; // default score
    l.CurrentLevel = 1;
    l.HighestScore = 20;// default Highest Score

    fwrite(&l,sizeof(l),1,log); // Write to file
    fclose(log); // close file

    printf("\n\nWelcome %s your Registration Successful !!!\n",l.name);
    login();
}

// login (read data from File created)
int login ()
{
    char username[30],password[20];
    FILE *log; // The C library function FILE

    log = fopen("login.txt","r"); // "r" Mode : Opens a file for reading. The file must exist.
    if (log == NULL) // if log not been created so return null we should send error then close program
    {
        fputs("Error at opening File!", stderr); // stderr : the standard error message
        exit(1);
    }

    struct loginStruct l;

    printf("\n\n\nPlease Enter your login Info below\n");

    printf("\nUsername:");
    scanf(" %s",username);
    printf("Password:");
    scanf("%s",password);

    while(fread(&l,sizeof(l),1,log)) // Read from file
    {
        if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0) // The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.

        {
            printf("\nSuccessful Login\n");
        }
        else
        {
            printf("\nIncorrect Login Details\nPlease enter the correct info\n");
            fclose(log); // close file
            return 0;
        }
    }

    fclose(log); // close file

    return 1;
}

// Solved final of the game
int solved_sudoku(int *board[36][36], int solutions)
{
    int *copy[36][36];
    int invalidflag, space, status;


    for (row = 0; row < 36; row++)
        for (col = 0; col < 36; col++)
            copy[row][col] = board[row][col];



    for (row = 0; row < sudoku_borad_row; row++)
    {
        for (col = 0; col < column_board; col++)
        {

            if (copy[row][col] != 0)
            {
                if (checking_invalid_numbers(copy, row, col) == 1)
                    return -1;
            }


            else
            {

                for (space = 1; space <= sudoku_borad_row; space++)
                {

                    copy[row][col] = space;


                    invalidflag = checking_invalid_numbers(copy, row, col);



                    if (invalidflag == 0)
                    {
                        status = solved_sudoku(copy, 0);

                        if ( status > 0)
                        {
                            return status;
                        }

                        else if ( status == -1 )
                            return -1;
                    }
                }


                return 0;
            }
        }
    }


    solutions++;

    if (solutions == 1)
    {

        for (row = 0; row < 36; row++)
        {
            for (col = 0; col < 36; col++)
            {
                temporary2[row][col] = dataTables[row][col];
                dataTables[row][col] = copy[row][col];
            }
        }


        printboard(dataTables);
    }

    return solutions;
}

// checking is number in cell is valid or invalid
int checking_invalid_numbers(int *copy[36][36], int row, int col)
{

    int i, j, k;
    int nonetrow, nonetcol;

    for (i = 0; i < sudoku_borad_row; i++)
    {

        if ((i == row));
        else if (copy[row][col] == copy[i][col])
            return 1;


        if ((i == col));
        else if (copy[row][col] == copy[row][i])
            return 1;
    }


    nonetrow = row / nonetsize;
    nonetcol = col / nonetsize;

    for(j = nonetrow*nonetsize; j < (nonetrow+1)*nonetsize; j++)
    {
        for(k = nonetcol*nonetsize; k < (nonetcol+1)*nonetsize; k++)
        {
            if (row == j && col == k);

            else if (copy[row][col] == copy[j][k])
                return 1;
        }
    }


    return 0;
}

// print our sudoku puzzle
void printboard(int *board[36][36])
{


    for (row = 0; row <= sudoku_borad_row; row++)
    {
        if (row == 0)
        {
            printf("\n");

            for (col = 1; col <= column_board; col++)
            {
                if (col == 1)
                    printf("    %d", col);
                else if (col > 9)
                    printf("  %d", col);
                else
                    printf("   %d", col);
            }
        }

        else
        {
            printf("\n  ");

            for (col = 1; col <= column_board; col++)
            {
                if ( (((row-1) % (nonetsize)) == 0) && ((row-1) != 0))
                    printf("+===");
                else
                    printf("+---");
            }

            printf("+");

            if (row > 9)
                printf("\n%d", row);
            else
                printf("\n%d ", row);

            for (col = 1; col <= column_board; col++)
            {
                if ( (((col-1) % (nonetsize)) == 0) && ((col-1) != 0))
                    printf("#");
                else
                    printf("|");

                if (board[row-1][col-1] != 0)
                {
                    if ((board[row-1][col-1]) > 9)
                        printf(" %d", board[row-1][col-1]);
                    else
                        printf(" %d ", board[row-1][col-1]);
                }
                else
                    printf("   ");
            }

            printf("|");

            if (row == sudoku_borad_row)
            {
                printf("\n  ");

                for (col = 1; col <= column_board; col++)
                {
                    printf("+---");
                }

                printf("+\n");
            }

        }

    }
}
