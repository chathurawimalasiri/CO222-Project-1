/*
 *	CO222 PROJECT 1
 *
 *	E/18/402
 *	WIMALASIRI K.H.C.T.
 *
 *	References are mentioned at the bottom.
 *
 */



#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>    //remove the warning due to sleep(1)
#include <stdlib.h>
#include <signal.h>



#define WHITE			7
#define NOT_CORRECT_COLOUR	9 
#define RESET			printf("\x1b[0m")
#define HIDE_THE_CURSOR		printf("\x1b[?25l")
#define MAKE_CURSOR_VISIBLE	printf("\033[?25h")
#define CLEAR_THE_SCREEN	printf("\x1b[2J")
#define SAVE_THE_SCREEN		printf("\033[?47h")
#define RESTORE_THE_SCREEN	printf("\033[?47l")
#define CENTER_ALIGNMENT	printf("\x1b[8;23H")

#define ERROR_HANDLING_1	printf("usage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n")

#define ERROR_HANDLING_2	printf("Invalid use of arguments.\nusage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n")

#define ERROR_WRONG_COLOUR	printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n",colourNameCopy)




//function prototypes

void deleteAllElemetsArray(char[], int);
void getPortionString(char[], char[],int);
void sigint_handler(int sig);
int charIndentifier(char);
int putBlockPosition(int);
void printSpaceTwoDots(int ,int);
void defineDigits(char,int,int);
void printDigitNumber(int (*array)[6],int,int);
int findTheColour(char[]);






int main(int argc, char **argv){



	int currentTimePossition,index,cFlagCounter = 0,totalcCounter = 0;
	int colourNumber;
	char colourNameCopy[100];	//copy colour name with lower case and print with necessary error handling cases
	



	colourNumber = WHITE ;		//defualt give white colour



	for(index = 0; index < argc ; index++){


                if( (strcmp(argv[index],"-c")) == 0 ){		//check agrv is equal to -c

			
			cFlagCounter++ ;			//check -c write odd patern or even pattern
			
			totalcCounter++;			//check total -c 

                        if( index == (argc - 1)){		//argv is equal to -c and there has no any arguments after that


                                ERROR_HANDLING_2;

                                return 0;

                        }



			else if( cFlagCounter % 2 == 1 ){

				
				deleteAllElemetsArray(colourNameCopy, strlen(colourNameCopy));		 //delete elements in the array before assign elements

					
                                strcpy(colourNameCopy,argv[index + 1]);                 	//copy colour name to print with  error handling cases


                                for(int index2 = 0; index2 < strlen(argv[index + 1]); index2++){           //conver the input colour name in to lower case to get same format


                                        colourNameCopy[index2] = tolower(colourNameCopy[index2]);

                                }


                                if(findTheColour(colourNameCopy) != -1 ){              	//input colour name is equal to colour names

                                        colourNumber = findTheColour(colourNameCopy);
					
					if( (argv[index + 1][0] != '-') && (argv[index + 1][1] != 'c') ){
				
					
						cFlagCounter = 0;

					}	
					

                                }


                                else if(findTheColour(colourNameCopy) == -1){          	//input colour name doesn't match with colour names
					
					
					colourNumber = NOT_CORRECT_COLOUR;
                                        
					if(  (argv[index + 1][0] != '-') && (argv[index + 1][1] != 'c') ){
						
					
                                                cFlagCounter = 0;

                                        }


                                }

				

                        }

		
			else{
		
				
				deleteAllElemetsArray(colourNameCopy, strlen(colourNameCopy));

				strcpy(colourNameCopy, argv[index] );
				
				for(int index2 = 0; index2 < strlen(argv[index + 1]); index2++){           //conver the input colour name in to lower case to get same format


					colourNameCopy[index2] = tolower(colourNameCopy[index2]);

                                
				}


				colourNumber = NOT_CORRECT_COLOUR;	



			}	



                }
		


		else if( (strcmp(argv[index],"-h")) == 0){		//argv is equal to -h then go to help conditions
			
	

			ERROR_HANDLING_1 ;

                	return 0;



		}	


		



		else if( argv[index][0] == '-' ){			//check any argv starts with '-'

			
			if(argv[index][1] == 'h'){                          //if argv starts with '-' and second character is 'h'

                        	ERROR_HANDLING_1 ;

                        	return 0;

                	}	
		
			
			
			else if( strlen(argv[index]) == 1 ){		//argv is equal to '-'

				cFlagCounter = 0;

				colourNumber = WHITE;

		
			}



		
			else if( (argv[index][1] == 'c') && (strlen(argv[index]) > 2)  ){

				totalcCounter++;
				
				cFlagCounter++;

		
				
				if( cFlagCounter % 2 == 1){
					
					deleteAllElemetsArray(colourNameCopy, strlen(colourNameCopy));

                        		getPortionString(colourNameCopy,argv[index],2);             		//copy all chars of argv[index] after -c to colourNameCopy



                        		for(int index2 = 0; index2 < strlen(colourNameCopy); index2++){                //convert to lower characters


                                		colourNameCopy[index2] = tolower(colourNameCopy[index2]);

                        		}



                        		if( findTheColour(colourNameCopy) != -1 ){              		//input colour name matches with colour names

                                		colourNumber = findTheColour(colourNameCopy);
						
						cFlagCounter = 0;

                        		}	

			
					
					else{
                                
						colourNumber = NOT_CORRECT_COLOUR;				//assign 8 for error handling 

						
						cFlagCounter = 0;

					}


					
                        	}	


				

				




                	}


			
			else if((argv[index][1] == '-') && (strlen(argv[index]) == 2) ){      //argv[index] is equal to -- then print with default colour
				
				cFlagCounter = 0;

				if( totalcCounter == 0 ){

					break ;
				
				}	
			

				else if( (totalcCounter != 0) && ( (strcmp(argv[index-1],"-c")) != 0 )){

					break;

				}	
				
				

                        	
								

                	}



                	else if(  strlen(argv[index]) > 2  ) {

				
				if( (strcmp(argv[index-1],"-c")) != 0){

                        		ERROR_HANDLING_2;

                        		return 0;

                		}


				else{

					
					cFlagCounter = 0;

		
				}	

			}


		}	




	}



	if( colourNumber == NOT_CORRECT_COLOUR ){		//assign value is not between 0 and 7

		ERROR_WRONG_COLOUR;

		return 0;


	}	




	SAVE_THE_SCREEN;


	//ctrl+c goes to previous screen
	signal(SIGINT, sigint_handler);


	HIDE_THE_CURSOR;

	CLEAR_THE_SCREEN;



	while(1){


		char currentTime[15], todayDate[15];

		time_t nowTime;      //stored system time value

		nowTime = time(0);   //time since 1970 January 1st .


		struct tm* dividedTime = localtime(&nowTime);  //divide the time

		strftime(currentTime,15,"%X",dividedTime);     //time format ex--> 01:20:40

		strftime(todayDate,15,"%Y-%m-%d",dividedTime);  //date format ex --> 2021-08-16




		for(currentTimePossition = 0 ; currentTimePossition < 2 ; currentTimePossition++){   //print the very first two digits of the clock

			defineDigits(currentTime[currentTimePossition],currentTimePossition,colourNumber);


		}


		printSpaceTwoDots(15 ,colourNumber);	//print the very first dots column


		for(currentTimePossition = 3 ; currentTimePossition < 5 ; currentTimePossition++){   //print the next two digits of the clock

                	defineDigits(currentTime[currentTimePossition],currentTimePossition,colourNumber);


        	}


		printSpaceTwoDots(34 ,colourNumber);	//print the next dots column


		for(currentTimePossition = 6 ; currentTimePossition < 8 ; currentTimePossition++){   //print the last two digits of the clock

                	defineDigits(currentTime[currentTimePossition],currentTimePossition,colourNumber);


        	}


		CENTER_ALIGNMENT ;  //adjust the alignment of the date


		printf("\x1b[0;3%dm",colourNumber);  //set the colour to date


		for(int i=0; i<10;i++){ 		//print the date

			printf("%c",todayDate[i]);

		}


		printf("\n");


		RESET;

		sleep(1);



	}



	return 0;


}




//delete all the elements in the array or assign NULL to given array
void deleteAllElemetsArray(char source[] , int SIZE){


	int index;

	for(index = 0; index < SIZE ; index++){

		source[index] = '\0';

	}	



}	




/*
 *
 *	this function is used instead of using memcpy() because memcpy() can't run untill meet NULL character.
 *	so it will cause to run loop unnecessarily.
 *
 *	this function is to assign values to destination array from source array and start from specific index number
 *
 *
 */




void getPortionString(char destination[], char source[],int startIndex){


	int index ;

	for(index = startIndex ; source[index] != '\0' ; index++ ){

		destination[index-startIndex] = source[index] ;

	}	
	
	destination[index] = '\0' ;

}	




/*
 * when ctrl+c exit the current screen and  goes to previous screen where we stop.
 *
 */

void sigint_handler(int sig){


        CLEAR_THE_SCREEN;

        RESTORE_THE_SCREEN;

	MAKE_CURSOR_VISIBLE;

        exit(0);


}




/*
 *	The connection between  numbers and colours are  given below.
 *
 *	black	0
 *	red     1
 *	green   2
 *	yellow  3
 *	blue    4
 *	magenta 5
 *	cyan    6
 *	white   7
 *
 *
 */



int findTheColour(char colourName[10]){

	char *colours[] = {"black","red","green","yellow","blue","magenta","cyan","white"};

	int colourIndex;

	for(colourIndex = 0 ; colourIndex < 8 ; colourIndex++ ){

		if(strcmp(colourName,colours[colourIndex] ) == 0 ){

			return colourIndex ;

		}

	}

	//if input colour is not match then

	return -1;


}




//the numbers of time is char array  so convert to equal integer

int charIndentifier(char charNumber){


	int charAsNumber;

	char digitsChars[] = {'0','1','2','3','4','5','6','7','8','9'};


	for(charAsNumber = 0; charAsNumber < 10; charAsNumber++){

		if(charNumber == digitsChars[charAsNumber]){

			return charAsNumber ;

		}

	}

/*
 *
 *	use the return 0 for remove the warning due to
 *	" warning: control reaches end of non-void function [-Wreturn-type] "
 *
 */


	return 0;


}





//given time convert to digits two dimensional array

void defineDigits(char digitNumber,int currentTimePossition,int colourNumber){

	int digitArray[5][6]  ; //define the an array to print the digits
	int number;


	number = charIndentifier(digitNumber);







/*
 *
 *	use "  __attribute__((unused)) " to avoid warning due to unused variable
 *
 */



	if(number == 0){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{1,1,0,0,1,1},
					{1,1,0,0,1,1},
					{1,1,0,0,1,1},
					{1,1,1,1,1,1}

					};
	}


	else if(number == 1){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{0,0,0,0,1,1},
					{0,0,0,0,1,1},
					{0,0,0,0,1,1},
					{0,0,0,0,1,1},
					{0,0,0,0,1,1}

					};
	}


	else if(number == 2){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{0,0,0,0,1,1},
					{1,1,1,1,1,1},
					{1,1,0,0,0,0},
					{1,1,1,1,1,1}

					};
	}

	else if(number == 3){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{0,0,0,0,1,1},
					{1,1,1,1,1,1},
					{0,0,0,0,1,1},
					{1,1,1,1,1,1}

					};
	}

	else if(number == 4){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,0,0,1,1},
					{1,1,0,0,1,1},
					{1,1,1,1,1,1},
					{0,0,0,0,1,1},
					{0,0,0,0,1,1}

					};

	}

	else if(number == 5){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{1,1,0,0,0,0},
					{1,1,1,1,1,1},
					{0,0,0,0,1,1},
					{1,1,1,1,1,1}

					};

	}

	else if(number == 6){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{1,1,0,0,0,0},
					{1,1,1,1,1,1},
					{1,1,0,0,1,1},
					{1,1,1,1,1,1}

					};

	}

	else if(number == 7){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{0,0,0,0,1,1},
					{0,0,0,0,1,1},
					{0,0,0,0,1,1},
					{0,0,0,0,1,1}

					};

	}

	else if(number == 8){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{1,1,0,0,1,1},
					{1,1,1,1,1,1},
					{1,1,0,0,1,1},
					{1,1,1,1,1,1}

					};

	}

	else if(number == 9){

		__attribute__((unused)) int digitArray[5][6] =
					{
					{1,1,1,1,1,1},
					{1,1,0,0,1,1},
					{1,1,1,1,1,1},
					{0,0,0,0,1,1},
					{1,1,1,1,1,1}

					};
	}


	printDigitNumber(digitArray,currentTimePossition,colourNumber);





}


/*
 *
 *	colours which works in linux have spefic number 0 to 7. If one of these colour is added to background then
 *	40 is added to that spefic number(0 to 7). Therefore, colour + 40 is used.
 *
 *
 */


//print the time in large scale

void printDigitNumber(int (*array)[6],int currentPossition,int colour){

        int rows,columns;

        for(rows = 0; rows < 5; rows++){

                for(columns = 0; columns < 6; columns++){

                        printf("\x1b[%d;%dH",rows + 2,columns + putBlockPosition(currentPossition)); 	//divide the terminal

			if(array[rows][columns] == 1){

				RESET;

				printf("\x1b[%dm",colour + 40); 	//fill the space with necessary colour

				printf(" ");

			}

			else if(array[rows][columns] == 0){

				RESET;

				printf(" ");			//print black colour black space

			}


                }


		RESET;


        }



}

//make the spaces for dividing the terminal

int putBlockPosition(int position){

	int putSpace;

	if(position == 0){

		putSpace = 2;

	}

	else if(position == 1){

		putSpace = 9;

	}

	else if(position == 3){

		putSpace = 21;

	}

	else if(position == 4){

		putSpace = 28;

	}

	else if(position == 6){

		putSpace = 40;

	}

	else if(position == 7){

		putSpace = 47;

	}

	return putSpace;


}



//print the two dots columns in large scale

void printSpaceTwoDots(int currentPossition ,int dotsColour){

	int rows,columns;

	int dotsArray[5][6] = {	{0,0,0,0,0,0},		//array for hours,minutes and seconds separated dots --> ex. 12:31:32
				{0,0,1,1,0,0},
				{0,0,0,0,0,0},
				{0,0,1,1,0,0},
				{0,0,0,0,0,0}
				} ;



	for(rows = 0 ; rows < 5; rows++){

		for(columns = 0; columns < 6; columns++){

			printf("\x1b[%d;%dH",rows + 2,columns + currentPossition);	//divide the terminal

			if(dotsArray[rows][columns] == 1){


				RESET;

                                printf("\x1b[%dm",dotsColour + 40);	//fill the space with necessary colour

                                printf(" ");


			}

			else if(dotsArray[rows][columns] == 0) {

				RESET;

				printf(" ");			//print black blank space

			}

		}

		RESET;

		printf("\n");


	}




}



/*
 * ---------------------------------------------------------------------- REFERENCES -------------------------------------------------------------------
 *
 *
 *
 *	https://cboard.cprogramming.com/linux-programming/151274-dividing-terminal.html
 *
 *	https://www.theurbanpenguin.com/4184-2/
 *
 *	https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/
 *
 *	https://www.codegrepper.com/code-examples/c/unused+variable+C
 *
 *
 *
 */









































































