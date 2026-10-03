#pragma once

#include <imgui.h>
#include <string>

namespace ForceAimBlueDark {

inline void ApplyBlueDarkTheme(ImGuiStyle& style) {
    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.60f;
    style.WindowPadding = ImVec2(12.0f, 10.0f);
    style.WindowRounding = 14.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildRounding = 12.0f;
    style.PopupRounding = 12.0f;
    style.FramePadding = ImVec2(8.0f, 6.0f);
    style.FrameRounding = 8.0f;
    style.ItemSpacing = ImVec2(8.0f, 8.0f);
    style.ItemInnerSpacing = ImVec2(8.0f, 6.0f);
    style.TouchExtraPadding = ImVec2(0.0f, 0.0f);
    style.IndentSpacing = 20.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabMinSize = 12.0f;
    style.GrabRounding = 8.0f;
    style.TabRounding = 10.0f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(0.89f, 0.94f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.56f, 0.62f, 0.72f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.08f, 0.14f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.12f, 0.18f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.10f, 0.17f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.17f, 0.39f, 0.64f, 0.70f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.17f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.20f, 0.30f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.19f, 0.29f, 0.42f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.15f, 0.22f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.10f, 0.15f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.11f, 0.16f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.04f, 0.06f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.17f, 0.38f, 0.60f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.22f, 0.47f, 0.75f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.28f, 0.58f, 0.90f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.82f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.78f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.90f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.12f, 0.18f, 0.30f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.16f, 0.28f, 0.46f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.09f, 0.42f, 0.72f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.11f, 0.19f, 0.31f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.16f, 0.28f, 0.44f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.12f, 0.35f, 0.60f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.50f, 0.75f, 0.60f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.19f, 0.53f, 0.80f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.64f, 0.92f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.18f, 0.39f, 0.68f, 0.60f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.20f, 0.46f, 0.80f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.94f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.13f, 0.20f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.24f, 0.40f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.12f, 0.18f, 0.30f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.09f, 0.12f, 0.18f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.12f, 0.18f, 0.30f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.20f, 0.56f, 0.92f, 0.70f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.05f, 0.08f, 0.14f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.31f, 0.79f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 0.85f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.75f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 0.90f, 1.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.07f, 0.12f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.17f, 0.39f, 0.64f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.12f, 0.18f, 0.26f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.16f, 0.27f, 0.48f, 0.60f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.18f, 0.54f, 0.88f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.19f, 0.52f, 0.84f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.05f, 0.08f, 0.12f, 0.65f);
}

inline void DrawTitleBar(const char* title, const ImVec2& pos, const ImVec2& size) {
    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImU32 bg = IM_COL32(12, 20, 32, 255);
    ImU32 accent = IM_COL32(0, 170, 255, 255);
    ImU32 line = IM_COL32(18, 93, 146, 255);

    draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), bg, 12.0f);
    draw->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), line, 12.0f, 0, 1.0f);
    draw->AddText(ImVec2(pos.x + 18.0f, pos.y + 10.0f), accent, title);
    draw->AddText(ImVec2(pos.x + size.x - 130.0f, pos.y + 10.0f), IM_COL32(135, 200, 255, 255), "BLUE-DARK");
}

inline void RenderLoginWindow(bool* authenticated,
    char username[64],
    char password[64],
    bool* showPassword,
    bool* loginError,
    const char* buttonLabel = "Login") {
    const ImVec2 screen = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2((screen.x - 420.0f) * 0.5f, (screen.y - 300.0f) * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(420.0f, 300.0f));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.04f, 0.07f, 0.11f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.12f, 0.70f, 1.00f, 1.00f));
    ImGui::Begin("FORCE-AIM LOGIN", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar);
    {
        DrawTitleBar("FORCE-AIM", ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowWidth(), 42.0f));

        ImGui::SetCursorPosY(68.0f);
        ImGui::Text("Username");
        ImGui::InputText("##user", username, 64);

        ImGui::Text("Password");
        ImGui::InputText("##pass", password, 64, (*showPassword) ? 0 : ImGuiInputTextFlags_Password);

        ImGui::Checkbox("Show password", showPassword);

        if (ImGui::Button(buttonLabel, ImVec2(-1, 34))) {
            *authenticated = true;
        }

        if (*loginError) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.30f, 0.30f, 1.00f));
            ImGui::Text("Invalid username or password");
            ImGui::PopStyleColor();
        }
    }
    ImGui::End();
    ImGui::PopStyleColor(2);
}

inline void RenderPrimaryMenu(const char* userName, const char* expiryText) {
    const ImVec2 screen = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2((screen.x - 920.0f) * 0.5f, (screen.y - 620.0f) * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(920.0f, 620.0f));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.04f, 0.07f, 0.11f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.14f, 0.76f, 1.00f, 0.80f));
    ImGui::Begin("FORCE-AIM MENU", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar);
    {
        DrawTitleBar("FORCE-AIM", ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowWidth(), 42.0f));

        ImGui::SetCursorPos(ImVec2(18.0f, 58.0f));
        ImGui::BeginChild("##sidebar", ImVec2(170.0f, ImGui::GetWindowHeight() - 88.0f), true);
        {
            ImGui::Text("Aimbot");
            ImGui::Text("Visuals");
            ImGui::Text("ESP");
            ImGui::Text("Misc");
            ImGui::Text("Settings");
        }
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::SetCursorPosY(58.0f);
        ImGui::BeginChild("##content", ImVec2(ImGui::GetWindowWidth() - 214.0f, ImGui::GetWindowHeight() - 88.0f), true);
        {
            ImGui::Text("User: %s", userName);
            ImGui::Text("Expiry: %s", expiryText);
            ImGui::Separator();

            ImGui::Checkbox("Enable Aimbot", (bool*)false);
            ImGui::Checkbox("Predict Movement", (bool*)false);
            ImGui::Checkbox("Silent Aim", (bool*)false);

            ImGui::SliderFloat("FOV", (float*)nullptr, 10.0f, 120.0f, "%.0f");
            ImGui::SliderFloat("Smooth", (float*)nullptr, 1.0f, 20.0f, "%.1f");
            ImGui::SliderFloat("Distance", (float*)nullptr, 50.0f, 500.0f, "%.0f");
        }
        ImGui::EndChild();
    }
    ImGui::End();
    ImGui::PopStyleColor(2);
}

} // namespace ForceAimBlueDark
