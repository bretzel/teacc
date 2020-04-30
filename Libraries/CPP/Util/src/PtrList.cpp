

#include <teacc/Util/PtrList.h>

namespace teacc::Util
{

vptr vptr::z((void *) 0);

vptr::~vptr()
{

}

vptr::vptr(vptr *parent)
{
    _parent = parent;
    _previous = _next = 0;
    __value = 0;
}
void vptr::_detach()
{
    if(_previous)
        _previous->_next = _next;
    if(_next)
        _next->_previous = _previous;
    if(_parent)
        _parent = 0;
}

pvlist::pvlist()
{
    __first = __last = 0;
    __count = 0;
}

pvlist::pvlist(const pvlist &other)
{
    __first = other.__first;
    __last = other.__last;
    __count = other.__count;
}

pvlist::~pvlist()
{
    if(__count)
        clear();
}

pvlist &pvlist::operator<<(void *v)
{
    
    vptr *n = new vptr(v);
    n->_parent = 0;
    n->_next = 0;
    n->_previous = __last; // either 0 or __first or [__last==__first] for previous ptr assign
    if(!__first)
        __first = n;
    if(__last)
        __last->_next = n;
    __last = n;
    
    ++__count;
    return *this;
}

pvlist &pvlist::operator<<(const void *v)
{
    vptr *n = new vptr((void *) v);
    //n->_set_cnt(this);
    n->_parent = 0;
    n->_next = 0;
    n->_previous = __last; // either 0 or __first or [__last==__first] for previous ptr assign
    if(!__first)
        __first = n;
    if(__last)
        __last->_next = n;
    __last = n;
    ++__count;
    return *this;
}

vptr &pvlist::begin()
{
    if(__first)
        return *__first;
    return vptr::z;
}

vptr &pvlist::end()
{
    if(__last)
        return *__last;
    return vptr::z;
}

void pvlist::remove(vptr &n)
{
    if(!__count)
        return;
    vptr *ipt = __first;
    if(n._previous)
        ipt = n._previous->_next;
    else
        __first = __first->_next;
    if(n == *__last)
        __last = __last->_previous;
    
    ipt->_detach();
    --__count;
    
    delete ipt;
    ++n;
}
bool pvlist::remove(void *ptr)
{
    vptr p = this->operator()(ptr);
    if(*p)
    {
        remove(p);
        return true;
    }
    return false;
}

vptr &pvlist::operator()(void *v)
{
    vptr *p = __first;
    if(!p)
        return vptr::z;
    do
    {
        if(p->__value == v)
            return *p;
        p = p->_next;
    }
    while(p);
    return vptr::z;
}

pvlist &pvlist::operator=(const pvlist &other)
{
    __first = other.__first;
    __last = other.__last;
    __count = other.__count;
    return *this;
}

bool pvlist::operator==(const pvlist &other) const
{
    throw " pvlist: un-implemented internal operator `==` ";
}

int pvlist::clear()
{
    vptr *p = __first;
    while(p)
    {
        vptr *np = p->_next;
        delete p;
        p = np;
    }
    __first = __last = 0;
    __count = 0;
    
    return 0;
}

vptr &operator++(vptr &a)
{
    a = a._next ? *a._next : vptr::z;
    return a;
}
vptr &operator++(vptr &a, int)
{
    a = a._next ? *a._next : vptr::z;
    return a;
}
vptr &operator--(vptr &a)
{
    a = a._previous ? *a._previous : vptr::z;
    return a;
    
}
vptr &operator--(vptr &a, int)
{
    a = a._previous ? *a._previous : vptr::z;
    return a;
    
}

}
