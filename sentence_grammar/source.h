#pragma once
#include "std_lib_facilities.h"

bool noun(vector<string>& string_stream);
bool phrase(vector<string>& string_stream);
bool verb(vector<string>& string_stream);
bool is_conjunction(vector<string>& string_stream);
bool article(vector<string>& string_stream);
bool sentence(vector<string>& string_stream);
void strip_input(string& input);
void pop_front(vector<string>& vec);
bool end_detected(vector<string>& string_stream);
void fill_stream(vector<string>& string_stream);
void read_stream(vector<string>& string_stream);
