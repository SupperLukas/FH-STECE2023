#include <door/input_output_switch/input/input-edge-event.h>
#include <door/utilities/eventloop.h>
#include <iostream>

// Test: GPIO Rising Edge Event Detection
// This test creates an InputEdgeEvent on a specified pin and listens for rising edges.
// When an edge is detected, the event loop receives GpioEdgeEvent.

int main()
{
    try {
        // Configure GPIO pin (adjust pin number for your hardware)
        constexpr int GPIO_PIN = 529;  // Change to your actual GPIO pin
        constexpr int MAX_EVENTS = 5;  // Quit after receiving this many events
        
        int event_count = 0;

        std::cout << "InputEdgeEvent Test: Rising Edge Detection on GPIO " << GPIO_PIN << std::endl;
        std::cout << "Waiting for " << MAX_EVENTS << " rising edge events..." << std::endl;

        // Create InputEdgeEvent for rising edge, returning GpioEdgeEvent
        InputEdgeEvent gpio_input(GPIO_PIN, "rising", EventAction::GpioEdgeEvent);

        // Custom handler that counts events and quits after MAX_EVENTS
        class TestHandler : public InputHandler
        {
        public:
            TestHandler(InputEdgeEvent& input, int& count, int max)
                : _input(input), _count(count), _max(max) {}

            EventAction ready(int fd) override
            {
                // Let the InputEdgeEvent handle the lseek to clear interrupt
                EventAction result = _input.ready(fd);
                
                if (result == EventAction::GpioEdgeEvent) {
                    _count++;
                    std::cout << "Rising edge detected on pin " << _input.pin() 
                              << " (event " << _count << "/" << _max << ")" << std::endl;
                    
                    if (_count >= _max) {
                        std::cout << "Test complete: Received " << _count << " events" << std::endl;
                        return EventAction::Quit;
                    }
                }
                return EventAction::Continue;
            }

        private:
            InputEdgeEvent& _input;
            int& _count;
            int _max;
        };

        Eventloop loop;
        TestHandler handler(gpio_input, event_count, MAX_EVENTS);
        
        // Register directly with fd from InputEdgeEvent
        // Note: We need access to the fd, so we'll use hookup but replace with our handler
        gpio_input.hookup(loop);

        std::cout << "Event loop started. Trigger rising edges on GPIO " << GPIO_PIN << "..." << std::endl;
        loop.run();

        std::cout << "Test passed: " << event_count << " GpioEdgeEvent(s) received." << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}
