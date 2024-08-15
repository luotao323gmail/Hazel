#pragma once


#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"
#include <sstream>

namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layuer");
		virtual ~Layer();

		virtual void OnAttach() {}
		
		virtual void OnDetach() {}

		virtual void OnUpdate() {}

		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }


	protected:
		std::string m_DebugName;
	};
}