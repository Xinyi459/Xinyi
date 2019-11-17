// Author: Nic Olsen

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <stddef.h>

// Given the CSV filename, parses the file into a 1D array representing a matrix
// in row-major order where each row correponds to a line of the input file and
// each column of that row is an entry in that line. The CSV file should have a
// header line which should be ignored. Each line will have the same number of
// floating point values separated by commas. Each line will be terminated by a
// newline ('\n').
// Returns the 1D array and sets the values pointed to by n_rows and n_cols to
// be the number of data lines (not including the header) and entries per line,
// respectively.
double* ReadCSV(const char* filename, size_t* n_rows, size_t* n_cols);

// Writes a CSV file witht the specified filename. The header should consist of
// the strings found in file_names. The data to write is found in row-major
// order in data. Each of the n_rows lines should contain n_cols entries
// separated by a single comma. Each line should end in a newline ('\n'). Each
// entry should be written with 12 digits after the decimal point.
void WriteCSV(const char* filename,
              const double* data,
              const char** field_names,
              size_t n_rows,
              size_t n_cols);

#endif
