/*
Tacitus @ LPUniversity
19-OCT-05
LPUniversity Macro File

*/

/* Last updated: August 10th, 2006 by Parthenon */

/* Redefinition warnings protection */

#ifndef MUDLIB
#define MUDLIB


/* Standard Inheritables */

#define BASE_OBJECT     "/std/object/object"
#define OBJECT          "/std/object/gb_object"
#define OB_E            "/std/object/ob_prop"
#define ROOM_BASE       "/std/area/rooms/room"
#define ROOM            "/std/area/rooms/vmaproom"
#define MOBILE          "/std/user/gb_mobile"
#define NPC             "/std/area/mobiles/npc"
#define GHOST           "/std/ghosts/ghost"
#define PLAYER          "/std/user/gb_player"
#define MONSTER         GHOST
#define COMMAND         "/std/command/command"
#define SHOPKEEPER      "/std/area/mobiles/shopkeep.c"
#define FURNITURE       "/std/object/furniture.c"
#define HITDATA         "/std/combat/HitData.c"

#define STREETS         "/home/e/emraef/public/streets/streets"

#define PROTONPACK      "/obj/protonpack/protonpack"
#define TRAP            "/obj/trap/trap"
#define PKEMETER        "/obj/pkemeter/pkemeter"
#define SAMPLE          "/obj/research/sample.c"
#define CONTAINMENTUNIT "/obj/containmentunit.c"
#define TOILET          "/obj/toilet.c"

/* Mudlib Objects */

#define OBJ_PAGER          "/obj/mudlib/pager/pager.c"
#define OBJ_SOCKET         "/obj/mudlib/sockets/socket_ob.c"
#define OBJ_NEWS_STDCLIENT "/obj/mudlib/newsclients/std_newsclient.c"
#define OBJ_SOUL_TOOL      "/obj/mudlib/emote_admin/emote_client.c"
#define OBJ_MAIL_CLIENT    "/obj/mudlib/mail_clients/mail_client.c"

#define ANNOUNCE_CHDMOD    "/adm/daemons/chmodules/announceNet.c"
#define LOCALNET_CHDMOD    "/adm/daemons/chmodules/localNet.c"
#define I3_CHDMOD          "/adm/daemons/chmodules/i3.c"

/* Daemons */

#define CHAN_D        "/adm/daemons/chan_d.c"
#define SHUTDOWN_D    "/adm/daemons/shutdown_d.c"
#define GA_SERVER     "/adm/daemons/ga_server.c"
#define NEWS_D        "/adm/daemons/news_d.c"
#define FINGER_D      "/adm/daemons/finger_d.c"
#define ANSI_PARSER   "/adm/daemons/ansi_parser.c"
#define TERMINAL_D    "/adm/daemons/terminal_d.c"
#define SOUL_D        "/adm/daemons/soul_d.c"
#define LOCKDOWN_D    "/adm/daemons/lockdown_d.c"
#define MAIL_D        "/adm/daemons/mail_d.c"
#define SOCKET_D      "/adm/daemons/socket_d.c"
#define RANK_D        "/adm/daemons/rank_d.c"
#define HISTORY_D     "/adm/daemons/history_d.c"
#define HTTP_D        "/adm/daemons/http_d.c"
#define JOBS_D        "/adm/daemons/jobs_d.c"
#define RESEARCH_D    "/adm/daemons/research_d.c"
#define COMBAT_D      "/adm/daemons/combat_d.c"


/* Global Defines */
#define DEFAULT_PROMPT       "$W>"
#define MOVE_WAIT_TIME_TYPE  3
#define MOVE_WAIT_TIME       250

/* Position Defines for mobile poisitions */
#define STAND 0
#define KNEEL 1
#define SIT   2
#define LAY   3
#define REST  4

/** Max string able to be printed */
#define MAX_PRINT_STRING 8192

/* Redefinition warnings protection */

#endif
