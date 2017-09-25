#ifndef _CONVERTCOMMENT_H
#define _CONVERTCOMMENT_H
/**********************************************************
*    > File Name: convertcomment.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 09时54分39秒
**********************************************************/

#include "utili.h"

FILE* open_file(char *file, char *mode);
void close_file(FILE *fp);
char read_ch(FILE *fp);
void write_ch(char ch, FILE *fp);
void write_double(char ch1, char ch2, FILE *fp);
/////////////////////////////////////////////////////

int convertcomment(FILE *inputfile, FILE *outputfile);
void eventpro(char ch);
void eventpro_no(char ch);
void eventpro_cpp(char ch);
void eventpro_c(char ch);
void eventpro_str(char ch);

#endif // _CONVERTCOMMENT_H
