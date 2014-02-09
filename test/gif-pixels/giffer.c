# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define WIDTH 50
# define HEIGHT 50
# define PIXELS WIDTH * HEIGHT

struct color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

struct point {
  unsigned int x;
  unsigned int y;
};

static const unsigned int color_distance = 20;
static struct point stack [(WIDTH+2)*(HEIGHT+2)];
static unsigned int sp = 0;
static const struct point max = {WIDTH,HEIGHT};
static struct color raster [WIDTH][HEIGHT];

struct color near ( struct color c) {
  c.r += (rand() % color_distance)-(color_distance/2);
  c.g += (rand() % color_distance)-(color_distance/2);
  c.b += (rand() % color_distance)-(color_distance/2);
  c.a = 0;
  return c;
}

void printint(unsigned int a)
{
  putchar((unsigned char)a);
  putchar((unsigned char)(a>>8));
}


void write(unsigned int x,unsigned int y,struct color c) {
  raster[x][y] = c;
  /*fprintf(stderr,
    "%d %d #%02x%02x%02x\n",
    x,y,
    c.r,
    c.g,
    c.b);*/
  /* Graphic Control Extension Block */
  putchar(0x21);
  putchar(0xf9);
  putchar(0x04);
  putchar(0x00);
  putchar(0x01);
  putchar(0x00);
  putchar(0x00);
  putchar(0x00);
  /* Image Block */
  putchar(0x2c);
  printint(x);
  printint(y);
  putchar(0x01);
  putchar(0x00);
  putchar(0x01);
  putchar(0x00);
  putchar(0x80);
  putchar(c.r);
  putchar(c.g);
  putchar(c.b);
  putchar(0x00);
  putchar(0x00);
  putchar(0x00);
  putchar(0x02);
  putchar(0x02);
  putchar(0x44);
  putchar(0x01);
  putchar(0x00);

}
void walk(struct point p, struct point max) {
  if (p.x > 0) {
    if (raster[p.x-1][p.y].a) {
      write(p.x-1, p.y, near(raster[p.x][p.y]));
      stack[sp++] = (struct point){p.x-1,p.y};
    }
  }
  if (p.y > 0) {
    if (raster[p.x][p.y-1].a) {
      write(p.x, p.y-1, near(raster[p.x][p.y]));
      stack[sp++] = (struct point){p.x,p.y-1};
    }
  }
  if (p.x < max.x) {
    if (raster[p.x+1][p.y].a) {
      write(p.x+1, p.y, near(raster[p.x][p.y]));
      stack[sp++] = (struct point){p.x+1,p.y};
    }
  }
  if (p.y < max.y) {
    if (raster[p.x][p.y+1].a) {
      write(p.x, p.y+1, near(raster[p.x][p.y]));
      stack[sp++] = (struct point){p.x,p.y+1};
    }
  }
}
void gif_header(void) {
  /* header */
  printf("GIF89a");
  /* logical screen info */
  printint(WIDTH);
  printint(HEIGHT);
  putchar(0x70); /* R8G8B8 no palette */
  putchar(0x00); /* background color index (meaningless) should be 0x00*/
  putchar(0x00); /* Pixel Aspect Ratio (no information) */

  putchar(0x21); /* Extension */
  putchar(0xff);
  putchar(0x0b);
  printf("NETSCAPE2.0");
  putchar(0x03);
  putchar(0x01);
  putchar(0x01);
  putchar(0x00);
  putchar(0x00);
}

int main(int argc, char * argv[]) {
  unsigned int i;
  unsigned int j;
  struct point x;
  unsigned int cont = 1;
  for (i=0;i<WIDTH;i++) {
    for (j=0;j<HEIGHT;j++) {
      raster[i][j] = (struct color){0x80,0x80,0x80,0xff};
    }
  }
  srand(time(NULL));
  stack[sp++] = (struct point){rand()%WIDTH,rand()%HEIGHT};

  gif_header();

  while (cont) {
    i = 0;
    j = (unsigned int)rand() % sp;
    x = stack[j];
    while (x.x == WIDTH && x.y == HEIGHT) {
      j = (j+1)%sp;
      x = stack[j];
      i++;
      if (i>PIXELS) {
        putchar(';'); /* gif trailer */
        return EXIT_SUCCESS;
      }
    }
    stack[j] = max;
    walk(x,max);
  }
  putchar(';'); /* gif trailer */
  return EXIT_SUCCESS;
}
