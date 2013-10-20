#include "text_stream.h"

text_stream::text_stream()
    : m_cursor_pos(0) {
}

void text_stream::set_text(const std::string &a, size_t position) {
    m_text = a;
    m_cursor_pos = position;
}

char text_stream::last_char() {
    if (!is_eof()) {
        return m_text[m_cursor_pos];
    }
    return 0x0;
}

void text_stream::next_char() {
    if (!is_eof()) {
        m_cursor_pos++;
    }
}

void text_stream::go_back() {
    if (m_cursor_pos > 0) {
        m_cursor_pos--;
    }
}

bool text_stream::is_eof() {
    return m_cursor_pos >= m_text.length();
}
