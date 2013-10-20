#ifndef TOKEN_READER_H
#define TOKEN_READER_H

#include <string>
#include <set>
#include "text_stream.h"

class token_reader {
public:
    enum e_token_type {tt_number, tt_variable, tt_operator};

private:
    text_stream m_stream;
    std::string m_last_token;
    e_token_type m_last_token_type;
    std::set<char> m_white_symbols;

    void init_white_symbols();

public:

    token_reader(text_stream s);

    std::string get_last_token();
    e_token_type get_last_token_type();
    void next_token();

    bool is_eof();
};

#endif // TOKEN_READER_H
