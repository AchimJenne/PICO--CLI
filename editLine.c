/**
 *
 */
#include "pico_cli.h"

/**
  @brief editLine - Interactive VT100- Terminal command input 
  @param [in, out] psLine Buffer to read and edit
  @param [in] inChar serial input byte to interpret
*/
bool editLine(char *psLine, char inChar)
{
  static char sBack[ILINE];
  char sTemp[ILINE];
  static unsigned char iIndx= 0;
  static uint8_t iESC= 0, iL2C= 0;
  static bool bEditMode= false;
  if ((inChar != SOH) && (inChar != NAK) && (inChar != ACK)) {
      if (inChar == '\r')       // CR key
      {
        printf( "\e[%dG", (int) (strlen(psLine) + strlen(sPath)+2));
        iIndx= 0;
        iESC= 0;
        strcpy(&sBack[0], psLine);
        bEditMode= true;
      } else {
        bEditMode= false;
        if (inChar == '\n')   // new line
        {
          putchar((int)inChar);
        } else 
        if ((inChar == '[') && (iESC ==1)) {
          iESC = 2;
        } else 
        if (((inChar == 'A')||(inChar == 'B')) && (iESC ==2)) // cursor up-down
        {
          for (char i=0; i<iIndx; i++) {
            printf("\b \b");
          }
          strcpy(&sTemp[0], psLine);
          strcpy(psLine, &sBack[0]);
          strcpy(&sBack[0], &sTemp[0]);
          printf("\e[0G%s>%s", sPath, psLine);
          iIndx= strlen(psLine);
          iESC= 0;
        } else 
        if ((inChar == 'D') && (iESC ==2)) // key left
        {
          if (iIndx >=1) {
            printf("\e[D");
            iIndx--;
          }
          iESC= 0;
        } else 
        if ((inChar == 'C') && (iESC ==2)) {  // key right
          if (strlen(psLine) > iIndx) {
            printf("\e[C");
            iIndx++;
          }
          iESC= 0;
        } else
        if ((inChar == '1') && (iESC ==2)) {
          iL2C= 1;
          iESC= 3;
        } else
        if ((inChar == '4') && (iESC ==2)) {
          iL2C= 4;
          iESC= 3;
        } else 
        if ((inChar == '5') && (iESC ==2)) {
          iL2C= 5;
          iESC= 3;
        } else 
        if ((inChar == '6') && (iESC ==2)) {
          iL2C= 6;
          iESC= 3;
        } else
        if ((inChar == '~') && (iESC ==3)) {  
          if (iL2C == 1) {
            printf( "\e[%dG", (int)(strlen(sPath)+2));
            iIndx= strlen(psLine);
            iESC= 0;
          } else
          if (iL2C == 4) {
            printf("\e[0G%s>%s", sPath, psLine);
            iIndx= strlen(psLine);          
            iESC= 0;
          }
          if (iL2C == 5) {
            printf("\e[25A");
            iESC= 0;
          }
          if (iL2C == 6) {
            printf("\e[25B");
            iESC= 0;
          }          
        } else
        if (iESC >= 2) { // unknown key 
          printf( "\r\n 0x%4.4x",(int)inChar);
        } else
        if ((inChar == C_BS)&&(iESC == 0)) { // backpace key 
          if (strlen(psLine) >= 1) {
            int iLen= strlen(psLine);
            if (iLen> iIndx) {
              for (int iLoop= iIndx; iLoop <= (iLen); iLoop++) {
                *(psLine+iLoop-1) = *(psLine+iLoop);
              }
              iIndx--;
              printf("\b%s ", (psLine + iIndx));
              printf("\e[%dD",(iLen-iIndx));
            } else {
              printf("\b \b");
              iIndx--;
              *(psLine+iIndx) = 0x00;
            }            
          }
        } else 
        if (inChar == C_ESC) {   // escape key
          if (iESC >= 1) {
            for (char i=0; i<iIndx; i++) {
               printf("\b \b");
            }
            *psLine= 0;
            iIndx= 0;
            bEditMode = false;
            iESC= 0;
          } else {
            iESC= 1;
          }
        } else           
        if (inChar == 0x7f) {
          int iLen= strlen(psLine);
          if (iLen> iIndx) {           
            for (int iLoop=iIndx+1; iLoop <= iLen; iLoop++){
              *(psLine+iLoop-1) = *(psLine+iLoop);
            }
            printf("%s", (psLine + iIndx));
            printf( "\e[%dD",(iLen - iIndx));
          }          
        } else {
          if (iIndx < ILINE) {
            putchar((int)inChar);
            int iLen= strlen(psLine);
            if (iLen> iIndx) {
              for (int iLoop=iLen; iLoop >= iIndx; iLoop--) {
                *(psLine+iLoop+1) = *(psLine+iLoop);
              } /* end for */
              *(psLine+iIndx) = inChar;
              printf("%s",(psLine + iIndx + 1));   
              printf( "\e[%dG",(int)(iIndx + 3 + strlen(sPath)));
              iIndx++;
            } else {
              *(psLine+iIndx) = inChar;
              iIndx++;
              *(psLine+iIndx) = 0x00;
            }
          }
        }
      }
    } else {
      // 
    }
  return (bEditMode);
}
