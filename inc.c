#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define MAX_STR 256

// borrowed from tsoding
const char *shift(int *argc, char ***argv)
{
    // assert(*argc > 0);
    const char *result = *argv[0];
    *argc -= 1;
    *argv += 1;
    return result;
}

int main(int argc, char **argv)
{
	shift(&argc, &argv); // shift program name
	const char *times = "1";
	if (argc > 0) {
		times = shift(&argc, &argv);
	}

	int x = atoi(times);
	int a;
	int apx;
	int zero_pad = 0;
	int sgn = 1;

	struct stat stats;
	fstat(fileno(stdin), &stats);
	int stats_mode = stats.st_mode;
	FILE *stream = fdopen(STDIN_FILENO, "r");
	// S_ISSOCK(stats_mode) - piped in from acme
	// S_ISFIFO(stats_mode) - piped in
	if (S_ISFIFO(stats_mode) || S_ISSOCK(stats_mode)) {
		size_t len = MAX_STR;
		char *buf = calloc(len, sizeof(char));
		int ctr = 0;
		while (1) {
			if (ctr >= len) {
				len *= 2;
				buf = realloc(buf, len);
				if (!buf) {
					fprintf(stderr, "[ERROR]: %s\n",errno);
					exit(1);
				}
			} 
			char c = fgetc(stream);
			if (c != EOF) {
				buf[ctr] = c;
				++ctr;
			} else {
				if (buf[0] == '-') {
					sgn = -1;
					buf = buf + 1;
				}
				if (buf[0] == '0') zero_pad = 1;
				a = atoi(buf);
				// free(buf);
				break;
			}
		}
	} else {
		printf("ELSE");
		a = 1;
	}
	// calc apx correctly, but keep it positive
	apx = ((sgn*a)+x)*sgn;
	if (a == 0) {
		printf("%d", x);
	} else if (sgn > 0 && zero_pad && apx < 10) {
		printf("0%d", apx);
	} else if (sgn > 0 && !zero_pad && apx < 10) {
		printf("%d", apx);
	} else if (sgn < 0 && zero_pad && apx < 10) {
		printf("-0%d", apx);
	} else if (sgn < 0 && !zero_pad && apx < 10) {
		printf("-%d", apx);
	} else {
		printf("%d", sgn*apx);
	}
	return fclose(stream);
}
