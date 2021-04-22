﻿#pragma once
#include "../grx/gdsmigr.h"

#define ads_malloc	gds_malloc
#define ads_free	  gds_free
#define ads__msize	gds__msize
#define ads_realloc gds_realloc
#define ads_calloc	gds_calloc
#define ads_strdup	gds_strdup
#define ads__strdup	gds__strdup

#define ads_getfullinput	gds_getfullinput
#define ads_getfullkword  gds_getfullkword
#define ads_getfullstring gds_getfullstring
#define	ads_getappname	gds_getappname
#define	ads_update	gds_update
#define	ads_command	gds_command
#define	ads_cmd	        gds_cmd
#define	ads_regfunc	gds_regfunc
#define	ads_usrbrk	gds_usrbrk
#define	ads_defun	gds_defun
#define	ads_setfunhelp	gds_setfunhelp
#define	ads_undef	gds_undef
#define	ads_getfuncode	gds_getfuncode
#define	ads_getargs	gds_getargs
#define	ads_retlist	gds_retlist
#define	ads_retval	gds_retval
#define	ads_retpoint	gds_retpoint
#define	ads_retstr	gds_retstr
#define	ads_retname	gds_retname
#define	ads_retint	gds_retint
#define	ads_retreal	gds_retreal
#define	ads_rett	gds_rett
#define	ads_retnil	gds_retnil
#define	ads_retvoid	gds_retvoid
#define	ads_entsel	gds_entsel
#define	ads_nentsel	gds_nentsel
#define	ads_nentselp	gds_nentselp
#define	ads_ssget	gds_ssget

#define	ads_ssgetfirst	gds_ssgetfirst
#define	ads_sssetfirst	gds_sssetfirst

#define	ads_ssfree	gds_ssfree
#define	ads_sslength	gds_sslength
#define	ads_ssadd	gds_ssadd
#define	ads_ssdel	gds_ssdel
#define	ads_ssmemb	gds_ssmemb
#define	ads_ssname	gds_ssname
#define	ads_ssnamex	gds_ssnamex
#define	ads_ssGetKwordCallbackPtr	gds_ssGetKwordCallbackPtr
#define	ads_ssSetKwordCallbackPtr	gds_ssSetKwordCallbackPtr
#define	ads_ssGetOtherCallbackPtr	gds_ssGetOtherCallbackPtr
#define	ads_ssSetOtherCallbackPtr	gds_ssSetOtherCallbackPtr
#define	ads_setvar	gds_setvar
#define	ads_initget	gds_initget
#define	ads_getsym	gds_getsym
#define	ads_putsym	gds_putsym
#define	ads_help	gds_help
#define	ads_fnsplit	gds_fnsplit
#define	ads_trans	gds_trans
#define	ads_arxloaded	gds_arxloaded
#define	ads_arxload	gds_arxload
#define	ads_arxunload	gds_arxunload
#define	ads_invoke	gds_invoke
#define	ads_getvar	gds_getvar
#define	ads_findfile	gds_findfile
#define	ads_findtrustedfile	gds_findtrustedfile
#define	ads_agetenv	gds_agetenv
#define	ads_asetenv	gds_asetenv
#define	ads_getenv	gds_getenv
#define	ads_setenv	gds_setenv
#define	ads_agetcfg	gds_agetcfg
#define	ads_asetcfg	gds_asetcfg
#define	ads_getcfg	gds_getcfg
#define	ads_setcfg	gds_setcfg
#define	ads_getstring	gds_getstring
#define	ads_getstringb	gds_getstringb
#define	ads_menucmd	gds_menucmd
#define	ads_prompt	gds_prompt
#define	ads_alert	gds_alert
#define	ads_getangle	gds_getangle
#define	ads_getcorner	gds_getcorner
#define	ads_getdist	gds_getdist
#define	ads_getorient	gds_getorient
#define	ads_getpoint	gds_getpoint
#define	ads_getint	gds_getint
#define	ads_getkword	gds_getkword
#define	ads_getreal	gds_getreal
#define	ads_getinput	gds_getinput
#define	ads_vports	gds_vports
#define	ads_textscr	gds_textscr
#define	ads_graphscr	gds_graphscr
#define	ads_textpage	gds_textpage
#define	ads_redraw	gds_redraw
#define	ads_osnap	gds_osnap
#define	ads_grread	gds_grread
#define	ads_grtext	gds_grtext
#define	ads_grdraw	gds_grdraw
#define	ads_grvecs	gds_grvecs
#define	ads_xformss	gds_xformss
#define	ads_draggen	gds_draggen
#define	ads_setview	gds_setview
#define	ads_getfiled	gds_getfiled
#define ads_getfilenavdialog gds_getfilenavdialog
#define	ads_textbox	gds_textbox
#define	ads_tablet	gds_tablet
#define	ads_getcname	gds_getcname


#define	ads_xdroom	gds_xdroom
#define	ads_xdsize	gds_xdsize

#define ads_name_set gds_name_set
#define ads_point_set gds_point_set


//gds_names
#define ads_name_clear gds_name_clear
#define ads_name_nil gds_name_nil
#define ads_name_equal gds_name_equal


#define	ads_entdel	gds_entdel
#define	ads_entgetx	gds_entgetx
#define	ads_entget	gds_entget
#define	ads_entlast	gds_entlast
#define	ads_entnext	gds_entnext
#define	ads_entupd	gds_entupd
#define	ads_entmod	gds_entmod
#define	ads_entmake	gds_entmake
#define	ads_entmakex	gds_entmakex
#define	ads_tblnext	gds_tblnext
#define	ads_tblsearch	gds_tblsearch
#define	ads_namedobjdict	gds_namedobjdict
#define	ads_dictsearch	gds_dictsearch
#define	ads_dictnext	gds_dictnext
#define	ads_dictrename	gds_dictrename
#define	ads_dictremove	gds_dictremove
#define	ads_dictadd	gds_dictadd
#define	ads_tblobjname	gds_tblobjname
#define	ads_handent	gds_handent
#define	ads_inters	gds_inters
#define	ads_snvalid	gds_snvalid
#define	ads_xstrsave	gds_xstrsave
#define	ads_xstrcase	gds_xstrcase
#define	ads_regapp	gds_regapp
#define	ads_fail	gds_fail
#define	ads_angtos	gds_angtos
#define	ads_rangtos	gds_rangtos
#define	ads_rtos	gds_rtos
#define	ads_angtof	gds_angtof
#define	ads_rangtof	gds_rangtof
#define	ads_distof	gds_distof
#define ads_regappx gds_regappx

#define	ads_printf	gds_printf
#define	ads_cvunit	gds_cvunit
#define	ads_wcmatch	gds_wcmatch
#define	ads_angle	gds_angle
#define	ads_distance	gds_distance
#define	ads_polar	gds_polar
#define	ads_isalpha	gds_isalpha
#define	ads_isupper	gds_isupper
#define	ads_islower	gds_islower
#define	ads_isdigit	gds_isdigit
#define	ads_isxdigit	gds_isxdigit
#define	ads_isspace	gds_isspace
#define	ads_ispunct	gds_ispunct
#define	ads_isalnum	gds_isalnum
#define	ads_isprint	gds_isprint
#define	ads_isgraph	gds_isgraph
#define	ads_iscntrl	gds_iscntrl
#define	ads_toupper	gds_toupper
#define	ads_tolower	gds_tolower
#define	ads_newrb	gds_newrb
#define	ads_relrb	gds_relrb
#define	ads_buildlist	gds_buildlist
#define ads_queueexpr	gds_queueexpr