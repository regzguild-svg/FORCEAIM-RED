#pragma once

//ImGui Includes
#include "imgui.h"
#include "imgui_edited.hpp"
#include "imgui_freetype.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

//System Includes
#include <algorithm>
#include <chrono>
#include <cmath>
#include <codecvt>
#include <ctime>
#include <dwmapi.h>
#include <filesystem>
#include <future>
#include <iomanip>
#include <iostream>
#include <Lmcons.h>
#include <locale>
#include <shlobj.h>
#include <ShObjIdl_core.h>
#include <sstream>
#include <string>
#include <strsafe.h>
#include <tchar.h>
#include <thread>
#include <TlHelp32.h>
#include <vector>
#include <winhttp.h>
#include <wininet.h>

//DirectX Includes
#include <d3d11.h>
#include <D3DX11tex.h>

//External Includes
#include "auth/auth.hpp"
#include "auth/skStr.h"
#include "AuthDLL/Header.h"
#include "font.h"
#include "texture.h"



#include "auth/skStr.h"
#include "Chams/Visuals.h"
#include "chrono"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imgui_settings.h"
#include <algorithm>
#include <GL/glew.h>
#include <cstring>
#include <d3d11.h>
#include <D3DX11.h> 
#include <D3DX11tex.h>
#include <dwmapi.h>
#include <functional>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include <Psapi.h>
#include <random>
#include <shobjidl.h>
#include <ShObjIdl_core.h>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <strsafe.h>
#include <tchar.h>
#include <thread>
#include <tlhelp32.h>
#include <vector>
#include <Windows.h>


#include "DiscordSDK/src/discord_register.h"
#include "DiscordSDK/src/discord_rpc.h"








//Libs
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "ntdll.lib")

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

void MANAS();

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();

HWND hwnd;
RECT rc;

static char username[64] = "";
static char password[64] = "";

static bool stream;
bool setup_done = false;



int rotation_start_index;

std::vector<ImFont*> g_FontFallbackChain;


std::string GetCredentialsFilePath()
{
    char appDataPath[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);

    std::string folder = std::string(appDataPath) + "\\Pico";
    CreateDirectoryA(folder.c_str(), NULL);

    return folder + "\\auth.txt";
}

void SaveCredentials(const char* user, const char* pass)
{
    std::ofstream file(GetCredentialsFilePath(), std::ios::trunc);
    if (file.is_open()) {
        file << user << '\n' << pass;
        file.close();
    }
}

void LoadCredentials()
{
    std::ifstream file(GetCredentialsFilePath());
    if (file.is_open()) {
        std::string user, pass;
        std::getline(file, user);
        std::getline(file, pass);
        file.close();


        if (!user.empty() && !pass.empty()) {
            strncpy(username, user.c_str(), sizeof(username) - 1);
            username[sizeof(username) - 1] = '\0';

            strncpy(password, pass.c_str(), sizeof(password) - 1);
            password[sizeof(password) - 1] = '\0';
        }
    }
}

void ImRotateStart()
{
    rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
}

ImVec2 ImRotationCenter()
{
    ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX);

    const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
    for (int i = rotation_start_index; i < buf.Size; i++)
        l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

    return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2);
}


void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
{
    float s = sin(rad), c = cos(rad);
    center = ImRotate(center, s, c) - center;

    auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
    for (int i = rotation_start_index; i < buf.Size; i++)
        buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
}



namespace notifications
{
    const char* notif_name;
    const char* notif_description;
    static int notif_state;
    static float notif_offset;
    static float notif_timer;
    static float notif_width;

    void Message(const char* name, const char* description)
    {
        notif_name = name;
        notif_description = description;
        notif_state = 1;
        notif_offset = 100.f;
        notif_timer = 0;
        notif_width = 0;
    }

    void NotifyUpdate(ImVec2 p)
    {
        if (ImGui::CalcTextSize(notif_name).x < 1.f)
            return;

        notif_offset = ImLerp(notif_offset, notif_state == 0 ? 200.f : 0.f, ImGui::GetIO().DeltaTime * 10.f);
        notif_timer += ImGui::GetIO().DeltaTime * 20.f;

        if (notif_timer > 70.f)
            notif_state = 0;

        if (notif_timer > 100.f)
            notif_name = "";

        ImVec2 notif_size = ImVec2(ImGui::CalcTextSize(notif_description).x + 30, ImGui::CalcTextSize(notif_name).y + 50 + notif_offset);

        ImVec2 notif_pos = ImVec2(ImGui::GetIO().DisplaySize.x / 2 - notif_size.x / 2, ImGui::GetIO().DisplaySize.y - notif_size.y);

        ImGui::SetNextWindowPos(notif_pos);
        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::Begin("Notification", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowSize(notif_size);

        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(notif_pos.x, notif_pos.y + notif_offset), ImVec2(notif_pos.x + notif_size.x, notif_pos.y), IM_COL32(14, 14, 14, 200));



        ImGui::GetWindowDrawList()->AddText(ImVec2(notif_pos.x, notif_pos.y + notif_offset) + ImVec2(10, 10), text_color[0], notif_name);


        ImGui::GetWindowDrawList()->AddText(ImVec2(notif_pos.x, notif_pos.y + notif_offset) + ImVec2(10, 30), text_color[1], notif_description);


        ImGui::GetWindowDrawList()->AddRect(ImVec2(notif_pos.x, notif_pos.y + notif_offset), ImVec2(notif_pos.x + notif_size.x, notif_pos.y), ImGui::GetColorU32(c::accent), 5.0f);

        ImGui::End();
    }
}



#pragma once
#include <vector>
#include <cmath>
#include <cstdlib>
#include "imgui.h"

struct BubbleP
{
    ImVec2 pos;
    ImVec2 vel;
    float  r;
    float  a;
    float  life;
};

inline float fx_rand01() { return (float)std::rand() / (float)RAND_MAX; }
inline float fx_rand(float a, float b) { return a + (b - a) * fx_rand01(); }

inline ImU32 fx_mul_alpha(ImU32 col, float mul)
{
    if (mul < 0.f) mul = 0.f; if (mul > 1.f) mul = 1.f;
    ImU32 A = (col >> 24) & 0xFF;
    A = (ImU32)(A * mul);
    return (col & 0x00FFFFFF) | (A << 24);
}

inline void fx_glow_circle(ImDrawList* dl, const ImVec2& p, float r, ImU32 col, float glow)
{
    // glow layers
    dl->AddCircleFilled(p, r + 14.f, fx_mul_alpha(col, 0.07f * glow));
    dl->AddCircleFilled(p, r + 9.f, fx_mul_alpha(col, 0.10f * glow));
    dl->AddCircleFilled(p, r + 5.f, fx_mul_alpha(col, 0.14f * glow));
    dl->AddCircleFilled(p, r + 2.f, fx_mul_alpha(col, 0.18f * glow));
    // core
    dl->AddCircleFilled(p, r, fx_mul_alpha(col, 0.22f * glow));
    dl->AddCircle(p, r, fx_mul_alpha(col, 0.55f * glow), 0, 1.2f);
    dl->AddCircle(p, r * 0.55f, fx_mul_alpha(col, 0.35f * glow), 0, 1.0f);
}


inline void DrawBubblesParticles()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* dl = ImGui::GetWindowDrawList();

    const ImVec2 wpos = ImGui::GetWindowPos();
    const ImVec2 wsz = ImGui::GetWindowSize();
    const float dt = io.DeltaTime > 0.f ? io.DeltaTime : 0.016f;

    // same color you gave (teal/cyan)
    const ImU32 ACCENT = IM_COL32(0, 255, 220, 255);

    // active/hovered => more glow + more reaction
    const bool active = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) || ImGui::IsWindowFocused();

    const ImVec2 mouse = io.MousePos;
    const bool inside =
        mouse.x >= wpos.x && mouse.x <= wpos.x + wsz.x &&
        mouse.y >= wpos.y && mouse.y <= wpos.y + wsz.y;

    // soft haze light (background “light”)
    float haze = active ? 0.16f : 0.10f;
    dl->AddRectFilled(wpos, wpos + wsz, fx_mul_alpha(ACCENT, haze), 18.f);

    // storage
    static std::vector<BubbleP> bubbles;
    static std::vector<BubbleP> sparks;

    // target bubbles count (like screenshot)
    const int TARGET = 60;
    while ((int)bubbles.size() < TARGET)
    {
        BubbleP b{};
        b.pos = ImVec2(wpos.x + fx_rand(0, wsz.x), wpos.y + fx_rand(0, wsz.y));
        b.vel = ImVec2(fx_rand(-14.f, 14.f), fx_rand(-22.f, -8.f)); // mostly upward
        b.r = fx_rand(6.f, 18.f);
        b.a = fx_rand(0.35f, 0.95f);
        b.life = 9999.f;
        bubbles.push_back(b);
    }

    // click burst (charara) inside window
    if (inside && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        for (int i = 0; i < 22; i++)
        {
            float ang = fx_rand(0.f, 6.2831853f);
            float sp = fx_rand(180.f, 420.f);
            BubbleP s{};
            s.pos = mouse;
            s.vel = ImVec2(std::cos(ang) * sp, std::sin(ang) * sp);
            s.r = fx_rand(1.4f, 3.0f);
            s.a = fx_rand(0.55f, 1.0f);
            s.life = fx_rand(0.20f, 0.45f);
            sparks.push_back(s);
        }
    }

    // mouse gentle pull (active only)
    const float pull = (active && inside) ? 40.f : 16.f;
    const float glow = active ? 1.0f : 0.70f;

    // clip to window (so bubbles don't draw outside)
    dl->PushClipRect(wpos, wpos + wsz, true);

    // update + draw bubbles
    for (auto& b : bubbles)
    {
        // movement
        b.pos.x += b.vel.x * dt;
        b.pos.y += b.vel.y * dt;

        // wrap: when bubble goes up, respawn bottom
        if (b.pos.y < wpos.y - 30.f)
        {
            b.pos.y = wpos.y + wsz.y + fx_rand(10.f, 80.f);
            b.pos.x = wpos.x + fx_rand(0.f, wsz.x);
            b.vel = ImVec2(fx_rand(-14.f, 14.f), fx_rand(-22.f, -8.f));
            b.r = fx_rand(6.f, 18.f);
            b.a = fx_rand(0.35f, 0.95f);
        }

        if (b.pos.x < wpos.x - 30.f) b.pos.x = wpos.x + wsz.x + 30.f;
        if (b.pos.x > wpos.x + wsz.x + 30.f) b.pos.x = wpos.x - 30.f;

        // slight wobble
        b.vel.x += std::sinf((b.pos.y + b.r) * 0.01f) * 2.0f * dt;

        // mouse attraction/repel (subtle)
        if (inside)
        {
            ImVec2 d(mouse.x - b.pos.x, mouse.y - b.pos.y);
            float dist2 = d.x * d.x + d.y * d.y;
            float maxD = 160.f;
            if (dist2 < maxD * maxD && dist2 > 4.f)
            {
                float dist = std::sqrt(dist2);
                d.x /= dist; d.y /= dist;
                // pull a bit
                b.vel.x += d.x * pull * dt * 0.25f;
                b.vel.y += d.y * pull * dt * 0.25f;
            }
        }

        // damping
        b.vel.x *= (1.f - 0.08f * dt);
        b.vel.y *= (1.f - 0.02f * dt);

        // draw glow bubble
        float g = glow * b.a;
        fx_glow_circle(dl, b.pos, b.r, ACCENT, g);
    }

    // update + draw sparks (charara)
    for (int i = (int)sparks.size() - 1; i >= 0; --i)
    {
        BubbleP& s = sparks[i];
        s.life -= dt;
        if (s.life <= 0.f) { sparks.erase(sparks.begin() + i); continue; }

        s.pos.x += s.vel.x * dt;
        s.pos.y += s.vel.y * dt;

        // gravity + damping
        s.vel.y += 260.f * dt;
        s.vel.x *= (1.f - 2.2f * dt);
        s.vel.y *= (1.f - 2.2f * dt);

        float fade = (s.life < 0.15f) ? (s.life / 0.15f) : 1.f;
        if (fade < 0.f) fade = 0.f;

        ImVec2 tail = ImVec2(s.pos.x - s.vel.x * 0.01f, s.pos.y - s.vel.y * 0.01f);
        dl->AddLine(tail, s.pos, fx_mul_alpha(ACCENT, 0.60f * fade), 1.8f);
        dl->AddCircleFilled(s.pos, s.r + 4.f, fx_mul_alpha(ACCENT, 0.10f * fade));
        dl->AddCircleFilled(s.pos, s.r, fx_mul_alpha(ACCENT, 0.80f * fade));
    }

    dl->PopClipRect();
}





namespace ImGui
{
    int rotation_start_index;
    void ImRotateStart()
    {
        rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
    }

    ImVec2 ImRotationCenter()
    {
        ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX);

        const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

        return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2);
    }


    void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
    {
        float s = sin(rad), c = cos(rad);
        center = ImRotate(center, s, c) - center;

        auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
    }
}

struct Particle
{
    ImVec2 pos;
    ImVec2 vel;
};

void RenderThunderStorm()
{
    static std::vector<Particle> particles;
    static float flashAlpha = 0.0f;
    static float timer = 0.0f;

    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    ImGuiIO& io = ImGui::GetIO();

    ImVec2 screen = io.DisplaySize;
    ImVec2 mouse = io.MousePos;
    float dt = io.DeltaTime;

    // Spawn rain
    while (particles.size() < 500)
    {
        particles.push_back({
            ImVec2((float)(rand() % (int)screen.x),
                   (float)(rand() % (int)screen.y)),
            ImVec2(-80.f + (rand() % 40),
                   700.f + (rand() % 250))
            });
    }

    // Update & Draw Rain
    for (auto& p : particles)
    {
        p.pos.x += p.vel.x * dt;
        p.pos.y += p.vel.y * dt;

        if (p.pos.y > screen.y)
        {
            p.pos.y = -10.f;
            p.pos.x = (float)(rand() % (int)screen.x);
        }

        draw->AddLine(
            p.pos,
            ImVec2(p.pos.x - 4.f, p.pos.y - 14.f),
            IM_COL32(170, 220, 255, 180),
            1.0f
        );
    }

    // Mouse Click Lightning
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        flashAlpha = 255.f;

        ImVec2 start(mouse.x + (rand() % 80 - 40), 0.f);
        ImVec2 current = start;

        for (int i = 0; i < 12; i++)
        {
            ImVec2 next(
                current.x + (rand() % 60 - 30),
                current.y + (mouse.y - current.y) / (12 - i)
            );

            draw->AddLine(current, next, IM_COL32(255, 255, 255, 255), 3.0f);
            current = next;
        }

        draw->AddLine(current, mouse, IM_COL32(255, 255, 255, 255), 4.0f);
    }

    // Random Lightning
    timer += dt;
    if (timer >= 4.0f)
    {
        timer = 0.0f;
        flashAlpha = 180.f;

        ImVec2 current((float)(rand() % (int)screen.x), 0.f);

        for (int i = 0; i < 10; i++)
        {
            ImVec2 next(
                current.x + (rand() % 70 - 35),
                current.y + 60.f
            );

            draw->AddLine(current, next, IM_COL32(255, 255, 255, 255), 2.5f);
            current = next;
        }
    }

    // Flash Effect
    if (flashAlpha > 0.f)
    {
        draw->AddRectFilled(
            ImVec2(0, 0),
            screen,
            IM_COL32(255, 255, 255, (int)flashAlpha)
        );

        flashAlpha -= 600.f * dt;

        if (flashAlpha < 0.f)
            flashAlpha = 0.f;
    }
}


void ParticlesV()
{

    ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

    static ImVec2 partile_pos[100];
    static ImVec2 partile_target_pos[100];
    static float partile_speed[100];
    static float partile_size[100];
    static float partile_radius[100];
    static float partile_rotate[100];

    for (int i = 1; i < 60; i++)
    {
        if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
        {
            partile_pos[i].x = rand() % (int)screen_size.x + 1;
            partile_pos[i].y = -15.f;
            partile_speed[i] = 1 + rand() % 25;
            partile_radius[i] = rand() % 4;
            partile_size[i] = rand() % 3;

            partile_target_pos[i].x = rand() % (int)screen_size.x;
            partile_target_pos[i].y = screen_size.y * 2;
        }

        partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));
        partile_rotate[i] += ImGui::GetIO().DeltaTime;

        if (partile_pos[i].y > screen_size.y)
        {
            partile_pos[i].x = 0;
            partile_pos[i].y = 0;
            partile_rotate[i] = 0;
        }

        ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_size[i] + 1.f, ImGui::GetColorU32(c::accent), 20);
        ImGui::GetWindowDrawList()->AddShadowCircle(partile_pos[i], 6.f, ImGui::GetColorU32(c::accent), 40.f + partile_size[i], ImVec2(0, 0), 0, 20);
    }
}


void Particles1()
{
    ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

    static ImVec2 partile_pos[100];
    static ImVec2 partile_target_pos[100];
    static float partile_speed[100];
    static float partile_size[100];
    static float partile_radius[100];
    static float partile_rotate[100];
    static ImU32 partile_color[100];

    for (int i = 1; i < 60; i++)
    {
        // ---- Initialisation ----
        if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
        {
            partile_pos[i].x = rand() % (int)screen_size.x + 1;
            partile_pos[i].y = -15.f;
            partile_speed[i] = 1 + rand() % 25;
            partile_radius[i] = 0.5f + (rand() % 10) / 10.f;   // glow intensity
            partile_size[i] = 4 + rand() % 8;                  // triangle size (radius)

            partile_target_pos[i].x = rand() % (int)screen_size.x;
            partile_target_pos[i].y = screen_size.y * 2;

            // Slight colour variation from your accent colour
            ImVec4 base = c::accent;
            float hue_shift = (rand() % 100 - 50) / 100.f * 0.2f;
            ImVec4 col = ImVec4(
                ImClamp(base.x + hue_shift, 0.f, 1.f),
                ImClamp(base.y + hue_shift, 0.f, 1.f),
                ImClamp(base.z + hue_shift, 0.f, 1.f),
                base.w
            );
            partile_color[i] = ImGui::GetColorU32(col);
        }

        // ---- Movement ----
        partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i],
            ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));
        partile_rotate[i] += ImGui::GetIO().DeltaTime * 2.0f; // spin speed

        if (partile_pos[i].y > screen_size.y)
        {
            partile_pos[i].x = 0;
            partile_pos[i].y = 0;
            partile_rotate[i] = 0;
            continue;
        }

        // ---- Drawing: Triangle with glow layers ----
        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 pos = partile_pos[i];
        float size = partile_size[i] * partile_radius[i]; // intensity affects size
        float angle = partile_rotate[i];
        ImU32 color = partile_color[i];

        // Helper to get a triangle vertex (equilateral, centred on pos)
        auto vertex = [&](float offset_angle, float scale) -> ImVec2 {
            float a = angle + offset_angle;
            return ImVec2(pos.x + size * scale * cosf(a), pos.y + size * scale * sinf(a));
            };

        // Glow layers: [scale, alpha]
        struct Layer { float scale; float alpha; };
        Layer layers[3] = {
            {1.0f, 1.0f},   // core
            {2.2f, 0.35f},  // mid glow
            {4.5f, 0.08f}   // outer soft glow
        };

        for (int l = 0; l < 3; l++)
        {
            float s = layers[l].scale;
            float a = layers[l].alpha;

            ImVec2 p1 = vertex(0.0f, s);          // 0°
            ImVec2 p2 = vertex(2.094f, s);        // 120°
            ImVec2 p3 = vertex(4.188f, s);        // 240°

            ImVec4 col4 = ImGui::ColorConvertU32ToFloat4(color);
            col4.w *= a;
            ImU32 tri_col = ImGui::GetColorU32(col4);
            draw->AddTriangleFilled(p1, p2, p3, tri_col);
        }

        // Optional tiny white-hot centre for extra pop
        float core_scale = 0.3f;
        ImVec2 cp1 = vertex(0.0f, core_scale);
        ImVec2 cp2 = vertex(2.094f, core_scale);
        ImVec2 cp3 = vertex(4.188f, core_scale);
        draw->AddTriangleFilled(cp1, cp2, cp3, IM_COL32(255, 255, 255, 180));
    }
}

void Destroy_ParticlesV()
{
    static ImVec2 partile_pos[100];
    static ImVec2 partile_target_pos[100];
    static float partile_speed[100];
    static float partile_size[100];
    static float partile_radius[100];
    static float partile_rotate[100];

    // Reset all particles by setting their position to (0,0)
    // This triggers reinitialization in your ParticlesV() loop
    for (int i = 0; i < 100; i++)  // Note: include index 0 as well
    {
        partile_pos[i] = ImVec2(0, 0);
        partile_target_pos[i] = ImVec2(0, 0);
        partile_speed[i] = 0.0f;
        partile_size[i] = 0.0f;
        partile_radius[i] = 0.0f;
        partile_rotate[i] = 0.0f;
    }
}

void DrawMouseDot()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* dl = ImGui::GetForegroundDrawList();

    static ImVec2 dotPos = ImVec2(0.f, 0.f);
    ImVec2 mouse = io.MousePos;

    // Smooth follow speed
    float speed = 18.0f;
    dotPos.x = ImLerp(dotPos.x, mouse.x, io.DeltaTime * speed);
    dotPos.y = ImLerp(dotPos.y, mouse.y, io.DeltaTime * speed);

    float radius = 4.5f;

    // Shadow
    dl->AddCircleFilled(dotPos + ImVec2(1, 1),
        radius + 2.0f,
        ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.35f)),
        24);

    // Glow (accent color)
    dl->AddCircleFilled(dotPos,
        radius + 3.5f,
        ImGui::GetColorU32(ImVec4(c::accent.x, c::accent.y, c::accent.z, 0.18f)),
        24);

    // Main dot
    dl->AddCircleFilled(dotPos,
        radius,
        ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.95f)),
        24);
}

void AnimatedCaption(const std::vector<std::string>& captions, ImVec2 center_pos)
{
    auto draw = ImGui::GetWindowDrawList();

    static int current_index = 0;
    static float timer = 0.0f;
    static float display_duration = 2.5f;
    static float randomize_duration = 1.5f;

    static std::string display_text;
    static std::vector<char> char_states;

    static bool resolving = false;
    static bool waiting = false;

    ImGuiIO& io = ImGui::GetIO();
    timer += io.DeltaTime;

    std::string& target = const_cast<std::string&>(captions[current_index]);

    if (display_text.empty() || target.length() != display_text.length())
    {
        display_text = std::string(target.length(), ' ');
        char_states = std::vector<char>(target.length(), 0);
    }

    float t = timer / (resolving ? display_duration : randomize_duration);
    t = ImClamp(t, 0.0f, 1.0f);
    float curve_speed = resolving ? (1.0f - t) : t;
    curve_speed = powf(curve_speed, 2.0f);
    float rand_chance = 1.0f - curve_speed * 0.9f;

    if (!waiting)
    {
        for (size_t i = 0; i < target.length(); ++i)
        {
            if (target[i] == ' ')
            {
                display_text[i] = ' ';
                continue;
            }

            if (!resolving)
            {
                if (ImGui::GetIO().Framerate > 0.0f && ((rand() % 100) / 100.0f < curve_speed))
                    display_text[i] = (char)('A' + (rand() % 26));
            }
            else if (char_states[i] == 0)
            {
                if ((rand() / (float)RAND_MAX) < rand_chance)
                    display_text[i] = (char)('A' + (rand() % 26));

                if ((rand() % 100) < 10)
                {
                    display_text[i] = target[i];
                    char_states[i] = 1;
                }
            }
        }
    }

    if (!resolving && timer >= randomize_duration)
    {
        resolving = true;
        timer = 0.0f;
    }
    else if (resolving && timer >= display_duration)
    {
        waiting = true;
        timer = 0.0f;
    }
    else if (waiting && timer >= 1.0f)
    {
        current_index = (current_index + 1) % captions.size();
        display_text.clear();
        char_states.clear();
        resolving = false;
        waiting = false;
        timer = 0.0f;
    }


    ImGui::PushFont(font::lexend_regular);

    ImVec2 text_size = ImGui::CalcTextSize(display_text.c_str());
    ImVec2 pos = center_pos - ImVec2(text_size.x / 2.0f, 0.0f);

    draw->AddText(pos, ImGui::GetColorU32(c::white, 0.4f), display_text.c_str());
    ImGui::PopFont();

    ImGui::Dummy(ImVec2(0, text_size.y + 10));
}

std::string FormatExpiryDate(const std::string& expiryString) {
    time_t expiryTimestamp = static_cast<time_t>(std::stoll(expiryString));
    std::tm* tmPtr = std::gmtime(&expiryTimestamp);
    std::ostringstream oss;
    oss << std::put_time(tmPtr, "%Y-%m-%d");
    return oss.str();
}


void RenderBlur(HWND hwnd)
{
    struct ACCENTPOLICY
    {
        int na;
        int nf;
        int nc;
        int nA;
    };
    struct WINCOMPATTRDATA
    {
        int na;
        PVOID pd;
        ULONG ul;
    };

    const HINSTANCE hm = LoadLibrary("user32.dll");
    if (hm)
    {
        typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

        const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute)
        {
            ACCENTPOLICY policy = { 3, 0, 0, 0 };

            WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
            SetWindowCompositionAttribute(hwnd, &data);
        }
        FreeLibrary(hm);
    }
}

void move_window() {
    ImGui::SetCursorPos(ImVec2(0, 0));
    if (ImGui::InvisibleButton("Move_detector", ImVec2(c::background::size.x, c::background::size.y)));
    if (ImGui::IsItemActive()) {

        GetWindowRect(hwnd, &rc);
        MoveWindow(hwnd, rc.left + ImGui::GetMouseDragDelta().x, rc.top + ImGui::GetMouseDragDelta().y, c::background::size.x, c::background::size.y, TRUE);
    }
}

void move_window2() {
    ImGui::SetCursorPos(ImVec2(0, 0));
    if (ImGui::InvisibleButton("Move_detector", ImVec2(c::background::size2.x, c::background::size2.y)));
    if (ImGui::IsItemActive()) {

        GetWindowRect(hwnd, &rc);
        MoveWindow(hwnd, rc.left + ImGui::GetMouseDragDelta().x, rc.top + ImGui::GetMouseDragDelta().y, c::background::size2.x, c::background::size2.y, TRUE);
    }
}



LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void ToggleClickability(bool clickable);

std::string GetUsername() {
    TCHAR usernamedx[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserName(usernamedx, &username_len)) {
#ifdef UNICODE
        std::wstring wstr(usernamedx);
        return std::string(wstr.begin(), wstr.end());
#else
        return std::string(usernamedx);
#endif
    }
    else {
        return "Unknown";
    }
}

void RunCommandHidden(const std::string& command)
{
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    std::string fullCmd = "cmd.exe /C " + command;

    if (CreateProcessA(nullptr, &fullCmd[0], nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

std::future<void> RunCommandAsync(const std::string& command) {
    return std::async(std::launch::async, [command]() {
        RunCommandHidden(command);
        });
}

std::chrono::milliseconds ToMilliseconds(float fakelag2)
{
    return std::chrono::milliseconds(static_cast<int>(std::round(fakelag2 * 1000.0f)));
}

void PauseNetwork()
{
    std::vector<std::string> paths = {
        R"(C:\Program Files\BlueStacks_nxt\HD-Player.exe)",
        R"(C:\ProgramData\BlueStacks_msi5\HD-Player.exe)",
        R"(C:\Program Files\BlueStacks\HD-Player.exe)",
        R"(C:\Program Files\BlueStacks_msi2\Bluestacks.exe)",
        R"(C:\Program Files\BlueStacks_msi2\HD-Player.exe)"
    };

    std::vector<std::future<void>> tasks;
    int i = 0;
    for (const auto& path : paths)
    {
        std::string name = "TempBlock" + std::to_string(++i);
        tasks.push_back(RunCommandAsync("netsh advfirewall firewall add rule name=\"" + name + "\" dir=in action=block profile=any program=\"" + path + "\""));
        tasks.push_back(RunCommandAsync("netsh advfirewall firewall add rule name=\"" + name + "\" dir=out action=block profile=any program=\"" + path + "\""));
    }

    for (auto& t : tasks)
        t.wait();
}

void ResumeNetwork()
{
    std::vector<std::string> paths = {
        R"(C:\Program Files\BlueStacks_nxt\HD-Player.exe)",
        R"(C:\ProgramData\BlueStacks_msi5\HD-Player.exe)",
        R"(C:\Program Files\BlueStacks\HD-Player.exe)",
        R"(C:\Program Files\BlueStacks_msi2\HD-Player.exe)"
    };

    std::vector<std::future<void>> tasks;
    for (const auto& path : paths)
    {
        tasks.push_back(RunCommandAsync("netsh advfirewall firewall delete rule name=all program=\"" + path + "\""));
    }

    for (auto& t : tasks)
        t.wait();
}




