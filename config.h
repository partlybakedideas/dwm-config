/* Hello there!
    ____                             _                        __ _
   / ___|___  _ __  _ __   ___  _ __( )___    ___ ___  _ __  / _(_) __ _
   | |   / _ \| '_ \| '_ \ / _ \| '__|// __|  / __/ _ \| '_ \| |_| |/ _` |
   | |__| (_) | | | | | | | (_) | |    \__ \ | (_| (_) | | | |  _| | (_| |
    \____\___/|_| |_|_| |_|\___/|_|    |___/  \___\___/|_| |_|_| |_|\__, |
                         You can look as cool                       |___/
			 as  I am ^TM
________
|      |
|      |
--------------
       |     |
       |     |
       -------
		     

   welcome to my config.

   Here are a few things to take note of:

   * vertpad and sidepad signify border padding.

   * by default the bar (and dmenu) are going to have #222233 as there background. you can change it in the `static const char *colors[]` section.

   	*to chnage dmenu look at the `*dmenucmd[]` part.

   * smartgaps are the gaps whenthere is only one window

   */
/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
#include "fibonacci.c"
#include "grid.c"
/* appearance */
static const unsigned int borderpx  	= 1;        /* border pixel of windows */
static const unsigned int smartborder 	= 0; /*border pixel when there is only one window */
static const unsigned int snap      	= 32;       /* snap pixel */
static const unsigned int vertpad   	= 0;
static const unsigned int sidepad   	= 0;
static const int user_bh            	= 0; //bar height. 0 means dwm will automaticaly adjust it.
static const int showbar            	= 1;        /* 0 means no bar */
static const int topbar             	= 1;        /* 0 means bottom bar */
static const int swallowfloating    	= 0;
static const char *fonts[]          	= { "DeJaVuSans Mono:size=9" };
static const char dmenufont[]       	= "DeJaVuSans Mono:size=9";
static const unsigned int gappx     	= 10;
static const unsigned int smartgaps 	= 15; //number of px in the gaps when there is one window
static const unsigned int baralpha  	= 130;
static const unsigned int borderalpha 	= OPAQUE;
static const char col_gray[]        	= "#111111";
static const char col_gray1[]       	= "#222222";
static const char col_gray2[]       	= "#444444";
static const char col_gray3[]       	= "#bbbbbb";
static const char col_gray4[]       	= "#eeeeee";
static const char col_gray5[]       	= "#555753";
static const char col_black[]       	= "#000000";
static const char col_cyan[]        	= "#005577";
static const char col_red[]         	= "#ca0000";
static const char col_blue[]        	= "#0000ff";
static const char col_blue1[]       	= "#3366ff";
static const char col_blue2[]      		= "#222233";
static const char col_white[]       	= "#ffffff";
static const char *colors[][3]      	= {
	/*     fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray2 }, 
	[SchemeSel] = { col_black, col_white, col_white, },
};	
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//static const char *alttags[] = { "@read", "@write", "@execute", "@4", "@5", "@6", "@7", "@8", "@9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
//       { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
//       { "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
//       { "urxvt",   NULL,     NULL,           0,         0,          1,          -1,        -1 },
       { NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */


static const Layout layouts[] = {

	/* symbol     arrange function */
	{ "[=]",      tile },    /* first entry is default */
	{ "[~]",      NULL },    /* no layout function means floating behavior */
	{ "[*]",      monocle }, //2
	{ "[@]",      spiral }, //3
	{ "[\\]",     dwindle }, //4
	{ "[#]",      grid }, //5
	{ "[M]",      centeredmaster }, //6
	{ "[F]",      centeredfloatingmaster }, //7
	{ "[T]",      bstack }, //8
	{ "[|]",      col }, //9
//	{ "[=]",      bstackhoriz }, //9
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define HOLDKEY 0
#define PRTSCR 0xff61

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

#define TERMINAL "alacritty"
#define ScreenShotLocation "/home/aamonm/Pictures/Screenshots/%F-%T-$w-$h.png"
#define FILMANAGER "dolphin"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_blue2, "-nf", col_gray4, "-sb", col_white, "-sf", col_black, "-p", "Run:", NULL };
static const char *termcmd[] = { TERMINAL, NULL };
static const char *filemanagercmd[] = { FILMANAGER, NULL };
//static const char *printcmd[]  = { "flameshot", "gui", NULL };
static const char *printcmd[]  = { "scrot", ScreenShotLocation, "-s", "-f", "-i", NULL };
//static const char *termcmd[] = { "st", NULL };
//static const char *stermcmd[]  = { "tabbed", "-c", "-r", "2", "st", "-w", "''", NULL };
//static const char *browsercmd[] = { "tabbed", "-c", "surf", "-e",  NULL };
//static const char *raisevolumecmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10", NULL};
//static const char *lowervolumecmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10", NULL};
//static const char *mutecmd[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
//static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
//static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };

static const char *brupcmd[] = { "sudo", "xbacklight", "-inc", "10", NULL };
static const char *brdowncmd[] = { "sudo", "xbacklight", "-dec", "10", NULL };

static const char *appfindercmd[] = { "xfce4-appfinder", NULL };

static Key keys[] = {
	/* modifier                     key        	function        argument */
// Start some program
	{ MODKEY,                       XK_p,      	spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 	spawn,          {.v = termcmd } },
//	{ MODKEY|ShiftMask,             XK_p,      	spawn,          {.v = appfindercmd } },
//	{ MODKEY,                       XK_F5,     	spawn,         	{.v = stermcmd } },
	{ MODKEY,                       XK_f,     	spawn,          {.v = filemanagercmd } },
//	{ MODKEY,                    	XK_backslash, spawn,       	{.v = termcmd } },
	{0, PRTSCR, 								spawn, 			{.v = printcmd}},
//
	{ MODKEY,                       XK_F12,    	spawn,          SHCMD("sudo shutdown -h now") },
// Move and modify open windows		
	{ MODKEY,                       XK_grave,  togglebar,      	{0} },
	{ MODKEY,                       XK_j,      focusstack,     	{.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     	{.i = -1 } },
	{ MODKEY,                       XK_equal,  incnmaster,     	{.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     	{.i = -1 } }, 
	{ MODKEY,                       XK_h,      setmfact,       	{.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       	{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       	{.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       	{.f = +0.05} },	
	{ MODKEY,                       XK_Return, zoom,           	{0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  	{0} },
	{ MODKEY,                       XK_Tab,    view,           	{0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     	{0} },
// Change window layout
	{ MODKEY,                       XK_t,      setlayout,      	{.v = &layouts[0]} },
	{ MODKEY,                       XK_n,      setlayout,      	{.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      	{.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      	{0} },
	{ MODKEY,                       XK_r,      setlayout,      	{.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      	{.v = &layouts[4]} },
	{ MODKEY,                       XK_g,      setlayout,      	{.v = &layouts[5]} }, //grid layout is number five
	{ MODKEY,                       XK_u,      setlayout,      	{.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      	{.v = &layouts[7]} },
	{ MODKEY,                       XK_y,      setlayout,      	{.v = &layouts[8]} },
	{ MODKEY,                       XK_i,      setlayout,      	{.v = &layouts[9]} },
//	{ MODKEY|ShiftMask,             XK_i,      setlayout,      	{.v = &layouts[9]} },
	{ MODKEY,                       XK_comma,  cyclelayout,    	{.i = -1 } },
	{ MODKEY,                       XK_period, cyclelayout,    	{.i = +1 } },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, 	{0} },
	{ MODKEY,                       XK_0,      view,           	{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            	{.ui = ~0 } },
	{ MODKEY,                       XK_bracketleft,  focusmon,  {.i = -1 } },
	{ MODKEY,                       XK_bracketright, focusmon,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagmon,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright, tagmon,    {.i = +1 } },
//	{ 0,                            XK_Print,  spawn,          	SHCMD("~/dwm-config/screenshot.sh") }, //I'm really sorry for all this bad hardcoding stuff but it's the only way it will work 
//	{ 0,                            XK_Print,  spawn,          	SHCMD("scrot") },
//	{ MODKEY,                       XK_w,      spawn,          	SHCMD("networkmanager_dmenu") },
//	{ MODKEY,                       XK_o,      spawn,          	{.v = browsercmd} }, //Don't ask me how I thought o is a great keybinding for the browser
//	{ 0, 				XF86XK_AudioMute, 	   spawn,   		{.v = mutecmd } },
//	{ 0, 				XF86XK_AudioLowerVolume, spawn, 		{.v = voldowncmd } },
//	{ 0, 				XF86XK_AudioRaiseVolume, spawn, 		{.v = volupcmd } },
	{ MODKEY,                       XK_Next,   viewtoleft,      {0} },
	{ MODKEY,                       XK_Prior,  viewtoright,     {0} },
	{ MODKEY|ShiftMask,             XK_Next,   tagtoleft,       {0} },
	{ MODKEY|ShiftMask,             XK_Prior,  tagtoright,      {0} },
	TAGKEYS(                        XK_1,                      	0)
	TAGKEYS(                        XK_2,                      	1)
	TAGKEYS(                        XK_3,                      	2)
	TAGKEYS(                        XK_4,                      	3)
	TAGKEYS(                        XK_5,                      	4)
	TAGKEYS(                        XK_6,                      	5)
	TAGKEYS(                        XK_7,                      	6)
	TAGKEYS(                        XK_8,                      	7)
	TAGKEYS(                        XK_9,                      	8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           	{0} },
	{ MODKEY|ControlMask|ShiftMask, XK_c,      quit,           	{1} },
	{ 0,                            HOLDKEY,    holdbar,        {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

