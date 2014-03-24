void printString(char*);

main(){
	printString("Hello World\0");	
}

void printString(char* chars){
	char al = 'Q';
	char ah = 0xe;
	int  ax = ah * 256+al;
	interrupt(0x10,ax,0,0,0);
}
