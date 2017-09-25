cct:convert.o convertcomment.o
	gcc -o cct convert.o convertcomment.o
convert.o:convert.c
	gcc -o convert.o -c convert.c -g
convertcomment.o:convertcomment.c
	gcc -o convertcomment.o -c convertcomment.c -g
clean:
	rm *.o cct
