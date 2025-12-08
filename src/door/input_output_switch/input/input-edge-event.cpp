#include "input-edge-event.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdexcept>
#include <sstream>
#include <cerrno>

// Helper: writes string to path, handles basic errors
static void sysfs_write(const std::string& path, const std::string& val )
{
    int fd = open(path.c_str(), O_WRONLY);
    if (fd == -1) {
       //todo
    }
    ssize_t n = write(fd, val.c_str(), val.length());
    close(fd);
    
    if (n == -1) {
      //todo
    }
}

InputEdgeEvent::InputEdgeEvent(int pin, const std::string& edge, const EventAction event)
: _pin(pin), _fd(-1), _event(event)
{
    // 1. Export Pin
    sysfs_write("/sys/class/gpio/export", std::to_string(pin));

    std::ostringstream oss;
    oss << "/sys/class/gpio/gpio" << pin;
    std::string base = oss.str();
    
    // 2. Set Direction Input
    sysfs_write(base + "/direction", "in");

    // 3. Set Edge Trigger
    sysfs_write(base + "/edge", edge);

    // 4. Open Value (store fd for the event loop)
    _fd = open((base + "/value").c_str(), O_RDONLY | O_NONBLOCK);
    if (_fd == -1) {
        std::ostringstream oss;
        oss << "open gpio value failed: " << strerror(errno);
        throw std::runtime_error(oss.str());
    }
}

InputEdgeEvent::~InputEdgeEvent()
{
    if (_fd != -1) close(_fd);
    //Todo ? unexport pin ?
}

void InputEdgeEvent::hookup(Eventloop& loop)
{
    loop.register_input(_fd, this);
}

EventAction InputEdgeEvent::ready(int fd)
{
    // REQUIRED: Seek to start to clear interrupt flag in sysfs
    lseek(fd, 0, SEEK_SET);
    return _event;
}