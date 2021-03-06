/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 8;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 8;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 28;       /* bar height */
static const char *fonts[]          = { "Iosevka:size=11:style=Regular"
                                        "Noto Sans CJK:size=11:style=regular" }; /* statusbar font */

/* colours */
static const char col_bg[]         = "#282828";
static const char col_fg[]         = "#ebdbb2";
static const char col_white[]      = "#e79921";
static const char col_normal[]     = "#3e3e3e";
static const char col_active[]     = "#ebdbb2";
static const char *colors[][3]     = {
	/*               fg         bg           border   */
	[SchemeNorm] = { col_fg,    col_bg,      col_normal },
	[SchemeSel]  = { col_white, col_bg,      col_active  },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance     title       tags mask     isfloating  isterminal  noswallow   monitor */
	{ "music",    NULL,       NULL,       0,            1,          0,          0,          -1 },
	{ "St",       NULL,       NULL,       0,            0,          1,          0           -1 },
	{ "Alacritty",NULL,       NULL,       0,            0,          1,          0           -1 },
	{ "Steam",    NULL,       NULL,       0,            1,          0,          0,          -1 },
	{ "Pcmanfm",  NULL,       NULL,       0,            1,          0,          0,          -1 },
	{ NULL,       NULL,       "Event Tester", 0,        1,          0,          1,          -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = {"launcher", NULL};
static const char *float_music[]  = {"st", "-c", "music", "-e", "ncmpcpp", NULL};
static const char *termcmd[]      = {"alacritty", NULL };
static const char *dmenuunicode[] = {"dmenuunicode", NULL };
static const char *clipmenu[]     = {"clipmenu", NULL };
static const char *powermenu[]    = {"powermenu", NULL };

/* screenshot */
static const char *scr_full[]     = {"flameshot", "full", "-p", "/home/elianiva/pix/shots/", NULL };
static const char *scr_select[]   = {"flameshot", "gui", "-p", "/home/elianiva/pix/shots/", NULL };

/* audio control */
/* static const char *vol_up[]       = {"pamixer", "-i", "2", NULL}; */
/* static const char *vol_down[]     = {"pamixer", "-d", "2", NULL}; */
/* static const char *vol_toggle[]   = {"pamixer", "-t", NULL}; */

/* brightness control */
static const char *bri_up[]       = {"light", "-A", "5", NULL};
static const char *bri_down[]     = {"light", "-U", "5", NULL};

/* music control */
static const char *mpd_toggle[]   = {"playerctl", "play-pause", NULL};
static const char *mpd_next[]     = {"playerctl", "next", NULL};
static const char *mpd_prev[]     = {"playerctl", "previous", NULL};

static Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_e,      spawn,          {.v = dmenuunicode } },
  { MODKEY,                       XK_s,      spawn,          {.v = float_music } },
  { MODKEY,                       XK_c,      spawn,          {.v = clipmenu } },
  { MODKEY,                       XK_x,      spawn,          {.v = powermenu } },
  { MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_g,      zoom,           {0} },
  /* { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, */
  /* { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } }, */
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
  { MODKEY,                       XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_0,      togglefullscr,  {0} },
  /* { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, */
  /* { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, */
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
  { MODKEY|ShiftMask,             XK_r,      quit,           {1} },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  /* TAGKEYS(                        XK_7,                      6) */
  /* TAGKEYS(                        XK_8,                      7) */
  /* TAGKEYS(                        XK_9,                      8) */

  /*audio keys*/
  { 0,                            XF86XK_AudioMute,		      spawn,		SHCMD("pamixer -t && pkill --signal RTMIN+10 -x dwmbar")},
  { 0,                            XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer -i 2 && pkill --signal RTMIN+10 -x dwmbar")},
  { 0,                            XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer -d 2 && pkill --signal RTMIN+10 -x dwmbar")},

  /*brightness keys*/
  { 0,                            XF86XK_MonBrightnessUp,	  spawn,		{.v = bri_up } },
  { 0,                            XF86XK_MonBrightnessDown,	spawn,		{.v = bri_down } },

  /*mpc keys*/
  { MODKEY,                       XK_p,                     spawn,    {.v = mpd_toggle} },
  { 0,                            XF86XK_AudioPlay,         spawn,    {.v = mpd_toggle} },
  { 0,                            XF86XK_AudioPrev,         spawn,    {.v = mpd_prev} },
  { 0,                            XF86XK_AudioNext,         spawn,    {.v = mpd_next} },

  /*screenshot keys*/
  {  0,                           XK_Print,                 spawn,    {.v = scr_full} },
  {  MODKEY,                      XK_Print,                 spawn,    {.v = scr_select} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

