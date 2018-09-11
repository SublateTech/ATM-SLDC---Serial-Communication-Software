# Microsoft Visual C++ generated build script - Do not modify

PROJ = BBVA
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\BBVAV1~1.4\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = BBVAWIN.CPP 
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"BBVA.PDB"
CFLAGS_R_WEXE = /nologo /G3 /W3 /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE 
LIBS_D_WEXE = oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw slibcew winsock 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = BBVA.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = BBVAWIN.SBR \
		ABOUT.SBR \
		COMMPORT.SBR \
		SYIO.SBR \
		DISKID.SBR \
		BBVA.SBR


BBVAWIN_DEP = c:\bbvav1~1.4\bbvawin.h


BBVA_RCDEP = c:\bbvav1~1.4\bbva.ico


ABOUT_DEP = c:\bbvav1~1.4\about.h \
	c:\bbvav1~1.4\bbvawin.h \
	c:\bbvav1~1.4\bbva.h \
	c:\bbvav1~1.4\diskid.h \
	c:\bbvav1~1.4\syio.h \
	c:\bbvav1~1.4\msa.h \
	c:\bbvav1~1.4\commport.h


COMMPORT_DEP = c:\bbvav1~1.4\commport.h \
	c:\bbvav1~1.4\bbva.h \
	c:\bbvav1~1.4\bbvawin.h \
	c:\bbvav1~1.4\diskid.h \
	c:\bbvav1~1.4\syio.h \
	c:\bbvav1~1.4\msa.h


SYIO_DEP = c:\bbvav1~1.4\syio.h \
	c:\bbvav1~1.4\msa.h \
	c:\bbvav1~1.4\commport.h


DISKID_DEP = c:\msvc\include\winsock.h \
	c:\bbvav1~1.4\diskid.h \
	c:\bbvav1~1.4\bbvawin.h


BBVA_DEP = c:\bbvav1~1.4\bbva.h \
	c:\bbvav1~1.4\bbvawin.h \
	c:\bbvav1~1.4\diskid.h \
	c:\bbvav1~1.4\syio.h \
	c:\bbvav1~1.4\msa.h \
	c:\bbvav1~1.4\commport.h \
	c:\bbvav1~1.4\about.h


all:	$(PROJ).EXE $(PROJ).BSC

BBVAWIN.OBJ:	BBVAWIN.CPP $(BBVAWIN_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c BBVAWIN.CPP

BBVA.RES:	BBVA.RC $(BBVA_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r BBVA.RC

ABOUT.OBJ:	ABOUT.CPP $(ABOUT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ABOUT.CPP

COMMPORT.OBJ:	COMMPORT.CPP $(COMMPORT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMMPORT.CPP

SYIO.OBJ:	SYIO.CPP $(SYIO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SYIO.CPP

DISKID.OBJ:	DISKID.CPP $(DISKID_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DISKID.CPP

BBVA.OBJ:	BBVA.CPP $(BBVA_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BBVA.CPP


$(PROJ).EXE::	BBVA.RES

$(PROJ).EXE::	BBVAWIN.OBJ ABOUT.OBJ COMMPORT.OBJ SYIO.OBJ DISKID.OBJ BBVA.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
BBVAWIN.OBJ +
ABOUT.OBJ +
COMMPORT.OBJ +
SYIO.OBJ +
DISKID.OBJ +
BBVA.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) BBVA.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	BBVA.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) BBVA.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
