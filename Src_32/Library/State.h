#ifndef LIBRARY_STATE_H
#define LIBRARY_STATE_H

template <typename Object, typename Event>
class State
{
public:
	State(){};

	virtual ~State(){};
public:
	virtual int GetStateID() = 0;

	virtual void Enter(Object& INobject) = 0;

	virtual void Execute(Object& INobject) = 0;

	virtual void Leave(Object& INobject) = 0;

	virtual int HandlerEvent(Object& INobject, Event& INevent) = 0;
};



#endif