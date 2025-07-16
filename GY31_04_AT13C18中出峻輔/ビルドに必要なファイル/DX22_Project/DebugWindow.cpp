#include "DebugWindow.h"

DebugWindow* DebugWindow::m_instance = nullptr;

Window::Window(std::string name, ImVec2 size, ImVec2 pos)
	: m_name(name), m_size(size), m_pos(pos)
{
}

Window::~Window()
{
}



void DebugWindow::Init(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto io = ImGui::GetIO();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(device, context);
}

void DebugWindow::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void DebugWindow::Update()
{
}

void DebugWindow::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	for (auto& window : m_windows)
	{
		ImGui::SetNextWindowSize(window->GetSize(), ImGuiCond_Once);
		ImGui::SetNextWindowPos(window->GetPos(), ImGuiCond_Once);
		ImGui::Begin(window->GetName().c_str());
		for (const auto& text : *window->GetTexts())
		{
			ImGui::Text("%s", text.c_str());
		}
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

