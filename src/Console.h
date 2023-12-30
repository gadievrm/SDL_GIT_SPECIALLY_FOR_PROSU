#pragma once
#include <list>
#include <string>
#include "GameSystems.h"

enum class ELog {
    Info,
    Debug,
    Warn,
    Error
};

struct TLogMessage {
    ELog type;
    std::string content;
};

class CConsole {
private:
    int m_n;
    std::list<TLogMessage> m_msgs;
    bool m_open;
    bool m_scroll_to_last;

    void addMessage(const TLogMessage& msg);
public:
    CConsole();
    void update(TGameSystems systems);
    void draw();
    void clear();
    void info(const std::string& what);
    void debug(const std::string& what);
    void warn(const std::string& what);
    void error(const std::string& what);
};

extern CConsole gConsole;