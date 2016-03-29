#ifndef NAMESIZE
#define NAMESIZE 20
#endif

#ifndef LINESIZE
#define LINESIZE 256
#endif

#ifndef BLOCK
#define BLOCK 2
#endif

#ifndef RECORD_H
#define RECORD_H



typedef struct {
	char last[NAMESIZE];
	char first[NAMESIZE];
} name;

typedef struct {
	name name;
	int score;               /* between 0 & 100 inclusive */
} record;

typedef struct {
	record **data;    /* points to dynamic array of pointers*/
	size_t nalloc;    /* number of pointers allocated */
	size_t nused;     /* number of pointers used */
					  /* additional mumbers you think nessisary*/
} record_list;

void input(record_list *recordlist) {

	record *prec = malloc(sizeof(record)); /* to store line temporarily */
	int validrec;

	recordlist->nalloc = 0;
	recordlist->nused = 0;


	if (prec == 0) {
		fprintf(stderr, "failed to allocate for prec");
		exit(1);
	}


	while ((validrec = input_record(prec))) { /* as long as we can read a line */
		if (validrec == 1) {


			if (recordlist->nused == recordlist->nalloc) {                /* if we have used up our allocated pointers */
				record ** tmp = realloc(recordlist->data, (recordlist->nalloc + BLOCK) * sizeof(record *));
				fprintf(stderr, "#");
				if (tmp == 0) {
					fprintf(stderr, "failed to add more pointers");
					break;
				}
				recordlist->data = tmp;
				recordlist->nalloc += BLOCK;
			}
			recordlist->data[recordlist->nused] = malloc(sizeof(record));
			fprintf(stderr, "%%");
			if (recordlist->data[recordlist->nused] == 0) {
				fprintf(stderr, "failed to add new record");
				break;
			}

			*(recordlist->data[recordlist->nused++]) = *prec;
		}
	}



}


/*
read in a new record
*/
int input_record(record *prec) {

	char line[LINESIZE];
	char first[LINESIZE];
	char last[LINESIZE];
	char scoreR[LINESIZE];
	int score = -1;
	size_t i;

	if (!fgets(line, LINESIZE, stdin)) {
		return 0;
	}

	if (sscanf(line, "%s %s %s", first, last, scoreR) < 3) {
		return -1;
	}

	if (strlen(first) + 1 > NAMESIZE || strlen(last) + 1 > NAMESIZE) {
		return -1;
	}

	for (i = 0; scoreR[i] != '\0'; i++) {
		if (!isdigit((int)scoreR[i])) {
			return -1;
		}
	}

	if (sscanf(scoreR, "%d", &score) < 1) {
		return -1;
	}
	if (score < 0 || score > 100) {
		return -1;
	}

	for (i = 0; first[i] != '\0'; i++) {
		first[i] = tolower((int)first[i]);
	}

	for (i = 0; last[i] != '\0'; i++) {
		last[i] = tolower((int)last[i]);
	}

	prec->score = score;
	strcpy(prec->name.first, first);
	strcpy(prec->name.last, last);

	return 1;
}



/*
prints a record
*/
void print_record(const record *prec) {
	printf("%s %s %d\n", prec->name.last, prec->name.first, prec->score);
}


#endif
