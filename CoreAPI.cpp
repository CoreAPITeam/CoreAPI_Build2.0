#pragma once
/*
This code was created by CoreAPITeam.
Please do not use without copyright notice.
For more information visit http://www.coreengine.de.vu/ (German Homepage)
Thanks and have fun
*/
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
#include "CoreAPI.h"
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
core::CoreAPI::CoreAPI()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	text_align = ALIGN_LEFT;
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
core::CoreAPI::CoreAPI(/*167,66*/short ScreenPosX, short ScreenPosY,short ScreenW,short ScreenH,const char* cConsolecaption,bool bShowCursor)
{
	HANDLE hConsoleOutput;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO  ConsoleInfo;
    HWND console = GetConsoleWindow();

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
    coord.X = ScreenPosX;
    coord.Y = ScreenPosY;
    SetConsoleScreenBufferSize(hConsoleOutput, coord);

    MoveWindow(console, ScreenPosX, ScreenPosY, ScreenW, ScreenH, TRUE);

	SetConsoleTitleA(cConsolecaption);

	static HANDLE		hOut;
	static BOOL		firstTime = TRUE;
	CONSOLE_CURSOR_INFO 	cursorInfo;

	if( firstTime )
	{
		hOut		= GetStdHandle( STD_OUTPUT_HANDLE );
		firstTime	= FALSE;
	}

	cursorInfo.dwSize	= 10;
	cursorInfo.bVisible 	= bShowCursor;

	SetConsoleCursorInfo( hOut,
                              &cursorInfo );
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	text_align = ALIGN_LEFT;

}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
SMALL_RECT core::CoreAPI::GetRect()
{
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole,&info);
	return info.srWindow;
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::StringTextElement(std::string Text, bool visible)
{
	if(visible)
	{
		std::cout << Text << std::endl;
	}
	
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::SetFontColor(byte Color)
{
	FontColor = Color;
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::SetBGColor(byte Color)
{
	BGColor = Color*0x10;
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::Write(char *Text)
{
	SetConsoleTextAttribute(hConsole,FontColor | BGColor);
	printf("%s",Text);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::DrawLine(char CHAR,byte color,int len)
{
	SetConsoleTextAttribute(hConsole,BGColor|color);
	for (int i = 0;i<len;i++)
		printf("%c",CHAR);		
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::DrawCenterBox(int y, int w, int h,byte BorderColor,int nItems,MenuItem *Items)
{
	SMALL_RECT rect = GetRect();
	int x = ((rect.Left+rect.Right)/2)-w/2;
	DrawBox(x,y,w,h,BorderColor,nItems,Items);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::DrawBox(int x, int y, int w, int h,byte BorderColor,int nItems,MenuItem* Items)
{
	int corner[4] = {201,187,200,188};
	int line[2] = {205,186};
	COORD coord = {x,y};
	SetConsoleCursorPosition(hConsole,coord);
	//Kasten dravvn
	SetConsoleTextAttribute(hConsole,BGColor|BorderColor);
	printf("%c",corner[0]);
	DrawLine(line[0],BorderColor,w-2);
	printf("%c\n",corner[1]);
	for (int i = 0;i<h;i++)
	{
		coord.X = x;
		coord.Y = y+1+i;
		SetConsoleCursorPosition(hConsole,coord);
		printf("%c",line[1]);
		DrawLine(' ',BorderColor,w-2);
		printf("%c\n",line[1]);
	}
	coord.X = x;
	coord.Y = y+h+1;
	SetConsoleCursorPosition(hConsole,coord);
	printf("%c",corner[2]);
	DrawLine(line[0],BorderColor,w-2);
	printf("%c\n",corner[3]);
	for (int i = 0;i<(nItems-1);i++)
	{
		SetConsoleTextAttribute(hConsole,BGColor | Items[i].color);

		if (Items[i].text_align == ALIGN_CENTER)
		{
			coord.X = (x+(w/2))-(strlen(Items[i].Caption)/2);
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == ALIGN_RIGHT)
		{
			coord.X = (x+w-1)-(strlen(Items[i].Caption));
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == caption)
		{
			coord.X = x+2;
			coord.Y = y+0+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
		else
		{
			coord.X = x+1;
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
	}

}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::DrawWin(int wx, int wy, int ww, int wh,byte wBorderColor,int wnItems,MenuItem* Items)
{
	int s = {219};
	
	COORD coord = {wx,wy};
	SetConsoleCursorPosition(hConsole,coord);
	//Kasten dravvn
	SetConsoleTextAttribute(hConsole,BGColor|wBorderColor);
	printf("%c",s);
	DrawLine(s,wBorderColor,ww-2);
	printf("%c\n",s);
	for (int i = 0;i<wh;i++)
	{
		coord.X = wx;
		coord.Y = wy+1+i;
		SetConsoleCursorPosition(hConsole,coord);
		printf("%c",s);
		DrawLine(' ',wBorderColor,ww-2);
		printf("%c\n",s);
	}
	coord.X = wx;
	coord.Y = wy+wh+1;
	SetConsoleCursorPosition(hConsole,coord);
	printf("%c",s);
	DrawLine(s,wBorderColor,ww-2);
	printf("%c\n",s);
	for (int i = 0;i<(wnItems-1);i++)
	{
		SetConsoleTextAttribute(hConsole,BGColor | Items[i].color);

		if (Items[i].text_align == ALIGN_CENTER)
		{
			coord.X = (wx+(ww/2))-(strlen(Items[i].Caption)/2);
			coord.Y = wy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == ALIGN_RIGHT)
		{
			coord.X = (wx+ww-1)-(strlen(Items[i].Caption));
			coord.Y = wy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == caption)
		{
			coord.X = wx+2;
			coord.Y = wy+0+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
		else
		{
			coord.X = wx+1;
			coord.Y = wy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
	}
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::DrawCenterWin(int wy, int ww, int wh,byte wBorderColor,int wnItems,MenuItem *Items)
{
	SMALL_RECT rect = GetRect();
	int x = ((rect.Left+rect.Right)/2)-ww/2;
	DrawWin(x,wy,ww,wh,wBorderColor,wnItems,Items);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::DrawCustomWindow(const char* Char, int cx, int cy, int cw, int ch,byte cBorderColor,int cnItems,MenuItem* Items)
{
	//char corner[4] = {201,187,200,188};
	//char line[2] = {205,186};
	//Char[0];
	COORD coord = {cx,cy};
	SetConsoleCursorPosition(hConsole,coord);
	//Kasten dravvn
	SetConsoleTextAttribute(hConsole,BGColor|cBorderColor);
	printf("%c",Char[0]);
	DrawLine(Char[0],cBorderColor,cw-2);
	printf("%c\n",Char[0]);
	for (int i = 0;i<ch;i++)
	{
		coord.X = cx;
		coord.Y = cy+1+i;
		SetConsoleCursorPosition(hConsole,coord);
		printf("%c",Char[0]);
		DrawLine(' ',cBorderColor,cw-2);
		printf("%c\n",Char[0]);
	}
	coord.X = cx;
	coord.Y = cy+ch+1;
	SetConsoleCursorPosition(hConsole,coord);
	printf("%c",Char[0]);
	DrawLine(Char[0],cBorderColor,cw-2);
	printf("%c\n",Char[0]);
	for (int i = 0;i<(cnItems-1);i++)
	{
		SetConsoleTextAttribute(hConsole,BGColor | Items[i].color);

		if (Items[i].text_align == ALIGN_CENTER)
		{
			coord.X = (cx+(cw/2))-(strlen(Items[i].Caption)/2);
			coord.Y = cy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == ALIGN_RIGHT)
		{
			coord.X = (cx+cw-1)-(strlen(Items[i].Caption));
			coord.Y = cy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == caption)
		{
			coord.X = cx+2;
			coord.Y = cy+0+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
		else
		{
			coord.X = cx+1;
			coord.Y = cy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
	}

}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::DrawCustomCenterWindow(const char* Char, int cy, int cw, int ch,byte cBorderColor,int cnItems,MenuItem *Items)
{
	SMALL_RECT rect = GetRect();
	int x = ((rect.Left+rect.Right)/2)-cw/2;
	DrawCustomWindow(Char,x,cy,cw,ch,cBorderColor,cnItems,Items);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::CreateMouseButtonArea(int y_begin , int y_end, int x_begin, int x_end,core::key::MOUSE_BUTTON mb, void (*action)())
{
	y_begin=-1;
	//y_end-1;
	x_begin=-1;
	//x_end-1;
	hStdInput=GetStdHandle(STD_INPUT_HANDLE);
	hStdOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hStdInput);
	hEvent=CreateEvent(NULL,FALSE,FALSE,NULL);                  //Event is created non-signaled (3rd param).
	HANDLE handles[2] = {hEvent, hStdInput};                    //Program loops monitoring two handles.  The
	while(WaitForMultipleObjects(2,handles,FALSE,INFINITE))     //1st handle ( handles(0) ) is an event which
	{                                                           //is initially set to non-signaled.  The 2nd
		ReadConsoleInput(hStdInput,ir,128,&nRead);                 //handle monitored by WaitForMultipleObjects()
		for(i=0;i<nRead;i++)                                       //is the standard input handle set up to
		{                                                          //allow access to mouse/keyboard input.  As
			switch(ir[i].EventType)                                //long as neither handle is in a signaled
			{                                                      //state, WaitForMultipleObjects() will block
																	//set to FALSE, the function will return i
			case MOUSE_EVENT:    
				if(mb == core::key::KEY_M_LEFT){             
					if(
						ir[i].Event.MouseEvent.dwButtonState & 0x01 &&
						ir[i].Event.MouseEvent.dwMousePosition.X > x_begin &&
						ir[i].Event.MouseEvent.dwMousePosition.X < x_end &&
						ir[i].Event.MouseEvent.dwMousePosition.Y > y_begin &&
						ir[i].Event.MouseEvent.dwMousePosition.Y < y_end
						)
					{
						action();
						return;
					}
				}
				if(mb == core::key::KEY_M_RIGHT){             
					if(
						ir[i].Event.MouseEvent.dwButtonState & 0x02 &&
						ir[i].Event.MouseEvent.dwMousePosition.X > x_begin &&
						ir[i].Event.MouseEvent.dwMousePosition.X < x_end &&
						ir[i].Event.MouseEvent.dwMousePosition.Y > y_begin &&
						ir[i].Event.MouseEvent.dwMousePosition.Y < y_end
						)
					{
						action();
						return;
					}
				}
				if(mb == core::key::KEY_M_MIDDLE){             
					if(
						ir[i].Event.MouseEvent.dwButtonState & 0x04 &&
						ir[i].Event.MouseEvent.dwMousePosition.X > x_begin &&
						ir[i].Event.MouseEvent.dwMousePosition.X < x_end &&
						ir[i].Event.MouseEvent.dwMousePosition.Y > y_begin &&
						ir[i].Event.MouseEvent.dwMousePosition.Y < y_end
						)
					{
						action();
						return;
					}
				}
			}
		}
	}

 /*
 VK_LBUTTON  (0x01)
    Left mouse button

VK_RBUTTON  (0x02)
    Right mouse button

VK_MBUTTON  (0x04)
    Middle mouse button (three-button mouse)
 */
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::Draw_unexpected_error_msg()
{
	CoreAPI* costum_info_msg = new CoreAPI();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Error !";
	m[0].color=core::color::COLOR_RED;
	m[0].text_align=caption;
	std::cout << "\a";
	m[1].Caption="Unhandled expection oscured";
	m[1].color=core::color::COLOR_WHITE;
	m[1].text_align=caption;

	costum_info_msg->SetBGColor(core::color::COLOR_BLUE);
	costum_info_msg->DrawCenterBox(8,30,5,core::color::COLOR_GREY,3,m);
	costum_info_msg->free(costum_info_msg);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::Draw_costum_error_msg(const char* errortext)
{
	CoreAPI* costum_info_msg = new CoreAPI();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Error ~";
	m[0].color=core::color::COLOR_RED;
	m[0].text_align=caption;
	std::cout << "\a";
	m[1].Caption=errortext;
	m[1].color=core::color::COLOR_WHITE;
	m[1].text_align=caption;

	costum_info_msg->SetBGColor(core::color::COLOR_BLUE);
	costum_info_msg->DrawCenterBox(8,30,5,core::color::COLOR_GREY,3,m);
	costum_info_msg->free(costum_info_msg);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::Draw_costum_warning_msg(const char* warningtext)
{
	CoreAPI* costum_info_msg = new CoreAPI();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Warning !!";
	m[0].color=core::color::COLOR_RED;
	m[0].text_align=caption;
	std::cout << "\a";
	m[1].Caption=warningtext;
	m[1].color=core::color::COLOR_WHITE;
	m[1].text_align=caption;

	costum_info_msg->SetBGColor(core::color::COLOR_BLUE);
	costum_info_msg->DrawCenterBox(8,30,5,core::color::COLOR_GREY,3,m);
	costum_info_msg->free(costum_info_msg);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::Draw_costum_info_msg(const char* infotext)
{
	CoreAPI* costum_info_msg = new CoreAPI();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Info ?";
	m[0].color=core::color::COLOR_RED;
	m[0].text_align=caption;
	std::cout << "\a";
	m[1].Caption=infotext;
	m[1].color=core::color::COLOR_WHITE;
	m[1].text_align=caption;

	costum_info_msg->SetBGColor(core::color::COLOR_BLUE);
	costum_info_msg->DrawCenterBox(8,30,5,core::color::COLOR_GREY,3,m);
	costum_info_msg->free(costum_info_msg);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::WriteLn(char *Text)
{
	SetConsoleTextAttribute(hConsole,FontColor | BGColor);

	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole,&info);

	if (text_align == ALIGN_CENTER)
	{
		info.dwCursorPosition.X = (info.srWindow.Left+info.srWindow.Right/2)-(strlen(Text)/2);
		SetConsoleCursorPosition(hConsole,info.dwCursorPosition);
		printf("%s\n",Text);
	}
	else if (text_align == ALIGN_RIGHT)
	{
		info.dwCursorPosition.X = (info.srWindow.Left+info.srWindow.Right)-(strlen(Text));
		SetConsoleCursorPosition(hConsole,info.dwCursorPosition);
		printf("%s\n",Text);
	}
	else
		printf("%s\n",Text);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::Fill(byte Color,bool OnlyVisible)
{
	SetConsoleTextAttribute(hConsole,Color*0x10);
	SMALL_RECT rect = GetRect();
	if (OnlyVisible)
	{
		for (int y = 0;y<(rect.Bottom+rect.Top)+1;y++)
			for (int x = 0;x<(rect.Left+rect.Right)+1;x++)
				printf(" ");
	}
	COORD coord = {0,0};
	SetConsoleCursorPosition(hConsole,coord);
	SetConsoleTextAttribute(hConsole,BGColor);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::SaveCursorPos(void)
{
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole,&info);
	CursorPos = info.dwCursorPosition;
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::GotoCursorPos(COORD coord)
{
	SetConsoleCursorPosition(hConsole,coord);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::show_cursor(bool bShowCursor)
{
	static HANDLE		hOut;
	static BOOL		firstTime = TRUE;
	CONSOLE_CURSOR_INFO 	cursorInfo;

	if( firstTime )
	{

		hOut		= GetStdHandle( STD_OUTPUT_HANDLE );
		firstTime	= FALSE;

	}

	cursorInfo.dwSize	= 10;
	cursorInfo.bVisible 	= bShowCursor;

	SetConsoleCursorInfo( hOut,
                              &cursorInfo );
} 
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::setScreenSize(int ScreenWidth,int ScreenHeigth,int ScreenCordx,int ScreenCordy)
{
	HANDLE hConsoleOutput;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO  ConsoleInfo;
    HWND console = GetConsoleWindow();

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
    coord.X = ScreenCordx;
    coord.Y = ScreenCordy;
    SetConsoleScreenBufferSize(hConsoleOutput, coord);

    MoveWindow(console, 20, 20, ScreenWidth, ScreenHeigth, TRUE);
} 
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::setCursorPos(short Cursorx, short Cursory)
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PlaceCursorHere;
	PlaceCursorHere.X = Cursorx;
	PlaceCursorHere.Y = Cursory;
	SetConsoleCursorPosition(hConsole, PlaceCursorHere);
	return;
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::setConsolecaption(const char* Consolecaption)
{
	
	SetConsoleTitleA(Consolecaption);
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::clear()
{


  DWORD n;                         /* Number of characters written */
  DWORD size;                      /* number of visible characters */
  COORD coord = {0};               /* Top left screen position */
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  /* Get a handle to the console */
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

  GetConsoleScreenBufferInfo ( h, &csbi );

  /* Find the number of characters to overwrite */
  size = csbi.dwSize.X * csbi.dwSize.Y;

  /* Overwrite the screen buffer with whitespace */
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

  /* Reset the cursor to the top left position */
  SetConsoleCursorPosition ( h, coord );

} 
//######################################################################################################################################
//##########################################################~1.2.0.3~###################################################################
//######################################################################################################################################
void core::CoreAPI::DrawBoxVec(int x, int y, int w, int h,byte BorderColor,int size__,std::vector<MenuItem> Items)
{
	//std::vector<MenuItem> __temp_( size__ );
	//__temp_.swap( Items );

	int corner[4] = {201,187,200,188};
	int line[2] = {205,186};
	COORD coord = {x,y};
	SetConsoleCursorPosition(hConsole,coord);
	//Kasten dravvn
	SetConsoleTextAttribute(hConsole,BGColor|BorderColor);
	printf("%c",corner[0]);
	DrawLine(line[0],BorderColor,w-2);
	printf("%c\n",corner[1]);
	for (int i = 0;i<h;i++)
	{
		coord.X = x;
		coord.Y = y+1+i;
		SetConsoleCursorPosition(hConsole,coord);
		printf("%c",line[1]);
		DrawLine(' ',BorderColor,w-2);
		printf("%c\n",line[1]);
	}
	coord.X = x;
	coord.Y = y+h+1;
	SetConsoleCursorPosition(hConsole,coord);
	printf("%c",corner[2]);
	DrawLine(line[0],BorderColor,w-2);
	printf("%c\n",corner[3]);
	for (int i = 0;i<(size__-1);i++)
	{
		SetConsoleTextAttribute(hConsole,BGColor | Items[i].color);

		if (Items[i].text_align == ALIGN_CENTER)
		{
			coord.X = (x+(w/2))-(strlen(Items[i].Caption)/2);
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == ALIGN_RIGHT)
		{
			coord.X = (x+w-1)-(strlen(Items[i].Caption));
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == caption)
		{
			coord.X = x+2;
			coord.Y = y+0+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
		else
		{
			coord.X = x+1;
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
	}

}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::Loader(int Segements,int time,int Size)
{
	int Partslength = Size/Segements;
	int timePerPart = time/Segements;

for(int i = 0; i<Segements; ++i)
{
    for(int a = 0; a<Partslength; ++a)
    {
		std::cout << char(219);
    }
    Sleep(timePerPart);
	//std::cout << "-" << std::endl;
} 
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::ColorUpdate()
{
	core::CoreAPI::Write("");
	
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
void core::CoreAPI::CircleLoader(short posX,short posY,byte highlightedcolor,byte backgroundcolor,int timepersegement)
{
	core::CoreAPI ca;

	int segements = 6;

	//int time_per_seg = math::Math::div(timepersegement,segements);

	int time_per_seg = 30;
	ca.SetBGColor(core::color::COLOR_BLACK);
	ca.SetFontColor(core::color::COLOR_GREY);
	ca.ColorUpdate();
	ca.SetFontColor(backgroundcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+3,posY);
	std::cout << "#\0";
	/**************************************/
	ca.setCursorPos(posX+6,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+1,posY+1);
	std::cout << "#\0";
	/**************************************/
	
	ca.setCursorPos(posX+3,posY+1);
	std::cout << "#\0";
	ca.setCursorPos(posX+5,posY+1);
	std::cout << "#\0";
	
	/**************************************/
	
	ca.setCursorPos(posX+1,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX+3,posY+3);
	std::cout << "#\0";
	
	/**************************************/
	
	ca.setCursorPos(posX+5,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX,posY+4);
	std::cout << "#\0";
	
	/**************************************/
	
	ca.setCursorPos(posX+3,posY+4);
	std::cout << "#\0";
	ca.setCursorPos(posX+6,posY+4);
	std::cout << "#\0";


	while(true){
	/*1*************************************/
	ca.SetFontColor(highlightedcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+1,posY+1);
	std::cout << "#\0";
	Sleep(time_per_seg);
	ca.SetFontColor(backgroundcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+1,posY+1);
	std::cout << "#\0";
	/*2*************************************/
	ca.SetFontColor(highlightedcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+3,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+3,posY+1);
	std::cout << "#\0";
	Sleep(time_per_seg);
	ca.SetFontColor(backgroundcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+3,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+3,posY+1);
	std::cout << "#\0";
	/*3*************************************/
	ca.SetFontColor(highlightedcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+6,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+5,posY+1);
	std::cout << "#\0";
	Sleep(time_per_seg);
	ca.SetFontColor(backgroundcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+6,posY);
	std::cout << "#\0";
	ca.setCursorPos(posX+5,posY+1);
	std::cout << "#\0";
	/*4*************************************/
	ca.SetFontColor(highlightedcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+1,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX,posY+4);
	std::cout << "#\0";
	Sleep(time_per_seg);
	ca.SetFontColor(backgroundcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+1,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX,posY+4);
	std::cout << "#\0";
	/*5*************************************/
	ca.SetFontColor(highlightedcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+3,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX+3,posY+4);
	std::cout << "#\0";
	Sleep(time_per_seg);
	ca.SetFontColor(backgroundcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+3,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX+3,posY+4);
	std::cout << "#\0";
	/*6*************************************/
	ca.SetFontColor(highlightedcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+5,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX+6,posY+4);
	std::cout << "#\0";
	Sleep(time_per_seg);
	ca.SetFontColor(backgroundcolor);
	ca.ColorUpdate();
	ca.setCursorPos(posX+5,posY+3);
	std::cout << "#\0";
	ca.setCursorPos(posX+6,posY+4);
	std::cout << "#\0";
	}
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
BOOL sound::Sound::play(LPCWSTR soundfile)
{
	PlaySound(soundfile, NULL, SND_FILENAME | SND_ASYNC);
	return 0;
}
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//################################################################File##################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################
//######################################################################################################################################