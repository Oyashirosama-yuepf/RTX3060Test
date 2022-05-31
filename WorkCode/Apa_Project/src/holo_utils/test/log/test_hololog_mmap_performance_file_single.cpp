#include <holo/log/hololog.h>
#include <holo/log/log4cplus/buffer/block.h>
#include <holo/log/log4cplus/buffer/buffer.h>
#include <holo/log/log4cplus/ostream.h>
#include <sys/time.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

using namespace holo;
using namespace log;
namespace log4 = ::holo::log::log4cplus;

static constexpr int g_num = 100 * 10000;

std::mutex                    g_buffer_mutex;
std::shared_ptr<log4::Buffer> g_buffer{nullptr};
std::string                   g_file;

static constexpr holo::uint32_t MAX_STREAM_BUFFER_SIZE = 20 * 1024;

thread_local holo::char_t  g_ostream_buffer[MAX_STREAM_BUFFER_SIZE]{};
thread_local log4::OStream tls_ostream{g_ostream_buffer, MAX_STREAM_BUFFER_SIZE};

std::shared_ptr<log4::Buffer> createBuffer(std::string const& file)
{
    std::unique_lock<std::mutex> looker(g_buffer_mutex);
    if (g_buffer == nullptr || g_buffer->IsBackup())
    {
        g_buffer = log4::Buffer::Create(file, 10 * 1024 * 1024, log4::BackupStrategy::INDEX);
    }
    return g_buffer;
}

void appendTime(std::ostream& output)
{
    struct timeval tv;
    struct ::tm    tm_time;

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_time);

    output << std::setw(4) << 1900 + tm_time.tm_year << std::setw(2) << 1 + tm_time.tm_mon << std::setw(2)
           << tm_time.tm_mday << ' ' << std::setw(2) << tm_time.tm_hour << ':' << std::setw(2) << tm_time.tm_min << ':'
           << std::setw(2) << tm_time.tm_sec << '.' << std::setw(6) << tv.tv_usec << ' ';
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (argc < 2)
    {
        std::cout << "input filename" << std::endl;
        return 0;
    }

    std::cout << "start test:" << std::endl;

    g_file                               = argv[1];
    std::shared_ptr<log4::Buffer> buffer = createBuffer(g_file);

    std::chrono::milliseconds start_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    for (uint32_t i = 0; i < g_num; i++)
    {
        appendTime(tls_ostream);
        tls_ostream << "main.cpp 69 INFO ";
        tls_ostream << "test log performance.  " << i << '\n';
        tls_ostream.Trunc();

        log4::Block block = buffer->RequestBlock(tls_ostream.Count());
        if (0 == block.Write(g_ostream_buffer, tls_ostream.Count()))
        {
            buffer->Backup();
            buffer            = createBuffer(g_file);
            log4::Block block = buffer->RequestBlock(tls_ostream.Count());
            if (0 == block.Write(g_ostream_buffer, tls_ostream.Count()))
            {
                std::cout << "create buffer error!" << std::endl;
            }
        }
        tls_ostream.Reset();
    }

    std::chrono::milliseconds end_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    std::cout << "start:" << start_ms.count() << std::endl;
    std::cout << "end:" << end_ms.count() << std::endl;
    std::cout << "end - start:" << end_ms.count() - start_ms.count() << std::endl;

    std::cout << std::endl << "end test" << std::endl;

    return 0;
}
