#define IMGUI_DEFINE_MATH_OPERATORS
#pragma once
#include <windows.h>
#include "imgui_internal.h"
#include "imgui.h"
#include <string>
#include <vector>

namespace font
{
    
    inline ImFont* Regzfront = nullptr;
    inline ImFont* DARK = nullptr;
    inline ImFont* Kenzofront = nullptr;
    inline ImFont* Joverfront = nullptr;
    inline ImFont* hoverfront = nullptr;
	inline ImFont* icomoon = nullptr;
	inline ImFont* picomoon = nullptr;
    inline ImFont* WeaponsIco = nullptr;
	inline ImFont* primary_font = nullptr;
	inline ImFont* second_font = nullptr;
	inline ImFont* icon_font = nullptr;
	inline ImFont* tab_font = nullptr;

	inline ImFont* lexend_bold = nullptr;
	inline ImFont* lexend_regular = nullptr;
	inline ImFont* lexend_general_bold = nullptr;
	inline ImFont* lexend_general_bold2 = nullptr;

	inline ImFont* icomoon_widget = nullptr;
	inline ImFont* icomoon_widget2 = nullptr;
	inline ImFont* icon_font2 = nullptr;
	inline ImFont* Nevan = nullptr;
	inline ImFont* ContiB = nullptr;
	inline ImFont* ContiM = nullptr;
	inline ImColor main_color(168, 35, 155);

    inline ImFont* gff = nullptr;

    inline ImFont* noto_reg = nullptr;
    inline ImFont* noto_symbols2 = nullptr;
    inline ImFont* noto_arabic = nullptr;
    inline ImFont* noto_devanagari = nullptr;
    inline ImFont* noto_japanese = nullptr;
    inline ImFont* noto_khmer = nullptr;
    inline ImFont* noto_korean = nullptr;
    inline ImFont* noto_sc = nullptr;
    inline ImFont* noto_sinhala = nullptr;
    inline ImFont* noto_tamil = nullptr;
    inline ImFont* noto_tc = nullptr;
    inline ImFont* noto_thai = nullptr;
    inline ImFont* unifont = nullptr;


}

inline ImGuiWindow* main_window;
inline char search[64];
inline float anim_speed = 8.f;



struct HealthBarSettings
{
    int position = 0;
    float offset_x = 0.0f;
    float offset_y = 0.0f;
};

static HealthBarSettings health_bar_settings;
namespace c
{

	inline ImVec4 accent = ImColor(230, 25, 25);

	inline ImVec4 white = ImColor(255, 255, 255);

	namespace background
	{
        inline ImVec4 bar = ImColor(7, 8, 8);
		inline ImVec4 filling = ImColor(5, 5, 5);
		inline ImVec4 stroke = ImColor(24, 26, 36);
        inline ImVec2 size = ImVec2(650, 490);
        inline ImVec2 size2 = ImVec2(350, 440);

		inline float rounding = 6;

	}



	namespace elements
	{
		inline ImVec4 mark = ImColor(255, 255, 255);
        
		inline ImVec4 stroke = ImColor(28, 26, 37);
		inline ImVec4 background = ImColor(15, 15, 17);
		inline ImVec4 filled_circle = ImColor(25, 25, 25);
		inline ImVec4 circle = ImColor(35, 35, 35);
		inline ImVec4 background_widget = ImColor(21, 23, 26);
		

		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hov = ImColor(81, 92, 109);
		inline ImVec4 text = ImColor(255, 255, 255, 255/2);
		inline ImVec4 text1 = ImColor(200, 200, 200);

		inline float rounding = 4;
	}

	namespace child
	{

	}

	namespace tab
	{
		inline ImVec4 tab_active = ImColor(22, 22, 22);

		inline ImVec4 border = ImColor(14, 14, 14);
	}

}


inline ImColor line_colorParticle(255, 255, 255, 200);

inline ImColor text_color[2] = { ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 150) };

inline ImColor GetColorWithAlpha(ImColor color, float alpha)
{
	return ImColor(color.Value.x, color.Value.y, color.Value.z, alpha);
}

inline ImVec2 center_text(ImVec2 min, ImVec2 max, const char* text)
{
	return min + (max - min) / 2 - ImGui::CalcTextSize(text) / 2;
}

struct Notification
{
    std::string message, information;
    ImColor color;
    ImRect bb;
    ImVec2 offset = ImVec2(400, 0);    
    ImVec2 target_offset = ImVec2(400, 0);
    float timer = 0;
    float shrink_progress = 1.0f;

    float y_position = 0;            
    float target_y_position = 0;     
};


class NotificationSystem
{
private:
    std::vector<Notification> notifications;

public:
    void AddNotification(std::string message, std::string information, ImColor color)
    {
        Notification notif;
        notif.message = message;
        notif.information = information;
        notif.color = color;
        notif.timer = 0;

        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        notif.offset = ImVec2(400.0f, 0); // Initial x offset for off-screen
        notif.target_offset = ImVec2(0.0f, 0); // Target on-screen position
        notif.shrink_progress = 1.0f;
        notif.y_position = static_cast<float>(GetSystemMetrics(SM_CYSCREEN)); // Start from bottom off-screen
        notif.target_y_position = 0.0f;

        notifications.push_back(notif);
    }

    void DrawNotifications()
    {
        float spacing = 65.0f;
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        float startX = static_cast<float>(screenWidth) - 360.0f; // Adjust this as needed

        float baseY = static_cast<float>(screenHeight) - 72.0f;

        for (int i = notifications.size() - 1; i >= 0; --i)
        {
            Notification& notif = notifications[i];
            notif.target_y_position = baseY;
            baseY -= spacing;
        }

        for (int i = 0; i < notifications.size(); )
        {
            Notification& notif = notifications[i];
            notif.timer += ImGui::GetIO().DeltaTime * 10.0f;

            // Animate out after 30s
            notif.target_offset = notif.timer > 30.0f ? ImVec2(400.0f, 0.0f) : ImVec2(0.0f, 0.0f);
            notif.offset = ImLerp(notif.offset, notif.target_offset, ImGui::GetIO().DeltaTime * 10.0f);
            notif.y_position = ImLerp(notif.y_position, notif.target_y_position, ImGui::GetIO().DeltaTime * 10.0f);

            notif.bb = ImRect(
                ImVec2(startX + notif.offset.x, notif.y_position),
                ImVec2(startX + 340.0f + notif.offset.x, notif.y_position + 52.0f)
            );

            ImGui::GetForegroundDrawList()->AddRectFilled(notif.bb.Min, notif.bb.Max, ImColor(10, 10, 10, 220), 2);
            ImGui::GetForegroundDrawList()->AddText(notif.bb.Min + ImVec2(12.5f, 6.0f), ImGui::GetColorU32(c::accent), notif.message.c_str());
            ImGui::PushFont(font::lexend_regular);
            ImGui::GetForegroundDrawList()->AddText(notif.bb.Min + ImVec2(12.5f, 28.0f), text_color[1], notif.information.c_str());
            ImGui::PopFont();

            notif.shrink_progress = fmax(notif.shrink_progress - ImGui::GetIO().DeltaTime * 0.35f, 0.0f);
            float shrink_width = notif.bb.GetWidth() * notif.shrink_progress;
            ImRect shrink_rect(notif.bb.Min + ImVec2(0.0f, 49.0f), notif.bb.Min + ImVec2(shrink_width, 52.0f));
            ImGui::GetForegroundDrawList()->AddRectFilled(shrink_rect.Min, shrink_rect.Max, ImGui::GetColorU32(c::accent));
            ImGui::GetForegroundDrawList()->AddShadowRect(shrink_rect.Min, shrink_rect.Max, ImGui::GetColorU32(c::accent), 30.0f, ImVec2(0, 0), 0, 0.0f);

            if (notif.timer > 35.0f && notif.offset.x >= 399.0f)
            {
                notifications.erase(notifications.begin() + i);
                continue;
            }

            ++i;
        }
    }
};


inline NotificationSystem notificationSystem;

