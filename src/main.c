/*
  Microkernel for T54 V4 
  It aims to support:
    * Basic I/O
    * Filesystem support (Obease filesystem)
    * Goofy ahh excecutable support
*/
// extern
extern switchToRealMode();
extern readValues();
extern jumpToVals();
// Basic utils
int strlen(char *str);
void clearScreen();
void charAt(char c, int x, int y, unsigned char color);
char* itoa(int val, int base);
// Basic Kernel components
void print(char *string,int* y);
void appPrint(char* proccessName, char* string);
void printInt(int val, int* y);
// TUI
void initTUI(char* title);
void tuiTerminalPrint(char* string);
/*
  KERNEL COMPONENTS
*/
// IO
unsigned char inb (unsigned short _port);
void outb (unsigned short _port, unsigned char _data);
// Keyboard
char pollKeys();
unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',     '9', '0', '-', '=', '\b',   '\t',
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',  0,
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '`',   0,
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 
  'm', ',', '.', '/',   0,
  '*',0, ' ', 0,  0, 0,   0,   0,   0,   0,   0,   0,   0,
    0,  
    0,  
    0,  
    0,  
    '~', 
    0,  
  '-',
    0, 
    0,
    0,  
  '+',
    0, 
    '|',  
    0,0,0,0,0,0,0,0,0,  
};
// Basic Kernel global Vars
#define WIDTH 80
#define HEIGHT 25
#define TERMINAL_MAX 23
#define TERMINAL_MIN 1
int terminalY = TERMINAL_MIN;
// COLORS
#define GREEN_BG 42
#define BLUE_BG 47
#define T_COLOR 0xc
// framebuffer video adress 
static char* const fb = (char*)(0xb8000);
int kmain(){
  /*
    Basic kernel init stuff
  */
  clearScreen();
  // create basic TUI
  initTUI("T54 Kernel");
  tuiTerminalPrint("Starting T54..");
  tuiTerminalPrint("Switching to real mode (for HD access)");
  switchToRealMode();
  tuiTerminalPrint("Done.");
  tuiTerminalPrint("Test read from HD....");
  readValues();
  tuiTerminalPrint("Done read test.");
  char* hdVal = (char*)(0x7C00);
  tuiTerminalPrint(hdVal);
  int x = 0;
  while(1){}
}
// Basic utils
int strlen(char *str){
  int i = 0;
  while(str[i++]){}
  return i;
}
void clearScreen(){
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++)
      charAt(' ',x,y, BLUE_BG);
  }
}
// from http://www.strudel.org.uk/itoa/
char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}
// Basic Kernel components
void charAt(char c, int x, int y, unsigned char color){
  int position = 2 * x + 160 * y;
  fb[position] = c;
  fb[position+1] = color;
}
void print(char *string,int* y){
 // clearScreen();
  for(int i = 0; i < strlen(string); i++){
    charAt(string[i],i,*y,GREEN_BG);
  }
  *y++;
}
void printInt(int val, int* y){
  print(itoa(val,10),*y);
}
// TUI
void initTUI(char* title){
  for(int i = 0; i < WIDTH; i++){
    if(strlen(title) > i){
      charAt(title[i],i,0,GREEN_BG);
    }else{
      charAt(' ',i,0,GREEN_BG);
    }
  }
  for(int y = 1; y < HEIGHT; y++)
    for(int x = 0; x < WIDTH; x++)
      charAt(' ',x,y,0x39);
}
void tuiTerminalPrint(char* string){
  if(terminalY > TERMINAL_MAX){
    for(int y = 1; y < TERMINAL_MAX; y++)
      for(int x = 0; x < WIDTH; x++)
        fb[2 * x + 160 * (y - 1)] = fb[2 * x + 160 * y];
    terminalY--;
  }
  for(int i= 0; i < strlen(string); i++){
    charAt(string[i],i,terminalY,0x39);
  }
  terminalY++;
}
// IO
// read from port
unsigned char inb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
// write to port
void outb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
// Keyboard
char pollKeys(){
  char c = keyboard_map[inb(0x60)];
  return c;
}