using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Console2dDrawing
{
    class c2dd
    {
        public static char BLOCK_FULL   = '\u2588';
        public static char BLOCK_THQU   = '\u2593';
        public static char BLOCK_HALF   = '\u2592';
        public static char BLOCK_ONQU   = '\u2591';

        public static char BLOCK_QUL    = '\u2598';
        public static char BLOCK_QUR    = '\u259D';
        public static char BLOCK_QLL    = '\u2596';
        public static char BLOCK_QLR    = '\u2597';
        public static char BLOCK_QULLR  = '\u259A';
        public static char BLOCK_QURLL  = '\u259E';

        public ushort screenWidth;
        public ushort screenHeight;

        private char[] screenBuf;

        const ConsoleColor foreground_default = ConsoleColor.White;
        const ConsoleColor background_default = ConsoleColor.Black;

        private ConsoleColor[] foreBuf;
        private ConsoleColor[] backBuf;

        public c2dd(ushort width, ushort height)
        {
            screenBuf = new char[(width + 1) * height];

            foreBuf = new ConsoleColor[(width + 1) * height];
            backBuf = new ConsoleColor[(width + 1) * height];

            screenWidth = width;
            screenHeight = height;
        }

        ~c2dd() { }

        void clearBuf()
        {
            for (uint count = 0; count < (screenWidth * screenHeight); count++)
            {
                screenBuf[count] = '\0';
            }
        }

        void fillWithSpaces()
        {
            for (uint count = 0; count < (screenWidth * screenHeight); count++)
            {
                screenBuf[count] = ' ';
            }
        }

        void replace(char from, char to)
        {
            for (uint count = 0; count < (screenWidth * screenHeight); count++)
            {
                if (screenBuf[count] == from)
                {
                    screenBuf[count] = to;
                }
            }
        }

        char getChar(uint x, uint y)
        {
            if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
                return screenBuf[(y - 1) * screenWidth + x - 1];
            else return '-';
        }

        bool setChar(uint x, uint y, char sym)
        {
            if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
            {
                screenBuf[(y - 1) * screenWidth + x - 1] = sym;
                return true;
            }
            else return false;
        }

        bool loadCharMap(char[] charsMap)
        {
            if (charsMap.Length == (screenWidth * screenHeight))
            {
                for (uint count = 0; count < (screenWidth * screenHeight); count++)
                {
                    screenBuf[count] = charsMap[count];
                }
                return true;
            }
            else return false;
        }

        void fillColor(ConsoleColor fcolor, ConsoleColor bcolor)
        {
            for (uint count = 0; count < (screenWidth * screenHeight); count++)
            {
                foreBuf[count] = fcolor;
            }
        }

        bool fillColor(ConsoleColor fcolor, ConsoleColor bcolor, uint startposX, uint startposY, uint endposeX, uint endposeY)
        {
            if (startposX <= endposeX && startposY <= endposeY && startposX > 0 && startposY > 0 && endposeX <= screenWidth && endposeY <= screenHeight)
            {
                for (uint ptrY = startposY; ptrY <= endposeY; ptrY++)
                {
                    for (uint ptrX = startposX; ptrX <= endposeX; ptrX++)
                    {
                        foreBuf[(ptrY - 2) * screenWidth + ptrX - 1] = fcolor;
                        backBuf[(ptrY - 2) * screenWidth + ptrX - 1] = bcolor;
                    }
                }
                return true;
            }
            else return false;
        }

        public static void setWindowSize(ushort width, ushort height)
        {
            Console.SetWindowSize(width, height);
        }

        public void setSelfWinSize()
        {
            Console.SetWindowSize(screenWidth, screenHeight);
        }

        ConsoleColor[] getColor(uint x, uint y)
        {
            if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
            {
                ConsoleColor[] retarr = { foreBuf[(y - 1) * screenWidth + x - 1], backBuf[(y - 1) * screenWidth + x - 1] };
                return retarr;
            }
            else
            {
                ConsoleColor[] errret = { ConsoleColor.Magenta, ConsoleColor.DarkMagenta };
                return errret;
            }
        }

        bool setColor(uint x, uint y, ConsoleColor fcolor, ConsoleColor bcolor)
        {
            if (y > 0 && y <= screenHeight && x > 0 && x <= screenWidth)
            {
                foreBuf[(y - 1) * screenWidth + x - 1] = fcolor;
                backBuf[(y - 1) * screenWidth + x - 1] = bcolor;
                return true;
            }
            else return false;
        }

        void showScr()
        {
            for (uint ptrY = 1; ptrY <= screenHeight; ptrY++)
            {
                for (uint ptrX = 1; ptrX <= screenWidth; ptrX++)
                {
                    Console.ForegroundColor = getColor(ptrX, ptrY)[0];
                    Console.BackgroundColor = getColor(ptrX, ptrY)[1];
                    Console.Write(getChar(ptrX, ptrY));
                    Console.ForegroundColor = foreground_default;
                    Console.BackgroundColor = background_default;
                }
                Console.Write('\n');
            }
        }

        void showScrBuf()
        {
            Console.WriteLine("screenBuf ="); Console.Write('{');
            for (uint count = 0; count < (screenWidth * screenHeight); count++)
            {
                Console.Write(screenBuf[count]);
            }
            Console.WriteLine('}');
            Console.WriteLine("screenBuf.Length = " + screenBuf.Length);
        }
    }
}