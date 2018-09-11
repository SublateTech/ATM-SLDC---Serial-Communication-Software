#include "windows.h"
#include "msa.h"
#include "CommPort.h"

class Moxa;

#if (!defined(_WIN_syio))
	#define _WIN_syio


#define SDLCPORT		8
#define READ_LEN	    64
#define BAUD_RATE	    38400
#define CRC_MODE	    NONE_CRC
#define TX_CLOCK	    TX_CLOCK_IN
#define DATA_ENCODING   NRZ
#define RXQUEUE         1024
#define TXQUEUE         1024


/***************************************************************
 * Descriptions and typedefs associated with the SDLC protocol *
 ***************************************************************/

 /* Type of frames */
#define UNNUMBERED            0x03
#define SUPERVISORY          0x02
#define SUPERVISORY8         0x01
#define INFO               0x00

/* Unnumbered frames */
#define UI                  0x03
#define RIM                  0x07
#define SIM                  0x07
#define DM                  0x0F
#define UP                  0x23
#define DISC               0x43
#define RD                  0x43
#define UA                  0x63
#define SNRM               0x83
#define FRMR               0x87
#define XID                  0xAF
#define CFGR               0xC7
#define SNRME               0xCF
#define TEST               0xE3
#define BCN                  0xEF

/* Supervisory frames */
#define RR                  0x01
#define RNR                  0x05
#define REJ                  0x09

/* Mask for the Poll/Final bit */
#define POLL_FINAL_BIT         0x10



class  Moxa 
{
private:
	
/*
 * Definition of the different frame formats
 */

/* Unnumbered frames */
typedef union {

   struct {
       BYTE unused1      : 4;
        BYTE PollFinal      : 1;
       BYTE unused2      : 3;
    };
    BYTE Type;

} u_frame;

       
/* Info frames, modulo 8 */
typedef struct {

   BYTE zero         : 1;
    BYTE Ns            : 3;
    BYTE PollFinal      : 1;
   BYTE Nr            : 3;

} i_frame;

	/* Supervidory frames, modulo 8 */
typedef struct {

    BYTE Type         : 4;
    BYTE PollFinal      : 1;
   BYTE Nr            : 3;

} s_frame;

/* General frame format */
typedef struct {

   BYTE addr;
   union {

      u_frame   u;
       s_frame   s;
       i_frame   i;
       BYTE      byte;
    };
   
} frame_t;

    
	
	char  szTemp[ TXQUEUE ] ;
	char szASL[TXQUEUE];
    
    
    int lFirst;
	HINSTANCE hInstance;
	
	
	
public:
	Moxa();
	~Moxa();
	
	BOOL IsOk();
	BOOL Open();
	Close();
	void ATMProc();
	int SDLCDecodeRx(frame_t *frame, char *OutString);
	void Init();


	char *IfFirst(char *pStr);
	char *IfLast(char *pStr);

	BOOL m_status;
	BOOL m_transac;
	int  m_timer;
	char m_mens[64];
	BOOL m_control;
	int nTimer; 
	HWND m_wnd;
	
	CommPort* serial;

};

#endif           
