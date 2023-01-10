/*
  Microkernel for T54 V4 
  It aims to support:
    * Basic I/O
    * Filesystem support (Obease filesystem)
    * Goofy ahh excecutable support
*/
// Basic utils
int strlen(char* str);
// Basic Kernel components
void print(char* string);
void appPrint(char* proccessName, char* string);
// Basic Kernel global Vars
int terminalX;
static char* const fb = (char*)(0xB8000);
int kmain(){
  print("T54 Starting.");
}
// Basic utils
int strlen(char* str){
  int i;
  while(str[i++]){}
  return i;
}
// Basic Kernel components
void print(char* string){
  for(int i = 0; i < strlen(string); i++){
    int position = (terminalX * 80) + 0;
    fb[position] = string[i];
    fb[position] = 0x07;
  }
}