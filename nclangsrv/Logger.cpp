#include "stdafx.h"

#include "Logger.h"

#include <ctime>
#include <iomanip>

namespace nclangsrv {

Logger::Logger(const std::string& path)
    : ostr(path.c_str(), std::ios::app)
{
}

std::ofstream& Logger::operator()()
{
    tm     buf;
    time_t now = std::time(nullptr);
    localtime_s(&buf , &now);
    ostr << "[" << std::put_time(&buf, "%F %T") << "] ";

    return ostr;
}

void Logger::flush()
{
    ostr.flush();
}

void Logger::close()
{
    ostr.close();
}

} // namespace nclangsrv