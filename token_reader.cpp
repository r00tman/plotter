#include "token_reader.h"

void token_reader::init_white_symbols() {
    m_white_symbols.clear();
    m_white_symbols.insert(' ');
    m_white_symbols.insert('\n');
}

token_reader::token_reader(text_stream s) {
    m_stream = s;
}

std::string token_reader::get_last_token() {
    return m_last_token;
}

token_reader::e_token_type token_reader::get_last_token_type() {
    return m_last_token_type;
}

void token_reader::next_token() {
    m_last_token.clear();

    while (m_white_symbols.find(m_stream.last_char()) != m_white_symbols.end()) {
        m_stream.next_char();
    }

    if (m_stream.last_char() >= '0' && m_stream.last_char() <= '9') {
        while (m_stream.last_char() >= '0' && m_stream.last_char() <= '9') {
            m_last_token.push_back(m_stream.last_char());
            m_stream.next_char();
        }
        if (m_stream.last_char() == '.') {
            m_last_token.push_back(m_stream.last_char());
            m_stream.next_char();
        }
        while (m_stream.last_char() >= '0' && m_stream.last_char() <= '9') {
            m_last_token.push_back(m_stream.last_char());
            m_stream.next_char();
        }
        if (m_stream.last_char() == 'e') {
            m_last_token.push_back(m_stream.last_char());
            m_stream.next_char();
            if (m_stream.last_char() == '-' || m_stream.last_char() == '+') {
                m_last_token.push_back(m_stream.last_char());
                m_stream.next_char();
            }
            while (m_stream.last_char() >= '0' && m_stream.last_char() <= '9') {
                m_last_token.push_back(m_stream.last_char());
                m_stream.next_char();
            }
        }
        m_last_token_type = tt_number;
        return;
    }

    if (m_stream.last_char() >= 'a' && m_stream.last_char() <= 'z') {
        m_last_token.push_back(m_stream.last_char());
        m_stream.next_char();
        m_last_token_type = tt_variable;
        return;
    }

    m_last_token_type = tt_operator;
    m_last_token.push_back(m_stream.last_char());
    m_stream.next_char();
}
