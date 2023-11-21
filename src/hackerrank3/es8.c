#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();
char *ltrim(char *);
char *rtrim(char *);

int parse_int(char *);

bool int_in_arr(const int integer, const int* arr, const size_t arr_size) {
  for (size_t i = 0; i < arr_size; i++) {
    if (integer == arr[i]) {
      return true;
    }
  }

  return false;
}

/*
 * Complete the 'count_equal' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER POINTER v1
 *  2. INTEGER POINTER v2
 *  3. INTEGER v_size
 */
unsigned count_equal(int *v1, int *v2, int v_size) {
  int count = 0;
  for(int i = 0; i < v_size; i++){
    if (int_in_arr(v1[i], v2, v_size)) {
      count++;
    }
  }

  return count;
}

int main() {
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  int v_size = parse_int(ltrim(rtrim(readline())));

  int *v1 = malloc(v_size * sizeof(int));

  int *v2 = malloc(v_size * sizeof(int));

  for (size_t i = 0; i < v_size; i++) {
    v1[i] = parse_int(ltrim(rtrim(readline())));
  }

  for (size_t i = 0; i < v_size; i++) {
    v2[i] = parse_int(ltrim(rtrim(readline())));
  }

  int result = count_equal(v1, v2, v_size);

  fprintf(fptr, "%u\n", result);

  fclose(fptr);

  return 0;
}

char *readline() {
  size_t alloc_length = 1024;
  size_t data_length = 0;

  char *data = malloc(alloc_length);

  while (true) {
    char *cursor = data + data_length;
    char *line = fgets(cursor, alloc_length - data_length, stdin);

    if (!line) {
      break;
    }

    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
      break;
    }

    alloc_length <<= 1;

    data = realloc(data, alloc_length);

    if (!data) {
      data = '\0';

      break;
    }
  }

  if (data[data_length - 1] == '\n') {
    data[data_length - 1] = '\0';

    data = realloc(data, data_length);

    if (!data) {
      data = '\0';
    }
  } else {
    data = realloc(data, data_length + 1);

    if (!data) {
      data = '\0';
    } else {
      data[data_length] = '\0';
    }
  }

  return data;
}

char *ltrim(char *str) {
  if (!str) {
    return '\0';
  }

  if (!*str) {
    return str;
  }

  while (*str != '\0' && isspace(*str)) {
    str++;
  }

  return str;
}

char *rtrim(char *str) {
  if (!str) {
    return '\0';
  }

  if (!*str) {
    return str;
  }

  char *end = str + strlen(str) - 1;

  while (end >= str && isspace(*end)) {
    end--;
  }

  *(end + 1) = '\0';

  return str;
}

int parse_int(char *str) {
  char *endptr;
  int value = strtol(str, &endptr, 10);

  if (endptr == str || *endptr != '\0') {
    exit(EXIT_FAILURE);
  }

  return value;
}
