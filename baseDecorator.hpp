#ifndef __BASEDECORATOR_HPP__
#define __BASEDECORATOR_HPP__

#include "base.hpp"

class BaseDecorator : public Base {
    private:
        Base* x;
    public:
        BaseDecorator(Base* src) { this->x = src; }
	
        virtual Base* at(int i) { return x->at(i); }
        virtual bool is_complete() { return x->is_complete(); }
        virtual void toggleComplete() { x->toggleComplete(); }
        virtual void display() { x->display(); }
	virtual void setString(std::string src) { x->setString(src); }
	virtual std::string getString() { return x->getString(); } 
	virtual void save(std::ofstream& out) { x->save(out); }
};

#endif //__BASEDECORATOR_HPP__

