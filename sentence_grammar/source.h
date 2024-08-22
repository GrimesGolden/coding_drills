#pragma once
#include "std_lib_facilities.h"

bool noun(string& word);
bool phrase(string& l_str, string& r_string);
bool verb(string& input);
bool conjunction(string& input);
bool article(string& input);
bool sentence(vector<string>& string_stream);
void strip_input(string& input);

//New
bool end_detected(string& word);
void fill_stream(vector<string>& string_stream);
void read_stream(vector<string>& string_stream);
