#include "pico_cli.h"

/**************************************************/
/*! \brief func_MonParser function                                 
    \param szCmdLn is a pointer of char Cmd-Line
    \return int value of token; 0: no token found
    \ingroup token_parser
    \sa datetime_t */
/**************************************************/
int func_MonParser(char *szCmdLn)
{
   int iCmdLn;
   int iCmdPos;
   int iRet;
 
   iCmdPos= strcspn(szCmdLn," ");
   if (iCmdPos <= 0) iCmdPos= strlen(szCmdLn);
 
   iCmdLn= strncmp( szCmdLn, "Jul", (iCmdPos>(const size_t)strlen("Jul")? iCmdPos: (const size_t)strlen("Jul")));
   if (iCmdLn < 0) // is less than Jul
   {
      iCmdLn= strncmp( szCmdLn, "Dec", (iCmdPos>(const size_t)strlen("Dec")? iCmdPos: (const size_t)strlen("Dec")));
      if (iCmdLn < 0) // is less than Dec
      {
         if (strncmp( szCmdLn, "Apr", (iCmdPos>(const size_t)strlen("Apr")? iCmdPos: (const size_t)strlen("Apr")))== 0)
         {
            iRet= 4;
         } else { // not Apr
            if (strncmp( szCmdLn, "Aug", (iCmdPos>(const size_t)strlen("Aug")? iCmdPos: (const size_t)strlen("Aug")))== 0)
            {
               iRet= 8;
            } else { //unknown token
               iRet= 0;
            } // End of(2:Aug)
         } // End of(1:Apr)
      } else {
         if (iCmdLn > 0) // is higher than Dec
         {
            if (strncmp( szCmdLn, "Feb", (iCmdPos>(const size_t)strlen("Feb")? iCmdPos: (const size_t)strlen("Feb")))== 0)
            {
               iRet= 2;
            } else { // not Feb
               if (strncmp( szCmdLn, "Jan", (iCmdPos>(const size_t)strlen("Jan")? iCmdPos: (const size_t)strlen("Jan")))== 0)
               {
                  iRet= 1;
               } else { //unknown token
                  iRet= 0;
               } // End of(5:Jan)
            } // End of(4:Feb)
         } else {
            if (iCmdLn == 0) // Token Dec found
            {
               iRet= 12;
            } // End of(3:Dec)
         }
      }
   } else {
      if (iCmdLn > 0) // is higher than Jul
      {
         iCmdLn= strncmp( szCmdLn, "Mar", (iCmdPos>(const size_t)strlen("Mar")? iCmdPos: (const size_t)strlen("Mar")));
         if (iCmdLn < 0) // is less than Mar
         {
            if (strncmp( szCmdLn, "Jun", (iCmdPos>(const size_t)strlen("Jun")? iCmdPos: (const size_t)strlen("Jun")))== 0)
            {
               iRet= 6;
            } else { // not Jun
               if (strncmp( szCmdLn, "Mai", (iCmdPos>(const size_t)strlen("Mai")? iCmdPos: (const size_t)strlen("Mai")))== 0)
               {
                  iRet= 5;
               } else { //unknown token
                  iRet= 0;
               } // End of(8:Mai)
            } // End of(7:Jun)
         } else {
            if (iCmdLn > 0) // is higher than Mar
            {
               iCmdLn= strncmp( szCmdLn, "Oct", (iCmdPos>(const size_t)strlen("Oct")? iCmdPos: (const size_t)strlen("Oct")));
               if (iCmdLn == 0)
               {
                  iRet= 10;
               } else { // not Oct
                  if (iCmdLn < 0)
                  {
                     iCmdLn= strncmp( szCmdLn, "Nov", (iCmdPos>(const size_t)strlen("Nov")? iCmdPos: (const size_t)strlen("Nov")));
                     if (iCmdLn == 0)
                     {
                        iRet= 11;
                     } else { //unknown token
                        iRet= 0;
                     }
                  } else {
                     if (strncmp( szCmdLn, "Sep", (iCmdPos>(const size_t)strlen("Sep")? iCmdPos: (const size_t)strlen("Sep")))== 0)
                     {
                        iRet= 9;
                     } else { //unknown token
                        iRet= 0;
                     } // End of(12:Sep)
                  } // End of(10:Nov)
               } // End of(11:Oct)
            } else {
               if (iCmdLn == 0) // Token Mar found
               {
                  iRet= 3;
               } // End of(9:Mar)
            }
         }
      } else {
         if (iCmdLn == 0) // Token Jul found
         {
            iRet= 7;
         } // End of(6:Jul)
      }
   }
   return(iRet);
} /* end of function func_MonParser */  

/**************************************************/
/*! \brief fnc_AUTO                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_AUTO(const char* szCmdLn)
{
    /* place your code here */
    if (bAuto) 
    {
      // tickHd100.detach();
      printf(": off\n");
      bAuto= false;
    } else {
      // tickHd100.attach_ms(100, task_ti100ms, (int) 1);
      printf(": on\n");
      bAuto = true;
    }
    return( eAUTO );
}  /* end of fnc_AUTO */


/**************************************************/
/*! \brief fnc_CD                                   
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_CD(const char* szCmdLn)
{
  /* place your code here */
  return( eCD );
}  /* end of fnc_CD */
 
/**************************************************/
/*! \brief fnc_CLS                                  
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_CLS(const char* szCmdLn)
{
   /* place your code here */
   printf("\e[0H\e[2J");
   return( eCLS );
}  /* end of fnc_CLS */
 
/**************************************************/
/*! \brief fnc_COPY                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_COPY(const char* szCmdLn)
{
  /* place your code here */
  return( eCOPY );
}  /* end of fnc_COPY */
 
/**************************************************/
/*! \brief fnc_CONFIG                               
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_CONFIG(const char* szCmdLn)
{
  /* place your code here */
  return( eCONFIG );
}  /* end of fnc_CONFIG */

/**************************************************/
/*! \brief fnc_DATE                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_DATE(const char* szCmdLn)
{
   int year, mon, day;
   datetime_t ti;
   rtc_get_datetime(&ti);
   if (strlen(szCmdLn) >= 8) {
      int16_t iResult= sscanf( szCmdLn, "%02d.%02d.%04d", &day, &mon, &year); 
      if (iResult == 3) {
         ti.day   = day;
         ti.month = mon; 
         ti.year  = year;
         rtc_set_datetime(&ti);
      }  
   } else {
      printf(" %2.2d.%2.2d.%4.4d", ti.day, ti.month, ti.year);
   }
   return( eDATE );
}  /* end of fnc_DATE */
 
/**************************************************/
/*! \brief fnc_DEL                                  
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_DEL(const char* szCmdLn)
{
  /* place your code here */
  return( eDEL );
}  /* end of fnc_DEL */
 
/**************************************************/
/*! \brief fnc_DIR                                  
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_DIR(const char* szCmdLn)
{
  /* place your code here */
   return( eDIR );
}  /* end of fnc_DIR */
 
/**************************************************/
/*! \brief fnc_ECHO                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_ECHO(const char* szCmdLn)
{
  /* place your code here */
   return( eECHO );
}  /* end of fnc_ECHO */
 
/**************************************************/
/*! \brief fnc_FORMAT                               
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_FORMAT(const char* szCmdLn)
{
  /* place your code here */
  return( eFORMAT );
}  /* end of fnc_FORMAT */
 
/**************************************************/
/*! \brief fnc_HELP                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_HELP(const char* szCmdLn)
{
  /* place your code here */
  printf(" :");
  printf("AUTO\n");
  printf("CLS\t clearscreen\n");
  printf("CONFIG\t display configuration\n");
  printf("COPY\t copy file; <src> <targ>\n");
  printf("DATE\t display/set date; format <DD.MM.YYYY>\n");
  printf("DEL\t delete file\n");
  printf("DIR\t display directory\n");
  printf("ECHO\t copy argument into logfile\n");
  printf("FORMAT\t <func. not available>\n");
  printf("HELP\t this help informations\n");
  printf("PATH\t display actual path\n");
  printf("REN\t rename file; <src> <targ>\n");
  printf("CD\t change directory\n");
  printf("MD\t make directory\n");
  printf("RD\t remove directory\n");
  printf("TIME\t display/set time; format <hh.mm.ss>\n");
  printf("TEMP\t display temperature(s)\n");
  printf("TYPE\t display ASCII-file\n");
  printf("VER\t display SW- Version\n");
  printf("VOL\t display SD-Card informations\n");
  printf("XREC\t XModem- download to uC\n");
  printf("XTRAN\t XModem- upload\n");
  return( eHELP );
}  /* end of fnc_HELP */
 
/**************************************************/
/*! \brief fnc_MD                                   
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_MD(const char* szCmdLn)
{
   /* place your code here */
  return( eMD );
}  /* end of fnc_MD */

/**************************************************/
/*! \brief fnc_PATH                               
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_PATH(const char* szCmdLn)
{
   /* place your code here */
   return( ePATH );
}  /* end of fnc_PROMPT */
 
/**************************************************/
/*! \brief fnc_RD                                   
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_RD(const char* szCmdLn)
{
  /* place your code here */
  return( eRD );
}  /* end of fnc_RD */
 
/**************************************************/
/*! \brief fnc_REN                               
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_REN(const char* szCmdLn)
{
  /* place your code here */
  return( eREN );
}  /* end of fnc_RENAME */
 
/**************************************************/
/*! \brief fnc_TEMP                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_TEMP(const char* szCmdLn)
{
  /* place your code here */
  return( eTEMP );
}  /* end of fnc_TEMP */
 
/**************************************************/
/*! \brief fnc_TIME                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_TIME(const char* szCmdLn)
{  
   /* place your code here */
   datetime_t ti;
   rtc_get_datetime(&ti);
   int hour, min, sec;
   if (strlen(szCmdLn) >= 5) {
      int16_t iResult= sscanf( szCmdLn, "%02d:%02d:%02d", &hour, &min, &sec); 
      if (iResult == 3) {
         ti.hour = hour;
         ti.min  = min; 
         ti.sec  = sec;
         rtc_set_datetime(&ti);
      } else
      if (iResult == 2) {
         ti.hour = hour;
         ti.min  = min; 
         rtc_set_datetime(&ti);
      } else {
         printf(" not valid %d", iResult);
      } 
   } else {
      printf(" %2.2d:%2.2d:%2.2d",ti.hour,ti.min,ti.sec);  
   }
   return( eTIME );
}  /* end of fnc_TIME */
 
/**************************************************/
/*! \brief fnc_TYPE                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_TYPE(const char* szCmdLn)
{
  /* place your code here */
   return( eTYPE );
}  /* end of fnc_TYPE */
 
/**************************************************/
/*! \brief fnc_VER                                  
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_VER(const char* szCmdLn)
{
   /* place your code here */
  return( eVER );
}  /* end of fnc_VER */
 
/**************************************************/
/*! \brief fnc_VOL                                  
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_VOL(const char* szCmdLn)
{
  /* place your code here */
  return( eVOL );
}  /* end of fnc_VOL */
 
/**************************************************/
/*! \brief fnc_XREC                                 
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_XREC(const char* szCmdLn)
{
   /* place your code here */
   return( eXREC );
}  /* end of fnc_XREC */

/**************************************************/
/*! \brief fnc_XTRAN                                
    \param argument string: pointer of char
    \return int- value of token
    \ingroup token_parser */
/**************************************************/
int fnc_XTRAN(const char* szCmdLn)
{
  /* place your code here */
  return( eXTRAN );
} /* end of fnc_XTRAN */

/**************************************************/
/*! \brief fnc_TokenNotFound
    \param argument string: pointer of char
    \return always 0
    \ingroup token_parser */
/**************************************************/
int fnc_TokenNotFound(const char* szCmdLn)
{
   /* place your code here */
   printf(" <?>\n");
   return( eNoToken );
}  /* end of fnc_TokenNotFound */
 
/**************************************************/
/*! \brief parser main function
     fnSDOS_Parser                                  
    \param szCmdLn is a pointer of char Cmd-Line
    \return int value of token; 0: no token found
    \ingroup token_parser
    \sa datetime_t */
/**************************************************/
int fnSDOS_Parser(char *szCmdLn)
{
   int iCmdLn;
   int iCmdPos;
   int iRet;
 
   iCmdPos= strcspn(szCmdLn," ");
   if (iCmdPos <= 0) iCmdPos= strlen(szCmdLn);
 
   // Recursion: 0; Test token no.:11 HELP
   // multible token
   iCmdLn= strncmp( szCmdLn, "HELP", (iCmdPos>(const size_t)strlen("HELP")? iCmdPos: (const size_t)strlen("HELP")));
   if (iCmdLn < 0) // is less than HELP
   {
      // search down(1,10)
      // Recursion: 1; Test token no.:5 COPY
      // multible token
      iCmdLn= strncmp( szCmdLn, "COPY", (iCmdPos>(const size_t)strlen("COPY")? iCmdPos: (const size_t)strlen("COPY")));
      if (iCmdLn < 0) // is less than COPY
      {
         // search down(1,4)
         // Recursion: 2; Test token no.:2 CD
         // multible token
         iCmdLn= strncmp( szCmdLn, "CD", (iCmdPos>(const size_t)strlen("CD")? iCmdPos: (const size_t)strlen("CD")));
         if (iCmdLn < 0) // is less than CD
         {
            // search down(1,1)
            // Recursion: 3; Test token no.:1 AUTO
            // single token
            if (strncmp( szCmdLn, "AUTO", (iCmdPos>(const size_t)strlen("AUTO")? iCmdPos: (const size_t)strlen("AUTO")))== 0)
            {
               iRet= fnc_AUTO(szCmdLn+((const size_t) strlen("AUTO")));
            } else { //unknown token)
               iRet= fnc_TokenNotFound(szCmdLn);
            } // End of(1:AUTO)
         } else {
            if (iCmdLn > 0) // is higher than CD
            {
               // search up(2,4)
               // Recursion: 4; Test token no.:3 CLS
               // double token
               if (strncmp( szCmdLn, "CLS", (iCmdPos>(const size_t)strlen("CLS")? iCmdPos: (const size_t)strlen("CLS")))== 0)
               {
                  iRet= fnc_CLS(szCmdLn+((const size_t) strlen("CLS")));
               } else { // not CLS
                  if (strncmp( szCmdLn, "CONFIG", (iCmdPos>(const size_t)strlen("CONFIG")? iCmdPos: (const size_t)strlen("CONFIG")))== 0)
                  {
                     iRet= fnc_CONFIG(szCmdLn+((const size_t) strlen("CONFIG")));
                  } else { //unknown token
                     iRet= fnc_TokenNotFound(szCmdLn);
                  } // End of(4:CONFIG)
               } // End of(3:CLS)
            } else {
               if (iCmdLn == 0) // Token CD found
               {
                  iRet= fnc_CD(szCmdLn+((const size_t) strlen("CD")));
               } // End of(2:CD)
            }
         }
      } else {
         if (iCmdLn > 0) // is higher than COPY
         {
            // search up(5,10)
            // Recursion: 3; Test token no.:8 DIR
            // multible token
            iCmdLn= strncmp( szCmdLn, "DIR", (iCmdPos>(const size_t)strlen("DIR")? iCmdPos: (const size_t)strlen("DIR")));
            if (iCmdLn < 0) // is less than DIR
            {
               // search down(6,7)
               // Recursion: 4; Test token no.:6 DATE
               // double token
               if (strncmp( szCmdLn, "DATE", (iCmdPos>(const size_t)strlen("DATE")? iCmdPos: (const size_t)strlen("DATE")))== 0)
               {
                  iRet= fnc_DATE(szCmdLn+((const size_t) strlen("DATE")));
               } else { // not DATE
                  if (strncmp( szCmdLn, "DEL", (iCmdPos>(const size_t)strlen("DEL")? iCmdPos: (const size_t)strlen("DEL")))== 0)
                  {
                     iRet= fnc_DEL(szCmdLn+((const size_t) strlen("DEL")));
                  } else { //unknown token
                     iRet= fnc_TokenNotFound(szCmdLn);
                  } // End of(7:DEL)
               } // End of(6:DATE)
            } else {
               if (iCmdLn > 0) // is higher than DIR
               {
                  // search up(8,10)
                  // Recursion: 5; Test token no.:9 ECHO
                  // double token
                  if (strncmp( szCmdLn, "ECHO", (iCmdPos>(const size_t)strlen("ECHO")? iCmdPos: (const size_t)strlen("ECHO")))== 0)
                  {
                     iRet= fnc_ECHO(szCmdLn+((const size_t) strlen("ECHO")));
                  } else { // not ECHO
                     if (strncmp( szCmdLn, "FORMAT", (iCmdPos>(const size_t)strlen("FORMAT")? iCmdPos: (const size_t)strlen("FORMAT")))== 0)
                     {
                        iRet= fnc_FORMAT(szCmdLn+((const size_t) strlen("FORMAT")));
                     } else { //unknown token
                        iRet= fnc_TokenNotFound(szCmdLn);
                     } // End of(10:FORMAT)
                  } // End of(9:ECHO)
               } else {
                  if (iCmdLn == 0) // Token DIR found
                  {
                     iRet= fnc_DIR(szCmdLn+((const size_t) strlen("DIR")));
                  } // End of(8:DIR)
               }
            }
         } else {
            if (iCmdLn == 0) // Token COPY found
            {
               iRet= fnc_COPY(szCmdLn+((const size_t) strlen("COPY")));
            } // End of(5:COPY)
         }
      }
   } else {
      if (iCmdLn > 0) // is higher than HELP
      {
         // search up(11,22)
         // Recursion: 2; Test token no.:17 TIME
         // multible token
         iCmdLn= strncmp( szCmdLn, "TIME", (iCmdPos>(const size_t)strlen("TIME")? iCmdPos: (const size_t)strlen("TIME")));
         if (iCmdLn < 0) // is less than TIME
         {
            // search down(12,16)
            // Recursion: 3; Test token no.:14 RD
            // multible token
            iCmdLn= strncmp( szCmdLn, "RD", (iCmdPos>(const size_t)strlen("RD")? iCmdPos: (const size_t)strlen("RD")));
            if (iCmdLn < 0) // is less than RD
            {
               // search down(12,13)
               // Recursion: 4; Test token no.:12 MD
               // double token
               if (strncmp( szCmdLn, "MD", (iCmdPos>(const size_t)strlen("MD")? iCmdPos: (const size_t)strlen("MD")))== 0)
               {
                  iRet= fnc_MD(szCmdLn+((const size_t) strlen("MD")));
               } else { // not MD
                  if (strncmp( szCmdLn, "PATH", (iCmdPos>(const size_t)strlen("PATH")? iCmdPos: (const size_t)strlen("PATH")))== 0)
                  {
                     iRet= fnc_PATH(szCmdLn+((const size_t) strlen("PATH")));
                  } else { //unknown token
                     iRet= fnc_TokenNotFound(szCmdLn);
                  } // End of(13:PATH)
               } // End of(12:MD)
            } else {
               if (iCmdLn > 0) // is higher than RD
               {
                  // search up(14,16)
                  // Recursion: 5; Test token no.:15 REN
                  // double token
                  if (strncmp( szCmdLn, "REN", (iCmdPos>(const size_t)strlen("REN")? iCmdPos: (const size_t)strlen("REN")))== 0)
                  {
                     iRet= fnc_REN(szCmdLn+((const size_t) strlen("REN")));
                  } else { // not REN
                     if (strncmp( szCmdLn, "TEMP", (iCmdPos>(const size_t)strlen("TEMP")? iCmdPos: (const size_t)strlen("TEMP")))== 0)
                     {
                        iRet= fnc_TEMP(szCmdLn+((const size_t) strlen("TEMP")));
                     } else { //unknown token
                        iRet= fnc_TokenNotFound(szCmdLn);
                     } // End of(16:TEMP)
                  } // End of(15:REN)
               } else {
                  if (iCmdLn == 0) // Token RD found
                  {
                     iRet= fnc_RD(szCmdLn+((const size_t) strlen("RD")));
                  } // End of(14:RD)
               }
            }
         } else {
            if (iCmdLn > 0) // is higher than TIME
            {
               // search up(17,22)
               // Recursion: 4; Test token no.:20 VOL
               // multible token
               iCmdLn= strncmp( szCmdLn, "VOL", (iCmdPos>(const size_t)strlen("VOL")? iCmdPos: (const size_t)strlen("VOL")));
               if (iCmdLn < 0) // is less than VOL
               {
                  // search down(18,19)
                  // Recursion: 5; Test token no.:18 TYPE
                  // double token
                  if (strncmp( szCmdLn, "TYPE", (iCmdPos>(const size_t)strlen("TYPE")? iCmdPos: (const size_t)strlen("TYPE")))== 0)
                  {
                     iRet= fnc_TYPE(szCmdLn+((const size_t) strlen("TYPE")));
                  } else { // not TYPE
                     if (strncmp( szCmdLn, "VER", (iCmdPos>(const size_t)strlen("VER")? iCmdPos: (const size_t)strlen("VER")))== 0)
                     {
                        iRet= fnc_VER(szCmdLn+((const size_t) strlen("VER")));
                     } else { //unknown token
                        iRet= fnc_TokenNotFound(szCmdLn);
                     } // End of(19:VER)
                  } // End of(18:TYPE)
               } else {
                  if (iCmdLn > 0) // is higher than VOL
                  {
                     // search up(20,22)
                     // Recursion: 6; Test token no.:21 XREC
                     // double token
                     if (strncmp( szCmdLn, "XREC", (iCmdPos>(const size_t)strlen("XREC")? iCmdPos: (const size_t)strlen("XREC")))== 0)
                     {
                        iRet= fnc_XREC(szCmdLn+((const size_t) strlen("XREC")));
                     } else { // not XREC
                        if (strncmp( szCmdLn, "XTRAN", (iCmdPos>(const size_t)strlen("XTRAN")? iCmdPos: (const size_t)strlen("XTRAN")))== 0)
                        {
                           iRet= fnc_XTRAN(szCmdLn+((const size_t) strlen("XTRAN")));
                        } else { //unknown token
                           iRet= fnc_TokenNotFound(szCmdLn);
                        } // End of(22:XTRAN)
                     } // End of(21:XREC)
                  } else {
                     if (iCmdLn == 0) // Token VOL found
                     {
                        iRet= fnc_VOL(szCmdLn+((const size_t) strlen("VOL")));
                     } // End of(20:VOL)
                  }
               }
            } else {
               if (iCmdLn == 0) // Token TIME found
               {
                  iRet= fnc_TIME(szCmdLn+((const size_t) strlen("TIME")));
               } // End of(17:TIME)
            }
         }
      } else {
         if (iCmdLn == 0) // Token HELP found
         {
            iRet= fnc_HELP(szCmdLn+((const size_t) strlen("HELP")));
         } // End of(11:HELP)
      }
   }
   return(iRet);
} /* end of function fnSDOS_Parser */
