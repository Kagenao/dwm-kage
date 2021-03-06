/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 7;        /* border pixel of windows */
static const unsigned int gappx     = 20;	/* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=14" };
static const char dmenufont[]       = "Hack Nerd Font:size=16";

/* Meine Farben yeah */
static const char col_bg[]          = "#080708";
static const char col_fg[]          = "#dad6d9";
static const char col_border[]      = "#1b181a";
static const char col_fg_sel[]      = "#e49f9d";
static const char col_bg_sel[]      = "#2d292c";
static const char col_border_sel[]  = "#2d292c";


static const char col_gray1[]       = "#222222";
static const char col_bubblegum1[]  = "#bd8337";
static const char col_gray2[]       = "#bd0000";
/* bar top left color */
static const char col_gray3[]       = "#ebc07c";

static const char col_font1[]       = "#ebc07c";
/* bar top left sel color */
static const char col_gray4[]       = "#9e8855";

static const char col_coral[]        = "#f0d5b1";
static const char col_1[]        = "#997842";
static const char col_2[]        = "#000000";
static const char col_3[]        = "#555555";
static const char *colors[][3]      = {
	/*               fg          bg          border   */
	[SchemeNorm] = { col_fg,     col_bg,     col_border },
	[SchemeSel]  = { col_fg_sel, col_bg_sel, col_border_sel  },
        [SchemeStatus]  = { col_fg,  col_bg,      "#000000"  }, // Statusbar right
	[SchemeTagsSel]  = { col_fg_sel, col_bg_sel,  "#000000"  }, // Tagbar left selected 
	[SchemeTagsNorm]  = { col_fg, col_bg,  "#000000"  }, // Tagbar left
	[SchemeInfoSel]  = { col_fg_sel, col_bg_sel,  col_border_sel  }, // infobar middle
	[SchemeInfoNorm]  = { col_fg, col_bg,  col_border  }, // infobar middle
};

/* tagging */
static const char *tags[] = { "???", "???", "???", "???", "???","???"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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

/* helper for spawning shell comman:ds in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/terminator", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *screenkey[] = { "screenkey", "--opacity", "0.2", "--bg-color", "black", "-s", "small", "-t", "1.5", NULL };
static const char *web[]  = { "firefox", "google.de", NULL };
static const char *screenkeyDel[]  = { "killall", "screenkey", NULL };
static const char *fm[]  = { "pcmanfm", NULL };
static const char *tm[]  = { "alacritty", "-e", "htop", NULL };
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY, 	                XK_w, 	   spawn,          {.v = web } },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,	   {.v = screenkeyDel } },
	{ MODKEY,     			XK_s,	   spawn,	   {.v = screenkey } },
	{ MODKEY|ShiftMask, 	        XK_f, 	   spawn,          {.v = fm } },
	{ MODKEY|ShiftMask, 	        XK_t, 	   spawn,          {.v = tm } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY, 		        XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,		XK_n,	   shiftview,	   { .i = +1} },
	{ MODKEY|ShiftMask,		XK_b,	   shiftview,	   { .i = -1} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

