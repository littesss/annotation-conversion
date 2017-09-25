
/**********************************************************
*    > File Name: convertcomment.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 09时55分30秒
**********************************************************/

#include "convertcomment.h"

//定义状态
typedef enum
{
    no_comment_state,
    c_comment_state,
    cpp_comment_state,
    str_state,
    end_state
}enum_state;

//定义状态机
typedef struct
{
    FILE *input;
    FILE *output;
    enum_state ulstate;
}state_machine;

//定义全局状态机
state_machine g_state;

/////////////////////////////////////////////////////////
FILE* open_file(char *file, char *mode)
{
    FILE *fp = fopen(file, mode);
    if(NULL == fp)
    {
        printf("open %s fail.\n",file);
        exit(1);
    }
    return fp;
}
void close_file(FILE *fp)
{
    assert(fp != NULL);
    fclose(fp);
}
char read_ch(FILE *fp)
{
    return fgetc(fp);
}
void write_ch(char ch, FILE *fp)
{
    fputc(ch, fp);
}
void write_double_ch(char ch1, char ch2, FILE *fp)
{
    fputc(ch1, fp);
    fputc(ch2, fp);
}

/////////////////////////////////////////////////////////


int convertcomment(FILE *inputfile, FILE *outputfile)
{
    if(inputfile==NULL || outputfile==NULL)
    {
        printf("invalid arugment inputfile or outputfile.\n");
        return -1;
    }

    /////////////////////////////////////////////////////////
    //初始化状态机
    g_state.input = inputfile;
    g_state.output = outputfile;
    g_state.ulstate = no_comment_state;

    char ch;
    while(g_state.ulstate != end_state)
    {
        ch = fgetc(g_state.input);
        eventpro(ch);
    }

    return 0;
}

void eventpro(char ch)
{
    switch(g_state.ulstate)
    {
    case no_comment_state:
        eventpro_no(ch);
        break;
    case c_comment_state:
        eventpro_c(ch);
        break;
    case cpp_comment_state:
        eventpro_cpp(ch);
        break;
    case str_state:
        eventpro_str(ch);
        break;
    }
}

void eventpro_no(char ch)
{
    char nextch;
    switch(ch)
    {
    case '/':
        nextch = fgetc(g_state.input);
        if(nextch == '/')   //C++
        {
            //fputc('/', g_state.output);
            //fputc('*', g_state.output);
            write_double_ch('/','*', g_state.output);
            g_state.ulstate = cpp_comment_state;
        }
        else if(nextch == '*')
        {
            fputc('/', g_state.output);
            fputc('*', g_state.output);
            g_state.ulstate = c_comment_state;
        }
        break;
    case EOF:
        g_state.ulstate = end_state;
        break;
    default:
        fputc(ch, g_state.output);
        break;
    }
}

void eventpro_cpp(char ch)
{
    char nextch;
    char thirdch;
    switch(ch)
    {
    case EOF:
        fputc('*', g_state.output);
        fputc('/', g_state.output);
        g_state.ulstate = end_state;
        break;
    case '\n':
        fputc('*', g_state.output);
        fputc('/', g_state.output);
        g_state.ulstate = no_comment_state;
        fputc('\n', g_state.output);
        break;
    case '/':
        nextch = fgetc(g_state.input);
        
        if(nextch=='/' || nextch=='*')   //123 //456  or //123 /*456
        {
            if(nextch == '/')
            {
                thirdch = fgetc(g_state.input);
                if(thirdch == '/')
                {
                    while((thirdch=fgetc(g_state.input)) == '/');
                    fputc(thirdch, g_state.output);
                }
                else
                {
                    fputc(' ', g_state.output);
                    fputc(' ', g_state.output);
                    fseek(g_state.input,-1, SEEK_CUR);
                }
            }
        }
        break;
    case '*':
        nextch = fgetc(g_state.input);
        if(nextch == '/')   // 123 */
        {
            fputc(' ', g_state.output);
            fputc(' ', g_state.output);
        }
        break;
    default:
        fputc(ch, g_state.output);
        break;
    }
}

void eventpro_c(char ch)
{
    char nextch;
    switch(ch)
    {
    case '*':
        nextch = fgetc(g_state.input);
        if(nextch == '/')    /*  123456 */
        {
            fputc('*', g_state.output);
            fputc('/', g_state.output);
            g_state.ulstate = no_comment_state;
        }
        break;
    case '/':
        nextch = fgetc(g_state.input);
        if(nextch == '/')   //  /*123 //456 */
        {
            fputc(' ', g_state.output);
            fputc(' ', g_state.output);
        }
        break;
    default:
        fputc(ch, g_state.output);
        break;
    }
}

void eventpro_str(char ch)
{
    //
}





















