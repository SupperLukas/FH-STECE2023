#pragma once

#include <map>

enum class EventAction 
{
    Continue,
    Quit,
    GpioEdgeEvent
};

class InputHandler
{
public:
    virtual ~InputHandler() = default;
    [[nodiscard]] virtual EventAction ready(int fd) = 0;
};

class Eventloop
{
public:
    void register_input(int fd, InputHandler*);
    void run();

private:
    std::map<int, InputHandler*> _inputs;    
};
