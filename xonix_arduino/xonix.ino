#include <MD_MAX72xx.h>
#include <TM1637Display.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES  4

const uint8_t CLK_PIN = 13;
const uint8_t DATA_PIN = 11;
const uint8_t CS_PIN = 10;

const int axisX=A0;
const int axisY=A1;
const int axisZ=A2;
int xval, yval, zval = 0;
int x, y = 5;

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const int minX = 0;
const int maxX = 32;
const int minY = 0;
const int maxY = 8;

int grid[maxX][maxY];

int getRandomMove()
{
  if (random(0, 2) > 0)
    return 1;
  else 
    return -1;
}

struct Enemy
{
  int x,y,dx,dy;

  Enemy()
  {
    x = random(3, maxX-3);
    y = random(3, maxY-3);
    dx = getRandomMove();
    dy = getRandomMove();
  }

  void move()
  { 
    //x += dx;     
    if (grid[x+dx][y]==1) { dx=-dx; }
    //y += dy;     
    if (grid[x][y+dy]==1) { dy=-dy; }

    x += dx; 
    y += dy;
  }
};


const int enemyCount = 3;
Enemy a[enemyCount];

void setup() {  
  
  for(int x = 0; x < maxX; x++)
    for(int y = 0; y < maxY; y++)
      if (x==0 || y==0 || x == maxX - 1 || y == maxY - 1)
        grid[x][y] = 1;
      else
        grid[x][y] = 0;
  
  //for(int y=0; y<maxY; y++)
  //  grid[1][y] = 1;
    
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(axisZ, INPUT_PULLUP);

  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 1);
}

void drop(int y,int x)
{
  if (grid[y][x]==0) grid[y][x]=-1;
  if (grid[y-1][x]==0) drop(y-1,x);
  if (grid[y+1][x]==0) drop(y+1,x);
  if (grid[y][x-1]==0) drop(y,x-1);
  if (grid[y][x+1]==0) drop(y,x+1);
}

void draw()
{
  // field
  for(int x = 0; x < maxX; x++)
    for(int y = 0; y < maxY; y++)
      if (grid[x][y] == 0)
        mx.setPoint(y, x, false);
      else 
        mx.setPoint(y, x, true);

  // enemies
  for (int i=0; i<enemyCount; i++)
    mx.setPoint(a[i].y, a[i].x, true);
}

void loop() 
{
  xval = analogRead(axisX);
  yval = analogRead(axisY);
  
  if (xval < 900) x = x + 1;
  if (xval > 100) x = x - 1;
  if (yval < 900) y = y - 1;
  if (yval > 100) y = y + 1;

  if (x > maxX - 1) x = maxX-1;  
  if (y > maxY - 1) y = maxY-1;
  if (x < minX) x = minX;
  if (y < minY) y = minY;
    
  //grid[x][y]=2;

  for (int i = 0; i < enemyCount; i++) a[i].move();

  draw();
  
  //mx.setPoint(5, 5, true);

  delay(30);  
}
