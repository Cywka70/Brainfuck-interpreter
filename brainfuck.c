#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char stack[30000];
int indexx = 0;
char * plus = "+";
char * minus = "-";
char * next = ">";
char * back = "<";
char * prt = ".";
char * inp = ",";
char * lp = "[";
char * llp = "]";
int rc = 0;
char * endl = "\n";
char * ex = "@";
int main(int argc, char **argv)
{
	memset(stack, 0, 30000);
	if (argc < 2) {
		printf("Startimg BrainFuck Shell...\n");
		char command[4096];
		int i = 1;
		do {
			printf("BF> ");
			gets(command);
			for (int x = 0; x < sizeof(command); x++) {
				if (command[x] == *plus) {
					stack[indexx]++;
				} else if (command[x] == *minus) {
					stack[indexx]--;
				} else if (command[x] == *next) {
					indexx++;
				} else if (command[x] == *back) {
					indexx--;
				} else if (command[x] == *prt) {
					putchar(stack[indexx]);
				} else if (command[x] == *inp) {
					char t[2];
					gets(t);
					stack[indexx] = (int)t[0];
				}else if (command[x] == *endl) {
					i = 1;
				} else if (command[x] == *ex) {
					i = 0;
				} else if (command[x] == *lp) {
					if (!stack[indexx]) {
						rc++;
						while (rc) {
							i++;
							if (command[x] == *lp) {
								rc++;
							}
							if (command[x] == *llp) {
								rc--;
							}
						}
					} else continue;
				} else if (command[x] == *llp) {
					if (!stack[indexx]) {
						continue;
					} else {
						if (command[x] == *llp) {
							rc++;
							while (rc) {
								x--;
								if (command[x] == *lp) {
									rc--;
								}
								if(command[x] == *llp) {
									rc++;
								}
							}
							x--;
						}
					}
				} else {
					continue;
				}
			}
		} while (i);
		return 0;
	}
	FILE * file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Cann't open file %s!\n", argv[1]);
		exit(1);
	}
	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	char buf[size];
	fread(buf, sizeof(buf), 1, file);
	for (int i = 0; i < sizeof(buf); i++) {
		if (buf[i] == *plus){
			stack[indexx]++;
		} else if (buf[i] == *minus) {
			stack[indexx]--;
		} else if (buf[i] == *next) {
			indexx++;
		} else if (buf[i] == *back) {
			indexx--;
		} else if (buf[i] == *prt) {
			putchar(stack[indexx]);
		} else if (buf[i] == *inp) {
			char c;
			scanf("%c", &c);
			stack[indexx] = (int)c;
		} else if (buf[i] == *lp) {
			if (!stack[indexx]) {
				rc++;
				while (rc) {
					i++;
					if (buf[i] == *lp) {
						rc++;
					}
					if (buf[i] == *llp) {
						rc--;
					} 
				}
			} else continue;
		} else if (buf[i] == *llp) {
			if(!stack[indexx]) {
				continue;
			} else {
				if (buf[i] == *llp) {
					rc++;
					while (rc) {
						i--;
						if (buf[i] == *lp) {
							rc--;
						}
						if (buf[i] == *llp) {
							rc++;
						}
					}
					i--;
				}
			}
		} else if (buf[i] == *ex) {
			return 0;
		}
	}
	return 0;
}