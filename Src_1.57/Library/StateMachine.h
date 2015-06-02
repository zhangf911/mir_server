#ifndef LIBRARY_STATEMACHINE_H
#define LIBRARY_STATEMACHINE_H

#include "State.h"

template <typename Object, typename Event>
class StateMachine
{
public:
	StateMachine(Object& INobject)
		: m_object(INobject)
	{
		m_currentState = nullptr;
		m_previousState = nullptr;
	};

	~StateMachine()
	{
		m_currentState = nullptr;
		m_previousState = nullptr;
	};

public:
	State<Object, Event>* GetCurrentState() { return m_currentState; }

	void SetCurrentState(State<Object, Event>* INstate)
	{
		m_currentState = INstate;
	};

	void SetPreviousState(State<Object, Event>* INstate)
	{
		m_previousState = INstate;
	};

	void SetGlobeState(State<Object, Event>* INstate)
	{
		m_globeState = INstate;
	};

	void Change(State<Object, Event>* INstate)
	{
		if(m_currentState)
		{
			m_currentState->Leave(m_object);
		}

		INstate->Enter(m_object);
		m_previousState = m_currentState;
		m_currentState = INstate;
	};

	void Leave()
	{
		if(m_currentState)
		{
			m_currentState->Leave(m_object);

			m_currentState = NULL;
		}
	};

	void Execute()
	{
		if(m_currentState)
		{
			m_currentState->Execute(m_object);
		}

		if(m_globeState)
		{
			m_globeState->Execute(m_object);
		}
	};

	void HandlerEvent(Event& INevent)
	{
		if(m_currentState && m_currentState->HandlerEvent(m_object, INevent) == 0)
		{
			return;
		}

		if(m_globeState && m_globeState->HandlerEvent(m_object, INevent) == 0)
		{
			return;
		}
	};

private:
	Object& m_object;
	State<Object, Event>* m_currentState;
	State<Object, Event>* m_previousState;
	State<Object, Event>* m_globeState;
};


#endif