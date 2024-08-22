#pragma once
#include "std_lib_facilities.h"

bool phrase(vector<string>& string_stream);
bool sentence(vector<string>& string_stream);
void strip_input(string& input);
void pop_front(vector<string>& vec);
bool end_detected(vector<string>& string_stream);
void fill_stream(vector<string>& string_stream);
void read_stream(vector<string>& string_stream);

bool check_grammar(vector<string>& string_stream, vector<string>& valid_strings);
