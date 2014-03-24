/*  Ethan Bennett
/   Operating Systems
/   Shell Project
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void split(char line[], char *pieces[]){  //this function parses the user inputs into meaningful pieces
	int linecounter = 0;  //initialize the line counter
	int wordcounter = 0; //intitialize the word counter
	while(line[linecounter]!='\0'){  //while the line is not NULL...
		int lettercounter = 0; //initialize letter counter
		while(line[linecounter]!= ' ' && line[linecounter] != '\0'){  //while the line is not a space or a NULL...
			char tocopy = line[linecounter]; //put the line in tocopy
			pieces[wordcounter][lettercounter] = tocopy; //tocopy is put into pieces at the point in word counter, at 									     //the point letter counter
			lettercounter++; //incremement letter counter
			linecounter++;} //increment letter counter
		pieces[wordcounter][lettercounter] = '\0'; //put a NULL at the end
		if (line[linecounter] == '\0')  //if the line is NULL...
			break; //stop
		wordcounter++; //increment word counter
		linecounter++;}} //increment line counter
void typeCmmd(char *pieces[]){  //function for running the type command
	int c; //initialize c
	FILE *file; //look at the file definition
	file = fopen(pieces[1], "r"); //open file name in read mode
	if (file) { //if the file opened...
	    while ((c = getc(file)) != EOF)  //get each char in file until the end of file
		putchar(c); //and putchar
	    fclose(file);} //close the file
	main();} //run main
void copyCmmd(char *pieces[]){ //function for running the copy command
	char ch; //initialize a char variable
	FILE *source, *target; //file pointers for source and target
	source = fopen(pieces[1], "r"); //make source equal to the first file in read mode
	if( source == NULL ){ //if source returns NULL...
		printf("There seems to have been an error. Please try again. \n"); //give an error
		main();} //return to main
	target = fopen(pieces[2], "w"); //make the target equal to the second file, in read mode
	if( target == NULL ){ //if target returns NULL...
		fclose(source); //close the source file
		printf("There seems to have been an error. Please try again. \n"); //give an error
		main(); //return to main
	}while( ( ch = fgetc(source) ) != EOF ) //while not at the end of the file, read chars from source
		fputc(ch, target);  //put chars in target
	printf("File copied successfully.\n"); //print success message
	fclose(source); //close the source file
	fclose(target); //close the target file
	main();} //return to main
void execute(char *pieces[]){ //function for executing an executable file
	char* args[1][1]; //initialize an array for the 2nd argument in execvp
	args[0][0]=NULL; //fill the array with NULL
	int pid = -1; //make pid = to -1 (to be safe)
	pid = fork(); //fork the program and save the value as pid
	if (pid==0){ //if one of the program's pID is equal to 0...
		execvp(pieces[0],args); //execute the file
		printf("Unknown command, please try again.\n"); //if the file returns there was an error
	}
	else if(pid > 0){ //if the program's pID was less than 0...
		wait(0); //wait until the other part of the forked program is done
	}
	main(); //return to main
}
void commandID(char *pieces[]){
	int exitCmp = strcmp(pieces[0],"exit"); //check if the first input is exit, return int value
	int typeCmp = strcmp(pieces[0],"type"); //check if the first input is type, return int value
	int copyCmp = strcmp(pieces[0],"copy"); //check if the first input is copy, return int value
	int delCmp = strcmp(pieces[0],"delete"); //check if the first input is delete, return int value
	if (exitCmp==0) // if the input was exit...
		exit(1); //exit
	else if (typeCmp==0) //if the input was type...
		typeCmmd(pieces); //run typeCmmd with the array of pointers
	else if (copyCmp==0) //if the input was copy...
		copyCmmd(pieces); //run copyCmmd with the array of pointers
	else if (delCmp==0){ //if the input was delete...
		remove(pieces[1]); //remove the file
		main();} //go back to main
	else if (exitCmp!=0 && typeCmp!=0 && copyCmp!=0) //if no inputs matched...
		execute(pieces);} //rune execute with the array of pointers
main(){
	printf("Awaiting command...\n");  //prompt
	char command[100];  //initial array for input
	int i;
	for (i= 0; i<100; i++){
		command[i] = getchar();  //get input and store in command
		if(command[i]==10)	//if user presses return, stop getting input
			break;}
	command[i] = 0;  //at the end of the command, insert a NULL
	char commandname[100];  // array for the command
	char argument1[100]; //array for the first argument
	char argument2[100]; //array for the second argument
	char* arrayOfPieces[3]; //an array of pointers
	arrayOfPieces[0] = commandname; //point to commandname
	arrayOfPieces[1] = argument1; //point to argument 1
	arrayOfPieces[2] = argument2; //point to argument 2
	split(command,arrayOfPieces); //run split function with the command and the array of pointers
	commandID(arrayOfPieces);} //run commandID function with the array of pointers
