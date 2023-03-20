struct item{
  char* title;
  unsigned char hdAddr;  
};


struct fs{
  struct item* items;
};
static char* const fb = (char*)(0xb8000);
void charAt(char c, int x, int y, unsigned char color){
  int position = 2 * x + 160 * y;
  fb[position] = c;
  fb[position+1] = color;
}
int main(){
  charAt('6',0,0,0xfc);
  return 0;
}