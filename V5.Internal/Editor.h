#pragma once
#include <V5/Application/Application.h>
#include <V5/Event/Event.h>


class Editor : public V5Core::Application
{
public:
	Editor() : Application("V5Editor") {};
	void OnStart() override;
	~Editor() {};
};