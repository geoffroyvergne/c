#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *ltrim(char *s) {
	char* tmp_s = (char *) malloc( sizeof(char) * 2000 );
	strcpy(tmp_s, s);

    while(isspace(*tmp_s)) tmp_s++;
    return tmp_s;
}

char *rtrim(char *s) {
	char* tmp_s = (char *) malloc( sizeof(char) * 2000 );
	strcpy(tmp_s, s);

    char* back = tmp_s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return tmp_s;
}

char *trim(char *s) {
	char* tmp_s = (char *) malloc( sizeof(char) * 2000 );
	strcpy(tmp_s, s);

    return rtrim(ltrim(tmp_s)); 
}

char* toLowerCase(char* s) {
	char* tmp_s = (char *) malloc( sizeof(char) * 2000 );
	strcpy(tmp_s, s);

  	for(char *p=tmp_s; *p; p++) *p=tolower(*p);
  	return tmp_s;
}

char* toUpperCase(char* s) {
	char* tmp_s = (char *) malloc( sizeof(char) * 2000 );
	strcpy(tmp_s, s);

  	for(char *p=tmp_s; *p; p++) *p=toupper(*p);
 	return tmp_s;
}

char* substr(const char *src, int m, int n) {
	// get length of the destination string
	int len = n - m;

	// allocate (len + 1) chars for destination (+1 for extra null character)
	char *dest = (char*)malloc(sizeof(char) * (len + 1));

	// extracts characters between m'th and n'th index from source string
	// and copy them into the destination string
	for (int i = m; i < n && (*(src + i) != '\0'); i++) {
		*dest = *(src + i);
		dest++;
	}

	// null-terminate the destination string
	*dest = '\0';

	// return the destination string
	return dest - len;
}