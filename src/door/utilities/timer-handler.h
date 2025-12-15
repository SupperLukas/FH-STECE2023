#pragma once

#include <sys/timerfd.h>
#include "eventloop.h"
#include <door/inputs.h>
#include <door/outputs.h>
#include <door/door.h>
#include <door/structs.h>

class TimerHandler : public InputHandler
{
public:
    TimerHandler(Inputs* inputs, Outputs* outputs, Door* door); //Add ms parameter
    void hookup(Eventloop&);
    EventAction ready(int fd) override;

private:
    int _timer_fd;
    Inputs* _inputs;
    Outputs* _outputs;
    Door* _door;
    events_t _ev;
    output_t _out;
};
