#ifndef TEXT_STREAM_H
#define TEXT_STREAM_H
#include <string>
#include <vector>

class text_stream {
private:
    std::string m_text;
    size_t m_cursor_pos;

public:
    text_stream();
    void set_text(const std::string &a, size_t position = 0);
    char last_char();
    void next_char();
    void go_back();
    bool is_eof();
};

#endif // TEXT_STREAM_H
