#include "timer-handler.h"

#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdexcept>
#include <format>
#include <stdint.h>

TimerHandler::TimerHandler(Inputs* inputs, Outputs* outputs, Door* door) {
    _inputs = inputs;
    _outputs = outputs;
    _door = door;
    _timer_fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
    if (_timer_fd == -1) {
        perror("timerfd_create");
        throw std::runtime_error("timerfd_create failed");
    }
    itimerspec spec{
        .it_interval = {0, 1000000},   // periodic: every 1ms
        .it_value    = {1, 0},   // first expiration 1 second after start
    };

    if (timerfd_settime(_timer_fd, 0, &spec, nullptr) == -1) {
        perror("timerfd_settime");
        throw std::runtime_error("timerfd_settime failed");
    }
}

void TimerHandler::hookup(Eventloop& loop)
{
    loop.register_input(_timer_fd, this);
}

EventAction TimerHandler::ready(int fd)
{
    if (fd == _timer_fd) {
        uint64_t expirations;
        ssize_t n = read(_timer_fd, &expirations, sizeof(expirations));

        if (n != sizeof(expirations)) {
            return EventAction::Continue;  
        }

        events_t ev  = _inputs->get_events();
        output_t out = _door->cyclic(ev);

        _outputs->set_outputs(out);

        return EventAction::Continue;
    }

    return EventAction::Continue;
}

