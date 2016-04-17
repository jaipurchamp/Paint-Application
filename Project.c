#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>
#define INCR 1
#define DECR -1
#define PREDX 1
#define PREDY 0



int    gm,gd=DETECT,button,x,y,ch,fg,bg,dx, dy, e, e_inc, e_noinc,j,w,h;
union  REGS i,o;
struct SREGS s ;
char   str[10];
char   buffer[3000];
int    hourglass[32]={
		/*hourglass screen mask*/
		0x0000,0x0000,0x0000,0x0000,
		0x8001,0xc003,0xf00f,0xfc3f,
		0xfc3f,0xf00f,0xc003,0x8001,
		0x0000,0x0000,0x0000,0x0000,
		/*the mouse ptr bitmap*/
		0xffff,0x8001,0xffff,0x8001,
		0x4002,0x2004,0x1008,0x0240,
		0x0240,0x0810,0x2004,0x4002,
		0x8001,0xffff,0x8001,0xffff};
int plus[32]={
		/*+ screen mask*/
		0xfe7f,0xfe7f,0xfe7f,0xfe7f,
		0xfe7f,0xfe7f,0xfe7f,0x0000,
		0x0000,0xfe7f,0xfe7f,0xfe7f,
		0xfe7f,0xfe7f,0xfe7f,0xfe7f,
		/*+mouseptr bitmap*/
		0x0180,0x0180,0x0180,0x0180,
		0x0180,0x0180,0x0180,0xfe7f,
		0xfe7f,0x0180,0x0180,0x0180,
		0x0180,0x0180,0x0180,0x0180};
int rubber[32]={
		/*Eraser screen mask*/
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		/*eraser bitmap*/
		0xffff,0x8001,0x8001,0x8001,
		0x8001,0x8001,0x8001,0x8001,
		0x8001,0x8001,0x8001,0x8001,
		0x8001,0x8001,0x8001,0xffff};
int hand[32]={/*hand-screenmask+pointer bitmap*/
		0xe1ff,0xe1ff,0xe1ff,0xe1ff,
		0xe1ff,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x1e00,0x1200,0x1200,0x2100,
		0x13ff,0x1249,0x1249,0xf249,
		0x9001,0x9001,0x9001,0x8001,
		0x8001,0x8001,0xffff,0x0000};

int pencil[32] = {
		0x3ff ,0x5ff ,0x6ff ,0x1b7f,
		0x1dbf,0x6edf,0xb76f,0xdbb7,
		0xeddb,0xf6ed,0xfb76,0xfdb8,
		0xfed9,0xff63,0xffa7,0xffcf,

		0xfc00,0xfa00,0xf900,0xe480,
		0xe240,0x9120,0x4890,0x2448,
		0x1224,0x912 ,0x489 ,0x247 ,
		0x126 ,0x9c  ,0x58  ,0x30   };

int bottle[32]={
		0x0000,0xbffe,0xdffe,0xeffe,
		0xf7fe,0xf7fe,0xf7fe,0xf7fe,
		0xf000,0xf000,0xf000,0xf7fe,
		0xf7fe,0xf7fe,0xf7fe,0xf000,
		0xffff,0x4001,0x2001,0x1001,
		0x801 ,0x801 ,0x801 ,0x801 ,
		0xfff ,0xfff ,0xfff ,0x801 ,
		0x801 ,0x801 ,0x801 ,0xfff };

char  NEW[]={"Creates A New File"};
char  OPEN[]={"Opens An Existing File"};
char  SAVE[]={"Saves The Active File"};
char  ABOUT[]={"Displays Information About Program"};
char  PENCIL[]={"Draws A Free Form Line One Pixel Width"};
char  PAINT[]={"Fills An Area With Current Drawing Colour select draw color by right click"};
char  RECTANGLE[]={"Draws A Rectangle"};
char  ELLIPSE[]={"Draws An Ellipse"};
char  LINE[]={"Draws A Straight Line"};
char  POLYLINE[]={"Draws A Polygon"};
char  COLOUR[]={"Left  Click -> Foreground Color  Right Click -> Background Color"};
char  ERASER[]={"Erases A Portion Of Figure"};
char  EXIT[]={"Quits Program"};

void initialize();
void structure();
int  getresponse();
int  check();
int  initmouse();
void showmouseptr();
void restrictmouseptr(int,int,int,int);
void getmousepos();
void hidemouseptr();
void freehand();
void rect();
void circ();
void lin();
void mypoly();
void paint();
void eraser();
void changemouseptr(int *);
void printmousepos();
void New();
void Open();
int  restore(int,int,int,int,char*);
void Save();
void About();
void bressline ( int, int, int, int );
void bressline1( int, int, int, int);
void drawline ( int , int , int , int , int , int );
void drawline1 ( int , int , int, int , int, int );
void Ellipse(int ,int ,int ,int );
void Ellipse1(int ,int ,int ,int );
void save(int,int ,int,int,char*);
void clearline();

void main()
{
	int pch=1;

	clrscr();
	initialize();
	structure();
	showmouseptr();


while(1)
{


   setcolor(fg);
   rectangle(35,40,600,450);

	ch=getresponse();
	if(ch==0||ch==35)
	ch=pch;

	switch(ch)
	{
	case 1:
		  rect();
		  break;
	case 2:
		  freehand();
		  break;
	case 3:
		  circ();
		  break;
	case 4:
		  eraser();
		  break;
	case 5:
		  lin();
		  break;
	case 6:
		  paint();
		  break;
	case 7:
		  mypoly();
		  break;
	case 30:
		  if(ch!=pch)
		  New();
		  break;
	case 31:
		  if(ch!=pch)
		  Open();
		  break;
	case 32:
		  if(ch!=pch)
		  Save();
		  break;
	case 33:
		  if(ch!=pch)
		  About();
		  break;
	case 34:
		  if(ch!=pch)
		  closegraph();
		  remove("c:/temp.tmp");
		  exit(0);
	default:
		  if(button==1)
		  {
		  fg=ch-10;
		  setfillstyle(SOLID_FILL,fg);
		  setcolor(15);
		  bar(2,445,17,465);
		  rectangle(2,445,17,465);
		  setcolor(fg);
		  rectangle(35,40,600,450);
		  }
		  else if(button==2)
		  {
		  bg=ch-10;
		  setcolor(15);
		  setfillstyle(SOLID_FILL,bg);
		  bar(10,455,25,475);
		  rectangle(10,455,25,475);
		  setfillstyle(SOLID_FILL,fg);
		  bar(2,445,17,465);
		  rectangle(2,445,17,465);
		  setcolor(fg);
		  }
		  else
		  setcolor(4);
		  outtextxy(35,457,COLOUR);
		  setcolor(fg);
		  break;



	}
	if(ch>30&&ch<=33||ch>=10&&ch<=25)
	pch=pch;
	else
	pch=ch;
}
}
void initialize()
{
	initgraph(&gd,&gm,"c:\\turboc30\\bgi");

	if(initmouse()==0)
	{
	closegraph();
	printf("\nMouse Driver is not present");
	getch();
	exit(0);
	}

}

initmouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return(o.x.ax);
}

void showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
}

void restrictmouseptr(int x1,int y1,int x2,int y2)
{
	i.x.ax=7;
	i.x.cx=x1;
	i.x.dx=x2;
	int86(0x33,&i,&o);
	i.x.ax=8;
	i.x.cx=y1;
	i.x.dx=y2;
	int86(0x33,&i,&o);
}

void getmousepos()
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	button=o.x.bx;
	x=o.x.cx;
	y=o.x.dx;
}

void hidemouseptr()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
}
void printmousepos()
{
	int x1,y1,x2,y2,i,j,col;

	col=getcolor();
	setcolor(11);
	x1=515+textwidth("x:");
	y1=455+1;
	x2=x1+textwidth(str);
	y2=y1+textheight(str);

	for(i=x1;i<=x2;i++)
		for(j=y1;j<=y2;j++)
			putpixel(i,j,7);

	outtextxy(515,455,"x:    y:    ");
	sprintf(str,"%3d   %3d",x-35,y-40);
	outtextxy(x1,y1,str);

	setcolor(col);
}

void changemouseptr ( int *shape )
{
	i.x.ax = 9 ;  /* service number */
	i.x.bx = 0 ;  /* actual cursor position from left */
	i.x.cx = 0 ;  /* actual cursor position from top */
	i.x.dx = ( unsigned ) shape ;  /* offset address of pointer image */
	segread ( &s ) ;
	s.es = s.ds ;  /* segment address of pointer */
	int86x ( 0x33, &i, &i, &s ) ;

}
int check()
{

	int row1,row2,i,flag=0,col1,col2;

	for(row1=100,i=1;i<=7;i++,row1=row1+45)
	{
	row2=row1+20;

		if(x>7&&x<27&&y>row1&&y<row2)
		{
		flag=1;
		goto down;
		}

	}

	for(row1=50,i=10;i<=25;i++,row1=row1+25)
	{
	row2=row1+20;

		if(x>610&&x<630&&y>row1&&y<row2)
		{
		flag=1;
		goto down;
		}

	}

	for(i=30;i<=34;i++)
	{
	if(i==30)
	{ col2=260;col1=220;  }
	else if(i==31)
	{
	  col1=270;col2=310;
	}
	else if(i==32)
	{
	  col1=320;col2=360;
	}
	else if(i==33)
	{
	  col1=370;col2=420;     }
	else
	{  col1=427;col2=465; }


		if(x>col1&&x<col2&&y>20&&y<35)
		{
		if(button==1)
		{
		  flag=1;
		  break;   }

		}

	}


down:
	if(flag==1)
	return i;
	else
	return 0;

}

int getresponse()
{
	int col,X;
	static int bn;
	static int pbn;
	static int flag;

	col=getcolor();
	getmousepos();
	bn=check();

	if(bn>=0&&bn<=7||bn>=10)
	{
		if(pbn!=bn)
		{
		switch(pbn)
		{

		case 1:
			  setcolor(15);
			  hidemouseptr();
			  rectangle(7,100,27,120);
			  showmouseptr();
			  break;
		case 2:
			  setcolor(15);
			  hidemouseptr();
			  rectangle(7,145,27,165);
			  showmouseptr();
			  break;
		case 3:
			  setcolor(15);
			  hidemouseptr();
			  rectangle(7,190,27,210);
			  showmouseptr();
			  break;
		case 4:
			  setcolor(15);
			  hidemouseptr();
			  rectangle(7,235,27,255);
			  showmouseptr();
			  break;
		case 5:
			  setcolor(15);
			  hidemouseptr();
			  rectangle(7,280,27,300);
			  showmouseptr();
			  break;
		case 6:
			  setcolor(15);
			  hidemouseptr();
			  rectangle(7,325,27,345);
			  showmouseptr();
			  break;
		case 7:
			  setcolor(15);
			  hidemouseptr();
			  rectangle(7,370,27,390);
			  showmouseptr();
			  break;
		case 0:
			  clearline();


	    }
	    }

		switch(bn)
		{
		case 1:
			  if(pbn!=bn)
			  {
				setcolor(RED);
				hidemouseptr();
				rectangle(7,100,27,120);
				showmouseptr();
				flag=0;
				outtextxy(35,457,RECTANGLE);
			  }
			  else if(button==1)
			  {
				setcolor(13);
				hidemouseptr();
				rectangle(7,100,27,120);
				showmouseptr();
				flag=1;
			  }
			  break;
		case 2:
			  if(pbn!=bn)
			  {
				setcolor(RED);
				hidemouseptr();
				rectangle(7,145,27,165);
				showmouseptr();
				flag=0;
				outtextxy(35,457,PENCIL);

			  }
			  else if(button==1)
			  {
				  setcolor(13);
				  hidemouseptr();
				  rectangle(7,145,27,165);
				  showmouseptr();
				  flag=1;

			  }
			  break;
		case 3:
			  if(pbn!=bn)
			  {
				setcolor(RED);
				hidemouseptr();
				rectangle(7,190,27,210);
				showmouseptr();
				flag=0;
				outtextxy(35,457,ELLIPSE);

			  }
			  else if(button==1)
			  {
				setcolor(13);
				hidemouseptr();
				rectangle(7,190,27,210);
				showmouseptr();
				flag=1;
			  }
			  break;
		case 4:
			  if(pbn!=bn)
			  {
				setcolor(RED);
				hidemouseptr();
				rectangle(7,235,27,255);
				showmouseptr();
				flag=0;
				outtextxy(35,457,ERASER);

			  }
			  else if(button==1)
			  {
				  setcolor(13);
				  hidemouseptr();
				  rectangle(7,235,27,255);
				  showmouseptr();
				  flag=1;
			  }
			  break;
		case 5:
			  if(pbn!=bn)
			  {
				setcolor(RED);
				hidemouseptr();
				rectangle(7,280,27,300);
				showmouseptr();
				flag=0;
				outtextxy(35,457,LINE);

			  }
			  else if(button==1)
			  {
				  setcolor(13);
				  hidemouseptr();
				  rectangle(7,280,27,300);
				  showmouseptr();
				  flag=1;
			  }
			  break;
		case 6:
			  if(pbn!=bn)
			  {
			  setcolor(RED);
			  hidemouseptr();
			  rectangle(7,325,27,345);
			  showmouseptr();
			  flag=0;
			  outtextxy(35,457,PAINT);

			  }
			  else if(button==1)
			  {
				  setcolor(13);
				  hidemouseptr();
				  rectangle(7,325,27,345);
				  showmouseptr();
				  flag=1;
			  }
			  break;
		case 7:
			  if(pbn!=bn)
			  {
				setcolor(RED);
				hidemouseptr();
				rectangle(7,370,27,390);
				showmouseptr();
				flag=0;
				outtextxy(35,457,POLYLINE);

			  }
			  else if(button==1)
			  {
				  setcolor(13);
				  hidemouseptr();
				  rectangle(7,370,27,390);
				  showmouseptr();
				  flag=1;
			  }

			  break;
		case 30:
			  if(button==1)
			  {
				  flag=1;
			  }
			  else if(pbn!=bn)
			  {
			  clearline();
			  setcolor(4);
			  outtextxy(35,457,NEW);
			  flag=0;
			  }
			  break;

		case 31:
			  if(button==1)
			  {
				  flag=1;
			  }
			  else if(pbn!=bn)
			  {
			  clearline();
			  setcolor(4);
			  outtextxy(35,457,OPEN);
			  flag=0;
			  }

			  break;
		case 32:
			  if(button==1)
			  {
				  flag=1;
			  }
			  else if(pbn!=bn)
			  {
			  clearline();
			  setcolor(4);
			  outtextxy(35,457,SAVE);
			  flag=0;
			  }

			  break;

		case 33:
			  if(button==1)
			  {
				  flag=1;
			  }
			  else if(pbn!=bn)
			  {
			  clearline();
			  setcolor(4);
			  outtextxy(35,457,ABOUT);
			  flag=0;
			  }

			  break;

		case 34:
			  if(button==1)
			  {
				  flag=1;
			  }
			  else if(pbn!=bn)
			  {
			  clearline();
			  setcolor(4);
			  outtextxy(35,457,EXIT);
			  flag=0;
			  }

			  break;
		case 0:
			  clearline();
		default:
			 flag=1;


		}



	}

	   setcolor(col);
	   pbn=bn;
	   if(flag==1)
	   {
	   flag=0;
	   return (bn);
	   }
	   else
	   return (0);
}

void freehand()
{
	int px=1,py=1,flag=0,but;

	while(1)
	{
	getmousepos();
	if(x>=35&&x<=600&&y>=40&&y<=450)
	{
	changemouseptr(pencil);
		 if(px!=x||py!=y)
		 printmousepos();

		  if(button==1)
		  {
			if(flag==0)
			{
				hidemouseptr();
				flag=1;
			}
			else
				line(px,py,x,y);
		   }
		   else if(flag!=0)
		   {

			showmouseptr();
			flag=0;

		   }
		   px=x;
		   py=y;
		}
		else
		{
			changemouseptr(hand);
			showmouseptr();
			break;
		}

	}

}

void rect()
{
	int ix,iy,fx,fy,px=1,py=1,but,flag=0,tx,ty,t=0;


	  while(1)
	  {
	  getmousepos();
		if(x>=35&&x<=600&&y>=40&&y<=450)
		{
		  if(button==1 && t==0)
		  {
		    tx=x;ty=y;
		    t=1;
		  }
		changemouseptr(plus);
			 if(px!=x||py!=y)
			 printmousepos();


			 if(button==1&&flag==0)
			 {
			 ix=x;iy=y;

			 flag=1;
			 }
			 else if(button==1 && flag==1 )
			 {
			 fx=x;fy=y;
			 hidemouseptr();
			 setcolor(fg);
			 rectangle(tx,ty,fx,fy);
			 setcolor(bg);
			 rectangle(tx,ty,fx,fy);
			 showmouseptr();
			 flag=0;
			 }
			 if(button!=1)
			 {
			   setcolor(fg);
			   rectangle(tx,ty,fx,fy);
			   t=0;
			 }

		}

		else
		{
		  if(t==1)
		  {
		  setcolor(fg);
	  rectangle(tx,ty,fx,fy);
		  }
		  t==0;
		  changemouseptr(hand);
		  break;
		}
		    px=x;
		    py=y;

	  }

}



void circ()
{
	int ix,iy,but,flag=0,p,q,a,b,p1,q1,a1,b1,px,py;

	while(1)
	{
		getmousepos();
		if(x>=35&&x<=600&&y>=40&&y<=450)
		{
			 changemouseptr(pencil);
			 if(px!=x||py!=y)
			 {
				printmousepos();
			 }
			 if(button==1)
			 {
				if(flag==0)
				{
					hidemouseptr();
					ix=x;iy=y;
					p1=q1=a1=b1=0;
					flag=1;
				}
				else
				{
					p=(ix+x)/2;
					q=(iy+y)/2;
					a=abs(ix-p);
					b=abs(iy-q);

					if(p1!=p||q1!=q)
					{
						Ellipse1(p1,q1,a1,b1);
						Ellipse(p,q,a,b);
						p1=p;q1=q;a1=a;b1=b;
					}
				}
			 }
			 else if(flag!=0)
			 {
				showmouseptr();
				flag=0;
			 }

			 px=x;
			 py=y;
		}
		else
		{
			 changemouseptr(hand);
			 showmouseptr();
				break;

		}

	}

}
void lin()
{
	int ix,iy,px=1,py=1,but,flag=0;

	while(1)
	{
		getmousepos();
		if(x>=35&&x<=600&&y>=40&&y<=450)
		{
			 changemouseptr(pencil);
			 if(px!=x||py!=y)
			 {
				printmousepos();
			 }
			 if(button==1)
			 {
				if(flag==0)
				{
					hidemouseptr();
					ix=px=x;iy=py=y;
					flag=1;
				}
				else
				{
					if(px!=x||py!=y)
					{
						bressline1(ix,iy,px,py);
						bressline(ix,iy,x,y);
					}
				}
			 }
			 else if(flag!=0)
			 {
				showmouseptr();
				flag=0;
			 }

			 px=x;
			 py=y;
		}
		else
		{
		    changemouseptr(hand);
		    break;
		}

	}


}
void mypoly()
{
	int ix,iy,fx,fy,px=1,py=1,but,flag=0;

	  while(1)
	  {
	  getmousepos();
		if(x>=35&&x<=600&&y>=40&&y<=450)
		{
		changemouseptr(pencil);
			 if(px!=x||py!=y)
			 printmousepos();


		      /*	 if(button==1&&flag==0)
			 {
			 ix=x;iy=y;
			 flag=1;
			 }*/
			 if(button==1)
			 {
			 hidemouseptr();
			// line(ix,iy,x,y);
			 lin();
			 showmouseptr();
			 ix=x;
			 iy=y;
			 }


		}
		else
		{
		 changemouseptr(hand);
		 break;
		}
		    px=x;
		    py=y;
	  }
}
void paint()
{
	int px=1,py=1,but;
	setfillstyle(SOLID_FILL,bg);

	  while(1)
	  {
	  getmousepos();

		if(x>=35&&x<=600&&y>=40&&y<=450)
		{
		changemouseptr(bottle);

		      if(px!=x||py!=y)
			 printmousepos();

			 if(button==1)
			 {
			 hidemouseptr();
			 floodfill(x,y,fg);
			 showmouseptr();
			 }
		}
		else
		{
		 changemouseptr(hand);
		 break;
		}
		    px=x;
		    py=y;
	  }



}
void eraser()
{

  int but,px,py,i,j;

	  while(1)
	  {
	    getmousepos();
		if(x>=36&&x<=583&&y>=41&&y<=433)
		{
		changemouseptr(rubber);
			 if(px!=x||py!=y)
			 printmousepos();

			 if(button==1)
			 {
			 hidemouseptr();
			 for(i=y;i<=y+16;i++)
			    for(j=x;j<=x+16;j++)
			    {
			    putpixel(j,i,bg);
			    }
			 showmouseptr();
			 }
		}
		else
		{
		changemouseptr(hand);
		break;
		}
		    px=x;
		    py=y;
	  }
}



void structure()
{
	int i,j,row;
	setfillstyle(SOLID_FILL,8);
	setcolor(15);
	bar(0,0,640,480);                    // screen back ground
	settextstyle(SMALL_FONT,HORIZ_DIR,4);

	for(i=0,row=50;i<=15;i++,row+=25)
	{

	setfillstyle(SOLID_FILL,i);            // color tool bars
	bar(610,row,630,row+20);
	rectangle(610,row,630,row+20);

	}

	setfillstyle(SOLID_FILL,8);           // draw tool bars
	setcolor(15);
	for(i=0,row=100;i<=6;i++,row+=45)
	{
	bar(7,row,27,row+20);
	rectangle(7,row,27,row+20);
	}

	setcolor(11);
	rectangle(9,104,25,116);           // rectangle tool bar

	line(9,147,15,147);                // pencil tool
	line(9,148,14,148);
	line(9,149,13,149);
	line(9,150,12,150);
	line(9,151,11,151);
	line(9,152,10,152);
	line(9,147,9,153);
	line(15,147,24,156);
	line(9,153,18,162);
	line(24,156,18,162);
	line(15,147,9,153);
	line(12,150,21,159);

	circle(17,200,8);                   // circle tool

	setcolor(11);                       // eraser tool
	setfillstyle(SOLID_FILL,11);
	bar3d(9,246,17,252,8,1);

	setcolor(11);
	line(10,283,24,297);               // line tool

	rectangle( 9,333,25,343);          // fill area tool
	arc(17,333,0,180,7);

	line(12,388,22,388);               // polygon tool
	line(12,388,9,380);
	line(22,388,25,380);
	line(17,372,25,380);
	line(17,372,9,380);

	fg=15;                             // assign colors
	bg=0;
	setfillstyle(SOLID_FILL,bg);       // bottom corner symbol
	bar(10,455,25,475);
	setcolor(15);
	rectangle(10,455,25,475);
	setfillstyle(SOLID_FILL,fg);
	bar(2,445,17,465);
	rectangle(2,445,17,465);
	setcolor(fg);
	rectangle(35,40,600,450);
	setfillstyle(SOLID_FILL,bg);
	floodfill(320,240,fg);

       //	outtextxy(230,20,"NEW    OPEN   SAVE   ABOUT  EXIT");
	setcolor(0);
	bar(220,20,260,35);
	bar(270,20,310,35);
	bar(320,20,360,35);
	bar(370,20,420,35);
	bar(427,20,465,35);
	setcolor(15);
	rectangle(220,20,260,35);
	rectangle(270,20,310,35);
	rectangle(320,20,360,35);
	rectangle(370,20,420,35);
	rectangle(427,20,465,35);
	outtextxy(230,20,"NEW     OPEN    SAVE     ABOUT    EXIT");

}
void bressline ( int x1, int y1, int x2, int y2 )
{
	int incdec, t, i ;

	if ( x1 > x2 )
	{
		t = x1 ; x1 = x2 ; x2 = t ;
		t = y1 ; y1 = y2 ; y2 = t ;
	}

	dx = x2 - x1 ; dy = y2 - y1 ;

	if ( dx == 0 ) /* vertical line */
	{
		if ( y1 > y2 )
		{
			t = y1 ; y1 = y2 ; y2 = t ;
		}

		for ( i = y1,j=0 ; i <= y2 ; i++,j++ )
		{
			buffer[j]=getpixel (x1,i);
			putpixel ( x1, i,fg) ;
		}
		return ;
	}

	if ( dy == 0 )  /* horizontal line */
	{
		for ( i = x1,j=0 ; i < x2 ; i++ ,j++)
		{
			buffer[j]=getpixel (i,y1);
			putpixel ( i, y1, fg ) ;
		}
		return ;
	}
    /* 0 < m < 1 */
	if ( dy < dx && dy > 0 )
	{
		e_noinc = 2 * dy ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline ( x1, y1, x2, y2, PREDX, INCR ) ;
	}
	/* m = 1 */
	if ( dy == dx && dy > 0 )
	{
		e_noinc = 2 * dy ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline ( x1, y1, x2, y2, PREDX, INCR ) ;
	}
	/* 1 < m < infinity */
	if ( dy > dx && dy > 0 )
	{
		e_noinc = 2 * dx ;
		e = 2 * dx - dy ;
		e_inc = 2 * ( dx - dy ) ;
		drawline ( x1, y1, x2, y2, PREDY, INCR ) ;
	}
	/* 0 > m > -1 */
	if ( -dy < dx && dy < 0 )
	{
		dy = -dy ;
		e_noinc = 2 * dy ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline ( x1, y1, x2, y2, PREDX, DECR ) ;
	}
	/* m = -1 */
	if ( dy == -dx && dy < 0 )
	{
		dy = -dy ;
		e_noinc = ( 2 * dy ) ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline ( x1, y1, x2, y2, PREDX, DECR ) ;
	}
	/* -1 > m > 0 */
	if ( -dy > dx && dy < 0 )
	{
		dx = -dx ;
		e_noinc = - ( 2*dx ) ; e = 2 * dx - dy ;
		e_inc = - 2 * ( dx - dy ) ;
		drawline ( x2, y2, x1, y1, PREDY, DECR ) ;
	}

}
void bressline1( int x1, int y1, int x2, int y2 )
{
	int incdec, t, i ;

	if ( x1 > x2 )
	{
		t = x1 ; x1 = x2 ; x2 = t ;
		t = y1 ; y1 = y2 ; y2 = t ;
	}

	dx = x2 - x1 ; dy = y2 - y1 ;

	if ( dx == 0 ) /* vertical line */
	{
		if ( y1 > y2 )
		{
			t = y1 ; y1 = y2 ; y2 = t ;
		}

		for ( i = y1,j=0 ; i <= y2 ; i++,j++ )
		{
			putpixel ( x1, i, buffer[j] ) ;
		}
		return ;
	}

	if ( dy == 0 )  /* horizontal line */
	{
		for ( i = x1,j=0 ; i < x2 ; i++ ,j++)
		{
			putpixel ( i, y1,buffer[j] ) ;
		}
		return ;
	}
    /* 0 < m < 1 */
	if ( dy < dx && dy > 0 )
	{
		e_noinc = 2 * dy ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline1( x1, y1, x2, y2, PREDX, INCR ) ;
	}
	/* m = 1 */
	if ( dy == dx && dy > 0 )
	{
		e_noinc = 2 * dy ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline1( x1, y1, x2, y2, PREDX, INCR ) ;
	}
	/* 1 < m < infinity */
	if ( dy > dx && dy > 0 )
	{
		e_noinc = 2 * dx ;
		e = 2 * dx - dy ;
		e_inc = 2 * ( dx - dy ) ;
		drawline1 ( x1, y1, x2, y2, PREDY, INCR ) ;
	}
	/* 0 > m > -1 */
	if ( -dy < dx && dy < 0 )
	{
		dy = -dy ;
		e_noinc = 2 * dy ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline1 ( x1, y1, x2, y2, PREDX, DECR ) ;
	}
	/* m = -1 */
	if ( dy == -dx && dy < 0 )
	{
		dy = -dy ;
		e_noinc = ( 2 * dy ) ;
		e = 2 * dy - dx ;
		e_inc = 2 * ( dy - dx ) ;
		drawline1( x1, y1, x2, y2, PREDX, DECR ) ;
	}
	/* -1 > m > 0 */
	if ( -dy > dx && dy < 0 )
	{
		dx = -dx ;
		e_noinc = - ( 2*dx ) ; e = 2 * dx - dy ;
		e_inc = - 2 * ( dx - dy ) ;
		drawline1( x2, y2, x1, y1, PREDY, DECR ) ;
	}

}



void drawline ( int x1, int y1, int x2, int y2, int pred, int incdec )
{
	int i, start, end, var ;
	if ( pred == PREDX )
	       {	start = x1 ;  end = x2 ;  var = y1 ;}
	else
	 {	start = y1 ;  end = y2 ;  var = x1 ;}


	for ( i = start,j=0 ; i <= end ; i++,j++ )
	{
		if ( pred == PREDY )
		{
			buffer[j]=getpixel (var,i);
			putpixel ( var, i, fg ) ;
		}
		else
		{
			buffer[j]=getpixel (i,var);
			putpixel ( i, var, fg ) ;
		}

		if ( e < 0 )
			e += e_noinc ;
		else
		{
			var += incdec ;
			e += e_inc ;
		}
	}

}
void drawline1 ( int x1, int y1, int x2, int y2, int pred, int incdec )
{
	int i, start, end, var ;
	if ( pred == PREDX )
	{
		start = x1 ;  end = x2 ;  var = y1 ;
	}
	else
	{
		start = y1 ;  end = y2 ;  var = x1 ;
	}

	for ( i = start,j=0 ; i <= end ; i++,j++ )
	{
		if ( pred == PREDY )
		{
			putpixel ( var, i,buffer[j]) ;
		}
		else
		{
			putpixel ( i, var, buffer[j] ) ;
		}

		if ( e < 0 )
			e += e_noinc ;
		else
		{
			var += incdec ;
			e += e_inc ;
		}
	}

}

void Ellipse(int xc,int yc,int a0,int b0)
{
	int x = 0;
	int y = b0;

	long a= a0;
	long b = b0;


	long Asquared = a*a;
	long TwoAsquared = 2 * Asquared;
	long Bsquared = b*b;
	long TwoBsquared = 2 * Bsquared;

	long d;
	long dx,dy;

	d = Bsquared - Asquared*b + Asquared/4;
	dx = 0;
	dy = TwoAsquared *b;

	j=0;

	while (dx < dy)
	{

	buffer[j]=getpixel(xc + x, yc + y);j++;
	buffer[j]=getpixel(xc - x, yc + y);j++;
	buffer[j]=getpixel(xc + x, yc - y);j++;
	buffer[j]=getpixel(xc - x, yc - y);j++;

	putpixel(xc + x, yc + y, fg);
	putpixel(xc - x, yc + y, fg);
	putpixel(xc + x, yc - y, fg);
	putpixel(xc - x, yc - y, fg);

		if (d > 0)
		{
			--y;
			dy -= TwoAsquared;
			d-=dy;
		}

		++x;
		dx+=TwoBsquared;
		d += Bsquared + dx;
	}

	d += (3 *(Asquared-Bsquared)/2 -(dx+dy)) / 2;

	while (y >=0)
	{
	buffer[j]=getpixel(xc + x, yc + y);j++;
	buffer[j]=getpixel(xc - x, yc + y);j++;
	buffer[j]=getpixel(xc + x, yc - y);j++;
	buffer[j]=getpixel(xc - x, yc - y);j++;

	putpixel(xc + x, yc + y, fg);
	putpixel(xc - x, yc + y, fg);
	putpixel(xc + x, yc - y, fg);
	putpixel(xc - x, yc - y, fg);

		if (d < 0) {
			++x;
			dx+= TwoBsquared;
			d+= dx;
		}

		--y;
		dy -= TwoAsquared;
		d+= Asquared - dy;
	}
}
void Ellipse1(int xc,int yc,int a0,int b0)
{
	int x = 0;
	int y = b0;

	long a= a0;
	long b = b0;


	long Asquared = a*a;
	long TwoAsquared = 2 * Asquared;
	long Bsquared = b*b;
	long TwoBsquared = 2 * Bsquared;

	long d;
	long dx,dy;

	d = Bsquared - Asquared*b + Asquared/4;
	dx = 0;
	dy = TwoAsquared *b;

	j=0;

	while (dx < dy)
	{
	putpixel(xc + x, yc + y,buffer[j]);j++;
	putpixel(xc - x, yc + y,buffer[j]);j++;
	putpixel(xc + x, yc - y,buffer[j]);j++;
	putpixel(xc - x, yc - y,buffer[j]);j++;

		if (d > 0)
		{
			--y;
			dy -= TwoAsquared;
			d-=dy;
		}

		++x;
		dx+=TwoBsquared;
		d += Bsquared + dx;
	}

	d += (3 *(Asquared-Bsquared)/2 -(dx+dy)) / 2;

	while (y >=0)
	{
	putpixel(xc + x, yc + y,buffer[j]);j++;
	putpixel(xc - x, yc + y,buffer[j]);j++;
	putpixel(xc + x, yc - y,buffer[j]);j++;
	putpixel(xc - x, yc - y,buffer[j]);j++;

		if (d < 0) {
			++x;
			dx+= TwoBsquared;
			d+= dx;
		}

		--y;
		dy -= TwoAsquared;
		d+= Asquared - dy;
	}
}
void New()
{
	hidemouseptr();
	structure();
	showmouseptr();
}
void Open()
{
	int i;
	char st[13];
	setcolor(15);
	hidemouseptr();
	save(220,200,420,280,"c:/temp.tmp");

	setfillstyle(SOLID_FILL,15);
	bar(220,200,420,280);
	setfillstyle(SOLID_FILL,8);
	bar(221,201,419,216);
	settextstyle(SMALL_FONT,HORIZ_DIR,5);

	outtextxy(222,201," OPEN");
	settextstyle(SMALL_FONT,HORIZ_DIR,4);
	setcolor(8);
	outtextxy(222,230,"     Enter the File Name");
	w=textwidth("a");
	h=textheight("a");

	bar(221,263,419,279);
	setcolor(15);
	outtextxy(320-(3*w),265,"< OK >");
	setcolor(8);
	for(i=0;st[i-1]!='\n';i++)
	{
	st[i]=getch();

	if(st[i]==13||i>11)
	{
	st[i]='\0';
	break;
	}
	else if(st[i]==27)
	{
	goto Down;
	}

	st[i+1]='\0';
	outtextxy(320-(6*w),245,st);
	}

	if(restore(36,41,599,449,st)==0)
	{
	setfillstyle(SOLID_FILL,15);
	bar(220,200,420,280);
	setfillstyle(SOLID_FILL,8);
	bar(221,201,419,216);
	settextstyle(SMALL_FONT,HORIZ_DIR,5);
	setcolor(15);
	outtextxy(222,201," ERROR!");
	settextstyle(SMALL_FONT,HORIZ_DIR,4);
	setcolor(8);
	outtextxy(265,239,"Incorrect File Name!");

	bar(221,263,419,279);
	setcolor(15);
	getch();
	Down:
	restore(220,200,420,280,"c:/temp.tmp");
	}
	remove("c:/temp.tmp");
	showmouseptr();
	setcolor(fg);

}

void About()
{

	int i,w,col;
	char st[13];
	setcolor(15);
	hidemouseptr();
	save(200,195,435,285,"c:/temp.tmp");

	setcolor(8);
  for(i=0;i<180;i++)
  {
    circle(320,240,i);
    delay(5);
  }
  setcolor(15);
  outtextxy(200,300,"KONERU LAKSHMAIAH COLLEGE OF ENGINEERING");
  outtextxy(250,160,"CREATERS AND DEVELOPERS ");
  outtextxy(290,200,"SREEKANTH");
  outtextxy(290,220,"SANTOSH");
  outtextxy(290,240,"SURESH");


	flushall();
	getch();

	setfillstyle(1,16);
       //	restore(100,100,500,400,"c:/temp.tmp");
	bar(50,50,500,430);
	remove("c:/temp.tmp");
	showmouseptr();
	setcolor(fg);


}

void Save()
{
	int i,flag=0;
	char st[13];
	setcolor(15);
	hidemouseptr();
	save(220,200,420,280,"c:/temp.tmp");

	setfillstyle(SOLID_FILL,15);
	bar(220,200,420,280);
	setfillstyle(SOLID_FILL,8);
	bar(221,201,419,216);
	settextstyle(SMALL_FONT,HORIZ_DIR,5);
	outtextxy(222,201," SAVE");
	settextstyle(SMALL_FONT,HORIZ_DIR,4);
	setcolor(8);
	outtextxy(222,230,"     Enter the File Name");
	w=textwidth("a");
	h=textheight("a");
	bar(221,263,419,279);
	setcolor(15);
	outtextxy(320-(3*w),265,"< OK >");
	setcolor(8);
	for(i=0;st[i-1]!='\n';i++)
	{
	st[i]=getch();

	if(st[i]==13||i>11)
	{
	st[i]='\0';
	flag=1;
	break;
	}
	else if(st[i]==27)
	{
	goto Down;
	}

	st[i+1]='\0';
	outtextxy(320-(6*w),245,st);
	}

	Down:
	restore(220,200,420,280,"c:/temp.tmp");
	if(flag==1)
	{
	save(36,41,599,449,st);
	}

	showmouseptr();
	setcolor(fg);

}


void save(int x1,int y1,int x2,int y2,char name[13])
{
 int i,j;
 char ch;
 FILE *fp;
 x=x2;
 y=y2;
 fp=fopen(name,"wb");
 if(fp!=NULL)
 {
 for(i=x1;i<=x2;i++)
  for(j=y1;j<=y2;j++)
  {
    ch=getpixel(i,j);
    fputc(ch,fp);
  }
  fclose(fp);
 }

}


int restore(int x1,int y1,int x2,int y2, char name[13])
{
 char ch;
 int i,j;
 FILE *fp;
 fp=fopen(name,"rb");
 if(fp!='\0')
 {
 for(i=x1;i<=x2;i++)
  for(j=y1;j<=y2;j++)
  {
    ch=fgetc(fp);
    putpixel(i,j,ch);
  }
    fclose(fp);
    return 1;
 }
  else
  return 0;
}
void clearline()
{
	int i,j;
	setcolor(8);
    //	for(i=457;i<=470;i++)
    //	  line(35,i,450,i);
      for(i=35;i<=450;i++)
	 for(j=457;j<=470;j++)
		putpixel(i,j,8);

}
