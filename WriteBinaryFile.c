#include <stdio.h>
//converts a text file of hex numbers into a binary form for 1/3 the file size
//input file needs to be manually deleted/done by different script
//IO files req, ex: ./WBin.out forest.htxt forest.bin

int hex_to_int(char * input) {
	if (*input >= '0' && *input <= '9') {return *input - '0';}
	return *input - 'a' + 10;
}

//arg1 = input file , arg2 = output file
int main(int argc, char *argv[]) {
	if (argc < 3) {printf("Err, not input I/O specified !\n"); return 1;}
	FILE *inputfile = fopen(argv[1], "r");
	if (inputfile == NULL) {printf("Err: no input file found.\n"); return 1;}
	FILE *outputfile = fopen (argv[2], "wb");
	if (outputfile == NULL) {printf("Err: unable to create an output file.\n"); return 1;}
	
	int eof_reached = 0;
	do {
		//read the file in sets of 64 bytes (technically 196 but shhh)
		char bytes[64][3] = {{":3"}};
		int bytes_length = 0;
		for (int i=0;i<64;i++) {
			if (fgets(bytes[i], 3, inputfile) == NULL) {
				eof_reached = 1;
				break;
			}
			bytes_length++;
			fgetc(inputfile); //skip delim
		}
		//convert each hex byte to int
		for (int i=0;i<bytes_length;i++) {
			char first[2] = {bytes[i][0]};
			char last[2] = {bytes[i][1]};
			int value = hex_to_int(first)*16 + hex_to_int(last);
			
			fwrite(&value, 1, 1, outputfile);
		}
	}
	while (eof_reached == 0);
	fclose(inputfile);
	fclose(outputfile);
}