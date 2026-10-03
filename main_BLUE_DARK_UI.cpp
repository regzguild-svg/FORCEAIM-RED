// ============================================================================
// FORCE-AIM-BLUE-DARK UI Theme - Complete Redesign
// ============================================================================
// Replace the color definitions and UI rendering sections with this version
// ============================================================================

#define IMGUI_DEFINE_MATH_OPERATORS
#include "main.h"

// ════════════════════════════════════════════════════════════════════════════
// COLOR PALETTE - BLUE-DARK THEME
// ════════════════════════════════════════════════════════════════════════════
namespace ColorTheme {
    // Primary Colors
    const ImVec4 PRIMARY_DARK = ImVec4(0.08f, 0.13f, 0.24f, 1.0f);      // #141E3D
    const ImVec4 SECONDARY_DARK = ImVec4(0.10f, 0.15f, 0.28f, 1.0f);    // #1A2847
    const ImVec4 TERTIARY_DARK = ImVec4(0.06f, 0.09f, 0.16f, 1.0f);     // #0F1729
    
    // Accent - Neon Blue/Cyan
    const ImVec4 ACCENT_BRIGHT = ImVec4(0.0f, 0.81f, 1.0f, 1.0f);       // #00CFFF (Neon Cyan)
    const ImVec4 ACCENT_MEDIUM = ImVec4(0.0f, 0.62f, 0.85f, 1.0f);      // #009ED8 (Medium Blue)
    const ImVec4 ACCENT_DARK = ImVec4(0.0f, 0.42f, 0.65f, 1.0f);        // #006BA8 (Dark Blue)
    
    // Text Colors
    const ImVec4 TEXT_PRIMARY = ImVec4(0.95f, 0.98f, 1.0f, 1.0f);        // #F2FAFE (Off-white)
    const ImVec4 TEXT_SECONDARY = ImVec4(0.70f, 0.75f, 0.85f, 1.0f);    // #B2BFDD (Muted)
    const ImVec4 TEXT_MUTED = ImVec4(0.50f, 0.55f, 0.65f, 1.0f);        // #808D95 (Dark muted)
    
    // Status Colors
    const ImVec4 STATUS_ACTIVE = ImVec4(0.0f, 0.85f, 0.4f, 1.0f);       // #00D966 (Green)
    const ImVec4 STATUS_WARNING = ImVec4(1.0f, 0.80f, 0.0f, 1.0f);      // #FFCC00 (Yellow)
    const ImVec4 STATUS_EXPIRED = ImVec4(1.0f, 0.40f, 0.40f, 1.0f);     // #FF6666 (Red)
    
    // Borders & UI
    const ImVec4 BORDER_LIGHT = ImVec4(0.0f, 0.81f, 1.0f, 0.4f);        // Cyan with alpha
    const ImVec4 BORDER_MEDIUM = ImVec4(0.0f, 0.62f, 0.85f, 0.6f);      // Medium blue with alpha
}

// ════════════════════════════════════════════════════════════════════════════
// USER ACCOUNT STRUCTURE
// ════════════════════════════════════════════════════════════════════════════
struct UserAccount {
    std::string username;
    std::string displayName;
    std::time_t expiryTime;
    std::time_t loginTime;
    bool isPremium;
    std::string subscriptionLevel; // "Free", "Basic", "Premium", "Elite"
};

// Global user session
UserAccount g_CurrentUser = {};

// ════════════════════════════════════════════════════════════════════════════
// UTILITY FUNCTIONS FOR USER DATA
// ════════════════════════════════════════════════════════════════════════════

std::string FormatExpiryDate(std::time_t expiryTime) {
    if (expiryTime == 0) return "N/A";
    
    std::tm* timeinfo = std::localtime(&expiryTime);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return std::string(buffer);
}

std::string GetTimeUntilExpiry(std::time_t expiryTime) {
    if (expiryTime == 0) return "N/A";
    
    std::time_t now = std::time(nullptr);
    double secondsLeft = std::difftime(expiryTime, now);
    
    if (secondsLeft <= 0) return "EXPIRED";
    
    int days = (int)(secondsLeft / 86400);
    int hours = (int)((secondsLeft - (days * 86400)) / 3600);
    
    if (days > 0) {
        return std::to_string(days) + "d " + std::to_string(hours) + "h";
    }
    return std::to_string(hours) + "h remaining";
}

ImVec4 GetExpiryStatusColor(std::time_t expiryTime) {
    if (expiryTime == 0) return ColorTheme::TEXT_SECONDARY;
    
    std::time_t now = std::time(nullptr);
    double secondsLeft = std::difftime(expiryTime, now);
    
    if (secondsLeft <= 0) {
        return ColorTheme::STATUS_EXPIRED;
    } else if (secondsLeft <= 259200) { // 3 days
        return ColorTheme::STATUS_WARNING;
    } else {
        return ColorTheme::STATUS_ACTIVE;
    }
}

// ════════════════════════════════════════════════════════════════════════════
// LOGIN UI - BLUE DARK THEME
// ════════════════════════════════════════════════════════════════════════════

void RenderLoginScreen() {
    static char username[64] = "knzz";
    static char password[64] = "";
    static bool show_password = false;
    static bool login_error = false;
    static float error_time = 0.0f;
    static bool is_authenticating = false;
    static float loading_start_time = 0.0f;
    
    ImGui::SetNextWindowSize(ImVec2(500, 600));
    ImGui::SetNextWindowPos(ImVec2(
        ImGui::GetIO().DisplaySize.x * 0.5f - 250,
        ImGui::GetIO().DisplaySize.y * 0.5f - 300
    ));
    
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ColorTheme::PRIMARY_DARK);
    ImGui::PushStyleColor(ImGuiCol_Border, ColorTheme::BORDER_MEDIUM);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.5f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(30, 30));
    
    if (ImGui::Begin("##LoginWindow", nullptr, 
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar)) {
        
        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetWindowPos();
        ImVec2 size = ImGui::GetWindowSize();
        
        // ─── Background Glow Effect ───
        draw->AddRectFilled(pos, pos + size, ImGui::GetColorU32(ColorTheme::SECONDARY_DARK), 15.0f);
        draw->AddRect(pos, pos + size, ImGui::GetColorU32(ColorTheme::BORDER_MEDIUM), 15.0f, 0, 1.5f);
        
        // ─── Corner Glow ───
        for (int i = 8; i >= 1; i--) {
            float alpha = 0.08f * (1.0f - (i / 9.0f));
            draw->AddCircleFilled(
                ImVec2(pos.x + size.x - 20, pos.y + 20),
                30.0f + (i * 5),
                ImGui::GetColorU32(ImVec4(ColorTheme::ACCENT_BRIGHT.x, ColorTheme::ACCENT_BRIGHT.y, 
                                         ColorTheme::ACCENT_BRIGHT.z, alpha))
            );
        }
        
        // ─── TITLE: "FORCE-AIM" ───
        ImGui::PushFont(font::Kenzofront);
        ImVec2 titleSize = ImGui::CalcTextSize("FORCE-AIM");
        ImGui::SetCursorPos(ImVec2((size.x - titleSize.x) * 0.5f, 30));
        draw->AddText(ImGui::GetCursorScreenPos(), ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), "FORCE-AIM");
        
        // ─── SUBTITLE: "BLUE-DARK" ───
        ImGui::PopFont();
        ImGui::PushFont(font::lexend_bold);
        ImVec2 subtitleSize = ImGui::CalcTextSize("BLUE-DARK");
        ImGui::SetCursorPos(ImVec2((size.x - subtitleSize.x) * 0.5f, 85));
        ImGui::TextColored(ColorTheme::ACCENT_BRIGHT, "BLUE-DARK");
        ImGui::PopFont();
        
        ImGui::Spacing();
        ImGui::Spacing();
        
        // ─── LOGIN FORM ───
        ImGui::SetCursorPos(ImVec2(30, 140));
        
        // Username
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.05f, 0.08f, 0.15f, 0.9f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.06f, 0.12f, 0.22f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.08f, 0.15f, 0.28f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ColorTheme::ACCENT_MEDIUM);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.2f);
        
        ImGui::TextColored(ColorTheme::TEXT_SECONDARY, "Username");
        ImGui::InputText("##username", username, IM_ARRAYSIZE(username));
        
        ImGui::Spacing();
        ImGui::TextColored(ColorTheme::TEXT_SECONDARY, "Password");
        ImGuiInputTextFlags password_flags = show_password ? 0 : ImGuiInputTextFlags_Password;
        ImGui::InputText("##password", password, IM_ARRAYSIZE(password), password_flags);
        
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(4);
        
        ImGui::Spacing();
        
        // Show Password Checkbox
        ImGui::TextColored(ColorTheme::TEXT_SECONDARY, "Show Password");
        ImGui::SameLine();
        ImGui::Checkbox("##show_pwd", &show_password);
        
        ImGui::Spacing();
        ImGui::Spacing();
        
        // ─── LOGIN BUTTON ───
        ImGui::PushStyleColor(ImGuiCol_Button, ColorTheme::ACCENT_BRIGHT);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ColorTheme::ACCENT_MEDIUM);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ColorTheme::ACCENT_DARK);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        
        if (ImGui::Button("LOGIN", ImVec2(size.x - 60, 40))) {
            if (strlen(username) > 0 && strlen(password) > 0) {
                // Simulate authentication
                g_CurrentUser.username = std::string(username);
                g_CurrentUser.displayName = std::string(username);
                g_CurrentUser.loginTime = std::time(nullptr);
                g_CurrentUser.expiryTime = g_CurrentUser.loginTime + (30 * 86400); // 30 days
                g_CurrentUser.isPremium = true;
                g_CurrentUser.subscriptionLevel = "Premium";
                
                authed = true;
                login_error = false;
            } else {
                login_error = true;
                error_time = (float)ImGui::GetTime();
            }
        }
        
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
        
        // ─── ERROR MESSAGE ───
        if (login_error && (ImGui::GetTime() - error_time) < 3.0f) {
            ImGui::Spacing();
            ImGui::TextColored(ColorTheme::STATUS_EXPIRED, "❌ Invalid credentials!");
        }
        
        // ─── FOOTER ───
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        ImVec2 discordSize = ImGui::CalcTextSize("Join Discord");
        ImGui::SetCursorPos(ImVec2((size.x - discordSize.x) * 0.5f, size.y - 40));
        
        ImGui::PushStyleColor(ImGuiCol_Text, ColorTheme::ACCENT_BRIGHT);
        if (ImGui::Selectable("Join Discord for Updates", false)) {
            ShellExecuteA(NULL, "open", "https://discord.gg/yourserver", NULL, NULL, SW_SHOW);
        }
        ImGui::PopStyleColor();
        
        ImGui::End();
    }
    
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(2);
}

// ════════════════════════════════════════════════════════════════════════════
// USER INFO PANEL - TOP RIGHT CORNER
// ════════════════════════════════════════════════════════════════════════════

void RenderUserInfoPanel() {
    ImDrawList* draw = ImGui::GetForegroundDrawList();
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    
    // Panel dimensions
    float panelWidth = 280;
    float panelHeight = 140;
    ImVec2 panelPos = ImVec2(displaySize.x - panelWidth - 15, 15);
    ImVec2 panelMax = ImVec2(panelPos.x + panelWidth, panelPos.y + panelHeight);
    
    // Background
    draw->AddRectFilled(panelPos, panelMax, ImGui::GetColorU32(ColorTheme::SECONDARY_DARK), 12.0f);
    draw->AddRect(panelPos, panelMax, ImGui::GetColorU32(ColorTheme::BORDER_LIGHT), 12.0f, 0, 1.5f);
    
    // Glow effect
    for (int i = 4; i >= 1; i--) {
        float alpha = 0.05f * (1.0f - (i / 5.0f));
        draw->AddCircleFilled(
            ImVec2(panelMax.x - 10, panelPos.y + 10),
            25.0f + (i * 4),
            ImGui::GetColorU32(ImVec4(0.0f, 0.81f, 1.0f, alpha))
        );
    }
    
    // User info text
    float textX = panelPos.x + 15;
    float textY = panelPos.y + 12;
    
    // Username
    std::string userDisplay = "👤 " + g_CurrentUser.displayName;
    draw->AddText(ImVec2(textX, textY), ImGui::GetColorU32(ColorTheme::TEXT_PRIMARY), userDisplay.c_str());
    
    // Subscription level
    ImVec4 subColor = g_CurrentUser.isPremium ? ColorTheme::ACCENT_BRIGHT : ColorTheme::TEXT_SECONDARY;
    std::string subDisplay = "Tier: " + g_CurrentUser.subscriptionLevel;
    draw->AddText(ImVec2(textX, textY + 25), ImGui::GetColorU32(subColor), subDisplay.c_str());
    
    // Expiry status
    std::string expiryStr = GetTimeUntilExpiry(g_CurrentUser.expiryTime);
    ImVec4 expiryColor = GetExpiryStatusColor(g_CurrentUser.expiryTime);
    std::string expiryDisplay = "Expires: " + expiryStr;
    draw->AddText(ImVec2(textX, textY + 50), ImGui::GetColorU32(expiryColor), expiryDisplay.c_str());
    
    // Login status indicator
    draw->AddCircleFilled(
        ImVec2(panelMax.x - 15, panelMax.y - 15),
        5.0f,
        ImGui::GetColorU32(ColorTheme::STATUS_ACTIVE)
    );
    draw->AddText(ImVec2(textX, textY + 75), ImGui::GetColorU32(ColorTheme::TEXT_SECONDARY), "✓ Connected");
}

// ════════════════════════════════════════════════════════════════════════════
// MAIN MENU UI - BLUE DARK THEME
// ════════════════════════════════════════════════════════════════════════════

void RenderMainMenuBlueD ark() {
    if (!authed) {
        RenderLoginScreen();
        return;
    }
    
    // Show user info panel
    RenderUserInfoPanel();
    
    static ImVec2 menuPos = ImVec2(0, 0);
    float windowCornerRounding = 18.0f;
    
    ImGui::SetNextWindowPos(menuPos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(900, 700));
    
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ColorTheme::PRIMARY_DARK);
    ImGui::PushStyleColor(ImGuiCol_Border, ColorTheme::BORDER_MEDIUM);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, windowCornerRounding);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.5f);
    
    if (ImGui::Begin("FORCE-AIM BLUE-DARK", nullptr, 
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
        
        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetWindowPos();
        ImVec2 size = ImGui::GetWindowSize();
        
        // ─── BACKGROUND ───
        draw->AddRectFilled(pos, pos + size, ImGui::GetColorU32(ColorTheme::SECONDARY_DARK), windowCornerRounding);
        draw->AddRect(pos, pos + size, ImGui::GetColorU32(ColorTheme::BORDER_MEDIUM), windowCornerRounding, 0, 1.5f);
        
        // ─── CORNER GLOW ───
        for (int i = 10; i >= 1; i--) {
            float alpha = 0.06f * (1.0f - ((float)i / 11.0f));
            draw->AddCircleFilled(
                ImVec2(pos.x + size.x - 20, pos.y + 20),
                40.0f + (i * 5),
                ImGui::GetColorU32(ImVec4(ColorTheme::ACCENT_BRIGHT.x, ColorTheme::ACCENT_BRIGHT.y, 
                                         ColorTheme::ACCENT_BRIGHT.z, alpha))
            );
        }
        
        // ─── HEADER ───
        ImGui::PushFont(font::Kenzofront);
        const char* title = "FORCE-AIM";
        const char* subtitle = " BLUE-DARK";
        ImVec2 titleSize = ImGui::CalcTextSize(title);
        ImVec2 subtitleSize = ImGui::CalcTextSize(subtitle);
        
        float titleX = pos.x + 30;
        float titleY = pos.y + 15;
        
        draw->AddText(ImVec2(titleX, titleY), ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), title);
        draw->AddText(ImVec2(titleX + titleSize.x, titleY), ImGui::GetColorU32(ColorTheme::ACCENT_BRIGHT), subtitle);
        ImGui::PopFont();
        
        draw->AddLine(ImVec2(pos.x + 20, pos.y + 50), ImVec2(pos.x + size.x - 20, pos.y + 50), 
                     ImGui::GetColorU32(ColorTheme::BORDER_LIGHT), 1.5f);
        
        // ─── TABS ───
        ImGui::SetCursorPos(ImVec2(30, 70));
        ImGui::BeginGroup();
        
        static int activePage = 0;
        const char* tabs[] = {"🎯 Aimbot", "👁 ESP", "🌐 Visuals", "⚙️ Settings"};
        
        for (int i = 0; i < IM_ARRAYSIZE(tabs); i++) {
            if (i > 0) ImGui::SameLine(0, 15);
            
            bool isActive = (activePage == i);
            ImGui::PushStyleColor(ImGuiCol_Button, isActive ? ColorTheme::ACCENT_BRIGHT : ColorTheme::TERTIARY_DARK);
            ImGui::PushStyleColor(ImGuiCol_Text, ColorTheme::TEXT_PRIMARY);
            
            if (ImGui::Button(tabs[i], ImVec2(100, 30))) {
                activePage = i;
            }
            
            ImGui::PopStyleColor(2);
        }
        
        ImGui::EndGroup();
        
        // ─── CONTENT AREA ───
        ImGui::SetCursorPos(ImVec2(30, 120));
        ImGui::BeginChild("ContentArea", ImVec2(size.x - 60, size.y - 160), true);
        
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ColorTheme::TERTIARY_DARK);
        ImGui::PushStyleColor(ImGuiCol_Border, ColorTheme::BORDER_LIGHT);
        
        // Tab content
        if (activePage == 0) {
            ImGui::TextColored(ColorTheme::ACCENT_BRIGHT, "🎯 AIMBOT SETTINGS");
            ImGui::Separator();
            
            static bool aimbot_enabled = false;
            static int fov = 65;
            static float smooth = 0.5f;
            
            ImGui::Checkbox("Enable Aimbot", &aimbot_enabled);
            ImGui::SliderInt("FOV", &fov, 10, 180);
            ImGui::SliderFloat("Smoothing", &smooth, 0.1f, 1.0f);
            
        } else if (activePage == 1) {
            ImGui::TextColored(ColorTheme::ACCENT_BRIGHT, "👁 ESP SETTINGS");
            ImGui::Separator();
            
            static bool esp_enabled = false;
            static bool show_boxes = false;
            static bool show_names = false;
            
            ImGui::Checkbox("Enable ESP", &esp_enabled);
            ImGui::Checkbox("Show Boxes", &show_boxes);
            ImGui::Checkbox("Show Names", &show_names);
            
        } else if (activePage == 2) {
            ImGui::TextColored(ColorTheme::ACCENT_BRIGHT, "🌐 VISUAL SETTINGS");
            ImGui::Separator();
            
            static bool wallhack = false;
            static float brightness = 1.0f;
            
            ImGui::Checkbox("Wallhack", &wallhack);
            ImGui::SliderFloat("Brightness", &brightness, 0.5f, 2.0f);
            
        } else if (activePage == 3) {
            ImGui::TextColored(ColorTheme::ACCENT_BRIGHT, "⚙️ SETTINGS");
            ImGui::Separator();
            
            ImGui::Text("Account: %s", g_CurrentUser.username.c_str());
            ImGui::Text("Tier: %s", g_CurrentUser.subscriptionLevel.c_str());
            ImGui::Text("Expires: %s", FormatExpiryDate(g_CurrentUser.expiryTime).c_str());
        }
        
        ImGui::PopStyleColor(2);
        ImGui::EndChild();
        
        // ─── FOOTER ───
        ImGui::SetCursorPos(ImVec2(30, size.y - 35));
        ImGui::TextColored(ColorTheme::TEXT_SECONDARY, "FORCE-AIM © 2026 | Made by KENZO & INDU");
        
        ImGui::End();
    }
    
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(2);
}

// ════════════════════════════════════════════════════════════════════════════
// UPDATE COLOR THEME FOR ENTIRE APPLICATION
// ════════════════════════════════════════════════════════════════════════════

void ApplyBlueD arkTheme(ImGuiStyle* style) {
    style->Colors[ImGuiCol_WindowBg] = ColorTheme::PRIMARY_DARK;
    style->Colors[ImGuiCol_PopupBg] = ColorTheme::SECONDARY_DARK;
    style->Colors[ImGuiCol_Border] = ColorTheme::BORDER_MEDIUM;
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
    
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.08f, 0.15f, 0.5f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.06f, 0.12f, 0.22f, 0.7f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.08f, 0.15f, 0.28f, 0.9f);
    
    style->Colors[ImGuiCol_TitleBg] = ColorTheme::SECONDARY_DARK;
    style->Colors[ImGuiCol_TitleBgActive] = ColorTheme::SECONDARY_DARK;
    style->Colors[ImGuiCol_TitleBgCollapsed] = ColorTheme::TERTIARY_DARK;
    
    style->Colors[ImGuiCol_MenuBarBg] = ColorTheme::SECONDARY_DARK;
    
    style->Colors[ImGuiCol_ScrollbarBg] = ColorTheme::TERTIARY_DARK;
    style->Colors[ImGuiCol_ScrollbarGrab] = ColorTheme::ACCENT_DARK;
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ColorTheme::ACCENT_MEDIUM;
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ColorTheme::ACCENT_BRIGHT;
    
    style->Colors[ImGuiCol_CheckMark] = ColorTheme::ACCENT_BRIGHT;
    style->Colors[ImGuiCol_SliderGrab] = ColorTheme::ACCENT_MEDIUM;
    style->Colors[ImGuiCol_SliderGrabActive] = ColorTheme::ACCENT_BRIGHT;
    
    style->Colors[ImGuiCol_Button] = ColorTheme::ACCENT_DARK;
    style->Colors[ImGuiCol_ButtonHovered] = ColorTheme::ACCENT_MEDIUM;
    style->Colors[ImGuiCol_ButtonActive] = ColorTheme::ACCENT_BRIGHT;
    
    style->Colors[ImGuiCol_Header] = ColorTheme::ACCENT_DARK;
    style->Colors[ImGuiCol_HeaderHovered] = ColorTheme::ACCENT_MEDIUM;
    style->Colors[ImGuiCol_HeaderActive] = ColorTheme::ACCENT_BRIGHT;
    
    style->Colors[ImGuiCol_Separator] = ColorTheme::BORDER_MEDIUM;
    style->Colors[ImGuiCol_SeparatorHovered] = ColorTheme::ACCENT_MEDIUM;
    style->Colors[ImGuiCol_SeparatorActive] = ColorTheme::ACCENT_BRIGHT;
    
    style->Colors[ImGuiCol_ResizeGrip] = ColorTheme::ACCENT_DARK;
    style->Colors[ImGuiCol_ResizeGripHovered] = ColorTheme::ACCENT_MEDIUM;
    style->Colors[ImGuiCol_ResizeGripActive] = ColorTheme::ACCENT_BRIGHT;
    
    style->Colors[ImGuiCol_PlotLines] = ColorTheme::ACCENT_BRIGHT;
    style->Colors[ImGuiCol_PlotLinesHovered] = ColorTheme::ACCENT_MEDIUM;
    style->Colors[ImGuiCol_PlotHistogram] = ColorTheme::ACCENT_BRIGHT;
    style->Colors[ImGuiCol_PlotHistogramHovered] = ColorTheme::ACCENT_MEDIUM;
    
    style->Colors[ImGuiCol_Text] = ColorTheme::TEXT_PRIMARY;
    style->Colors[ImGuiCol_TextDisabled] = ColorTheme::TEXT_SECONDARY;
    
    // Styling
    style->WindowRounding = 15.0f;
    style->FrameRounding = 8.0f;
    style->GrabRounding = 6.0f;
    style->PopupRounding = 12.0f;
    
    style->WindowBorderSize = 1.5f;
    style->FrameBorderSize = 1.0f;
    
    style->WindowPadding = ImVec2(15, 15);
    style->FramePadding = ImVec2(8, 6);
    style->ItemSpacing = ImVec2(12, 8);
    
    style->Alpha = 1.0f;
}

// ════════════════════════════════════════════════════════════════════════════
// CALL THESE FUNCTIONS IN YOUR MAIN RENDER LOOP
// ════════════════════════════════════════════════════════════════════════════

/* 
    In your main MANAS() function, replace the ImGui::Begin() calls with:
    
    // Apply theme once
    static bool themeApplied = false;
    if (!themeApplied) {
        ApplyBlueDarkTheme(&ImGui::GetStyle());
        themeApplied = true;
    }
    
    // Render appropriate UI
    if (authed) {
        RenderMainMenuBlueDark();
    } else {
        RenderLoginScreen();
    }
    
    // Show user info if logged in
    if (authed) {
        RenderUserInfoPanel();
    }
*/
