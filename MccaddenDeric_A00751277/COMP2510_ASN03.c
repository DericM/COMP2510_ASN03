/*
* COMP2510_ASN03.c
*
*    Created on: Feb 02, 2016
*        Author: Mccadden, Deric
* StudentNumber: A00751277
*/

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "sort.h"
#include "record.h"


#define NAMESIZE 20
#define LINESIZE 256







int input_record(record *prec);
int validate_arg(char arg[]);

void print_record(const record *prec);
void validate_argv2(char arg1[], char arg2[]);
void input(record_list *recordlist);


int main(int argc, char *argv[])
{

	char opt1[LINESIZE];
	char opt2[LINESIZE];
	size_t i;

	record_list *recordlist = malloc(sizeof(record_list));
	fprintf(stderr, "#");
	if (recordlist == 0) {
		fprintf(stderr, "failed to allocate for recordlist");
		exit(1);
	}

	if (argc == 3) {
		strcpy(opt1, argv[1]);
		strcpy(opt2, argv[2]);
	}
	else if (argc == 2) {
		strcpy(opt1, argv[1]);
		opt2[0] = opt2[1] = ' ';
	}
	else if (argc == 1) {
		opt1[0] = opt1[1] = opt2[0] = opt2[1] = ' ';
	}
	else {
		perror("usage: {FILE.c} {OPT1} {OPT2} \n");
		exit(1);
	}

	validate_argv2(opt1, opt2);
	input(recordlist);
	sort_record(opt1, opt2, recordlist); 

	for (i = 0; i < recordlist->nused; i++) {
		print_record(recordlist->data[i]);
	}

	for (i = 0; i < recordlist->nused; i++) {
		free(recordlist->data[i]);
		fprintf(stderr, "%%");
	}
	free(recordlist->data);

	getchar();
	return 0;
}



void validate_argv2(char arg1[], char arg2[]) {

	if (!validate_arg(arg1) || !validate_arg(arg2)) {
		perror("Invalid arguments");
		exit(1);
	}
	if (arg1[1] == arg2[1] && arg1[1] != ' ' && arg2[1] != ' ') {
		perror("Repeated arguments");
		exit(1);
	}
}


int validate_arg(char arg[]) {
	if (strlen(arg) > 2) {
		return 1;
	}
	if (arg[0] != '-' || arg[0] != '+' || arg[0] != ' ') {
		return 1;
	}
	if (arg[1] != 'n' || arg[1] != 's' || arg[1] != ' ') {
		return 1;
	}
	return 0;
}



