#pragma once

struct ansi_color
{
    static constexpr const char* fg_black         = "\033[30m";
    static constexpr const char* fg_red           = "\033[31m";
    static constexpr const char* fg_green         = "\033[32m";
    static constexpr const char* fg_yellow        = "\033[33m";
    static constexpr const char* fg_blue          = "\033[34m";
    static constexpr const char* fg_magenta       = "\033[35m";
    static constexpr const char* fg_cyan          = "\033[36m";
    static constexpr const char* fg_white         = "\033[37m";
    static constexpr const char* fg_gray          = "\033[90m";
    static constexpr const char* fg_brightred     = "\033[91m";
    static constexpr const char* fg_brightgreen   = "\033[92m";
    static constexpr const char* fg_brightyellow  = "\033[93m";
    static constexpr const char* fg_brightblue    = "\033[94m";
    static constexpr const char* fg_brightmagenta = "\033[95m";
    static constexpr const char* fg_brightcyan    = "\033[96m";
    static constexpr const char* fg_brightwhite   = "\033[97m";

    static constexpr const char* bg_black         = "\033[40m";
    static constexpr const char* bg_red           = "\033[41m";
    static constexpr const char* bg_green         = "\033[42m";
    static constexpr const char* bg_yellow        = "\033[43m";
    static constexpr const char* bg_blue          = "\033[44m";
    static constexpr const char* bg_magenta       = "\033[45m";
    static constexpr const char* bg_cyan          = "\033[46m";
    static constexpr const char* bg_white         = "\033[47m";
    static constexpr const char* bg_gray          = "\033[100m";
    static constexpr const char* bg_brightred     = "\033[101m";
    static constexpr const char* bg_brightgreen   = "\033[102m";
    static constexpr const char* bg_brightyellow  = "\033[103m";
    static constexpr const char* bg_brightblue    = "\033[104m";
    static constexpr const char* bg_brightmagenta = "\033[105m";
    static constexpr const char* bg_brightcyan    = "\033[106m";
    static constexpr const char* bg_brightwhite   = "\033[107m";
};