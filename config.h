/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 9;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 9;        /* vert inner gap between windows */
static const unsigned int gappoh    = 9;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 9;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 7;        /* vertical padding for statusbar */

static const char *fonts[] = { "FontAwesome:size=12", "xos4terminus:regular:pixelsize=14" };
static const char dmenufont[] = "xos4terminus:regular:pixelsize=14";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[]  = "#005577";
static const char col_green[] = "#354831";

static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_green,  col_green  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "firefox",    NULL,     NULL,       1 << 0,       0,           -1 },
    { "code",       NULL,     NULL,       1 << 1,       0,           -1 },
    { "Telegram",   NULL,     NULL,       1 << 7,       0,           -1 }
};

/* layout(s) */
static const float mfact       = 0.55; /* factor of master area size [0.05..0.95] */
static const int   nmaster     = 1;    /* number of clients in master area */
static const int   resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]",      tile },    /* split vertical*/
    { "[F]",      centeredfloatingmaster }, /* float */
    { "[H]",      bstack }, /* split horizontal */
    { "[M]",      monocle },
    //{ "",      NULL },    /* no layout function means floating behavior */
    { ":::",      gaplessgrid }, /* split vertical*/
    { "|M|",      centeredmaster },
    { "---",      horizgrid }, /* split vertical*/
    { "###",      nrowgrid },
    { "HHH",      grid }, /* split horizontal*/
    { "===",      bstackhoriz }, /* split horizontal*/
    { "H[]",      deck },
    { "[\\]",     dwindle },
    { "[@]",      spiral },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define L_ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_green, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "/opt/alacritty/target/release/alacritty", "--config-file", "/opt/alacritty/alacritty.yml", NULL };
static const char *bluetoothstart[] = {"/home/lisp3r/go/bin/sluez", "auto", "--device", "F4:7D:EF:B1:A3:E4", NULL};
// static const char *vpn[] = {"/usr/local/bin/openvpn", NULL};
static const char *vpn[] = {"/usr/local/bin/wireguard", NULL};
static const char *setupmon[] = {"xrandr", "--output", "DP1", "--auto", "--right-of", "eDP1", NULL};
// Script is not working
// static const char *spotify[] = {"spotify", NULL};

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
//static char *statuscmds[] = { "notify-send Mouse$BUTTON" };
//static const char *statuscmds[] = { "volume", "cpu", "battery" };
//static char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_space,  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },               // fullscreen
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
//  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    //{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_i,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
    { MODKEY|ControlMask,           XK_b,      spawn,          {.v = bluetoothstart } },
    { MODKEY|ControlMask,           XK_v,      spawn,          {.v = vpn } },
    { MODKEY|ControlMask,           XK_d,      spawn,          {.v = setupmon } },
    //{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    //{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
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
	// { ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	// { ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	// { ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
