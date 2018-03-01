
#ifndef CSIM_TICKED_OBJECT_H
#define CSIM_TICKED_OBJECT_H

#include <cstdint>
#include <functional>
#include <limits>
#include <queue>
#include <vector>

struct Event
{
    int64_t tick;
    std::function<void(void)> function;
    Event(int64_t tick, const std::function<void(void)>& function) :
        tick(tick), function(function) { }
};

struct Comp {
    bool operator()(Event *e1, Event *e2) const {
        return e1->tick > e2->tick;
    }
};

class TickedObject
{
  private:

    static int64_t currentTick;

    static std::priority_queue<Event*, std::vector<Event*>, Comp> queue;

  public:
    TickedObject();

    void schedule(int64_t ticks_from_now,
                  const std::function<void(void)>& function);

    static void runSimulation(int64_t ticks =
                                std::numeric_limits<int64_t>::max());

  protected:
    int64_t curTick();
};

#endif // CSIM_TICKED_OBJECT_H
