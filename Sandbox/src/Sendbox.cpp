#include <hzpch.h>
#include <Hazel.h>


class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//HZ_CLIENT_INFO("ExampleLayer::Update");

		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB)) {
			//HZ_CLIENT_TRACE("Tab key is pressed(poll)!");
		}

	}

	void OnEvent(Hazel::Event& event) override
	{
		//HZ_CLIENT_TRACE("{0}", event.ToString());
		if (event.GetEventType() == Hazel::EventType::KeyPressed) {
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB) {
				HZ_CLIENT_TRACE("Tab key is pressed(event)!");
			}
			HZ_CLIENT_TRACE("{0}", (char)e.GetKeyCode());

			Hazel::Vector2D vec1(1.0, 2.0);
			Hazel::Vector2D vec2(4.0, 6.0);

			Hazel::Vector2D vecSum = vec1 + vec2;

			HZ_CLIENT_TRACE("X={0}", vecSum.getX());
			HZ_CLIENT_TRACE("y={0}", vecSum.getY());
			double dotProduct = vec1 * vec2;
			double angle = vec1.angleBetween(vec2);
			HZ_CLIENT_TRACE("angle={0}", angle);

			//std::cout << "向量 1: " << vec1 << std::endl;

		/*	HZ_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
			std::cout << "向量 1: " << vec1 << std::endl;
			std::cout << "向量 2: " << vec2 << std::endl;

			Hazel::Vector2D vecSum = vec1 + vec2;
			std::cout << "向量和: " << vecSum << std::endl;

			Hazel::Vector2D vecDiff = vec1 - vec2;
			std::cout << "向量差: " << vecDiff << std::endl;

			double dotProduct = vec1 * vec2;
			std::cout << "点积: " << dotProduct << std::endl;

			double angle = vec1.angleBetween(vec2);
			std::cout << "夹角（弧度）: " << angle << std::endl;*/

		}

	}
};


class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};


Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
