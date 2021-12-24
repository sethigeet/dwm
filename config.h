/* See LICENSE file for copyright and license details. */

/* appearance */
static       unsigned int borderpx  = 1;        /* border pixel of windows */
static       unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 6;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;        /* vert inner gap between windows */
static const unsigned int gappoh    = 6;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 6;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static       int showbar            = 1;        /* 0 means no bar */
static       int topbar             = 1;        /* 0 means bottom bar */
static       int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static       char *altbarclass      = "Polybar"; /* Alternate bar class name */
static       char *alttrayname      = "tray";    /* Polybar tray instance name */
static       char *altbarcmd        = "$XDG_CONFIG_HOME/polybar/launch.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "monospace:size=10" };
static char normbgcolor[]           = "#1F2335";
static char normbordercolor[]       = "#545C7E";
static char normfgcolor[]           = "#C0CAF5";
static char selfgcolor[]            = "#7AA2F7";
static char selbordercolor[]        = "#7AA2F7";
static char selbgcolor[]            = "#7AA2F7";
static char *colors[][3] = {
	/*                   fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
 };

/* tagging */
static const char *tags[] = { "", "﬏", "", "", "煉", "", "", "", "" };

static const Rule rules[] = {
	/* class      instance  title                    tags mask     iscentered  isfloating      float x,y,w,h,     isterminal   noswallow  monitor  scratch key */

	/* Make some windows floating */
	{ "ssh-askpass",  NULL,     NULL,                   0,             0,           1,      -1,  -1,  -1,  -1,        0,           0,        -1,        0   }, /* ssh-askpass */
	{ "kite",         NULL,     NULL,                   0,             0,           1,      -1,  -1,  -1,  -1,        0,           0,        -1,        0   }, /* Kite Co pilot */
	{ NULL,           NULL,     "pinentry",             0,             0,           1,      -1,  -1,  -1,  -1,        0,           0,        -1,        0   }, /* GPG key password entry */
	{ NULL,           NULL,     "win0",                 0,             0,           1,      -1,  -1,  -1,  -1,        0,           0,        -1,        0   }, /* Android Studio startup screen */
	{ NULL,           NULL,     "^Android Emulator*",   0,             0,           1,      -1,  -1,  -1,  -1,        0,           0,        -1,        0   }, /* Android Emulator */
	{ NULL,           NULL,     "^Participants*",       0,             0,           1,      -1,  -1,  -1,  -1,        0,           0,        -1,        0   }, /* Zoom meetings */

	/* Swallow terminals */
	{ "Alacritty",    NULL,     NULL,                   0,             0,           0,      -1,  -1,  -1,  -1,        1,           0,        -1,        0   },
	{ "kitty",        NULL,     NULL,                   0,             0,           0,      -1,  -1,  -1,  -1,        1,           0,        -1,        0   },
	{ "St",           NULL,     NULL,                   0,             0,           0,      -1,  -1,  -1,  -1,        1,           0,        -1,        0   },
	{ NULL,           NULL,     "Event Tester",         0,             0,           0,      -1,  -1,  -1,  -1,        0,           1,        -1,        0   }, /* xev */
	{ "Xephyr",       NULL,     NULL,                   0,             0,           0,      -1,  -1,  -1,  -1,        0,           1,        -1,        0   }, /* xephyr */

	/* Scratchpads */
	{ NULL,          NULL,      "terminal scratchpad",  0,             0,           1,      90, 11, 1728, 360,        1,           0,        -1,        't' }, /* terminal scratchpad */
	{ NULL,          NULL,      "Calculator",           0,             0,           1,     640, 360, 700, 360,        0,          -1,        -1,        'c' }, /* calculator scratchpad */
};

/* layout(s) */
static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "selfrestart.c"

static const Layout layouts[] = {
	/* symbol      layout function */
	{ "",            tile },
	{ "",             monocle },
	{ "",             spiral },
	{ "ﭕ",             dwindle },
	{ "ﲜ",             deck },
	{ "",             bstack },
	{ "",             bstackhoriz },
	{ "",             grid },
	{ "###",           nrowgrid },
	{ "---",           horizgrid },
	{ ":::",           gaplessgrid },
	{ "",             centeredmaster },
	{ "",           centeredfloatingmaster },
	{ "",             NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      swaptags,       {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,      XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD,      XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD,      XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD,      XK_a,     ACTION##stack, {.i = 0 } }, \
	{ MOD,      XK_z,     ACTION##stack, {.i = 1 } }, \
	{ MOD,      XK_x,     ACTION##stack, {.i = 2 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char promptmon[2] = "0"; /* component of promptcmd, manipulated in spawn() */
static const char *promptcmd[] = { "rofi", "-show", "drun", "-monitor", promptmon, NULL };
static const char *termcmd[]  = { "/bin/sh", "-c", "$TERMINAL", NULL };
/* First arg only serves to match against key in rules */
static const char *terminalscratchpadcmd[] = {"t", "/bin/sh", "-c", "$TERMINAL --title 'terminal scratchpad'", NULL}; 
static const char *calculatorscratchpadcmd[] = {"c", "gnome-calculator", NULL}; 

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{ "normbgcolor",        STRING,  &normbgcolor },
	{ "normbordercolor",    STRING,  &normbordercolor },
	{ "normfgcolor",        STRING,  &normfgcolor },
	{ "selbgcolor",         STRING,  &selbgcolor },
	{ "selbordercolor",     STRING,  &selbordercolor },
	{ "selfgcolor",         STRING,  &selfgcolor },
	{ "borderpx",          	INTEGER, &borderpx },
	{ "snap",               INTEGER, &snap },
	{ "showbar",          	INTEGER, &showbar },
	{ "topbar",             INTEGER, &topbar },
	{ "usealtbar",          INTEGER, &usealtbar },
	{ "altbarclass",        STRING,  &altbarclass },
	{ "alttrayname",        STRING,  &alttrayname },
	{ "altbarcmd",          STRING,  &altbarcmd },
	{ "nmaster",            INTEGER, &nmaster },
	{ "resizehints",       	INTEGER, &resizehints },
	{ "mfact",            	FLOAT,   &mfact },
};

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* Scratchpads */
	{ MODKEY|ShiftMask,             XK_t,      togglescratch,  {.v = terminalscratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_c,      togglescratch,  {.v = calculatorscratchpadcmd } },

	/* Stack */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_d,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_0,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },

	/* Layouts */
	{ MODKEY,                       XK_f,      fullscreen,     {0} },
	{ MODKEY|ControlMask,           XK_f,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_s,      togglesticky,   {0} },
	{ MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },

	/* Move floating windows */
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },


	/* Tags and Monitors */
	{ Mod1Mask,                     XK_Tab,    goback,         {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Tab,    viewadjacent,   {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    viewadjacent,   {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      viewadjacent,   {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      viewadjacent,   {.i = +1 } },
	{ MODKEY|ControlMask,           XK_h,      tagadjacent,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_l,      tagadjacent,    {.i = +1 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* General */
	{ MODKEY|ControlMask,           XK_r,      self_restart,   {0} },
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
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

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(view,                1,      {ARG_TYPE_UINT} ),
  IPCCOMMAND(toggleview,          1,      {ARG_TYPE_UINT} ),
  IPCCOMMAND(tag,                 1,      {ARG_TYPE_UINT} ),
  IPCCOMMAND(toggletag,           1,      {ARG_TYPE_UINT} ),
  IPCCOMMAND(tagmon,              1,      {ARG_TYPE_UINT} ),
  IPCCOMMAND(focusmon,            1,      {ARG_TYPE_SINT} ),
  IPCCOMMAND(focusstack,          1,      {ARG_TYPE_SINT} ),
  IPCCOMMAND(zoom,                1,      {ARG_TYPE_NONE} ),
  IPCCOMMAND(incnmaster,          1,      {ARG_TYPE_SINT} ),
  IPCCOMMAND(killclient,          1,      {ARG_TYPE_SINT} ),
  IPCCOMMAND(togglefloating,      1,      {ARG_TYPE_NONE} ),
  IPCCOMMAND(setmfact,            1,      {ARG_TYPE_FLOAT}),
  IPCCOMMAND(setlayoutsafe,       1,      {ARG_TYPE_PTR}  ),
  IPCCOMMAND(quit,                1,      {ARG_TYPE_NONE} )
};

