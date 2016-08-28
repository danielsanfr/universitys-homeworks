#include "monitor.h"
#include "utils.h"


unsigned short *video_memory = (unsigned short *)0xB8000;


unsigned char cursor_x = 0;
unsigned char cursor_y = 0;


static void move_cursor()
{
    

    unsigned short cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4,14);                  
    outb(0x3D5,cursorLocation >> 8); 
    outb(0x3D4,15);                
    outb(0x3D5,cursorLocation);
}


static void scroll()
{
    
    unsigned char attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    unsigned short blank = 0x20 /* space */ | (attributeByte << 8);

    
    if(cursor_y >= 25)
    {
        
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        
        for (i = 24*80; i < 25*80; i++)
        {
            video_memory[i] = blank;
        }
	
        cursor_y = 24;
    }
}


void monitor_put(char c)
{
    //background colour = black (0),foreground = white (15).
    unsigned char backColour = 0;
    unsigned char foreColour = 15;

   
    unsigned char  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    unsigned short attribute = attributeByte << 8;
    unsigned short *location;

    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }
    else if (c == '\r')
    {
        cursor_x = 0;
    }
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    scroll();
    move_cursor();
}


void monitor_clear()
{
    unsigned char attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    unsigned short blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80*25; i++)
    {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}


void monitor_write(char *c)
{
    int i = 0;
    while (c[i])
    {
        monitor_put(c[i++]);
    }
}


void monitor_write_dec(unsigned int d)
{
    int n;
    int top=-1;
    char *digits="0123456789ABCDEF";
    char stack[10];

    while (d>0)
    {
        n = d % 10;
        stack[++top] = digits[n];
        d /= 10;
    }
    if (top==-1) monitor_put(digits[0]);
    while (top>=0)
    {
        monitor_put(stack[top--]);
    }
}


void monitor_write_hex(unsigned int d)
{
    int i, shiftd;
    char *digits="0123456789ABCDEF";

    for (i=0; i<8; i++)
    {
        shiftd = d >> (32 - 4 - 4*i) & 0x0F;
        monitor_put(digits[shiftd]);
    }
}

