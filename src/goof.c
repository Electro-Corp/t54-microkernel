static char* const fb = (char*)(0xb8000);
int strlen(char *str){
  int i = 0;
  while(str[i++]){}
  return i;
}
void charAt(char c, int x, int y){
  int position = 2 * x + 160 * y;
  fb[position] = c;
}
void print(char *string,int* y){
 // clearScreen();
  for(int i = 0; i < strlen(string); i++){
    charAt(string[i],i,*y);
  }
  *y++;
  }
int kmain(){
  print("hard drive was (read)",0);
}