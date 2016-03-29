
#ifndef SORT_H
#define SORT_H

#include "record.h"
#include <string.h>
#include <stdlib.h>


int cmp_N(const void *p, const void *q) {
	record *rec1 = *(record * const *)p;
	record *rec2 = *(record * const *)q;

	int i = strcmp(rec1->name.last, rec2->name.last);
	if (i == 0) {
		return strcmp(rec1->name.first, rec2->name.first);
	}
	return i;
}

int cmp_S(const void *p, const void *q) {
	record *rec1 = *(record * const *)p;
	record *rec2 = *(record * const *)q;
	return rec1->score - rec2->score;
}


int name_asc(const void *p, const void *q) {
	return cmp_N(p, q);
}

int name_desc(const void *p, const void *q) {
	return cmp_N(q, p);
}

int score_asc(const void *p, const void *q) {
	return cmp_S(p, q);
}

int score_desc(const void *p, const void *q) {
	return cmp_S(q, p);
}

int name_asc_score_asc(const void *p, const void *q) {
	int i = name_asc(p, q);
	if (i == 0)
		return score_asc(p, q);
	return i;
}

int name_asc_score_desc(const void *p, const void *q) {
	int i = name_asc(p, q);
	if (i == 0)
		return score_desc(p, q);
	return i;
}

int name_desc_score_asc(const void *p, const void *q) {
	int i = name_desc(p, q);
	if (i == 0)
		return score_asc(p, q);
	return i;
}

int name_desc_score_desc(const void *p, const void *q) {
	int i = name_desc(p, q);
	if (i == 0)
		return score_desc(p, q);
	return i;
}

int score_asc_name_asc(const void *p, const void *q) {
	int i = score_asc(p, q);
	if (i == 0)
		return name_asc(p, q);
	return i;
}

int score_asc_name_desc(const void *p, const void *q) {
	int i = score_asc(p, q);
	if (i == 0)
		return name_desc(p, q);
	return i;
}

int score_desc_name_asc(const void *p, const void *q) {
	int i = score_desc(p, q);
	if (i == 0)
		return name_asc(p, q);
	return i;
}

int score_desc_name_desc(const void *p, const void *q) {
	int i = score_desc(p, q);
	if (i == 0)
		return name_desc(p, q);
	return i;
}


void sort_record(const char opt1[], const char opt2[], record_list *recordlist) {
	if		  (opt1[0] == ' '
			&& opt1[1] == ' '
			&& opt2[0] == ' '
			&& opt2[1] == ' ') {
		; /* do not sort */
	}
	else if   (opt1[0] == '+'
			&& opt1[1] == 'n'
			&& opt2[0] == ' '
			&& opt2[1] == ' ') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), name_asc);
	}
	else if   (opt1[0] == '-'
			&& opt1[1] == 'n'
			&& opt2[0] == ' '
			&& opt2[1] == ' ') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), name_desc);
	}
	else if   (opt1[0] == '+'
			&& opt1[1] == 's'
			&& opt2[0] == ' '
			&& opt2[1] == ' ') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), score_asc);
	}
	else if   (opt1[0] == '-'
			&& opt1[1] == 's'
			&& opt2[0] == ' '
			&& opt2[1] == ' ') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), score_desc);
	}
	else if   (opt1[0] == '+'
			&& opt1[1] == 'n'
			&& opt2[0] == '+'
			&& opt2[1] == 's') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), name_asc_score_asc);
	}
	else if   (opt1[0] == '+'
			&& opt1[1] == 'n'
			&& opt2[0] == '-'
			&& opt2[1] == 's') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), name_asc_score_desc);
	}
	else if	  (opt1[0] == '-'
			&& opt1[1] == 'n'
			&& opt2[0] == '+'
			&& opt2[1] == 's') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), name_desc_score_asc);
	}
	else if   (opt1[0] == '-'
			&& opt1[1] == 'n'
			&& opt2[0] == '-'
			&& opt2[1] == 's') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), name_desc_score_desc);
	}
	else if   (opt1[0] == '+'
			&& opt1[1] == 's'
			&& opt2[0] == '+'
			&& opt2[1] == 'n') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), score_asc_name_asc);
	}
	else if   (opt1[0] == '+'
			&& opt1[1] == 's'
			&& opt2[0] == '-'
			&& opt2[1] == 'n') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), score_asc_name_desc);
	}
	else if   (opt1[0] == '-'
			&& opt1[1] == 's'
			&& opt2[0] == '+'
			&& opt2[1] == 'n') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), score_desc_name_asc);
	}
	else if   (opt1[0] == '-'
			&& opt1[1] == 's'
			&& opt2[0] == '-'
			&& opt2[1] == 'n') {
		qsort(recordlist->data, recordlist->nused, sizeof(record*), score_desc_name_desc);
	}
	else {
		perror("Something terrible has happened");
		exit(1);
	}
}

#endif