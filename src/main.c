/*
  Microkernel for T54 V4 
  It aims to support:
    * Basic I/O
    * Filesystem support (Obease filesystem)
    * Goofy ahh excecutable support
*/
// extern
extern switchToRealMode();
// Basic utils
int strlen(char *str);
void clearScreen();
void charAt(char c, int x, int y);
// Basic Kernel components
void print(char *string,int* y);
void appPrint(char* proccessName, char* string);
// Basic Kernel global Vars
int terminalY = 0;
static char* const fb = (char*)(0xb8000);
int kmain(){
  // Baisc kernel init stuff
  clearScreen();
  print("T54 Starting",&terminalY);
  print("Switching to real mode",&terminalY);
  switchToRealMode();
  print("Finished.",&terminalY);
  while(1){}
}
// Basic utils
int strlen(char *str){
  int i = 0;
  while(str[i++]){}
  return i;
}
void clearScreen(){
  for(int y = 0; y < 25; y++){
    for(int x = 0; x < 80; x++)
      charAt(' ',x,y);
  }
}
// Basic Kernel components
void charAt(char c, int x, int y){
  int position = 2 * x + 160 * y;
  fb[position] = c;
}
void print(char *string,int* y){
  for(int i = 0; i < strlen(string); i++){
    charAt(string[i],i,*y);
  }
  *y++;
}