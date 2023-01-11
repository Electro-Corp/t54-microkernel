/*
  Microkernel for T54 V4 
  It aims to support:
    * Basic I/O
    * Filesystem support (Obease filesystem)
    * Goofy ahh excecutable support
*/
// Basic utils
int strlen(char *str);
// Basic Kernel components
void print(char *string,int* y);
void appPrint(char* proccessName, char* string);
// Basic Kernel global Vars
int terminalY = 0;
static char* const fb = (char*)(0xB8000);
int kmain(){
  print("T54 Starting.",&terminalY);
  //print("Switiching to Real Mode...",&terminalY);
}
// Basic utils
int strlen(char *str){
  int i = 0;
  while(str[i++]){}
  return i;
}
// Basic Kernel components
void print(char *string,int* y){
  for(int i = 0; i < strlen(string); i++){
    int position = 2 * i + 160 * *y;
    fb[position] = string[i];
    fb[position] = 0x07;
  }
  y++;
}