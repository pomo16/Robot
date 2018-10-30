#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define A_COL_1 PCout(0)
#define A_COL_2 PCout(2)
#define A_COL_3 PAout(1)
#define A_ROW_1 PAin(4)
#define A_ROW_2 PAin(6)
#define A_ROW_3 PCin(4)
#define A_ROW_4 PBin(0)

#define B_COL_1 PEout(1)
#define B_COL_2 PEout(3)
#define B_COL_3 PEout(5)
#define B_ROW_1 PCin(13)
#define B_ROW_2 PFin(1)
#define B_ROW_3 PFin(3)
#define B_ROW_4 PFin(5)

#define C_COL_1 PAout(13)
#define C_COL_2 PCout(9)
#define C_COL_3 PCout(7)
#define C_ROW_1 PGin(8)
#define C_ROW_2 PGin(6)
#define C_ROW_3 PGin(4)
#define C_ROW_4 PGin(2)

#define D_COL_1 PEout(0)
#define D_COL_2 PEout(2)
#define D_COL_3 PEout(4)
#define D_ROW_1 PEin(6)
#define D_ROW_2 PFin(0)
#define D_ROW_3 PFin(2)
#define D_ROW_4 PFin(4)

#define E_COL_1 PCout(5)
#define E_COL_2 PBout(1)
#define E_COL_3 PFout(11)
#define E_ROW_1 PFin(13)
#define E_ROW_2 PFin(15)
#define E_ROW_3 PGin(1)
#define E_ROW_4 PBin(12)

void KEY_Init(void);//IO≥ı ºªØ
int KEYA_Scan(void);
int KEYB_Scan(void);
int KEYC_Scan(void);
int KEYD_Scan(void);
int KEYE_Scan(void);

#endif
