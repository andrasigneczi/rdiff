#ifndef __CLOCKINTERFACE_H__
#define __CLOCKINTERFACE_H__

#include <string>
#include <memory>

class ClockInterface;
using ClockInterfaceUPtr = std::unique_ptr<ClockInterface>;

class ClockInterface {
public:
    virtual ~ClockInterface() = default;
    virtual void markTime() = 0;
    virtual void printResult() = 0;
    virtual void reset() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void printDuration() = 0;
    virtual ClockInterfaceUPtr clone() = 0;
    virtual void setTitle(std::string name) = 0;

    static void markTime(ClockInterfaceUPtr& p)      {if(p) p->markTime();}
    static void printResult(ClockInterfaceUPtr& p)   {if(p) p->printResult();}
    static void reset(ClockInterfaceUPtr& p)         {if(p) p->reset();}
    static void start(ClockInterfaceUPtr& p)         {if(p) p->start();}
    static void stop(ClockInterfaceUPtr& p)          {if(p) p->stop();}
    static void printDuration(ClockInterfaceUPtr& p) {if(p) p->printDuration();}
    static void setTitle(ClockInterfaceUPtr& p, std::string name) {if(p) p->setTitle(std::move(name));}
};

#endif // __CLOCKINTERFACE_H__
