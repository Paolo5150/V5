#pragma once
#include <string>
#include <V5/Event/Event.h>
#include <V5/Core/Layer.h>
#include <V5/Scene/Scene.h>

using namespace V5Core;



class ImGuiLayer : public Layer
{
public:
	ImGuiLayer() : m_DebugName("ImGui Layer") {};
	virtual ~ImGuiLayer() = default;

	virtual void OnAttach(Scene* scene) override;
	virtual void OnDetach() override;

	void Begin();
	void End();

	const std::string& GetName() const { return m_DebugName; }
protected:
	std::string m_DebugName;
};