#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
	int opt;
	bool scramble = true;

	while ((opt = getopt(argc, argv, "us")) != -1) {
		switch (opt) {
		case 's':
			scramble = true;
			break;
		case 'u':
			scramble = false;
			break;
		case '?':
			fprintf(stderr, "unknown option: %c\n", opt);
			return 1;
		default:
			fprintf(stderr, "unexpcted option: %c\n", opt);
			abort();
		}
	}

	if(argc != 4) {
		fprintf(stderr, "usage: %s <-s|-u> <input-file> <key>\n" , argv[0]);
		return EXIT_FAILURE;
	}	

	// file is now in argv[2] and key is in argv[3]
	FILE *file;
        file = fopen(argv[2], "r");
	
	if(file == NULL) {
		fprintf(stderr, "The file does not exist.");
	}

	int outputc;
	int keycount = 0;
	size_t keylen = strlen(argv[3]);
	char key[keylen];
	strcpy(key, argv[3]);

	while ((outputc=fgetc(file)) != EOF){
		if((outputc < 97 && outputc > 90) || outputc < 65 || outputc > 122) {
			continue;
		} else if(scramble) {
			fputc((toupper(outputc) - 65 + key[keycount % keylen] - 65) % 26 + 65, stdout);
			keycount++;
		} else{
			fputc((toupper(outputc) - 65 + 26 - key[keycount % keylen] + 65) % 26 + 65, stdout);
			keycount++;
		}
	}
	
	fputc('\n',stdout);
	fclose(file);
	return 0;
};
