#include "easy_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

int		e_resize(t_easy_string *this, const int new_size, ...) {
	va_list	ap;
	char   	c = 0;
	
	va_start(ap, new_size);
	c = va_arg(ap, int);
	printf("char = [%c]\n", c);
	if (new_size > this->allocated_memory) {
		if ((this->string = realloc(this->string, new_size + 1)) == NULL) {
			fprintf(stderr, ERROR_MALLOC_FAILED, strerror(errno));
			exit(-1);
		}
		if (c) {
			int i = 0;
			for (i = this->len; i < new_size; i++) {
				this->string[i] = c;
			}
			this->string[i] = '\0';
			this->len = strlen(this->string);
		}
	} else if (new_size < this->allocated_memory) {
		if ((this->string = realloc(this->string, (new_size + 1) * sizeof(char))) == NULL) {
			fprintf(stderr, ERROR_MALLOC_FAILED, strerror(errno));
			exit(-1);
		}
		this->string[new_size] = '\0';
		this->len = strlen(this->string);
	}
	va_end(ap);
	return	this->allocated_memory = new_size * sizeof(char);
}

int		e_len(t_easy_string *this) {
	return this->len;
}

int		e_reserve(t_easy_string *this, const int new_size) {
	if ((this->string = realloc(this->string, new_size + 1)) == NULL) {
		fprintf(stderr, ERROR_MALLOC_FAILED, strerror(errno));
		exit(-1);
	}
	this->allocated_memory = new_size;
	return new_size;
}

int		e_clear(t_easy_string *this) {
	memset(this->string, 0, this->len * sizeof(char));
	this->len = 0;
	return 0;
}

int		e_empty(t_easy_string *this) {
	if (this->len == 0 || this->string == NULL) {
		return 1;
	}
	return 0;
}

int		e_shrink_to_fit(t_easy_string *this) {
	if ((this->string = realloc(this->string, this->len + 1)) == NULL) {
		fprintf(stderr, ERROR_MALLOC_FAILED, strerror(errno));
		exit(-1);
	}
	return this->allocated_memory = this->len;
}

int		e_string_init(t_easy_string *this, char *str) {
	this->len = strlen(str);
	this->e_len = &e_len;
	this->e_resize = &e_resize;
	this->e_reserve = &e_reserve;
	this->e_clear = &e_clear;
	this->e_empty = &e_empty;
	this->e_shrink_to_fit = &e_shrink_to_fit;
	if ((this->string = malloc((this->len + 1) * sizeof(char))) == NULL) {
		fprintf(stderr, ERROR_MALLOC_FAILED, strerror(errno));
		exit(-1);
	}
	memset(this->string, 0, this->len);
	this->string = strcpy(this->string, str);
	this->allocated_memory = this->len * sizeof(char);
	return 0;
}

int		e_string_destroy(t_easy_string *this) {
	free(this->string);
	return 0;
}

int main() {
	t_easy_string str;

	e_string_init(&str, "COUCOU c'est mo");
	printf("string = %s\n", str.string);
	printf("string len = %d\n", str.e_len(&str));
	printf("alocated memory = %d\n", str.allocated_memory);
	
	printf("allocated memory after resize 1 = %d\n", str.e_resize(&str, str.e_len(&str) + 1, 'i'));
	printf("string after resize 1 = %s\n", str.string);
	str.e_resize(&str, str.e_len(&str) - 7);
	printf("%s\n", str.string);
	str.e_clear(&str);
	printf("[%s]\n", str.string);
	e_string_destroy(&str);
	return 0;
}
