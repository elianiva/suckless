//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	  /*Command*/		/*Update Interval*/	  /*Update Signal*/
	{" ",   "wlan",             60,                   0},
  {" ",   "",                 0,                    0},
	{" ",   "netspeed",         1,                    0},
  {" ",   "",                 0,                    0},
	{" ",   "volume",           1,                    0},
  {" ",   "",                 0,                    0},
	{" ",   "memory",           5,                    0},
  {" ",   "",                 0,                    0},
	{" ",   "cpu",              5,                    0},
  {" ",   "",                 0,                    0},
	{" ",   "temp",             2,                    0},
  {" ",   "",                 0,                    0},
	{" ",   "battery",          5,                    0},
  {" ",   "",                 0,                    0},
	{" ",   "clock",            60,                   0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = '\0';
