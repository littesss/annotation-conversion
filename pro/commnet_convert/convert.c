
/**********************************************************
*    > File Name: convert.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 09时46分48秒
**********************************************************/

#include "utili.h"
#include "convertcomment.h"

// ./cct -s /home/xxx -d /home/xxxx

int main(int argc, char *argv[])
{
    FILE *fpin = open_file("./src_file/input.c", "r");
    FILE *fpout = open_file("./dest_file/output.c", "w");

    convertcomment(fpin, fpout);

    close_file(fpin);
    close_file(fpout);
    printf("Commnet Convert Completion.......\n");
    return 0;
}
