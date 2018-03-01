
#include <cassert>
#include <iostream>

#include "ticked_object.hh"
#include "util.hh"

TickedObject::TickedObject()
{

}

void
TickedObject::schedule(int64_t ticks_from_now,
                       const std::function<void(void)>& function)
{
    // NOTE: Not using a *new* event here causes all sorts of issues...
    queue.push(new Event(currentTick+ticks_from_now, function));
}

void
TickedObject::runSimulation(int64_t ticks)
{
    while(currentTick < ticks && !queue.empty()) {
        assert(currentTick >= 0);
        Event* e = queue.top();
        queue.pop();
        currentTick = e->tick;
        e->function();
        delete e;
    }
    std::cout << "Finished! ";
    std::cout << "Execution took " << currentTick << " ticks." << std::endl;
}

int64_t
TickedObject::curTick()
{
    return currentTick;
}

int64_t TickedObject::currentTick(0);

std::priority_queue<Event*, std::vector<Event*>, Comp> TickedObject::queue;
