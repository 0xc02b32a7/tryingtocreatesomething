#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32

#include <Windows.h>

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_FONT_INFOEX cfa;

#define CL_BLACK				0
#define CL_BLUE					1
#define CL_GREEN				2
#define CL_CYAN					3
#define CL_RED					4
#define CL_MAGENTA				5
#define CL_BROWN				6
#define CL_LIGHTGRAY			7
#define CL_DARKGRAY				8
#define CL_LIGHTBLUE			9
#define CL_LIGHTGREEN			10
#define CL_LIGHTCYAN			11
#define CL_LIGHTRED				12
#define CL_LIGHTMAGENTA			13
#define CL_YELLOW				14
#define CL_WHITE				15

#define FG_BLACK				0
#define FG_BLUE					1
#define FG_GREEN				2
#define FG_CYAN					3
#define FG_RED					4
#define FG_MAGENTA				5
#define FG_BROWN				6
#define FG_LIGHTGRAY			7
#define FG_DARKGRAY				8
#define FG_LIGHTBLUE			9
#define FG_LIGHTGREEN			10
#define FG_LIGHTCYAN			11
#define FG_LIGHTRED				12
#define FG_LIGHTMAGENTA			13
#define FG_YELLOW				14
#define FG_WHITE				15

#define BG_BLACK				0
#define BG_BLUE					1
#define BG_GREEN				2
#define BG_CYAN					3
#define BG_RED					4
#define BG_MAGENTA				5
#define BG_BROWN				6
#define BG_LIGHTGRAY			7
#define BG_DARKGRAY				8
#define BG_LIGHTBLUE			9
#define BG_LIGHTGREEN			10
#define BG_LIGHTCYAN			11
#define BG_LIGHTRED				12
#define BG_LIGHTMAGENTA			13
#define BG_YELLOW				14
#define BG_WHITE				15

#else

#define FG_BLACK				"0;30"
#define FG_BLUE					"0;34"
#define FG_GREEN				"0;32"
#define FG_CYAN					"0;36"
#define FG_RED					"0;31"
#define FG_MAGENTA				"0;35"
#define FG_BROWN				"0;33"
#define FG_LIGHTGRAY			"0;37"
#define FG_DARKGRAY				"1;30"
#define FG_LIGHTBLUE			"1;34"
#define FG_LIGHTGREEN			"1;32"
#define FG_LIGHTCYAN			"1;36"
#define FG_LIGHTRED				"1;31"
#define FG_LIGHTMAGENTA			"1;35"
#define FG_YELLOW				"1;33"
#define FG_WHITE				"1;37"

#define BG_BLACK				"0;40"
#define BG_BLUE					"0;44"
#define BG_GREEN				"0;42"
#define BG_CYAN					"0;46"
#define BG_RED					"0;41"
#define BG_MAGENTA				"0;45"
#define BG_BROWN				"0;43"
#define BG_LIGHTGRAY			"0;47"
#define BG_DARKGRAY				"1;40"
#define BG_LIGHTBLUE			"1;44"
#define BG_LIGHTGREEN			"1;42"
#define BG_LIGHTCYAN			"1;46"
#define BG_LIGHTRED				"1;41"
#define BG_LIGHTMAGENTA			"1;45"
#define BG_YELLOW				"1;43"
#define BG_WHITE				"1;47"

#endif

#define BLOCK_FULL				'\u2588'
#define BLOCK_THQU				'\u2593'
#define BLOCK_HALF				'\u2592'
#define BLOCK_ONQU				'\u2591'

#define BLOCK_QUL				'\u2598'
#define BLOCK_QUR				'\u259D'
#define BLOCK_QLL				'\u2596'
#define BLOCK_QLR				'\u2597'
#define BLOCK_QULLR				'\u259A'
#define BLOCK_QURLL				'\u259E'

#include <cwchar>

#include <iostream>

#define C2DD_VERSION			0.3f

class c2dd
{
protected:

#ifdef _WIN32

	const unsigned short foreground_default = CL_WHITE;
	const unsigned short background_default = CL_BLACK;

#else

	const std::string foreground_default = FG_WHITE;
	const std::string background_default = BG_BLACK;

#endif

private:

	std::unique_ptr<wchar_t[]> screenBuf;

#ifdef _WIN32

	std::unique_ptr<WORD[]> colorBuf;

	unsigned short fontWidth;
	unsigned short fontHeight;

	wchar_t* fontName;

	WORD intToWORD(unsigned short fcolor, unsigned short bcolor)
	{
		return ((bcolor & 0x0F) << 4) + (fcolor & 0x0F);
	}

#else

	std::unique_ptr<std::string[]> foreBuf;
	std::unique_ptr<std::string[]> backBuf;

#endif

public:

	unsigned short screenWidth;
	unsigned short screenHeight;
	
#ifdef _WIN32

	c2dd(unsigned short width, unsigned short height, unsigned short fontsize, const wchar_t fontname[] = L"Consolas", unsigned short fontwidthmultipler = 1)

#else

	c2dd(unsigned short width, unsigned short height)

#endif
	{
		screenBuf = std::make_unique<wchar_t[]>((width + 1) * height);

#ifdef _WIN32

		colorBuf = std::make_unique<WORD[]>((width + 1) * height);

		fontWidth = fontsize / 2 * fontwidthmultipler;
		fontHeight = fontsize;
		fontName = new wchar_t[std::wcslen(fontname)];
		std::wcscpy(fontName, (wchar_t*)fontname);

#else

		foreBuf = std::make_unique<std::string[]>((width + 1) * height);
		backBuf = std::make_unique<std::string[]>((width + 1) * height);

#endif

		screenWidth = width;
		screenHeight = height;
	}
	
	~c2dd() {}

	void ClearBuf()
	{
		for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
		{
			screenBuf[count] = L' ';
		}
	}

	void Replace(wchar_t from, wchar_t to)
	{
		for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
		{
			if (screenBuf[count] == from)
			{
				screenBuf[count] = to;
			}
		}
	}

	wchar_t GetChar(unsigned short x, unsigned short y)
	{
		if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
			return screenBuf[(y - 1) * screenWidth + x - 1];
		else return L'-';
	}

	wchar_t GetCharByIndex(unsigned int index)
	{
		if(index >= 0 && index < (screenWidth * screenHeight))
		{
			return screenBuf[index];
		}
		else return L'-';
	}

	bool SetChar(unsigned short x, unsigned short y, wchar_t sym)
	{
		if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
		{
			screenBuf[(y - 1) * screenWidth + x - 1] = sym;
			return true;
		}
		else return false;
	}

	bool SetCharByIndex(unsigned int index, wchar_t sym)
	{
		if(index >= 0 && index < (screenWidth * screenHeight))
		{
			screenBuf[index] = sym;
			
			return true;
		}
		else return false;
	}

	void FillChar(wchar_t sym)
	{
		for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
		{
			screenBuf[count] = sym;
		}
	}

	bool FillChar(wchar_t sym, unsigned short startposX, unsigned short startposY, unsigned short endposX, unsigned short endposY)
	{
		if (startposX <= endposX && startposY <= endposY && startposX > 0 && startposY > 0 && endposX <= screenWidth && endposY <= screenHeight)
		{
			for (unsigned short ptrY = startposY; ptrY <= endposY; ptrY++)
			{
				for (unsigned short ptrX = startposX; ptrX <= endposX; ptrX++)
				{
					screenBuf[(ptrY - 2) * screenWidth + ptrX - 1] = sym;
				}
			}
			return true;
		}
		else return false;
	}

	bool LoadCharMap(const wchar_t* charsMap)
	{
		if (sizeof(charsMap) <= (screenWidth * screenHeight))
		{
			for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
			{
				screenBuf[count] = (wchar_t)charsMap[count];
			}
			return true;
		}
		else return false;
	}

	bool WriteTillPointX(const wchar_t* text, unsigned short startposX, unsigned short endposX, unsigned short posY)
	{
		if (startposX <= endposX && startposX > 0 && endposX <= screenWidth && posY > 0 && posY <= screenHeight)
		{
			unsigned short pospointer = 0;

			for (unsigned short ptrX = startposX; ptrX <= endposX; ptrX++)
			{
				screenBuf[(posY - 1) * screenWidth + ptrX - 1] = (wchar_t)text[pospointer];
				pospointer++;
			}
			return true;
		}
		else return false;
	}

	bool WriteTillPointY(const wchar_t* text, unsigned short startposY, unsigned short endposY, unsigned short posX)
	{
		if (posX <= endposY && startposY > 0 && endposY <= screenHeight && posX > 0 && posX <= screenWidth)
		{
			unsigned short pospointer = 0;
			
			for (unsigned short ptrY = startposY; ptrY <= endposY; ptrY++)
			{
				screenBuf[(ptrY - 1) * screenWidth + posX - 1] = (wchar_t)text[pospointer];
				pospointer++;
			}
			return true;
		}
		else return false;
	}

#ifdef _WIN32

	void FillColor(unsigned short fcolor, unsigned short bcolor)
	{
		for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
		{
			colorBuf[count] = intToWORD(fcolor, bcolor);
		}
	}

	bool FillColor(unsigned short fcolor, unsigned short bcolor, unsigned short startposX, unsigned short startposY, unsigned short endposX, unsigned short endposY)
	{
		if (startposX <= endposX && startposY <= endposY && startposX > 0 && startposY > 0 && endposX <= screenWidth && endposY <= screenHeight)
		{
			for (unsigned short ptrY = startposY; ptrY <= endposY; ptrY++)
			{
				for (unsigned short ptrX = startposX; ptrX <= endposX; ptrX++)
				{
					colorBuf[(ptrY - 2) * screenWidth + ptrX - 1] = intToWORD(fcolor, bcolor);
				}
			}
			return true;
		}
		else return false;
	}

	static void SetWindowSize(unsigned short width, unsigned short height)
	{
		COORD crd = { width, height };

		SMALL_RECT src = { 0, 0, crd.X, crd.Y };

		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), crd);
		
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &src);
	}

	void SetSelfWinSize()
	{
		COORD crd = { screenWidth, screenHeight };

		SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };

		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), crd);
		
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &src);
	}

	WORD GetColor(unsigned short x, unsigned short y)
	{
		if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
			return colorBuf[(y - 1) * screenWidth + x - 1];
		else return '-';
	}

	WORD GetColorByIndex(unsigned int index)
	{
		if(index >= 0 && index < (screenWidth * screenHeight))
		{
			return colorBuf[index];
		}
		else return L'-';
	}

	bool SetColor(unsigned short x, unsigned short y, unsigned short fcolor, unsigned short bcolor)
	{
		if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
		{
			colorBuf[(y - 1) * screenWidth + x - 1] = intToWORD(fcolor, bcolor);
			return true;
		}
		else return false;
	}

	bool SetColorByIndex(unsigned int index, unsigned short fcolor, unsigned short bcolor)
	{
		if(index >= 0 && index < (screenWidth * screenHeight))
		{
			colorBuf[index] = intToWORD(fcolor, bcolor);

			return true;
		}
		else return false;
	}

	bool LoadColorMap(unsigned short* fcolorarray, unsigned short* bcolorarray)
	{
		if (sizeof(fcolorarray) == sizeof(bcolorarray))
		{
			for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
			{
				colorBuf[count] = intToWORD(fcolorarray[count], bcolorarray[count]);
			}
			return true;
		}
		else return false;
	}

	void ChangeDefColor(unsigned short fcolor, unsigned short bcolor)
	{
		foreground_default = fcolor;
		background_default = bcolor;
	}

	void ShowScr()
	{
		for (unsigned short ptrY = 1; ptrY <= screenHeight; ptrY++)
		{
			for (unsigned short ptrX = 1; ptrX <= screenWidth; ptrX++)
			{
				SetConsoleTextAttribute(hConsole, GetColor(ptrX, ptrY));
				std::wcout << GetChar(ptrX, ptrY);
				SetConsoleTextAttribute(hConsole, intToWORD(foreground_default, background_default));
			}
			std::cout << std::endl;
		}
	}

	void ShowScrBuf()
	{
		std::cout << "screenBuf =\n{";
		for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
		{
			std::wcout << screenBuf[count];
		}
		std::cout << "}"<< std::endl;
		std::cout << "screenBuf.LENGTH = " << screenWidth * screenHeight << std::endl;
	}

	static void Switch(c2dd& object, bool setselfwinsize = true)
	{
		cfa.cbSize = sizeof(cfa);
		cfa.nFont = 0;
		cfa.dwFontSize.X = object.fontWidth;
		cfa.dwFontSize.Y = object.fontHeight;
		cfa.FontFamily = FF_DONTCARE;
		cfa.FontWeight = FW_NORMAL;
		std::wcscpy(cfa.FaceName, object.fontName);
		SetCurrentConsoleFontEx(hConsole, FALSE, &cfa);

		if (setselfwinsize)
		{
			COORD crd = { object.screenWidth, object.screenHeight };

			SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };

			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), crd);
		
			SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &src);
		}
	}

#else

	void FillColor(char* fcolor, char* bcolor)
	{
		for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
		{
			foreBuf[count] = fcolor;
			backBuf[count] = bcolor;
		}
	}

	bool FillColor(char* fcolor, char* bcolor, unsigned short startposX, unsigned short startposY, unsigned short endposX, unsigned short endposY)
	{
		if (startposX <= endposX && startposY <= endposY && startposX > 0 && startposY > 0 && endposX <= screenWidth && endposY <= screenHeight)
		{
			for (unsigned short ptrY = startposY; ptrY <= endposY; ptrY++)
			{
				for (unsigned short ptrX = startposX; ptrX <= endposX; ptrX++)
				{
					foreBuf[(ptrY - 2) * screenWidth + ptrX - 1] = fcolor;
					backBuf[(ptrY - 2) * screenWidth + ptrX - 1] = bcolor;
				}
			}
			return true;
		}
		else return false;
	}

	static void SetWindowSize(unsigned short width, unsigned short height)
	{
		std::cout << "\e[8;" << height << ';' << width << 't';
	}

	void SetSelfWinSize()
	{
		std::cout << "\e[8;" << screenHeight << ';' << screenWidth << 't';
	}

	char** GetColor(unsigned short x, unsigned short y)
	{
		if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
			char** retanswer = { foreBuf[(y - 1) * screenWidth + x - 1], backBuf[(y - 1) * screenWidth + x - 1] };
			return retanswer;
		else return '-';
	}

	char** GetColorByIndex(unsigned int index)
	{
		if(index >= 0 && index < (screenWidth * screenHeight))
		{
			char** retanswer = { foreBuf[index], backBuf[index] };
			return retanswer;
		}
		else return L'-';
	}

	bool SetColor(unsigned short x, unsigned short y, char* fcolor, char* bcolor)
	{
		if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
		{
			foreBuf[(y - 1) * screenWidth + x - 1] = fcolor;
			backBuf[(y - 1) * screenWidth + x - 1] = bcolor;
			return true;
		}
		else return false;
	}

	bool SetColorByIndex(unsigned int index, char* fcolor, char* bcolor)
	{
		if(index >= 0 && index < (screenWidth * screenHeight))
		{
			foreBuf[index] = fcolor;
			backBuf[index] = bcolor;

			return true;
		}
		else return false;
	}

	bool LoadColorMap(std::string fcolorarray, std::string bcolorarray)
	{
		if (sizeof(fcolorarray) == sizeof(bcolorarray))
		{
			for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
			{
				foreBuf[count] = fcolorarray[count];
				backBuf[count] = bcolorarray[count];
			}
			return true;
		}
		else return false;
	}

	void ChangeDefColor(std::string fcolor, std::string bcolor)
	{
		foreground_default = fcolor;
		background_default = bcolor;
	}

	void ShowScr()
	{
		for (unsigned short ptrY = 1; ptrY <= screenHeight; ptrY++)
		{
			for (unsigned short ptrX = 1; ptrX <= screenWidth; ptrX++)
			{
				std::cout << "\e[" << getColor(ptrX, ptrY)[0] << 'm' << "\e[" << getColor(ptrX, ptrY)[1] << 'm'; 
				std::wcout << getChar(ptrX, ptrY); std::cout <<"\e[m";
			}
			std::cout << std::endl;
		}
	}

	void ShowScrBuf()
	{
		std::cout << "screenBuf =\n{";
		for (unsigned int count = 0; count < (screenWidth * screenHeight); count++)
		{
			std::wcout << screenBuf[count];
		}
		std::cout << "}"<< std::endl;
		std::cout << "screenBuf.LENGTH = " << screenWidth * screenHeight << std::endl;
	}

	static void Switch(c2dd object, bool setselfwinsize = true)
	{
		if (setselfwinsize)
			std::cout << "\e[8;" << object.screenHeight << ';' << object.screenWidth << 't';
	}

#endif
};