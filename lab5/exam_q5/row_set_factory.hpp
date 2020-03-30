#ifndef row_set_factory_hpp
#define row_set_factory_hpp

#include "row_set.hpp"

// Create an empty row set for the given field name
RowSet *create_row_set(const string &field);

// Read a row set from the stream, for any field type known to create_row_set
RowSet *read_row_set(istream &src);

// Write a row set to a stream
// A is not const because we need to manipulate its buffer
void write_row_set(RowSet *A, ostream &dst);

#endif
