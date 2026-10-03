#define IMGUI_DEFINE_MATH_OPERATORS

#include "main.h"




// Esp Line
#include "ESP/ESP LINES/Offset.hpp"
#include "ESP/ESP LINES/Unity.hh"
#include "ESP/ESP LINES/ADBZapi.hpp"
#include <examples/example_win32_directx11/ESP/ESP LINES/Complementos.h>
#include "ESP/MinHook/include/MinHook.h"
#include "Particles/AnimVector.h"
#include "Chams/Visuals.h"

#include "FakeLag/windivert.h"
#include "FakeLag/FakeLag.h"
#include "FakeLag/AimLag.h"


#include "MemoryF.h"
#include <chrono>
#include <cstdio>

// Global Variables
int lastEntitiesCount = 0;
bool matchStarted = false;
bool timerFinished = false;
std::chrono::steady_clock::time_point matchStartTime;

// DrawTextGlow Function Definition
void DrawTextGlow(ImDrawList* drawList, ImVec2 pos, ImU32 textColor, ImU32 glowColor, const char* text)
{
    if (!drawList || !text) return;

    drawList->AddText(ImVec2(pos.x - 1, pos.y), glowColor, text);
    drawList->AddText(ImVec2(pos.x + 1, pos.y), glowColor, text);
    drawList->AddText(ImVec2(pos.x, pos.y - 1), glowColor, text);
    drawList->AddText(ImVec2(pos.x, pos.y + 1), glowColor, text);

    drawList->AddText(pos, textColor, text);
}





Memory MemoryFastInject;


static float SilentPower = 1.0f;
static int aim_head;
bool LOGSPANEL = true;
bool LOGSFAKELAG = false;
bool EspRadar360 = false;
bool SilentHook = false;
bool SilentHookG = false;
float FovAll = 500;
int DistanceAll = 300;
int FovRage = 500;
static float aimvisibleStrengthhh = 0.8f;
bool ESPArmas = false;
static DWORD levitationStartTime = 0;
static DWORD descendStartTime = 0;
static float floatingY = 0.0f;
static Vector3 targetPosition;
static bool isTeleporting = false;
static bool isLevitating = false;
static bool isDescending = false;
static int aim_neck;
static int aim_drag;
static int fakelag_key;
static int streamer_mode;
bool beginmark = true;
bool SilentAim = false;
bool CustomCrosshairType = false;
bool CustomCrosshair = false;

int AimLagkey = 0;

int FlyHackinkey = 0;
int flykey1 = 0;
int frwardPlayerkey = 0;

int FlyHackin1key = 0;
static int show_hide_menu_key;

bool EspTimerEnabled = false;
bool PullPlayer = false;
bool AimForceEnabled = false;
int AimForceType = 0;
int teleportmarkkey = 0;
int AimForceFireCooldownMs = 100;
bool AimForceIgnoreKnocked = true;

int selectedTargetBone = 0; // 0 = Head, 1 = Chest
static bool isToggleKeyPressed = false; // Debounce Check සඳහ

int tpkey = 0;
int dwkey = 0;

bool DownPlayerEnable = false;
bool AutoFire = false;
bool pullene = false;
bool pulleneRISK = false;
bool pullenesiper = false;
namespace edited { extern const char* keys[]; }

static int silent_combo;
const char* silent_list[] = { "180", "360" };

struct SilentTarget {
    uint32_t entity = 0;
    Vector3 headPosition;
    float screenDistance = FLT_MAX;
};

float speedMultiplier = 2.5f;

float smoothFactorX = 0.90f;
float smoothFactorY = 0.90f;
float maxSpeedX = 1.5f;
float maxSpeedY = 1.5f;
bool RgbMode = false;
static bool AimShowFovCircle = false;
float fovThickness = 1.0f;
float fovThicknessAimbot = 1.0f;
float fovRadius = 60.0f;
float fovRadiusAimbot = 10.0f; 
static bool LineRunning = true;
static bool DotRunning = false;
static bool TriangleRunning = false;

bool SpeedTimerEnable;

static bool spawnKill = false;

namespace texture
{
    ID3D11ShaderResourceView* logo = nullptr;
}

static float fakelag2 = 2.0f;

int page = 0;

static float tab_alpha = 0.f;   static float tab_add;   static int active_tab = 0;

std::string btn_txt = "Login";

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;


int Tptaworekey = 0;
bool Tptawore = false;
bool done = false;
bool fake_lag;
static bool streammode = false;

bool authed = false;

bool TeleportMarkEnable = false;
int TeleportMarkEnablekey = 0;


ImFont* InterSemiBold = nullptr;
bool chams1 = false;
bool chams2 = false;

bool aimbotpro2 = false;
bool fuckwukong = false;
bool clearesp = false;
bool glow11 = false;
int key7777 = 0;
int key777 = 0;
bool TpBaseCheck = false;
namespace var
{
    bool chams1;
    bool chams2;
}

int slider3 = 0;
void SpeedInject() {

    MemoryFastInject.EnablesSX("Speed", 0x0L, 0x00007fffffffffff, "", "", "Speed");
};


int FlyWall;
int WallHack;
int CamarDerecha;
ImVec4 boxColornormalv1 = ImVec4(25 / 255.f, 215 / 255.f, 130 / 255.f, 1.0f);
ImVec4 boxColornormalv2 = ImVec4(25 / 255.f, 215 / 255.f, 130 / 255.f, 1.0f);
ImVec4 distanciaColor = ImVec4(1.f, 1.f, 1.f, 0.6f);

void LoginManual()
{

    std::string KeyAuth_USER_user_str(KeyAuth_USER_user_char);
    std::string KeyAuth_USER_pass_str(KeyAuth_USER_pass_char);


    std::string KeyAuth_login_URL =
        "https://prod.keyauth.com/api/1.3/?type=login&username=" + KeyAuth_USER_user_str +
        "&pass=" + KeyAuth_USER_pass_str +
        "&hwid=" + KeyAuth_USER_HWID +
        "&sessionid=" + KeyAuth_sessionid +
        "&name=" + name + "&ownerid=" + ownerid;


    wrap::Response r1 = wrap::HttpsRequest(wrap::Url{ KeyAuth_login_URL.c_str() }, wrap::Method{ "POST" });

    json data1;
    try {
        data1 = json::parse(r1.text);
    }
    catch (...) {
        notificationSystem.AddNotification("Error", "Failed to parse response JSON!", ImGui::GetColorU32(c::accent));
        authed = false;
        btn_txt = "Login";
        return;
    }


    KeyAuth_message = data1.value("message", "Not Found");

    if (data1.contains("info") && data1["info"].contains("subscriptions") && !data1["info"]["subscriptions"].empty()) {
        KeyAuth_expiry = data1["info"]["subscriptions"][0].value("expiry", "0");
    }
    else {
        KeyAuth_expiry = "0";
    }


    if (KeyAuth_message == "Logged in!") {

        notificationSystem.AddNotification("Success", "Successfully Logged In!", ImGui::GetColorU32(c::accent));
        SaveCredentials(KeyAuth_USER_user_char, KeyAuth_USER_pass_char);
        authed = true;
        LOGSPANEL = true;
        btn_txt = "Login";


        std::time_t currentTime = std::time(0);
        std::time_t expiryTime = std::atoi(KeyAuth_expiry.c_str());


        std::string usernameDisplay = "User: " + KeyAuth_USER_user_str;
        std::string expiryDisplay = "Expiry: " + FormatExpiryDate(KeyAuth_expiry);;

        static char usernameBuf[64];
        static char expiryBuf[64];
        strncpy(usernameBuf, usernameDisplay.c_str(), sizeof(usernameBuf));
        strncpy(expiryBuf, expiryDisplay.c_str(), sizeof(expiryBuf));

        DiscordEventHandlers handle;
        memset(&handle, 0, sizeof(handle));
        Discord_Initialize("1371392284440006656", &handle, 1, NULL);

        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.details = usernameBuf;
        discordPresence.state = expiryBuf;
        discordPresence.startTimestamp = currentTime;
        discordPresence.largeImageKey = "https://i.ibb.co/qL3XJb2P/Chat-GPT-Image-May-5-2025-11-09-07-PM.png";
        discordPresence.largeImageText = "KIRA ";
        discordPresence.smallImageKey = "https://i.gifer.com/3OWpa.gif";
        discordPresence.button1_label = "KIRA ";
        discordPresence.button1_url = "https://discord.gg/eUW7fBpzt";
        discordPresence.button2_label = "Join Discord";
        discordPresence.button2_url = "https://discord.gg/KwpMmGZhR";

        Discord_UpdatePresence(&discordPresence);
    }
    else {

        notificationSystem.AddNotification("Failed", "Authentication Failed!", ImGui::GetColorU32(c::accent));
        authed = false;
        btn_txt = "Login";
    }


    std::cout << "Message: " << KeyAuth_message << std::endl;
    std::cout << "Expiry: " << KeyAuth_expiry << std::endl;
}

ImFont* FindFontForChar(ImWchar c) {
    if (font::noto_reg->FindGlyphNoFallback(c)) return font::noto_reg;
    if (font::noto_korean->FindGlyphNoFallback(c)) return font::noto_korean;
    if (font::noto_khmer->FindGlyphNoFallback(c)) return font::noto_khmer;
    if (font::noto_arabic->FindGlyphNoFallback(c)) return font::noto_arabic;
    if (font::noto_devanagari->FindGlyphNoFallback(c)) return font::noto_devanagari;
    if (font::noto_sinhala->FindGlyphNoFallback(c)) return font::noto_sinhala;
    if (font::noto_tamil->FindGlyphNoFallback(c)) return font::noto_tamil;
    if (font::noto_thai->FindGlyphNoFallback(c)) return font::noto_thai;
    if (font::noto_symbols2->FindGlyphNoFallback(c)) return font::noto_symbols2;
    if (font::unifont->FindGlyphNoFallback(c)) return font::unifont;
    return font::noto_reg;
}



float GetDistance(ImVec2 a, ImVec2 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}


struct SearchData {
    DWORD pid;
    HWND resultHwnd = nullptr;
};

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
    char title[256];
    GetWindowTextA(hWnd, title, sizeof(title));
    std::string windowTitle(title);
    if (windowTitle == "HD-Player" || windowTitle == "_ctl.Window") {
        SearchData* data = reinterpret_cast<SearchData*>(lParam);
        data->resultHwnd = hWnd;
        return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK EnumTopLevelProc(HWND hWnd, LPARAM lParam) {
    SearchData* data = reinterpret_cast<SearchData*>(lParam);
    DWORD windowPid = 0;
    GetWindowThreadProcessId(hWnd, &windowPid);
    if (windowPid == data->pid) {
        EnumChildWindows(hWnd, EnumChildProc, lParam);
        if (data->resultHwnd != nullptr)
            return FALSE;
    }
    return TRUE;
}

HWND zGetHwndBsEx()
{
    DWORD pid = GetProcZ("Bluestacks.exe");
    if (pid == 0)
    {
        pid = GetCurrentProcessId();
    }

    SearchData data;
    data.pid = pid;
    EnumWindows(EnumTopLevelProc, reinterpret_cast<LPARAM>(&data));
    return data.resultHwnd;
}






bool CheckSilentTargetValid(uint32_t entityAddr, uint32_t localPlayer, Vector3 cameraPos, Matrix4x4 viewMatrix, int screenWidth, int screenHeight, Vector3& outHeadPos) {
    if (entityAddr == 0 || entityAddr == localPlayer) return false;

    bool isVisible = false, isTeam = false, isDead = false, isKnocked = false;
    uint32_t avatarManager = 0, avatar = 0, avatarData = 0;

    if (ReadZ(entityAddr + Offsets::AvatarManager, avatarManager) &&
        ReadZ(avatarManager + Offsets::Avatar, avatar) &&
        ReadZ(avatar + Offsets::Avatar_Data, avatarData)) {
        ReadZ(avatar + Offsets::Avatar_IsVisible, isVisible);
        ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam);
    }

    ReadZ(entityAddr + Offsets::Player_IsDead, isDead);

    uint32_t shadowBase = 0;
    if (ReadZ(entityAddr + Offsets::Player_ShadowBase, shadowBase) && shadowBase != 0) {
        int pose;
        if (ReadZ(shadowBase + Offsets::XPose, pose) && ReadZ(shadowBase + Offsets::XPose, pose) && pose == 8)
            isKnocked = true;
    }

    if (isKnocked || isDead || !isVisible || isTeam) return false;

    uint32_t headBone = 0;
    if (!ReadZ(entityAddr + Offsets::Bones::Head, headBone) || headBone == 0) return false;

    Vector3 headWorld = {};
    if (!GetNodePosition(headBone, headWorld)) return false;

    float distance3D = Vector3::Distance(cameraPos, headWorld);
    if (distance3D > DistanceAll || distance3D < 1.0f) return false;

    ImVec2 head2D = WorldToScreenImVec2(viewMatrix, headWorld, screenWidth, screenHeight);
    if (head2D.x == -1 && head2D.y == -1) return false;

    ImVec2 screenCenter = ImVec2(screenWidth / 2.0f, screenHeight / 2.0f);
    float distToCrosshair = GetDistance(head2D, screenCenter);

    if (silent_combo != 1) {
        if (head2D.x < 0 || head2D.x > screenWidth || head2D.y < 0 || head2D.y > screenHeight) return false;
        if (distToCrosshair > FovRage) return false;
    }

    outHeadPos = headWorld;
    return true;
}

SilentTarget FindBestSilentTarget(uint32_t localPlayer, Vector3 cameraPos, Matrix4x4 viewMatrix, uint32_t entities, uint32_t count, int screenWidth, int screenHeight) {
    SilentTarget bestTarget;
    bestTarget.screenDistance = FLT_MAX;

    ImVec2 screenCenter = ImVec2(screenWidth / 2.0f, screenHeight / 2.0f);

    uint32_t maxCheck = (count > 50) ? 50 : count;

    for (uint32_t i = 0; i < maxCheck; ++i) {
        uint32_t entityAddr = 0;
        if (!ReadZ(entities + i * 4, entityAddr) || entityAddr == 0)
            continue;

        Vector3 headPos;
        if (!CheckSilentTargetValid(entityAddr, localPlayer, cameraPos, viewMatrix, screenWidth, screenHeight, headPos))
            continue;

        ImVec2 head2D = WorldToScreenImVec2(viewMatrix, headPos, screenWidth, screenHeight);
        float distToCrosshair = GetDistance(head2D, screenCenter);

        if (distToCrosshair < bestTarget.screenDistance) {
            bestTarget.entity = entityAddr;
            bestTarget.headPosition = headPos;
            bestTarget.screenDistance = distToCrosshair;
        }
    }

    return bestTarget;
}


void DoSilentAim(uint32_t localPlayer, const Vector3& targetHead)
{
    uint32_t weaponInstance = 0;
    if (!ReadZ(localPlayer + Offsets::sAim2, weaponInstance) || weaponInstance == 0)
        return;

    Vector3 fireStart;
    if (!ReadZ(weaponInstance + Offsets::sAim3, fireStart))
        return;

    Vector3 aimDir = targetHead - fireStart;

    if (std::isnan(aimDir.X) || std::isnan(aimDir.Y) || std::isnan(aimDir.Z) ||
        std::isinf(aimDir.X) || std::isinf(aimDir.Y) || std::isinf(aimDir.Z))
        return;

    float magnitude = std::sqrt(aimDir.X * aimDir.X + aimDir.Y * aimDir.Y + aimDir.Z * aimDir.Z);
    if (magnitude < 0.1f || magnitude > 20000.0f)
        return;

    aimDir.X /= magnitude;
    aimDir.Y /= magnitude;
    aimDir.Z /= magnitude;

    // Multiply by a very large number for maximum power and instant hit
    aimDir = aimDir * (SilentPower * 1000.0f);

    // Reliable write loop (adjusted to 500 for performance/reliability balance)
    for (int i = 0; i < 500; ++i) {
        WriteZ<Vector3>(weaponInstance + Offsets::sAim4, aimDir);
    }
}

namespace SilentAimLoop {
    static std::atomic<bool> running{ false };
    static std::atomic<bool> hasTarget{ false };
    static Vector3 targetHeadPos = Vector3::Zero();
    static uint32_t cachedLocalPlayer = 0;
    static std::thread workerThread;

    static void StartLoop() {
        if (running.load()) return;

        running.store(true);
        workerThread = std::thread([] {
            while (running.load()) {
                if (!hasTarget.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }

                uint32_t lp = cachedLocalPlayer;
                if (lp == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }

                bool canShoot = false;
                if (!ReadZ(lp + Offsets::sAim1, canShoot)) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }

                if (!canShoot) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }

                Vector3 currentTarget = targetHeadPos;
                DoSilentAim(lp, currentTarget);

                std::this_thread::yield();
            }
            });
    }

    static void StopLoop() {
        running.store(false);
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }

    static void UpdateTarget(uint32_t localPlayer, const Vector3& headPos, bool active) {
        cachedLocalPlayer = localPlayer;
        targetHeadPos = headPos;
        hasTarget.store(active);
    }
}





HWND InjectADB()
{
    bool adbinject = true;
    if (!adbinject)
        return NULL;

    auto vmm = GetModuleHandleA("BstkVMM.dll");
    if (vmm == nullptr) return NULL;

    auto readFunc = (PGMPhysReadFunc)GetProcAddress(vmm, "PGMPhysRead");
    if (readFunc == nullptr) return NULL;

    MH_Initialize();
    if (MH_CreateHook((LPVOID)readFunc, HookedPGMPhysRead, (LPVOID*)&ogPhysRead) != MH_OK) return NULL;
    if (MH_EnableHook((LPVOID)readFunc) != MH_OK) return NULL;

    while (vmPtr == nullptr) Sleep(10);

    ogCPU = (VMMGetCpuByIdFunc)GetProcAddress(vmm, "VMMGetCpuById");
    if (ogCPU == nullptr) return NULL;

    ogCast = (PGMPhysGCPtr2GCPhysFunc)GetProcAddress(vmm, "PGMPhysGCPtr2GCPhys");
    if (ogCast == nullptr) return NULL;

    ogWrite = (PGMPhysSimpleWriteGCPhysFunc)GetProcAddress(vmm, "PGMPhysSimpleWriteGCPhys");
    if (ogWrite == nullptr) return NULL;

    InitializeZ(vmPtr);
    std::cout << "-: Virt MemoryZ : " << pVMAddr << std::endl;

    bool GetDir = CambiarDirectoryZ(GetExeDirectoryZ());
    if (!GetDir)
        MessageBox(NULL, "Error Get Dir Emulator", "Error", NULL);

    KillAdbZ();
    ComdADBZ("kill-server");
    ComdADBZ("devices");

    std::string il2cppStr = ShellGetAddressNoSuZ("cat /proc/$(pidof com.dts.freefiremax)/maps | grep libil2cpp.so ; cat /proc/$(pidof com.dts.freefireth)/maps | grep libil2cpp.so ; cat /proc/$(pidof com.dts.freefireindia)/maps | grep libil2cpp.so");
    if (il2cppStr.empty())
        MessageBox(NULL, "Error Get Il2cpp Emulator", "Error", NULL);

    Offsets::Il2Cpp = uIntExtrZ(il2cppStr);
    if (Offsets::Il2Cpp == 0)
        MessageBox(NULL, "Error Get Il2cpp Panel", "Error", NULL);

    Sleep(100);

    KillProcessByD7("HD-Adb.exe");
    KillProcessByD7("BstkSVC.exe");

    std::string EmulatorDet = "NULL";
    HWND HwndEmul = NULL;
    // Add LDPlayer and 3LAX support
    HwndEmul = FindWindow(NULL, "LDPlayer"); // LDPlayer
    if (HwndEmul == NULL) HwndEmul = FindWindow(NULL, "LDPlayerNet");
    if (HwndEmul == NULL) HwndEmul = FindWindow(NULL, "3LAX"); // 3LAX emulator
    if (HwndEmul == NULL) HwndEmul = FindWindow(NULL, "BlueStacks App Player"); //BS5
    if (HwndEmul == NULL)
    {
        HwndEmul = FindWindow(NULL, "MSI App Player"); //MSI5
        if (HwndEmul == NULL)
        {
            HwndEmul = FindWindow(NULL, "BlueStacks"); //BS4
            if (HwndEmul == NULL)
            {
                HwndEmul = FindWindow(NULL, "App Player"); //MSI4
                if (HwndEmul == NULL)
                {
                    HwndEmul = FindWindow(NULL, "MSIZ"); //MSIZ
                    if (HwndEmul == NULL)
                    {
                        HwndEmul = FindWindow(NULL, "e4vX Bs4"); // New window
                        if (HwndEmul != NULL)
                            EmulatorDet = "e4vX Bs4";
                    }
                    else
                    {
                        EmulatorDet = "MSIZ";
                    }
                }
                else
                {
                    EmulatorDet = "MSI 4";
                }
            }
            else
            {
                EmulatorDet = "BlueStacks 4";
            }
        }
        else
        {
            EmulatorDet = "MSI 5";
        }
    }
    else
    {
        EmulatorDet = "BlueStacks 5";
    }
    if (HwndEmul == NULL) {
        MessageBox(NULL, "No supported emulator window found (BlueStacks/MSI/LDPlayer/3LAX)", "ADB Error", MB_OK | MB_ICONERROR);
        return NULL;
    }

    HWND hdPlayerWindow = FindHDPlayerWindow(HwndEmul);


    notificationSystem.AddNotification("Notification", "adb Activado ", ImGui::GetColorU32(c::accent));


    NEXUSV1 = true;

    return hdPlayerWindow;
}



void MANAS()
{

    if (FirstStart == true)
    {

        wrap::Response r = wrap::HttpsRequest(wrap::Url{ KeyAuth_init_URL }, wrap::Method{ "POST" });
        KeyAuth_init_URL;

        json data = json::parse(r.text);
        KeyAuth_message = data.value("message", "Not Found");
        KeyAuth_sessionid = data.value("sessionid", "Not Found");
        if (KeyAuth_message != "Initialized")
        {

            authed = false;
            LOGSPANEL = true;
        }


        FirstStart = false;

    }

    int width2 = GetSystemMetrics(SM_CXSCREEN);
    int height2 = GetSystemMetrics(SM_CYSCREEN);

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = nullptr;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = L"ImGui";
    wc.lpszClassName = L"Example";
    checkDebugPort();
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
    ::RegisterClassExW(&wc);

    hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED,
        wc.lpszClassName, L" ",
        WS_POPUP,
        0, 0, width2, height2,
        nullptr, nullptr, wc.hInstance, nullptr
    );



    SetWindowLongA(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | ~WS_EX_TRANSPARENT);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);

    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);


    POINT mouse;
    RECT rc = { 0 };


    GetWindowRect(hwnd, &rc);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    static ImWchar font_range[] = { 0x0020, 0x10FFFF, 0 };

    ImFontConfig cfg;
    cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;
    cfg.OversampleH = 2;
    cfg.OversampleV = 1;
    cfg.PixelSnapH = true;


    cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;

    io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof PoppinsRegular, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::hoverfront = io.Fonts->AddFontFromMemoryTTF(&Hover, sizeof Hover, 85, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::Regzfront = io.Fonts->AddFontFromMemoryTTF(&Regz, sizeof Regz, 59, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::Kenzofront = io.Fonts->AddFontFromMemoryTTF(&Kenzo, sizeof Kenzo, 54, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::primary_font = io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof PoppinsRegular, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::second_font = io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof(PoppinsRegular), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::icon_font = io.Fonts->AddFontFromMemoryTTF(&ico_moon, sizeof(ico_moon), 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::DARK = io.Fonts->AddFontFromMemoryTTF(DARK, sizeof(DARK), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    font::lexend_general_bold = io.Fonts->AddFontFromMemoryTTF(lexend_bold, sizeof(lexend_bold), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_general_bold2 = io.Fonts->AddFontFromMemoryTTF(lexend_bold2, sizeof(lexend_bold2), 30.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_bold = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_regular = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 14.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::picomoon = io.Fonts->AddFontFromMemoryTTF(picomoon, sizeof(picomoon), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    font::Nevan = io.Fonts->AddFontFromMemoryTTF(Nevan, sizeof(Nevan), 40.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::ContiB = io.Fonts->AddFontFromMemoryTTF(continuum_bold, sizeof(continuum_bold), 39.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::ContiM = io.Fonts->AddFontFromMemoryTTF(continuum_medium, sizeof(continuum_medium), 45.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    ImFont* ContiM2 = io.Fonts->AddFontFromMemoryTTF(continuum_medium, sizeof(continuum_medium), 32.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::tab_font = io.Fonts->AddFontFromMemoryTTF(continuum_medium, sizeof(continuum_medium), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    font::icomoon_widget = io.Fonts->AddFontFromMemoryTTF(icomoon_widget, sizeof(icomoon_widget), 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon_widget2 = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 16.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icon_font2 = io.Fonts->AddFontFromMemoryTTF(&icomoon2, sizeof icomoon2, 35, NULL, io.Fonts->GetGlyphRangesCyrillic());

    








    D3DX11_IMAGE_LOAD_INFO info;
    ID3DX11ThreadPump* pump{ nullptr };
    if (texture::logo == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo, sizeof(logo), &info, pump, &texture::logo, 0);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);



    while (!done)
    {

        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done) break;

        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();

        static int opacity = 255;
        static bool hide = false;

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            hide = !hide;
            isClickable = !isClickable;
            ToggleClickability(isClickable);

            // Menu eka open weddi saha hide weddi wenas beep sounds enna:
            if (!hide)
            {
                Beep(800, 100); // Menu eka show weddi (High pitch - frequency: 800Hz, duration: 100ms)
            }
            else
            {
                Beep(500, 100); // Menu eka hide weddi (Low pitch - frequency: 500Hz, duration: 100ms)
            }
        }


        if (GetAsyncKeyState(FreezeLagKey) & 0x1)
        {
            FreezeHR = !FreezeHR;
            {
                Beep(FreezeHR ? 1500 : 800, 100);
            }

            if (FreezeHR)
            {
                CreateThread(NULL, 0, FakeFreezeHR, NULL, 0, NULL);
                // MemoryLogs = "Freeze Lag - Enable !";
                notificationSystem.AddNotification("Enable", "Fake Freeze Lag!", ImGui::GetColorU32(c::accent));
                // ImGui::Notification({ ImGuiToastType_Success, 4000, MemoryLogs.c_str() });
            }
            else
            {
                // MemoryLogs = "Freeze Lag - Disable !";
                notificationSystem.AddNotification("Disable", "Fake Freeze Lag!", ImGui::GetColorU32(c::accent));
            }
        }

        if (GetAsyncKeyState(GhostHackKey) & 0x1)
        {
            GhostLagHR = !GhostLagHR;
            {
                Beep(FreezeHR ? 1500 : 800, 100);
            }

            if (GhostLagHR)
            {
                CreateThread(NULL, 0, FakeHR, NULL, 0, NULL);
                //MemoryLogs = "Ghost Hack - Enable !";
                notificationSystem.AddNotification("Enable", "Ghost Hack!", ImGui::GetColorU32(c::accent));
                // ImGui::Notification({ ImGuiToastType_Success, 4000, MemoryLogs.c_str() });
            }
            else
            {
                // MemoryLogs = "Ghost Hack - Enable !";
                notificationSystem.AddNotification("Disable", "Ghost Hack!", ImGui::GetColorU32(c::accent));
                // ImGui::Notification({ ImGuiToastType_Success, 4000, MemoryLogs.c_str() });
            }
        }
        if (GetAsyncKeyState(AimLagkey) & 0x1)
        {
            AimLagHR = !AimLagHR;
            {
                Beep(FreezeHR ? 1500 : 800, 100);
            }

            if (AimLagHR)
            {
                CreateThread(NULL, 0, FakeHR, NULL, 0, NULL);
                //MemoryLogs = "Ghost Hack - Enable !";
                notificationSystem.AddNotification("Enable", "Aim lag!", ImGui::GetColorU32(c::accent));
                // ImGui::Notification({ ImGuiToastType_Success, 4000, MemoryLogs.c_str() });
            }
            else
            {
                // MemoryLogs = "Ghost Hack - Enable !";
                notificationSystem.AddNotification("Disable", "Aim lag!", ImGui::GetColorU32(c::accent));
                // ImGui::Notification({ ImGuiToastType_Success, 4000, MemoryLogs.c_str() });
            }
        }

        if (GetAsyncKeyState(streamer_mode) & 1)
        {
            streammode = !streammode;

            HWND hwnd = GetActiveWindow();

            if (streammode)
            {
                notificationSystem.AddNotification("Done", "Stream Mode Enabled!", ImGui::GetColorU32(c::accent));

                SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);

                ITaskbarList* pTaskList = nullptr;
                CoInitialize(nullptr);
                if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList)))
                {
                    pTaskList->DeleteTab(hwnd);
                    pTaskList->Release();
                }
                CoUninitialize();
            }
            else
            {
                notificationSystem.AddNotification("Done", "Stream Mode Disabled!", ImGui::GetColorU32(c::accent));

                SetWindowDisplayAffinity(hwnd, WDA_NONE);

                ITaskbarList* pTaskList = nullptr;
                CoInitialize(nullptr);
                if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList)))
                {
                    pTaskList->AddTab(hwnd);
                    pTaskList->Release();
                }
                CoUninitialize();
            }
        }

        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            exit(0);
        }

        static bool isKeyPressed = false;

        if ((GetAsyncKeyState(fakelag_key) & 0x8000) && fakelag2 > 0)
        {
            if (!isKeyPressed && fake_lag)
            {
                isKeyPressed = true;
                std::thread([]
                    {
                        Beep(444, 500);
                        auto start = std::chrono::steady_clock::now();

                        PauseNetwork();

                        auto elapsed = std::chrono::steady_clock::now() - start;
                        auto delay = ToMilliseconds(fakelag2);

                        auto remaining = delay - std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);

                        if (remaining.count() > 0)
                            std::this_thread::sleep_for(remaining);

                        ResumeNetwork();
                        Beep(666, 470);
                    }).detach();
            }
        }
        else isKeyPressed = false;

        static bool wasKeyDown1 = false;
        if (GetAsyncKeyState(SpeedKey) & 0x8000)
        {
            if (!wasKeyDown1)
            {
                SpeedEnable = !SpeedEnable;

                if (SpeedEnable)
                {
                    std::thread([]() {
                        std::thread(SpeedInject).detach();
                        }).detach();
                }
                else
                {
                    std::thread([]() {
                        std::thread(SpeedInject).detach();
                        }).detach();
                }

                wasKeyDown1 = true;
            }
        }
        else
        {
            wasKeyDown1 = false;
        }

        ImGui::NewFrame();
        {

            // ─── Lightning/Spark Data Structure ───
            struct LightningEffect {
                ImVec2 start;
                ImVec2 end;
                float spawnTime;
                float duration;
            };

            // ─── MOVING "KENZO REGZ" WATERMARK WITH HIGH-QUALITY TEXT & EFFECTS ───
            if (beginmark && NEXUSV1)
            {
                ImVec2 screenSize = ImGui::GetIO().DisplaySize;

                // ─── Variables ───
                static ImVec2 pos = ImVec2(100.0f, 100.0f);
                static ImVec2 dir = ImVec2(1.0f, 1.0f);
                static bool initialized = false;
                static std::vector<LightningEffect> lightnings;

                if (!initialized)
                {
                    pos = ImVec2(screenSize.x * 0.3f, screenSize.y * 0.3f);
                    initialized = true;
                }

                // ─── Speed & Scale Control ───
                float speed = 1.0f;
                const char* wmText = "</> KENZO & INDU";

                // High quality display scale calculation
                float fontScale = 0.95f;
                ImVec2 textSize = ImGui::CalcTextSize(wmText);
                textSize.x *= fontScale;
                textSize.y *= fontScale;

                // Current Time
                float currentTime = (float)ImGui::GetTime();

                // ─── Movement Logic & Collision Detection ───
                pos.x += dir.x * speed;
                pos.y += dir.y * speed;

                bool bounced = false;
                ImVec2 hitPoint = pos;

                // Horizontal Bounce (X Boundary)
                if (pos.x <= 10.0f)
                {
                    dir.x *= -1.0f;
                    pos.x = 10.0f;
                    hitPoint = ImVec2(10.0f, pos.y + textSize.y * 0.5f);
                    bounced = true;
                }
                else if (pos.x + textSize.x >= screenSize.x - 10.0f)
                {
                    dir.x *= -1.0f;
                    pos.x = screenSize.x - 10.0f - textSize.x;
                    hitPoint = ImVec2(screenSize.x - 10.0f, pos.y + textSize.y * 0.5f);
                    bounced = true;
                }

                // Vertical Bounce (Y Boundary)
                if (pos.y <= 10.0f)
                {
                    dir.y *= -1.0f;
                    pos.y = 10.0f;
                    hitPoint = ImVec2(pos.x + textSize.x * 0.5f, 10.0f);
                    bounced = true;
                }
                else if (pos.y + textSize.y >= screenSize.y - 10.0f)
                {
                    dir.y *= -1.0f;
                    pos.y = screenSize.y - 10.0f - textSize.y;
                    hitPoint = ImVec2(pos.x + textSize.x * 0.5f, screenSize.y - 10.0f);
                    bounced = true;
                }

                // ⚡ 1. Spawn Boundary Lightning ⚡
                if (bounced)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        float offsetX = ((rand() % 80) - 40) * 1.0f;
                        float offsetY = ((rand() % 80) - 40) * 1.0f;

                        LightningEffect light;
                        light.start = hitPoint;
                        light.end = ImVec2(hitPoint.x + offsetX, hitPoint.y + offsetY);
                        light.spawnTime = currentTime;
                        light.duration = 0.25f;

                        lightnings.push_back(light);
                    }
                }

                // ⚡ 2. Spawn Continuous Micro-Sparks Around Text ⚡
                if ((rand() % 100) < 35) // Controlled spark rate for clean look
                {
                    float randomX = pos.x + ((rand() % (int)(textSize.x > 1.0f ? textSize.x : 1.0f)));
                    float randomY = pos.y + ((rand() % (int)(textSize.y > 1.0f ? textSize.y : 1.0f)));

                    float lengthX = ((rand() % 24) - 12) * 1.0f;
                    float lengthY = ((rand() % 24) - 12) * 1.0f;

                    LightningEffect spark;
                    spark.start = ImVec2(randomX, randomY);
                    spark.end = ImVec2(randomX + lengthX, randomY + lengthY);
                    spark.spawnTime = currentTime;
                    spark.duration = 0.10f;

                    lightnings.push_back(spark);
                }

                // Fullscreen Overlay Window
                ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
                ImGui::SetNextWindowSize(screenSize);
                ImGui::SetNextWindowBgAlpha(0.0f);

                ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration |
                    ImGuiWindowFlags_NoInputs |
                    ImGuiWindowFlags_NoNav |
                    ImGuiWindowFlags_NoFocusOnAppearing |
                    ImGuiWindowFlags_NoBringToFrontOnFocus;

                ImGui::Begin("##KenzoRegzMovingWatermark", nullptr, flags);
                ImDrawList* drawList = ImGui::GetWindowDrawList();

                // ⚡ Render & Update All Lightning Effects ⚡
                for (auto it = lightnings.begin(); it != lightnings.end(); )
                {
                    float elapsed = currentTime - it->spawnTime;
                    if (elapsed > it->duration)
                    {
                        it = lightnings.erase(it);
                    }
                    else
                    {
                        float alpha = 1.0f - (elapsed / it->duration);
                        ImU32 lightningColor = IM_COL32(230, 248, 255, (int)(alpha * 255));
                        ImU32 glowColor = IM_COL32(0, 162, 255, (int)(alpha * 140));

                        ImVec2 mid = ImVec2((it->start.x + it->end.x) * 0.5f, (it->start.y + it->end.y) * 0.5f);
                        mid.x += ((rand() % 10) - 5);
                        mid.y += ((rand() % 10) - 5);

                        drawList->AddLine(it->start, mid, glowColor, 2.0f);
                        drawList->AddLine(mid, it->end, glowColor, 2.0f);

                        drawList->AddLine(it->start, mid, lightningColor, 1.0f);
                        drawList->AddLine(mid, it->end, lightningColor, 1.0f);

                        ++it;
                    }
                }

                // 🔹 High Quality Text Color Configurations
                ImU32 textColor = IM_COL32(255, 255, 255, 255);            // pure crisp white
                ImU32 textSubtleGlow = IM_COL32(180, 220, 255, 30);         // clean electric tint glow
                ImU32 crispShadow = IM_COL32(0, 0, 0, 120);                 // dark background contrast outline for sharp edges
                ImU32 whiteShadowSoft = IM_COL32(255, 255, 255, 45);        // faint ambient white glow

                float fontSize = ImGui::GetFontSize() * fontScale;

                // ─── High Quality Layering Pipeline ───

                // 1. Dark Edge Contrast Line (නම Blur නොවී Sharp ව කැපී පෙනීමට)
                drawList->AddText(ImGui::GetFont(), fontSize, pos + ImVec2(1.0f, 1.0f), crispShadow, wmText);
                drawList->AddText(ImGui::GetFont(), fontSize, pos + ImVec2(-1.0f, -1.0f), crispShadow, wmText);

                // 2. Soft Ambient White Outer Glow
                drawList->AddText(ImGui::GetFont(), fontSize, pos + ImVec2(-2.0f, 0.0f), textSubtleGlow, wmText);
                drawList->AddText(ImGui::GetFont(), fontSize, pos + ImVec2(2.0f, 0.0f), textSubtleGlow, wmText);
                drawList->AddText(ImGui::GetFont(), fontSize, pos + ImVec2(0.0f, -2.0f), textSubtleGlow, wmText);
                drawList->AddText(ImGui::GetFont(), fontSize, pos + ImVec2(0.0f, 2.0f), textSubtleGlow, wmText);

                // 3. Subtle White Drop Offset
                drawList->AddText(ImGui::GetFont(), fontSize, pos + ImVec2(1.0f, 1.0f), whiteShadowSoft, wmText);

                // 4. Main Ultra-Sharp White Text
                drawList->AddText(ImGui::GetFont(), fontSize, pos, textColor, wmText);

                ImGui::End();
            }


            //if (beginmark && NEXUSV1)
            //{
            //    // 1. Match State Detection
            //    bool isInMatch = (hdPlayerWindow != nullptr);

            //    static float g_startTime = 0.0f;
            //    static bool  g_wasInMatch = false;

            //    float currentTime = ImGui::GetTime();

            //    if (isInMatch && !g_wasInMatch)
            //    {
            //        g_startTime = currentTime;
            //        g_wasInMatch = true;
            //    }
            //    else if (!isInMatch && g_wasInMatch)
            //    {
            //        g_wasInMatch = false;
            //    }

            //    float elapsedTime = isInMatch ? (currentTime - g_startTime) : 0.0f;
            //    float remainingTime = 180.0f - elapsedTime;
            //    if (remainingTime < 0.0f) remainingTime = 0.0f;

            //    if (isInMatch && ImGui::IsKeyPressed(ImGuiKey_F12))
            //    {
            //        g_startTime = currentTime;
            //    }

            //    // Dynamic Accent Colors (RGB Effect)
            //    float r = (sinf(currentTime * 2.0f) * 0.5f) + 0.5f;
            //    float g = (sinf(currentTime * 2.0f + 2.0f) * 0.5f) + 0.5f;
            //    float b = (sinf(currentTime * 2.0f + 4.0f) * 0.5f) + 0.5f;
            //    ImU32 dynamicAccentColor = ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, 1.0f));

            //    // Overlay Window Settings
            //    ImVec2 overlaySize = ImVec2(220.0f, 320.0f);
            //    static ImVec2 g_overlayPos = ImVec2(20.0f, 100.0f);
            //    static bool   g_overlayInitialized = false;

            //    if (!g_overlayInitialized)
            //    {
            //        g_overlayPos = ImVec2(20.0f, 100.0f);
            //        g_overlayInitialized = true;
            //    }

            //    ImGui::SetNextWindowPos(g_overlayPos, ImGuiCond_Always);
            //    ImGui::SetNextWindowSize(overlaySize);
            //    ImGui::SetNextWindowBgAlpha(0.65f); // Semi-transparent glass style background

            //    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
            //    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.2f);
            //    ImGui::PushStyleColor(ImGuiCol_Border, dynamicAccentColor);
            //    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.08f, 0.12f, 0.75f));

            //    ImGui::Begin("KENZO REGZ", nullptr,
            //        ImGuiWindowFlags_NoDecoration |
            //        ImGuiWindowFlags_NoFocusOnAppearing |
            //        ImGuiWindowFlags_NoNav);

            //    ImDrawList* drawList = ImGui::GetWindowDrawList();
            //    ImVec2 pos = ImGui::GetWindowPos();

            //    // ── Header Section ──
            //    ImGui::SetWindowFontScale(0.95f);
            //    ImGui::SetCursorPos(ImVec2(10.0f, 8.0f));
            //    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "  KENZO REGZ");

            //    // Dynamic Underline
            //    drawList->AddLine(ImVec2(pos.x + 10, pos.y + 28), ImVec2(pos.x + overlaySize.x - 10, pos.y + 28), dynamicAccentColor, 1.5f);

            //    // ── Feature Row Items Helper ──
            //    auto DrawFeatureRow = [&](const char* icon, const char* label, const char* bind, bool enabled, float yPos)
            //        {
            //            ImGui::SetCursorPos(ImVec2(12.0f, yPos));

            //            // Icon
            //            ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "%s", icon);
            //            ImGui::SameLine(30.0f);

            //            // Feature Label
            //            ImGui::TextColored(ImVec4(0.9f, 0.9f, 0.9f, 1.0f), "%s", label);

            //            // Keybind Text (if applicable)
            //            if (bind && strlen(bind) > 0)
            //            {
            //                ImGui::SameLine();
            //                ImGui::TextColored(ImVec4(0.2f, 0.7f, 0.9f, 0.8f), "[%s]", bind);
            //            }

            //            // Status Circle Indicator (Green = ON, Red = OFF)
            //            ImVec2 indicatorCenter = ImVec2(pos.x + overlaySize.x - 20.0f, pos.y + yPos + 8.0f);
            //            ImU32 indicatorColor = enabled ? IM_COL32(0, 255, 100, 255) : IM_COL32(255, 50, 50, 255);

            //            drawList->AddCircleFilled(indicatorCenter, 4.5f, indicatorColor);
            //            if (enabled)
            //            {
            //                drawList->AddCircle(indicatorCenter, 6.0f, IM_COL32(0, 255, 100, 150), 12, 1.0f);
            //            }
            //        };

            //    // ── Feature List ──
            //    ImGui::SetWindowFontScale(0.82f);

            //    // Example Toggle Variables (Replace with your own cheat states)
            //    static bool bHookStatus = true;
            //    static bool coverhit = true;
            //    static bool dwkey = false;
            //    static bool bOscarX = false;
            //    static bool bTpWall = false;
            //    static bool bTelekill = false;
            //    static bool bGhostLag = false;
            //    static bool bTeleportMap = false;
            //    static bool bSpeedHack = true;

            //    DrawFeatureRow("*", "Hook Status", "", bHookStatus, 36.0f);
            //    DrawFeatureRow("*", "Force On Aim", "", coverhit, 58.0f);
            //    DrawFeatureRow("*", "Dive Kill", "M5", dwkey, 80.0f);
            //    DrawFeatureRow("*", "Oscar X Inf", "Q", bOscarX, 102.0f);
            //    DrawFeatureRow("*", "Tp Wall", "None", bTpWall, 124.0f);
            //    DrawFeatureRow("*", "Telekill Infinity", "None", bTelekill, 146.0f);
            //    DrawFeatureRow("*", "Ghost Lag", "None", bGhostLag, 168.0f);
            //    DrawFeatureRow("*", "Teleport Map", "None", bTeleportMap, 190.0f);
            //    DrawFeatureRow("*", "Speed Hack", "", bSpeedHack, 212.0f);

            //    // ── Bottom Footer Section ──
            //    drawList->AddLine(ImVec2(pos.x + 10, pos.y + 285), ImVec2(pos.x + overlaySize.x - 10, pos.y + 285), IM_COL32(100, 100, 100, 150), 1.0f);

            //    ImGui::SetCursorPos(ImVec2(12.0f, 292.0f));
            //    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Players: 4 | Bots: 0");

            //    // ── Draggable Window Handling ──
            //    ImGui::SetCursorPos(ImVec2(0, 0));
            //    ImGui::InvisibleButton("overlay_drag_area", overlaySize);
            //    if (!hide && ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            //    {
            //        g_overlayPos = g_overlayPos + ImGui::GetIO().MouseDelta;
            //        ImGui::SetWindowPos(g_overlayPos);
            //    }

            //    ImGui::End();
            //    ImGui::PopStyleColor(2);
            //    ImGui::PopStyleVar(2);
            //}

            if (NEXUSV1)
            {
                RECT rect;
                GetWindowRect(hdPlayerWindow, &rect);
                int x = rect.left;
                int y = rect.top;
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;
                Vector2 screenCenter = Vector2(x + width / 2, y + height / 2);

                uint32_t baseGameFacade = 0;
                ReadZ(Offsets::Il2Cpp + Offsets::InitBase, baseGameFacade);

                uint32_t gameFacade = 0;
                ReadZ(baseGameFacade, gameFacade);

                uint32_t staticGameFacade = 0;
                ReadZ(gameFacade + Offsets::StaticClass, staticGameFacade);

                uint32_t currentGame = 0;
                ReadZ(staticGameFacade, currentGame);

                uint32_t currentMatch = 0;
                ReadZ(currentGame + Offsets::CurrentMatch, currentMatch);

                uint32_t matchStatus = 0;
                ReadZ(currentMatch + Offsets::MatchStatus, matchStatus);

                uint32_t localPlayer = 0;
                if (ReadZ(currentMatch + Offsets::LocalPlayer, localPlayer)) {}

                uint32_t mainTransform = 0;
                ReadZ(localPlayer + Offsets::MainCameraTransform, mainTransform);

                Vector3 mainPos;
                GetPosition(mainTransform, mainPos);

                uint32_t followCamera = 0;
                ReadZ(localPlayer + Offsets::FollowCamera, followCamera);

                uint32_t camera = 0;
                ReadZ(followCamera + Offsets::Camera, camera);

                uint32_t cameraBase = 0;
                ReadZ(camera + 0x8, cameraBase);

                Matrix4x4 viewMatrix;
                ReadZ(cameraBase + Offsets::ViewMatrix, viewMatrix);

                // ---- Teleport Mark ----
                if (teleportmap && localPlayer != 0) {
                    uint32_t markGame = 0;
                    if (ReadZ(staticGameFacade, markGame)) {
                        uint32_t UIInGameScene = 0;
                        if (ReadZ(markGame + 0x8, UIInGameScene)) {
                            uint32_t m_BigMapCtrl = 0;
                            if (ReadZ(UIInGameScene + 0x218, m_BigMapCtrl)) {
                                uint32_t m_MapContentCtrl = 0;
                                if (ReadZ(m_BigMapCtrl + 0x54, m_MapContentCtrl)) {
                                    uint32_t m_LocalMapMarkController = 0;
                                    if (ReadZ(m_MapContentCtrl + 0x90, m_LocalMapMarkController)) {
                                        Vector3 markPos;
                                        if (ReadZ(m_LocalMapMarkController + 0x58, markPos)) {
                                            if (markPos != Vector3::Zero()) {
                                                if (!isLevitating && !isTeleporting && !isDescending) {
                                                    targetPosition = markPos;
                                                    isLevitating = true;
                                                    isTeleporting = true;
                                                    levitationStartTime = GetTickCount();
                                                    floatingY = 0.0f;
                                                }
                                            }
                                            if (isLevitating && isTeleporting) {
                                                DWORD elapsed = GetTickCount() - levitationStartTime;
                                                if (elapsed < 1000) {
                                                    uint32_t localRootBonePtr = 0;
                                                    if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr)) {
                                                        uint32_t localTransformValue = 0;
                                                        if (ReadZ(localRootBonePtr + 0x8, localTransformValue)) {
                                                            uint32_t localTransformObjPtr = 0;
                                                            if (ReadZ(localTransformValue + 0x8, localTransformObjPtr)) {
                                                                uint32_t localMatrixValue = 0;
                                                                if (ReadZ(localTransformObjPtr + 0x20, localMatrixValue)) {
                                                                    Vector3 newPos = targetPosition;
                                                                    if (floatingY == 0.0f) floatingY = targetPosition.Y + 5.0f;
                                                                    newPos.Y = floatingY;
                                                                    WriteZ<Vector3>(localMatrixValue + 0x60, newPos);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                else {
                                                    isLevitating = false;
                                                    isTeleporting = false;
                                                    isDescending = true;
                                                    descendStartTime = GetTickCount();
                                                }
                                            }
                                            else if (isDescending) {
                                                DWORD elapsed = GetTickCount() - descendStartTime;
                                                if (elapsed < 500) {
                                                    uint32_t localRootBonePtr = 0;
                                                    if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr)) {
                                                        uint32_t localTransformValue = 0;
                                                        if (ReadZ(localRootBonePtr + 0x8, localTransformValue)) {
                                                            uint32_t localTransformObjPtr = 0;
                                                            if (ReadZ(localTransformValue + 0x8, localTransformObjPtr)) {
                                                                uint32_t localMatrixValue = 0;
                                                                if (ReadZ(localTransformObjPtr + 0x20, localMatrixValue)) {
                                                                    WriteZ<Vector3>(localMatrixValue + 0x60, targetPosition);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                else {
                                                    isDescending = false;
                                                    floatingY = 0.0f;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                uint32_t entityDictionary = 0;
                ReadZ(currentGame + Offsets::DictionaryEntities, entityDictionary);

                uint32_t entities = 0;
                ReadZ(entityDictionary + 0xc, entities);
                entities += 0x1c;

                uint32_t entitiesCount = 0;
                ReadZ(entityDictionary + 0x10, entitiesCount);

                // 1. localPlayer != 0 check එක ඉවත් කර ඇත (Player මැරුණත් ESP වැඩ කිරීම සඳහා)
                if (currentMatch != 0 && entitiesCount > 0 && entitiesCount < 2000)
                {
                    static HWND hwndEmulator = nullptr;
                    static ULONGLONG lastWindowCheck = 0;
                    ULONGLONG currentTime = GetTickCount64();

                    if (!hwndEmulator || (currentTime - lastWindowCheck > 2000)) {
                        const char* windowTitles[] = { "MSI App Player", "BlueStacks App Player", nullptr };
                        hwndEmulator = nullptr;
                        for (int j = 0; windowTitles[j]; j++) {
                            if ((hwndEmulator = FindWindowA(NULL, windowTitles[j]))) break;
                        }
                        lastWindowCheck = currentTime;
                    }

                    if (!hwndEmulator) return;

                    RECT clientRect, windowRect;
                    GetClientRect(hwndEmulator, &clientRect);
                    GetWindowRect(hwndEmulator, &windowRect);

                    int emulatorWidth = clientRect.right - clientRect.left;
                    int emulatorHeight = clientRect.bottom - clientRect.top;
                    int clientX = windowRect.left;
                    int clientY = windowRect.top + (windowRect.bottom - windowRect.top - emulatorHeight);

                    // ESP Timer Render (Loop එකෙන් පිටතට ගෙන ඇත - Performance සඳහා)
                    if (EspTimerEnabled)
                    {
                        static int lastBeepSecond = -1;

                        ImVec2 timerStartPoint(clientX + (emulatorWidth * 0.5f), clientY + 33.0f);
                        if (lineType == 1) timerStartPoint = ImVec2(clientX + (emulatorWidth * 0.5f), clientY + (emulatorHeight * 0.5f));
                        else if (lineType == 2) timerStartPoint = ImVec2(clientX + (emulatorWidth * 0.5f), clientY + (emulatorHeight - 20.0f));

                        if (entitiesCount < lastEntitiesCount)
                        {
                            matchStarted = false;
                            timerFinished = false;
                            lastBeepSecond = -1;
                        }

                        if (entitiesCount > 1 && !matchStarted)
                        {
                            matchStartTime = std::chrono::steady_clock::now();
                            matchStarted = true;
                            timerFinished = false;
                            lastBeepSecond = -1;
                        }

                        lastEntitiesCount = entitiesCount;

                        if (matchStarted)
                        {
                            auto now = std::chrono::steady_clock::now();
                            int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - matchStartTime).count();
                            int remaining = 180 - elapsed;

                            if (remaining <= 3 && remaining > 0 && remaining != lastBeepSecond)
                            {
                                lastBeepSecond = remaining;
                                std::thread([]() { Beep(800, 100); }).detach();
                            }

                            char timerText[16];
                            if (remaining <= 0)
                            {
                                remaining = 0;
                                timerFinished = true;
                                snprintf(timerText, sizeof(timerText), "Ready");
                            }
                            else
                            {
                                int minutes = remaining / 60;
                                int seconds = remaining % 60;
                                snprintf(timerText, sizeof(timerText), "%02d:%02d", minutes, seconds);
                            }

                            ImVec2 ts = ImGui::CalcTextSize(timerText);
                            float padX = 8.0f;
                            float padY = 4.0f;

                            ImVec2 boxMin(timerStartPoint.x - (ts.x * 0.5f) - padX, timerStartPoint.y - (ts.y * 0.5f) - padY);
                            ImVec2 boxMax(timerStartPoint.x + (ts.x * 0.5f) + padX, timerStartPoint.y + (ts.y * 0.5f) + padY);
                            ImVec2 textPos(timerStartPoint.x - (ts.x * 0.5f), timerStartPoint.y - (ts.y * 0.5f));

                            auto vListTimer = ImGui::GetForegroundDrawList();
                            vListTimer->AddRectFilled(boxMin, boxMax, IM_COL32(15, 15, 15, 220), 4.0f);
                            ImU32 borderColor = timerFinished ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 165, 0, 255);
                            vListTimer->AddRect(boxMin, boxMax, borderColor, 4.0f, 0, 1.5f);

                            ImU32 textColor = timerFinished ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 255, 255, 255);
                            vListTimer->AddText(textPos, textColor, timerText);
                        }
                    }

                    for (uint32_t i = 0; i < entitiesCount; i++)
                    {
                        bool isDead = false, IsKnown = false, IsTeam = false, isVisible = false, isBot = false;
                        int EspHealthInt = 0;
                        float DistanceA = 0.0f, rectWidth = 150.0f, rectHeight = 30.0f;

                        uint32_t entity = 0;
                        if (!ReadZ(entities + i * 0x10, entity) || !entity) continue;

                        if (localPlayer != 0 && entity == localPlayer) continue;

                        if (ReadZ(entity + Offsets::Player_IsDead, isDead) && isDead) continue;

                        uint32_t avatarManager = 0;
                        if (!ReadZ(entity + Offsets::AvatarManager, avatarManager) || !avatarManager) continue;

                        uint32_t avatar = 0;
                        if (!ReadZ(avatarManager + Offsets::Avatar, avatar) || !avatar) continue;
                        if (!ReadZ(avatar + Offsets::Avatar_IsVisible, isVisible)) continue;

                        uint32_t avatarData = 0;
                        if (!ReadZ(avatar + Offsets::Avatar_Data, avatarData) || !avatarData) continue;

                        bool isTeam = false;
                        if (ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam)) {
                            IsTeam = isTeam;
                            IsKnown = !isTeam;
                        }

                        ReadZ(entity + Offsets::isBotOffs, isBot);

                        struct BonePositions {
                            Vector3 HeadV3, RootV3, LeftWristV3, SpineV3, HipV3,
                                RightCalfV3, LeftCalfV3, RightFootV3, LeftFootV3,
                                RightWristV3, LeftHandV3, LeftShoulderV3, RightShoulderV3,
                                RightWristJointV3, LeftWristJointV3, LeftElbowV3, RightElbowV3;
                        } bonePositions;

                        std::vector<std::pair<uint32_t, Vector3*>> bones = {
                            {Offsets::Bones::Head,           &bonePositions.HeadV3},
                            {Offsets::Bones::Root,           &bonePositions.RootV3},
                            {Offsets::Bones::LeftWrist,      &bonePositions.LeftWristV3},
                            {Offsets::Bones::Neck,           &bonePositions.SpineV3},
                            {Offsets::Bones::Hip,            &bonePositions.HipV3},
                            {Offsets::Bones::RightFoot,      &bonePositions.RightFootV3},
                            {Offsets::Bones::LeftFoot,       &bonePositions.LeftFootV3},
                            {Offsets::Bones::RightWrist,     &bonePositions.RightWristV3},
                            {Offsets::Bones::LeftHand,       &bonePositions.LeftHandV3},
                            {Offsets::Bones::LeftShoulder,   &bonePositions.LeftShoulderV3},
                            {Offsets::Bones::RightShoulder,  &bonePositions.RightShoulderV3},
                            {Offsets::Bones::LeftElbow,      &bonePositions.LeftElbowV3},
                            {Offsets::Bones::RightElbow,     &bonePositions.RightElbowV3}
                        };

                        for (const auto& [boneID, bonePos] : bones) {
                            uint32_t bone = 0;
                            if (ReadZ(entity + boneID, bone) && bone) GetNodePosition(bone, *bonePos);
                        }

                        DistanceA = Vector3::Distance(mainPos, bonePositions.HeadV3);
                        if (DistanceA > maxDistance) continue;

                        if (SHowVis == false && !isVisible) continue;

                        auto headScreenPos = WorldToScreenImVec2(viewMatrix, bonePositions.HeadV3, width, height);
                        auto bottomScreenPos = WorldToScreenImVec2(viewMatrix, bonePositions.RootV3, width, height);

                        bool isOnScreen = (headScreenPos.x > 0 && headScreenPos.y > 0 &&
                            (x + headScreenPos.x) >= clientX && (x + headScreenPos.x) <= clientX + emulatorWidth &&
                            (y + headScreenPos.y) >= clientY && (y + headScreenPos.y) <= clientY + emulatorHeight);

                        if (!isOnScreen) continue;

                        if (ESPHealth) {
                            uint32_t dataPool = 0;
                            if (ReadZ(entity + Offsets::Player_Data, dataPool)) {
                                uint32_t poolObj = 0;
                                if (ReadZ(dataPool + 0x8, poolObj)) {
                                    uint32_t pool = 0;
                                    if (ReadZ(poolObj + 0x10, pool)) {
                                        int Health = 0;
                                        if (ReadZ(pool + 0x10, Health) && Health) EspHealthInt = Health;
                                    }
                                }
                            }
                        }

                        // Knocked (Down) status check
                        bool isKnocked = false;
                        uint32_t shadowBase = 0;
                        if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase) && shadowBase) {
                            int xpose = 0;
                            if (ReadZ(shadowBase + Offsets::XPose, xpose) && xpose == 8) isKnocked = true;
                        }

                        auto vList = ImGui::GetForegroundDrawList();
                        vList->PushClipRect(ImVec2(clientX, clientY),
                            ImVec2(clientX + emulatorWidth, clientY + emulatorHeight), true);

                        ImVec2 rectTopLeft = ImVec2(x + headScreenPos.x - rectWidth / 2, y + headScreenPos.y - rectHeight - 10);
                        ImVec2 rectBottomRight = ImVec2(x + headScreenPos.x + rectWidth / 2, y + headScreenPos.y - 10);

                        Vector2 PlayerPosHead(x + headScreenPos.x, y + headScreenPos.y);
                        Vector2 PlayerPosBott(x + bottomScreenPos.x, y + bottomScreenPos.y);
                        float CornerHeight = std::abs(PlayerPosHead.Y - PlayerPosBott.Y);
                        float CornerWidth = CornerHeight * 0.65f;

                        // -------------------------------------------------------------
                        // DRAWING ESP ELEMENTS
                        // -------------------------------------------------------------

                        // ESP Name (Down වුනොත් රතු පාටින්)
                        if (ESPNameZ)
                        {
                            uint32_t nameAddr = 0;
                            std::string strEspNameScan = "";

                            if (ReadZ(entity + Offsets::Player_Name, nameAddr) && nameAddr != 0)
                            {
                                strEspNameScan = ReadPlayerName(nameAddr);
                            }

                            strEspNameScan.erase(
                                std::remove_if(strEspNameScan.begin(), strEspNameScan.end(), [](unsigned char c) {
                                    return !std::isprint(c);
                                    }),
                                strEspNameScan.end()
                            );

                            if (strEspNameScan.empty() || strEspNameScan == "?")
                            {
                                strEspNameScan = defaultName;
                            }

                            ImVec2 textSize = ImGui::CalcTextSize(strEspNameScan.c_str());
                            float centerX = (rectTopLeft.x + rectBottomRight.x) * 0.5f;

                            ImVec2 namePos(centerX - (textSize.x * 0.5f), rectTopLeft.y - textSize.y - 2.0f);

                            ImU32 shadowColor = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
                            ImU32 mainColor = isKnocked ? IM_COL32(255, 0, 0, 255) : ImGui::GetColorU32(nameColor);

                            vList->AddText(ImVec2(namePos.x + 1.0f, namePos.y + 1.0f), shadowColor, strEspNameScan.c_str());
                            vList->AddText(namePos, mainColor, strEspNameScan.c_str());
                        }

                        // ESP Radar
                        if (EspRadar360) {
                            float radarSiceSpace = 160.0f;
                            float radarRangeSpace = 100.0f;

                            float radarSize = radarSiceSpace;
                            float radarRange = radarRangeSpace;

                            static HWND hwndEmulator = nullptr;
                            if (!hwndEmulator || !IsWindow(hwndEmulator)) {
                                hwndEmulator = hdPlayerWindow;
                            }

                            if (hwndEmulator) {
                                RECT clientRect;
                                POINT screenPos = { 0, 0 };
                                if (GetClientRect(hwndEmulator, &clientRect)) {
                                    ClientToScreen(hwndEmulator, &screenPos);

                                    int emulatorWidth = clientRect.right;
                                    int emulatorHeight = clientRect.bottom;
                                    int x = screenPos.x;
                                    int y = screenPos.y;

                                    float radarX = x + (emulatorWidth - radarSize) / 2.0f;
                                    float radarY = y + (emulatorHeight - radarSize) / 2.0f;

                                    float centerX = radarSize / 2.0f;
                                    float centerY = radarSize / 2.0f;

                                    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

                                    ImU32 crosshairColor = IM_COL32(200, 200, 200, 200);
                                    float lineLength = 7.0f;
                                    drawList->AddLine(ImVec2(radarX + centerX - lineLength, radarY + centerY),
                                        ImVec2(radarX + centerX + lineLength, radarY + centerY), crosshairColor, 2.0f);
                                    drawList->AddLine(ImVec2(radarX + centerX, radarY + centerY - lineLength),
                                        ImVec2(radarX + centerX, radarY + centerY + lineLength), crosshairColor, 2.0f);

                                    Vector3 localPlayerPos = Vector3::Zero();
                                    uint32_t boneRoot = 0;
                                    if (ReadZ(localPlayer + Offsets::Bones::Root, boneRoot)) {
                                        GetNodePosition(boneRoot, localPlayerPos);
                                    }

                                    float forwardX = viewMatrix.m02;
                                    float forwardZ = viewMatrix.m22;
                                    float playerAngle = atan2f(forwardZ, forwardX);

                                    for (int i = 0; i < entitiesCount; i++) {
                                        uint32_t entity;
                                        if (!ReadZ((uintptr_t)(i * 0x10 + entities), entity) || entity == 0 || entity == localPlayer) continue;

                                        bool isVisible = false, isTeam = false, isKnocked = false;
                                        uint32_t avatarManager, avatar, avatarData, shadowBase;

                                        if (!ReadZ(entity + Offsets::AvatarManager, avatarManager) ||
                                            !ReadZ(avatarManager + Offsets::Avatar, avatar) ||
                                            !ReadZ(avatar + Offsets::Avatar_IsVisible, isVisible) ||
                                            !ReadZ(avatar + Offsets::Avatar_Data, avatarData) ||
                                            !ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam)) {
                                            continue;
                                        }

                                        if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase)) {
                                            int xpose = 0;
                                            ReadZ(shadowBase + Offsets::XPose, xpose);
                                            if (xpose == 8) isKnocked = true;
                                        }

                                        if (isKnocked || (!SHowVis && isTeam) || (!SHowVis && !isVisible)) continue;

                                        ImU32 vidaColor = IM_COL32(255, 0, 0, 255);
                                        if (!isTeam) {
                                            uint32_t dataPool;
                                            if (ReadZ(entity + Offsets::Player_Data, dataPool)) {
                                                uint32_t poolObj;
                                                if (ReadZ(dataPool + 0x8, poolObj)) {
                                                    uint32_t pool;
                                                    if (ReadZ(poolObj + 0x10, pool)) {
                                                        int currentHealth;
                                                        if (ReadZ(pool + 0x10, currentHealth) && currentHealth > 0) {
                                                            float healthPercentage = (float)currentHealth / 200.0f;
                                                            if (healthPercentage >= 0.75f) vidaColor = IM_COL32(255, 0, 0, 255);
                                                            else if (healthPercentage >= 0.50f) vidaColor = IM_COL32(255, 0, 0, 255);
                                                            else if (healthPercentage >= 0.25f) vidaColor = IM_COL32(255, 0, 0, 255);
                                                            else vidaColor = IM_COL32(255, 0, 0, 255);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else {
                                            vidaColor = IM_COL32(0, 128, 255, 255);
                                        }

                                        Vector3 entityPos = Vector3::Zero();
                                        uint32_t boneRootEnemy = 0;
                                        if (!ReadZ(entity + Offsets::Bones::Root, boneRootEnemy)) continue;
                                        if (!GetNodePosition(boneRootEnemy, entityPos)) continue;

                                        float dx = entityPos.X - localPlayerPos.X;
                                        float dz = entityPos.Z - localPlayerPos.Z;

                                        float rotatedX = cosf(-playerAngle) * dx - sinf(-playerAngle) * dz;
                                        float rotatedZ = sinf(-playerAngle) * dx + cosf(-playerAngle) * dz;

                                        float angle = atan2f(-rotatedX, -rotatedZ);
                                        float radius = radarSize / 2.0f + 8.0f;
                                        float radarPosX = centerX + cosf(angle) * radius;
                                        float radarPosY = centerY + sinf(angle) * radius;

                                        ImVec2 center = ImVec2(radarX + radarPosX, radarY + radarPosY);

                                        float size = 13.0f;
                                        float head_height = size * 0.6f;
                                        float head_width = size * 0.65f;
                                        float tail_width = size * 0.28f;

                                        const int head_points_count = 3;
                                        ImVec2 head_points[head_points_count] =
                                        {
                                            ImVec2(0.0f, -size / 2.0f),
                                            ImVec2(head_width / 2.0f, -size / 2.0f + head_height),
                                            ImVec2(-head_width / 2.0f, -size / 2.0f + head_height)
                                        };
                                        const int tail_points_count = 4;
                                        ImVec2 tail_points[tail_points_count] =
                                        {
                                            ImVec2(-tail_width / 2.0f, -size / 2.0f + head_height),
                                            ImVec2(tail_width / 2.0f, -size / 2.0f + head_height),
                                            ImVec2(tail_width / 2.0f, size / 2.0f),
                                            ImVec2(-tail_width / 2.0f, size / 2.0f)
                                        };
                                        const int outline_points_count = 7;
                                        ImVec2 outline_points[outline_points_count] =
                                        {
                                            ImVec2(0.0f, -size / 2.0f),
                                            ImVec2(head_width / 2.0f, -size / 2.0f + head_height),
                                            ImVec2(tail_width / 2.0f, -size / 2.0f + head_height),
                                            ImVec2(tail_width / 2.0f, size / 2.0f),
                                            ImVec2(-tail_width / 2.0f, size / 2.0f),
                                            ImVec2(-tail_width / 2.0f, -size / 2.0f + head_height),
                                            ImVec2(-head_width / 2.0f, -size / 2.0f + head_height)
                                        };

                                        float correctedAngle = angle + 1.57079632679f; // PI / 2
                                        float cos_a = cosf(correctedAngle);
                                        float sin_a = sinf(correctedAngle);

                                        ImVec2 transformed_head_points[head_points_count];
                                        for (int j = 0; j < head_points_count; ++j) {
                                            float r_x = head_points[j].x * cos_a - head_points[j].y * sin_a;
                                            float r_y = head_points[j].x * sin_a + head_points[j].y * cos_a;
                                            transformed_head_points[j] = ImVec2(center.x + r_x, center.y + r_y);
                                        }
                                        ImVec2 transformed_tail_points[tail_points_count];
                                        for (int j = 0; j < tail_points_count; ++j) {
                                            float r_x = tail_points[j].x * cos_a - tail_points[j].y * sin_a;
                                            float r_y = tail_points[j].x * sin_a + tail_points[j].y * cos_a;
                                            transformed_tail_points[j] = ImVec2(center.x + r_x, center.y + r_y);
                                        }
                                        ImVec2 transformed_outline_points[outline_points_count];
                                        for (int j = 0; j < outline_points_count; ++j) {
                                            float r_x = outline_points[j].x * cos_a - outline_points[j].y * sin_a;
                                            float r_y = outline_points[j].x * sin_a + outline_points[j].y * cos_a;
                                            transformed_outline_points[j] = ImVec2(center.x + r_x, center.y + r_y);
                                        }

                                        ImU32 shadow_col = (vidaColor & 0x00FFFFFF) | (180 << 24);
                                        float brilloglow = 50.0f;
                                        ImVec2 shadow_offset = ImVec2(1.0f, 1.0f);
                                        ImDrawFlags shadow_flags = ImDrawFlags_None;
                                        ImU32 outline_color = IM_COL32(0, 0, 0, 255);
                                        float outline_thickness = 1.0f;

                                        drawList->AddShadowConvexPoly(transformed_head_points, head_points_count, shadow_col, brilloglow, shadow_offset, shadow_flags);
                                        drawList->AddShadowConvexPoly(transformed_tail_points, tail_points_count, shadow_col, brilloglow, shadow_offset, shadow_flags);

                                        drawList->AddConvexPolyFilled(transformed_head_points, head_points_count, vidaColor);
                                        drawList->AddConvexPolyFilled(transformed_tail_points, tail_points_count, vidaColor);

                                        drawList->AddPolyline(transformed_outline_points, outline_points_count, outline_color, true, outline_thickness);
                                    }
                                }
                            }
                        }

                        // ESP Box (Down වුනොත් රතු පාටින්)
                        if (ESPBox)
                        {
                            float WBox = CornerWidth;
                            float HBox = CornerHeight + 20.0f;
                            float XBox = PlayerPosHead.X - (WBox / 2);
                            float YBox = PlayerPosHead.Y - 10.0f;

                            float thickness = 1.5f;
                            float cornerSize = WBox * 0.18f;

                            ImU32 boxColorx = isKnocked ? IM_COL32(255, 0, 0, 255) : ImGui::ColorConvertFloat4ToU32(boxColor);

                            if (ESPBoxType == 0) // Cornered Box
                            {
                                vList->AddLine(ImVec2(XBox, YBox), ImVec2(XBox + cornerSize, YBox), boxColorx, thickness);
                                vList->AddLine(ImVec2(XBox, YBox), ImVec2(XBox, YBox + cornerSize), boxColorx, thickness);
                                vList->AddLine(ImVec2(XBox + WBox - cornerSize, YBox), ImVec2(XBox + WBox, YBox), boxColorx, thickness);
                                vList->AddLine(ImVec2(XBox + WBox, YBox), ImVec2(XBox + WBox, YBox + cornerSize), boxColorx, thickness);
                                vList->AddLine(ImVec2(XBox, YBox + HBox - cornerSize), ImVec2(XBox, YBox + HBox), boxColorx, thickness);
                                vList->AddLine(ImVec2(XBox, YBox + HBox), ImVec2(XBox + cornerSize, YBox + HBox), boxColorx, thickness);
                                vList->AddLine(ImVec2(XBox + WBox - cornerSize, YBox + HBox), ImVec2(XBox + WBox, YBox + HBox), boxColorx, thickness);
                                vList->AddLine(ImVec2(XBox + WBox, YBox + HBox - cornerSize), ImVec2(XBox + WBox, YBox + HBox), boxColorx, thickness);
                            }
                            else if (ESPBoxType == 1) // Full Box
                            {
                                vList->AddRect(ImVec2(XBox, YBox), ImVec2(XBox + WBox, YBox + HBox), boxColorx, 0, 0, thickness);
                            }
                        }
                        if (CustomCrosshair)
                        {
                            // Get emulator window position and size
                            RECT emulatorRect;
                            ImVec2 center;

                            if (hdPlayerWindow && IsWindow(hdPlayerWindow))
                            {
                                GetWindowRect(hdPlayerWindow, &emulatorRect);
                                int emulatorWidth = emulatorRect.right - emulatorRect.left;
                                int emulatorHeight = emulatorRect.bottom - emulatorRect.top;
                                center = ImVec2(emulatorRect.left + emulatorWidth / 2.0f, emulatorRect.top + emulatorHeight / 2.0f);
                            }
                            else
                            {
                                // Fallback to screen center if emulator not found
                                center = ImVec2(ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f);
                            }

                            ImDrawList* draw = ImGui::GetBackgroundDrawList();

                            // Clip to emulator window if it exists
                            if (hdPlayerWindow && IsWindow(hdPlayerWindow))
                            {
                                draw->PushClipRect(ImVec2(emulatorRect.left, emulatorRect.top),
                                    ImVec2(emulatorRect.right, emulatorRect.bottom), true);
                            }

                            float time = (float)ImGui::GetTime();

                            switch (CustomCrosshairType)
                            {
                            case 0: // --- Style 0: Rotating Star ---
                            {
                                float starRadius = 14.0f;
                                float innerRadius = 6.0f;
                                int points = 6;
                                float angle = time * 2.0f; // Rotation speed
                                float thickness = 2.0f;

                                ImU32 starColor = IM_COL32(180, 100, 255, 255);
                                ImU32 starGlow = IM_COL32(180, 100, 255, 80);

                                // Draw star spokes
                                for (int i = 0; i < points; i++)
                                {
                                    float a = angle + (i * 2.0f * 3.14159f / points);
                                    float cos_a = cosf(a);
                                    float sin_a = sinf(a);

                                    ImVec2 inner = center + ImVec2(cos_a * innerRadius, sin_a * innerRadius);
                                    ImVec2 outer = center + ImVec2(cos_a * starRadius, sin_a * starRadius);

                                    // Glow
                                    draw->AddLine(inner, outer, starGlow, thickness + 3.0f);
                                    // Main line
                                    draw->AddLine(inner, outer, starColor, thickness);
                                    // Bright tip
                                    draw->AddCircleFilled(outer, 2.0f, IM_COL32(220, 160, 255, 255));
                                }

                                // Outer ring rotating
                                draw->AddCircle(center, starRadius + 2.0f, IM_COL32(180, 100, 255, 60), 24, 1.0f);
                                // Center dot
                                draw->AddCircleFilled(center, 2.5f, IM_COL32(255, 255, 255, 255));
                                draw->AddShadowCircle(center, 4.0f, starColor, 12.0f, ImVec2(0, 0));
                                break;
                            }

                            case 1: // --- Style 1: Purple Glow Crosshair ---
                            {
                                float lineLen = 12.0f;
                                float gap = 4.0f;
                                float thickness = 2.5f;

                                ImU32 purpleCore = IM_COL32(180, 100, 255, 255);
                                ImU32 purpleGlow = IM_COL32(150, 60, 255, 90);
                                ImU32 outline = IM_COL32(0, 0, 0, 130);

                                // 4 directional lines: Up, Down, Left, Right
                                ImVec2 dirs[4] = { ImVec2(0, -1), ImVec2(0, 1), ImVec2(-1, 0), ImVec2(1, 0) };
                                for (int i = 0; i < 4; i++)
                                {
                                    ImVec2 d = dirs[i];
                                    ImVec2 p1 = center + ImVec2(d.x * gap, d.y * gap);
                                    ImVec2 p2 = center + ImVec2(d.x * (gap + lineLen), d.y * (gap + lineLen));

                                    // Outline shadow
                                    draw->AddLine(p1, p2, outline, thickness + 2.0f);
                                    // Glow
                                    draw->AddLine(p1, p2, purpleGlow, thickness + 4.0f);
                                    // Core line
                                    draw->AddLine(p1, p2, purpleCore, thickness);
                                }

                                // Center dot
                                draw->AddCircleFilled(center, 2.0f, IM_COL32(255, 255, 255, 255));
                                draw->AddShadowCircle(center, 5.0f, purpleCore, 15.0f, ImVec2(0, 0));
                                break;
                            }

                            case 2: // --- Style 2: Small Minimalist X ---
                            {
                                float armLen = 5.0f;
                                float gap = 2.0f;
                                float thickness = 1.8f;

                                ImU32 xColor = IM_COL32(230, 230, 230, 240);
                                ImU32 xOutline = IM_COL32(0, 0, 0, 180);

                                // 4 arms of X at 45, 135, 225, 315 degrees (static, no rotation)
                                for (int i = 0; i < 4; i++)
                                {
                                    float a = (i * 90.0f + 45.0f) * 0.0174533f;
                                    float cos_a = cosf(a);
                                    float sin_a = sinf(a);

                                    ImVec2 p1 = center + ImVec2(cos_a * gap, sin_a * gap);
                                    ImVec2 p2 = center + ImVec2(cos_a * (gap + armLen), sin_a * (gap + armLen));

                                    // Shadow outline
                                    draw->AddLine(p1, p2, xOutline, thickness + 1.5f);
                                    // Main line
                                    draw->AddLine(p1, p2, xColor, thickness);
                                }

                                // Small center dot
                                draw->AddCircleFilled(center, 1.5f, IM_COL32(255, 255, 255, 220));
                                break;
                            }
                            } // end switch

                            // Pop the clip rect if we pushed it
                            if (hdPlayerWindow && IsWindow(hdPlayerWindow))
                            {
                                draw->PopClipRect();
                            }
                        }
                        // FILLED BOX
                        if (ESPBoxFILLED)
                        {
                            float XBox = PlayerPosHead.X - (CornerWidth / 2.0f);
                            float YBox = PlayerPosHead.Y - 10.0f;
                            float WBox = CornerWidth;
                            float HBox = CornerHeight + 20.0f;
                            float rounding = 3.0f;

                            if (isKnocked) {
                                vList->AddRectFilled(ImVec2(XBox, YBox), ImVec2(XBox + WBox, YBox + HBox), IM_COL32(255, 0, 0, 80), rounding);
                            }
                            else if (rgbMode) {
                                double t = getCurrentTime();
                                float freq = 0.5f;
                                auto getRGB = [&](float off, int a) -> ImU32 {
                                    return IM_COL32(
                                        (int)(0.5f * (1.0f + sinf(6.28f * freq * (float)t + off)) * 255),
                                        (int)(0.5f * (1.0f + sinf(6.28f * freq * (float)t + off + 2.09f)) * 255),
                                        (int)(0.5f * (1.0f + sinf(6.28f * freq * (float)t + off + 4.18f)) * 255), a);
                                    };
                                vList->AddRectFilled(ImVec2(XBox, YBox), ImVec2(XBox + WBox, YBox + HBox), getRGB(0.2f, 80), rounding);
                            }
                            else {
                                ImU32 fillCol = IM_COL32(
                                    (int)(boxColorFilled.x * 255), (int)(boxColorFilled.y * 255),
                                    (int)(boxColorFilled.z * 255), 50);
                                vList->AddRectFilled(ImVec2(XBox, YBox), ImVec2(XBox + WBox, YBox + HBox), fillCol, rounding);
                            }
                        }

                        // ESP Lines (Down වුනොත් රතු පාටින්)
                        if (EspLineZ)
                        {
                            ImU32 lineColor;

                            if (isKnocked)
                            {
                                lineColor = IM_COL32(255, 0, 0, 255);
                            }
                            else if (IsTeam)
                            {
                                lineColor = ImColor(0, 255, 0, 255);
                            }
                            else
                            {
                                lineColor = ImGui::ColorConvertFloat4ToU32(lineColorEnemy);
                            }

                            ImVec2 startPoint(clientX + (emulatorWidth * 0.5f), clientY + 33.0f);
                            if (lineType == 1) startPoint = ImVec2(clientX + (emulatorWidth * 0.5f), clientY + (emulatorHeight * 0.5f));
                            else if (lineType == 2) startPoint = ImVec2(clientX + (emulatorWidth * 0.5f), clientY + (emulatorHeight - 20.0f));

                            ImVec2 enemyPos(x + headScreenPos.x, y + headScreenPos.y);
                            vList->AddLine(startPoint, enemyPos, lineColor, EsplineWidth);
                            vList->AddCircleFilled(enemyPos, EsplineWidth * 0.5f, lineColor);
                        }

                        // ESP Health Bar
                        if (ESPHealth)
                        {
                            if (!std::isnan(PlayerPosHead.X) && !std::isnan(PlayerPosHead.Y))
                            {
                                ImFont* font = InterSemiBold ? InterSemiBold : ImGui::GetFont();
                                if (font)
                                {
                                    float fontSize = font->FontSize * 0.75f;
                                    float vidaPorcentaje = std::clamp(static_cast<float>(EspHealthInt) / 200.0f, 0.0f, 1.0f);

                                    float XBox = PlayerPosHead.X - (CornerWidth / 2.0f);
                                    float YBox = PlayerPosHead.Y - 10.0f;
                                    float HBox = CornerHeight + 20.0f;

                                    DrawVerticalHealthBar(EspHealthInt, 200, ImVec2(XBox - 5.0f, YBox), HBox);

                                    char hpTxt[12];
                                    snprintf(hpTxt, sizeof(hpTxt), "%d", EspHealthInt);
                                    ImU32 tc = vidaPorcentaje <= 0.25f ? IM_COL32(255, 60, 60, 220)
                                        : vidaPorcentaje <= 0.5f ? IM_COL32(255, 215, 0, 220)
                                        : IM_COL32(255, 255, 255, 200);
                                    vList->AddText(font, fontSize, ImVec2(XBox - 0.5f, YBox + HBox + 1.0f), tc, hpTxt);
                                }
                            }
                        }

                        // ESP Distance
                        if (ESPDistance)
                        {
                            float WBox = CornerWidth;
                            float HBox = CornerHeight + 20.0f;
                            float YBox = PlayerPosHead.Y - 10.0f;

                            std::string distStr = std::to_string(static_cast<int>(DistanceA)) + "m";

                            ImFont* font = InterSemiBold ? InterSemiBold : ImGui::GetFont();
                            float fontSize = font ? (font->FontSize * 0.65f) : 10.0f;

                            ImVec2 textSize = font ? font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, distStr.c_str()) : ImGui::CalcTextSize(distStr.c_str());

                            ImVec2 distPos(
                                PlayerPosHead.X - (textSize.x * 0.5f),
                                YBox + HBox + 2.0f
                            );

                            vList->AddText(font, fontSize, ImVec2(distPos.x + 1.0f, distPos.y + 1.0f), IM_COL32(0, 0, 0, 220), distStr.c_str());
                            vList->AddText(font, fontSize, distPos, IM_COL32(255, 255, 255, 255), distStr.c_str());
                        }

                        // ESP Skeleton (Bones - Down නම් රතු, නැතහොත් සාමාන්‍ය පාට)
                        if (ESPBones)
                        {
                            auto draw = ImGui::GetBackgroundDrawList();
                            ImColor finalColor = isKnocked ? ImColor(255, 0, 0, 255) : ImColor(ImGui::GetColorU32(bonesColor));

                            auto DrawBone = [&](uint32_t offsetFrom, uint32_t offsetTo) {
                                uint32_t boneA = 0, boneB = 0;
                                Vector3 posA{}, posB{};
                                if (!ReadZ(entity + offsetFrom, boneA) || !boneA) return;
                                if (!ReadZ(entity + offsetTo, boneB) || !boneB) return;
                                if (!GetNodePosition(boneA, posA)) return;
                                if (!GetNodePosition(boneB, posB)) return;

                                auto f = WorldToScreenImVec2(viewMatrix, posA, width, height);
                                auto t = WorldToScreenImVec2(viewMatrix, posB, width, height);
                                if (f.x > 0 && f.y > 0 && t.x > 0 && t.y > 0)
                                    draw->AddLine(
                                        ImVec2(x + f.x, y + f.y),
                                        ImVec2(x + t.x, y + t.y),
                                        finalColor, boneThickness);
                                };

                            float circleSize = 3.5f * std::clamp(100.0f / DistanceA, 0.5f, 1.5f);
                            vList->AddCircle(ImVec2(x + headScreenPos.x, y + headScreenPos.y), circleSize, finalColor, 16, boneThickness);

                            DrawBone(Offsets::Bones::Head, Offsets::Bones::Neck);
                            DrawBone(Offsets::Bones::Neck, Offsets::Bones::Hip);
                            DrawBone(Offsets::Bones::Hip, Offsets::Bones::Root);
                            DrawBone(Offsets::Bones::Neck, Offsets::Bones::LeftShoulder);
                            DrawBone(Offsets::Bones::LeftShoulder, Offsets::Bones::LeftElbow);
                            DrawBone(Offsets::Bones::LeftElbow, Offsets::Bones::LeftWrist);
                            DrawBone(Offsets::Bones::Neck, Offsets::Bones::RightShoulder);
                            DrawBone(Offsets::Bones::RightShoulder, Offsets::Bones::RightElbow);
                            DrawBone(Offsets::Bones::RightElbow, Offsets::Bones::RightWrist);
                            DrawBone(Offsets::Bones::Hip, Offsets::Bones::LeftFoot);
                            DrawBone(Offsets::Bones::Hip, Offsets::Bones::RightFoot);
                        }
                    
                
                    
                
                   
                    
                
                
                    
                
                
                    
                
                    
                
                
                    
                
                    
                
















                        if (aimbotVisibleActive)
                        {
                            static bool fire;
                            ReadZ(localPlayer + 0x488, fire);

                            uint32_t bestTarget = 0;
                            float closestDistSq = FLT_MAX;
                            Vector2 screenCenter(emulatorWidth / 2.0f, emulatorHeight / 2.0f);
                            const float fovSq = 120.0f * 120.0f;
                            for (int i = 0; i < entitiesCount; ++i)
                            {
                                uint32_t entity = 0;
                                if (!ReadZ((uintptr_t)(i * 0x4 + entities), entity) || !entity) continue;
                                if (!IsValidEntity(entity)) continue;

                                bool isDead = false;
                                ReadZ(entity + Offsets::Player_IsDead, isDead);
                                if (isDead) continue;

                                uint32_t avatarManager = 0, avatar = 0;
                                bool isVisible = false, isTeam = false;

                                if (ReadZ(entity + Offsets::AvatarManager, avatarManager) && avatarManager &&
                                    ReadZ(avatarManager + Offsets::Avatar, avatar) && avatar &&
                                    ReadZ(avatar + Offsets::Avatar_IsVisible, isVisible))
                                {
                                    uint32_t avatarData;
                                    if (ReadZ(avatar + Offsets::Avatar_Data, avatarData) && avatarData)
                                    {
                                        ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam);
                                    }
                                }

                                if (isTeam || !isVisible) continue;
                                Vector3 headPos;
                                uint32_t headBone;
                                if (ReadZ(entity + Offsets::Bones::Head, headBone) && headBone) {
                                    GetNodePosition(headBone, headPos);
                                    headPos = headPos + Vector3(0, 0.05f, 0);

                                    ImVec2 head2D = WorldToScreenImVec2(viewMatrix, headPos, width, height);

                                    if (IsValidScreenPosition(ImVec2(head2D.x, head2D.y), emulatorWidth, emulatorHeight))
                                    {
                                        float dx = head2D.x - screenCenter.X;
                                        float dy = head2D.y - screenCenter.Y;
                                        float distSq = dx * dx + dy * dy;

                                        if (distSq <= fovSq && distSq < closestDistSq)
                                        {
                                            closestDistSq = distSq;
                                            bestTarget = entity;
                                        }
                                    }
                                }
                            }
                            if (bestTarget != 0)
                            {
                                uintptr_t patchAddr = bestTarget + 0x50;
                                uint32_t headCollider = 0;
                                if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
                                {
                                    if (!ReadZ(bestTarget + Offsets::HeadCollider, headCollider) || headCollider == 0)
                                        goto restore_patch;

                                    if (!isPatched)
                                    {
                                        if (!ReadZ(patchAddr, lastOriginalValue)) goto restore_patch;
                                        lastPatchedAddr = patchAddr;
                                    }

                                    WriteZ(patchAddr, headCollider);
                                    if (!isPatched) isPatched = true;
                                }
                                else
                                {
                                restore_patch:
                                    if (isPatched && lastPatchedAddr)
                                    {
                                        WriteZ(lastPatchedAddr, lastOriginalValue);
                                        isPatched = false;
                                        lastPatchedAddr = 0;
                                        lastOriginalValue = 0;
                                    }
                                }
                            }
                            else
                            {
                                if (isPatched && lastPatchedAddr)
                                {
                                    WriteZ(lastPatchedAddr, lastOriginalValue);
                                    isPatched = false;
                                    lastPatchedAddr = 0;
                                    lastOriginalValue = 0;
                                }
                            }
                        }

                        auto WIDGET = zGetInfoW(entity, ESPArmas);

                        if (ESPArmas && !IsTeam)
                        {
                            static HWND emulatorHwnd = nullptr;

                            if (!emulatorHwnd)
                            {
                                emulatorHwnd = FindWindowA(NULL, "MSI App Player");
                                if (!emulatorHwnd)
                                    emulatorHwnd = FindWindowA(NULL, "BlueStacks App Player");
                            }

                            if (!emulatorHwnd)
                                return; // مرة واحدة فقط خارج loop الرئيسي

                            RECT clientRect, windowRect;
                            GetClientRect(emulatorHwnd, &clientRect);
                            GetWindowRect(emulatorHwnd, &windowRect);

                            int width = clientRect.right;
                            int height = clientRect.bottom;
                            int x0 = windowRect.left;
                            int y0 = windowRect.bottom - height;

                            auto vList = ImGui::GetForegroundDrawList();
                            vList->PushClipRect(
                                ImVec2(x0, y0),
                                ImVec2(x0 + width, y0 + height),
                                true
                            );

                            auto WIDGET = zGetInfoW(entity, ESPArmas);
                            std::string weaponName = zGetWName(WIDGET);
                            const char* icono = zGetWIcon(WIDGET);

                            if (!weaponName.empty() && icono)
                            {
                                ImVec2 textSize = ImGui::CalcTextSize(weaponName.c_str());
                                float boxWidth = textSize.x + 20.f;

                                ImVec2 basePos(
                                    x + headScreenPos.x - boxWidth / 2.f,
                                    y + headScreenPos.y - 100.f
                                );

                                ImGui::PushFont(font::WeaponsIco);
                                vList->AddText(
                                    ImVec2(basePos.x + boxWidth / 2.f - 7.f, basePos.y),
                                    IM_COL32_WHITE,
                                    icono
                                );
                                ImGui::PopFont();

                                ImGui::PushFont(font::lexend_regular);
                                vList->AddText(
                                    ImVec2(basePos.x + (boxWidth - textSize.x) / 2.f, basePos.y + 20.f),
                                    IM_COL32_WHITE,
                                    weaponName.c_str()
                                );
                                ImGui::PopFont();
                            }

                            vList->PopClipRect();
                        }

                        
                        // FlyHack එක සක්‍රිය වන විට player උස ලොක් කර තබා ගැනීමට static variable එකක්
                        static bool isFlyActive = false;
                        static float lockedY = 0.0f;

                        if (FlyHackin)
                        {
                            uint32_t localRootBonePtr;
                            if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr))
                            {
                                Vector3 localRootPos;
                                if (GetNodePosition(localRootBonePtr, localRootPos))
                                {
                                    // Toggle වන මුල් අවස්ථාවේ පමණක් අඩි 15 (units 4.57f / 15.0f) උස එකතු කර Y-axis එක Lock කරන්න
                                    if (!isFlyActive)
                                    {
                                        // Game units අනුව අඩි 15 යනු සාමාන්‍යයෙන් 4.57f හෝ 15.0f වේ.
                                        // අවශ්‍ය පරිදි 4.57f / 15.0f මාරු කර බලන්න.
                                        lockedY = localRootPos.Y + 4.30f;
                                        isFlyActive = true;
                                    }

                                    // X සහ Z වෙනස් නොවී, Y-axis එක පමණක් lockedY හි තබයි
                                    Vector3 newPos = localRootPos;
                                    newPos.Y = lockedY;

                                    uint32_t localTransformValue;
                                    if (ReadZ(localRootBonePtr + 0x8, localTransformValue))
                                    {
                                        uint32_t localTransformObjPtr;
                                        if (ReadZ(localTransformValue + 0x8, localTransformObjPtr))
                                        {
                                            uint32_t localMatrixValue;
                                            if (ReadZ(localTransformObjPtr + 0x20, localMatrixValue))
                                            {
                                                // මීට අමතරව Gravity/Velocity එක මඟින් පහළට වැටීම වැළැක්වීමට නිරන්තරයෙන් Height එක Write කරයි
                                                WriteZ<Vector3>(localMatrixValue + 0x60, newPos);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            // FlyHack OFF කල විට Lock එක reset කරන්න
                            isFlyActive = false;
                        }
                        

                        //static Vector3 startPos;
                        //static Vector3 lastForcedPos;
                        //static bool positionSet = false;
                        //static bool wasActiveLastFrame = false;

                        //if (FlyHackin == true)
                        //{
                        //    wasActiveLastFrame = true; // OFF වෙන වෙලාව අල්ලගන්න මෙක set කරනවා

                        //    uint32_t rootPtr = 0;
                        //    if (ReadZ(localPlayer + Offsets::Bones::Root, rootPtr) && rootPtr != 0)
                        //    {
                        //        Vector3 currentPos;
                        //        if (GetNodePosition(rootPtr, currentPos))
                        //        {
                        //            // Feature එක ON කරපු ගමන් මුලින්ම ඉන්න තැන Save කරගැනීම
                        //            if (!positionSet)
                        //            {
                        //                startPos = currentPos;
                        //                positionSet = true;
                        //            }

                        //            Vector3 forcedPos = currentPos;

                        //            // 1. Uda yanne nathiwa Y height eka thaba ganeema
                        //            forcedPos.Y = startPos.Y;

                        //            // 2. Maximum 5m limit kireema
                        //            float deltaX = forcedPos.X - startPos.X;
                        //            float deltaZ = forcedPos.Z - startPos.Z;
                        //            float currentDist = sqrtf(deltaX * deltaX + deltaZ * deltaZ);

                        //            float maxDistance = 5.0f; // Max 5 Meters

                        //            if (currentDist > maxDistance)
                        //            {
                        //                float angle = atan2f(deltaZ, deltaX);
                        //                forcedPos.X = startPos.X + cosf(angle) * maxDistance;
                        //                forcedPos.Z = startPos.Z + sinf(angle) * maxDistance;
                        //            }

                        //            // Awaasana position eka save kara ganeema
                        //            lastForcedPos = forcedPos;

                        //            // Biththi atharin yata position write kireema
                        //            uint32_t t1 = 0, t2 = 0, t3 = 0;
                        //            if (ReadZ(rootPtr + 0x8, t1) && t1 != 0 &&
                        //                ReadZ(t1 + 0x8, t2) && t2 != 0 &&
                        //                ReadZ(t2 + 0x20, t3) && t3 != 0)
                        //            {
                        //                for (int i = 0; i < 50; i++)
                        //                {
                        //                    WriteZ<Vector3>(t3 + 0x60, forcedPos);
                        //                }
                        //            }
                        //        }
                        //    }
                        //}
                        //else
                        //{
                        //    // Feature එක OFF වුණු ගමන් (First Frame of OFF state)
                        //    if (wasActiveLastFrame)
                        //    {
                        //        uint32_t rootPtr = 0;
                        //        if (ReadZ(localPlayer + Offsets::Bones::Root, rootPtr) && rootPtr != 0)
                        //        {
                        //            // Player OFF වුණු තැනම නතර කිරීමට අවසාන Forced position එක main root node එකට එක පාරක් write කිරීම
                        //            uint32_t t1 = 0, t2 = 0, t3 = 0;
                        //            if (ReadZ(rootPtr + 0x8, t1) && t1 != 0 &&
                        //                ReadZ(t1 + 0x8, t2) && t2 != 0 &&
                        //                ReadZ(t2 + 0x20, t3) && t3 != 0)
                        //            {
                        //                WriteZ<Vector3>(t3 + 0x60, lastForcedPos);
                        //            }

                        //            // Player ගේ සාමාන්‍ය position vector එකටත් අලුත් තැන set කිරීම (Rubberband නොවීමට)
                        //            WriteZ<Vector3>(localPlayer + 0x130, lastForcedPos); // (Note: Oyage engine eke localPlayer pos offset eka tiyenam methanata danna)
                        //        }

                        //        wasActiveLastFrame = false; // Off logic eka run une 1i kiyala confirm kireema
                        //    }

                        //    // Reset variables for next turn ON
                        //    positionSet = false;
                        //    hasDropped = false;
                        //}




                        /*for (int i = 0; i < 400; i++)
                        {
                            WriteZ<Vector3>(t3 + 0x80, forcedPos);
                            WriteZ<Vector3>(t3 + 0x80, forcedPos);
                        }*/



                        if (camerahack && !IsTeam) {
                            uint32_t attrPtr = 0;
                            if (ReadZ(localPlayer + Offsets::FollowCamera, attrPtr)) {

                                float newSpeed = VisionHack;
                                WriteZ<float>(attrPtr + 0x44, newSpeed);
                            }
                        }
                        /* if (NoReload4) {
                             uint32_t reload;
                             if (ReadZ(localPlayer + Offsets::PlayerAttributes, reload)) {
                                 WriteZ<bool>(reload + Offsets::NoReload, true);
                             }
                         }
                        */


                        if (AimbotRage) {
                            uint32_t bestEntity = 0;
                            Vector3 bestHeadPos;
                            float closestCrosshairDistance = FLT_MAX;
                            Vector3 cameraPosition;
                            Vector2 screenCenter(g_windowWidth / 2.0f, g_windowHeight / 2.0f);

                            bool keyPressed = false;

                            keyPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

                            if (!keyPressed) goto skip_rage_aimbot;

                            uint32_t mainCameraTransform;
                            if (!ReadZ(localPlayer + Offsets::MainCameraTransform, mainCameraTransform) || mainCameraTransform == 0) {
                                goto skip_rage_aimbot;
                            }

                            if (!GetPosition(mainCameraTransform, cameraPosition)) {
                                goto skip_rage_aimbot;
                            }

                            for (int i = 0; i < entitiesCount; i++) {
                                uint32_t entity;
                                if (!ReadZ((uintptr_t)(i * 0x10 + entities), entity)) continue;
                                if (entity == 0 || entity == localPlayer) continue;

                                bool entityIsDead = false;
                                bool entityIsKnocked = false;
                                bool entityIsVisible = false;
                                bool entityIsTeam = false;

                                ReadZ(entity + Offsets::Player_IsDead, entityIsDead);
                                if (entityIsDead) continue;

                                uint32_t shadowBase = 0;
                                if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase)) {
                                    int xpose = 0;
                                    ReadZ(shadowBase + Offsets::XPose, xpose);
                                    if (xpose == 8) entityIsKnocked = true;
                                }
                                if (entityIsKnocked) continue;

                                uint32_t avatarManager = 0;
                                if (!ReadZ(entity + Offsets::AvatarManager, avatarManager) || avatarManager == 0) continue;

                                uint32_t avatar = 0;
                                if (!ReadZ(avatarManager + Offsets::Avatar, avatar) || avatar == 0) continue;

                                ReadZ(avatar + Offsets::Avatar_IsVisible, entityIsVisible);
                                if (!entityIsVisible) continue;

                                uint32_t avatarData = 0;
                                if (!ReadZ(avatar + Offsets::Avatar_Data, avatarData) || avatarData == 0) continue;

                                ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, entityIsTeam);
                                if (entityIsTeam) continue;

                                uint32_t headBone;
                                if (!ReadZ(entity + Offsets::Bones::Head, headBone) || headBone == 0) continue;

                                Vector3 headWorldPos;
                                if (!GetNodePosition(headBone, headWorldPos)) continue;

                                float playerDistance = Vector3::Distance(cameraPosition, headWorldPos);
                                if (playerDistance > RageAimbotDistance || playerDistance < 1.0f) continue;

                                ImVec2 headScreen = WorldToScreenImVec2(viewMatrix, headWorldPos, g_windowWidth, g_windowHeight);
                                if (headScreen.x < 1.0f || headScreen.y < 1.0f) continue;

                                float x = headScreen.x - screenCenter.X;
                                float y = headScreen.y - screenCenter.Y;
                                float crosshairDist = sqrtf(x * x + y * y);

                                if (playerDistance > RageAimbotDistance || playerDistance < 1.0f) continue;
                                if (crosshairDist < closestCrosshairDistance) {
                                    closestCrosshairDistance = crosshairDist;
                                    bestEntity = entity;
                                    bestHeadPos = headWorldPos;
                                }
                            }

                            if (bestEntity != 0) {
                                auto targetRotation = AimBZ::GetRotationToLocation(bestHeadPos, 0.1f, cameraPosition);
                                WriteZ(localPlayer + Offsets::AimRotation, targetRotation);
                                // Delay removed – aim is now instantaneous.
                            }

                        skip_rage_aimbot:;
                        }



                        if (AimbotAI && !IsTeam) {

                            ImVec2 screenCenter(g_windowWidth / 2.0f, g_windowHeight / 2.0f);
                            POINT middlePos;

                            bool isKeyPressed = false;
                            if (selectedKey == AimKey::LeftMouseButton) {
                                isKeyPressed = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) || (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
                            }

                            if (isKeyPressed) {
                                Vector3 selectedBonePos;
                                switch (selectedBone) {
                                case 0: selectedBonePos = bonePositions.HeadV3; break;
                                case 1: selectedBonePos = bonePositions.SpineV3; break;
                                default: selectedBonePos = bonePositions.HeadV3; break;
                                }

                                ImVec2 targetPos = WorldToScreenImVec2(viewMatrix, selectedBonePos, g_windowWidth, g_windowHeight);

                                bool isOnScreen = targetPos.x > 0.0f && targetPos.y > 0.0f && targetPos.x < g_windowWidth && targetPos.y < g_windowHeight;

                                if (isOnScreen) {
                                    float dx = targetPos.x - screenCenter.x;
                                    float dy = targetPos.y - screenCenter.y;
                                    float distanceSq = dx * dx + dy * dy;

                                    if (distanceSq <= fov * fov) {
                                        uint32_t rHeadCollider = 0;
                                        if (ReadZ(entity + Offsets::HeadCollider, rHeadCollider) && rHeadCollider) {
                                            WriteZ(entity + Offsets::CurrentMatch, rHeadCollider);
                                            std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                        }
                                    }
                                }
                            }
                        }






                        if (AimbotLegit && !IsTeam) {

                            ImVec2 screenCenter(width / 2.0f, height / 2.0f);

                            ImVec2 targetPos = WorldToScreenImVec2(viewMatrix, bonePositions.HeadV3, width, height);

                            bool isKeyPressed = false;
                            if (selectedKey == AimKey::LeftMouseButton)
                                isKeyPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

                            if (isKeyPressed)
                            {
                                float dx = targetPos.x - screenCenter.x;
                                float dy = targetPos.y - screenCenter.y;
                                float distanceSq = dx * dx + dy * dy;

                                if (distanceSq <= fov * fov)
                                {
                                    auto aimRotation = AimBZv2::GetRotationToLocation(bonePositions.HeadV3, smoothFactor, mainPos);
                                    WriteZ(localPlayer + Offsets::AimRotation, aimRotation);

                                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                                }
                            }
                        }

                        if (AimbotVisible == true) {
                            ImVec2 screenCenter(g_windowWidth / 2.0f, g_windowHeight / 2.0f);

                            bool isKeyPressed = false;
                            if (selectedKey == AimKey::LeftMouseButton) {
                                isKeyPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
                            }

                            if (isKeyPressed) {
                                for (uint32_t i = 0; i < entitiesCount; i++) {
                                    uint32_t entity = 0;
                                    if (!ReadZ(entities + i * 0x10, entity) || !entity) continue;
                                    if (entity == localPlayer) continue;

                                    uint32_t avatarManager = 0;
                                    if (!ReadZ(entity + Offsets::AvatarManager, avatarManager) || !avatarManager) continue;

                                    uint32_t avatar = 0;
                                    if (!ReadZ(avatarManager + Offsets::Avatar, avatar) || !avatar) continue;

                                    bool isVisible = false;
                                    if (!ReadZ(avatar + Offsets::Avatar_IsVisible, isVisible)) continue;
                                    if (!isVisible) continue;

                                    uint32_t avatarData = 0;
                                    if (!ReadZ(avatar + Offsets::Avatar_Data, avatarData) || !avatarData) continue;

                                    bool isTeam = false;
                                    ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam);
                                    if (isTeam) continue;

                                    bool isDead = false;
                                    ReadZ(entity + Offsets::Player_IsDead, isDead);
                                    if (isDead) continue;

                                    uint32_t headBone = 0;
                                    if (!ReadZ(entity + Offsets::Bones::Head, headBone) || headBone == 0) continue;

                                    Vector3 headWorldPos;
                                    if (!GetNodePosition(headBone, headWorldPos)) continue;

                                    ImVec2 targetPos = WorldToScreenImVec2(viewMatrix, headWorldPos, g_windowWidth, g_windowHeight);
                                    if (targetPos.x <= 0.0f || targetPos.y <= 0.0f ||
                                        targetPos.x >= g_windowWidth || targetPos.y >= g_windowHeight) continue;

                                    uint32_t rHeadCollider = 0;
                                    if (ReadZ(entity + Offsets::Visibleoffest, rHeadCollider) && rHeadCollider) {
                                        float randomValue = static_cast<float>(rand()) / RAND_MAX;
                                        if (randomValue <= aimvisibleStrengthhh) {
                                            WriteZ(entity + 0x54, rHeadCollider);
                                            // Delay removed – writes happen immediately
                                        }
                                    }
                                }
                            }
                        }


                        //if (UpPlayer == true && !IsTeam)
                        //{
                        //    uintptr_t bestTarget = 0;
                        //    float closestDistance = FLT_MAX;


                        //    {
                        //        uint32_t entity = 0;
                        //        if (!ReadZ((uintptr_t)(i * 0x4 + entities), entity)) continue;

                        //        if (entity == 0 || entity == localPlayer) continue;

                        //        bool isDead = false;
                        //        if (ReadZ(entity + Offsets::Player_IsDead, isDead) && isDead) continue;

                        //        bool isKnocked = false;
                        //        uint32_t shadowBase;
                        //        if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase) && shadowBase)
                        //        {
                        //            int xpose;
                        //            if (ReadZ(shadowBase + Offsets::XPose, xpose) && xpose == 8) isKnocked = true;
                        //        }
                        //        if (isKnocked) continue;

                        //        uint32_t enemyRootBonePtr;
                        //        if (!ReadZ(entity + Offsets::Bones::Root, enemyRootBonePtr)) continue;

                        //        Vector3 enemyRootPos;
                        //        if (!GetNodePosition(enemyRootBonePtr, enemyRootPos)) continue;

                        //        float playerDistance = Vector3::Distance(mainPos, enemyRootPos);
                        //        if (playerDistance > 100.0f) continue;

                        //        if (playerDistance < closestDistance)
                        //        {
                        //            closestDistance = playerDistance;
                        //            bestTarget = entity;
                        //        }
                        //    }

                        //    if (bestTarget != 0)
                        //    {
                        //        uint32_t enemyRootBonePtr;
                        //        if (ReadZ(bestTarget + Offsets::Bones::Root, enemyRootBonePtr))
                        //        {
                        //            uint32_t enemyTransformValue;
                        //            if (ReadZ(enemyRootBonePtr + 0x8, enemyTransformValue))
                        //            {
                        //                uint32_t enemyTransformObjPtr;
                        //                if (ReadZ(enemyTransformValue + 0x8, enemyTransformObjPtr))
                        //                {
                        //                    uint32_t enemyMatrixValue;
                        //                    if (ReadZ(enemyTransformObjPtr + 0x20, enemyMatrixValue))
                        //                    {
                        //                        Vector3 currentPos;
                        //                        if (ReadZ<Vector3>(enemyMatrixValue + 0x80, currentPos))
                        //                        {
                        //                            Vector3 upPos = currentPos + Vector3(0, UpPlayerAlture, 0); // Subir 15 metros
                        //                            WriteZ<Vector3>(enemyMatrixValue + 0x80, upPos);
                        //                        }
                        //                    }
                        //                }
                        //            }
                        //        }
                        //    }
                        //}

                        if (norecoilpro == true)
                        {
                            uint32_t weapon;
                            if (ReadZ(localPlayer + Offsets::Weapon, weapon)) {
                                uint32_t weaponData;
                                if (ReadZ(weapon + Offsets::WeaponData, weaponData)) {
                                    float recoil;
                                    if (ReadZ(weaponData + Offsets::WeaponRecoil, recoil) && recoil != recoiloff) {
                                        WriteZ(weaponData + Offsets::WeaponRecoil, recoiloff);
                                    }
                                }
                            }
                        }


                        if (FastReload)
                        {
                            uint32_t reload;
                            if (ReadZ(localPlayer + Offsets::PlayerAttributes, reload) && reload != 0)
                            {
                                WriteZ(reload + Offsets::NoReload2, true);
                            }
                        }
                        else
                        {
                            uint32_t reload;
                            if (ReadZ(localPlayer + Offsets::PlayerAttributes, reload) && reload != 0)
                            {
                                WriteZ(reload + Offsets::NoReload2, false);
                            }
                        }

                        if (ingerknocked) {
                            bool isKnocked = true;
                            uint32_t shadowBase;
                            if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase) && shadowBase) {
                                int xpose;
                                if (ReadZ(shadowBase + Offsets::XPose, xpose) && xpose == 8)
                                    isKnocked = true;
                            }
                            if (isKnocked) continue;
                        }

                        

                        if (coverhit == true && !IsTeam)
                        {
                            float maxAimFOV = 90.0f;            // 🎯 Crosshair එකට අසලම සිටින අය පමණක් Target කිරීමට

                            // firing check using sAim1
                            bool isFiring = false;
                            if (ReadZ(localPlayer + Offsets::sAim1, isFiring) && isFiring)
                            {
                                float closestDistance = maxAimFOV;
                                uint32_t bestEnemy = 0;
                                Vector3 enemyOriginalHeadPos = Vector3::Zero();

                                uint32_t localRootBonePtr = 0;
                                Vector3 localRootPos = Vector3::Zero();

                                // Local Player ගේ Root Bone එක ලබාගැනීම
                                if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr))
                                {
                                    if (GetNodePosition(localRootBonePtr, localRootPos))
                                    {
                                        // 🎯 1. Crosshair එකට ආසන්නතම Target Enemy සෙවීම
                                        for (int j = 0; j < entitiesCount; j++)
                                        {
                                            uint32_t currentEntity = 0;
                                            if (!ReadZ((uintptr_t)(j * 0x10 + entities), currentEntity) || currentEntity == 0)
                                                continue;

                                            if (currentEntity == localPlayer)
                                                continue;

                                            // Dead check
                                            bool isDead = false;
                                            if (!ReadZ(currentEntity + Offsets::Player_IsDead, isDead) || isDead)
                                                continue;

                                            // Knocked check
                                            bool isKnocked = false;
                                            uint32_t shadowBase = 0;
                                            if (ReadZ(currentEntity + Offsets::Player_ShadowBase, shadowBase) && shadowBase != 0)
                                            {
                                                int xpose = 0;
                                                if (ReadZ(shadowBase + Offsets::XPose, xpose) && xpose == 8)
                                                    isKnocked = true;
                                            }
                                            if (isKnocked) continue;

                                            // Team check
                                            bool isTeamMate = false;
                                            uint32_t avatarManager = 0;
                                            if (ReadZ(currentEntity + Offsets::AvatarManager, avatarManager) && avatarManager != 0)
                                            {
                                                uint32_t avatar = 0;
                                                if (ReadZ(avatarManager + Offsets::Avatar, avatar) && avatar != 0)
                                                {
                                                    uint32_t avatarData = 0;
                                                    if (ReadZ(avatar + Offsets::Avatar_Data, avatarData) && avatarData != 0)
                                                    {
                                                        ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeamMate);
                                                    }
                                                }
                                            }
                                            if (isTeamMate) continue;

                                            // Enemy Head Bone Read කිරීම
                                            uint32_t enemyHeadBonePtr = 0;
                                            Vector3 enemyHeadPos = Vector3::Zero();
                                            if (ReadZ(currentEntity + Offsets::Bones::Head, enemyHeadBonePtr))
                                            {
                                                if (GetNodePosition(enemyHeadBonePtr, enemyHeadPos))
                                                {
                                                    ImVec2 screenPos = WorldToScreenImVec2(viewMatrix, enemyHeadPos, width, height);

                                                    if (screenPos.x >= -500 && screenPos.x <= width + 500 &&
                                                        screenPos.y >= -500 && screenPos.y <= height + 500)
                                                    {
                                                        float dx = screenPos.x - (width / 2.0f);
                                                        float dy = screenPos.y - (height / 2.0f);
                                                        float distanceToCenter = sqrtf(dx * dx + dy * dy);

                                                        if (distanceToCenter < closestDistance)
                                                        {
                                                            closestDistance = distanceToCenter;
                                                            bestEnemy = currentEntity;
                                                            enemyOriginalHeadPos = enemyHeadPos;
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        // 🎯 2. තෝරාගත් Targeted Enemy (bestEnemy) ට පමණක් Position Update කිරීම
                                        if (bestEnemy != 0 && closestDistance < 1000.0f)
                                        {
                                            uint32_t enemyRootBonePtr = 0;
                                            if (ReadZ(bestEnemy + Offsets::Bones::Root, enemyRootBonePtr))
                                            {
                                                uint32_t enemyTransformValue = 0;
                                                if (ReadZ(enemyRootBonePtr + 0x8, enemyTransformValue))
                                                {
                                                    uint32_t enemyTransformObjPtr = 0;
                                                    if (ReadZ(enemyTransformValue + 0x8, enemyTransformObjPtr))
                                                    {
                                                        uint32_t enemyMatrixValue = 0;
                                                        if (ReadZ(enemyTransformObjPtr + 0x20, enemyMatrixValue))
                                                        {
                                                            Vector3 forwardDir = Vector3(viewMatrix.m02, viewMatrix.m12, viewMatrix.m22);

                                                            Vector3 diff = enemyOriginalHeadPos - mainPos;
                                                            float currentDistance = Vector3::Distance(mainPos, enemyOriginalHeadPos);

                                                            Vector3 newDir = forwardDir;
                                                            Vector3 newHeadPos = mainPos + (newDir * currentDistance);

                                                            Vector3 offset = newHeadPos - enemyOriginalHeadPos;

                                                            // ⚡ උඩට ඇදීම (Vertical Height Offset) පාලනය කිරීම
                                                            if (offset.Y > 0.1f)
                                                            {
                                                                offset.Y *= 0.1f; // උඩට ඇදීම 90% කින් අඩු කරයි (0.0f යෙදුවහොත් උඩට ඇදීම සම්පූර්ණයෙන්ම නතර වේ)
                                                            }
                                                           


                                                            Vector3 currentRootPos;
                                                            if (ReadZ<Vector3>(enemyMatrixValue + 0x60, currentRootPos))
                                                            {
                                                                Vector3 newRootPos = currentRootPos + offset;

                                                                WriteZ<Vector3>(enemyMatrixValue + 0x60, newRootPos);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (AutoFire && !IsTeam && !isDead && !isKnocked && IsKnown)
                        {
                            ImGuiIO& io = ImGui::GetIO();
                            if (!io.WantCaptureMouse)
                            {
                                static bool isShooting = false;
                                static DWORD lastCheckTime = 0;
                                DWORD currentTime = GetTickCount();
                                if (currentTime - lastCheckTime >= 50)
                                {
                                    lastCheckTime = currentTime;

                                    static ImVec2 screenCenter(g_windowWidth / 2.0f, g_windowHeight / 2.0f);
                                    ImVec2 headScreen = WorldToScreenImVec2(viewMatrix, bonePositions.HeadV3, g_windowWidth, g_windowHeight);

                                    bool targetInRange = false;
                                    if (headScreen.x > 0 && headScreen.y > 0)
                                    {
                                        float dx = headScreen.x - screenCenter.x;
                                        float dy = headScreen.y - screenCenter.y;

                                        if (abs(dx) <= 180 && abs(dy) <= 180)
                                        {
                                            targetInRange = true;
                                        }
                                    }
                                    if (targetInRange)
                                    {
                                        if (!isShooting)
                                        {
                                            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                            isShooting = true;
                                        }
                                    }
                                    else
                                    {
                                        if (isShooting)
                                        {
                                            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                            isShooting = false;
                                        }
                                    }
                                }
                            }
                        }

                        //{
                        //    static uint32_t lastValidSpeedTimer = 0;
                        //    static std::chrono::steady_clock::time_point startTime;
                        //    static std::chrono::steady_clock::time_point lastWriteTime;
                        //    static bool isTimerRunning = false;
                        //    static float lastWrittenSpeed = 0.0f;

                        //    // Fixed Safe Ultra Fast Speeds
                        //    const float SLOW_SPEED = 0.053000f;       // Normal Speed
                        //    const float FAST_SPEED = 0.065000f;       // Fast Speed
                        //    const float ULTRA_FAST_SPEED = 0.098000f; // Disconnect නොවෙන Safe Ultra Fast Speed Value

                        //    const int DELAY_MS = 1000;                // Initial delay (1.0 sec)
                        //    const int RAMP_DURATION_MS = 800;         // Freeze නොවී Smooth වීමට යන කාලය (0.8 sec)
                        //    const int WRITE_INTERVAL_MS = 16;         // ~60FPS Rate Limiting (Frame Freeze වැළැක්වීමට)

                        //    bool UltraSpeedEnable = true;

                        //    uint32_t bGF = 0, gF = 0, sGF = 0, cG = 0, sT = 0;

                        //    // Pointer address path verification
                        //    if (Offsets::Il2Cpp != 0 &&
                        //        ReadZ(Offsets::Il2Cpp + Offsets::InitBase, bGF) && bGF &&
                        //        ReadZ(bGF, gF) && gF &&
                        //        ReadZ(gF + Offsets::StaticClass, sGF) && sGF &&
                        //        ReadZ(sGF, cG) && cG &&
                        //        ReadZ(cG + 0x10, sT) && sT)
                        //    {
                        //        lastValidSpeedTimer = sT;
                        //    }

                        //    if (lastValidSpeedTimer != 0)
                        //    {
                        //        if (SpeedTimerEnable)
                        //        {
                        //            auto currentTime = std::chrono::steady_clock::now();

                        //            if (!isTimerRunning)
                        //            {
                        //                startTime = currentTime;
                        //                lastWriteTime = currentTime;
                        //                isTimerRunning = true;
                        //            }

                        //            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
                        //            auto timeSinceLastWrite = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastWriteTime).count();

                        //            float targetSpeed = UltraSpeedEnable ? ULTRA_FAST_SPEED : FAST_SPEED;
                        //            float currentSpeed = SLOW_SPEED;

                        //            if (elapsedTime < DELAY_MS)
                        //            {
                        //                currentSpeed = SLOW_SPEED;
                        //            }
                        //            else if (elapsedTime < (DELAY_MS + RAMP_DURATION_MS))
                        //            {
                        //                // Smooth Step Transition (Ease-In-Out) - Sudden speed jumps වැළැක්වීමට
                        //                float progress = static_cast<float>(elapsedTime - DELAY_MS) / static_cast<float>(RAMP_DURATION_MS);

                        //                // Linear LERP වෙනුවට Smooth Step Equation එකක් භාවිතා කිරීම
                        //                float smoothProgress = progress * progress * (3.0f - 2.0f * progress);
                        //                currentSpeed = SLOW_SPEED + smoothProgress * (targetSpeed - SLOW_SPEED);
                        //            }
                        //            else
                        //            {
                        //                currentSpeed = targetSpeed;
                        //            }

                        //            // Fix 1: Memory Rate Limiting (තත්පරයට Frame 60කට වඩා Write නොකිරීම මගින් Freeze වීම නතර වේ)
                        //            // Fix 2: Value එක වෙනස් වුවහොත් පමණක් Write කිරීම (Redundant Writes වැළැක්වීම)
                        //            if (timeSinceLastWrite >= WRITE_INTERVAL_MS && std::abs(currentSpeed - lastWrittenSpeed) > 0.0001f)
                        //            {
                        //                WriteZ(lastValidSpeedTimer + 0x24, currentSpeed);
                        //                lastWrittenSpeed = currentSpeed;
                        //                lastWriteTime = currentTime;
                        //            }
                        //        }
                        //        else
                        //        {
                        //            if (isTimerRunning)
                        //            {
                        //                isTimerRunning = false;
                        //                lastWrittenSpeed = 0.0f;
                        //                WriteZ(lastValidSpeedTimer + 0x24, SLOW_SPEED);
                        //            }
                        //        }

                        //    }
                        //}



                        //if (PullPlayer)
                        //{

                        //    int EnemyPullBind = 0;
                        //    int EnemyPullStrength = 1;           // 0 = Hip, 1 = Head
                        //    int EnemyPullMaxDistance = 150;      // Max distance in meters
                        //    float PullHeightOffset = 0.0f;       // Height offset
                        //    float verticalPullFactor = 0.1f;     // 0.0f - 1.0f (උඩට ඇදෙන ප්‍රමාණය අඩු කිරීමට: 0.1f = ඉතා අඩුයි)

                        //    // 🎛️ Pull වෙන ප්‍රමාණය සහ Aim Target එක පාලනය කිරීමට:
                        //    //float verticalPullFactor = 0.1f;     // උඩට ඇදෙන ප්‍රමාණය (0.1f = ඉතා අඩුයි)
                        //    //float horizontalPullFactor = 0.2f;   // දෙපැත්තට ඇදෙන ප්‍රමාණය (0.2f = ඉතා අඩුයි)
                        //    float maxAimFOV = 150.0f;            // 🎯 Crosshair එකේ සිට Enemy ට ඇති උපරිම පරතරය (Pixels). මේකෙන් Aim කරන කෙනාව විතරක් Target කරයි.


                        //    bool isCurrentlyFiring = false;
                        //    if (ReadZ(localPlayer + Offsets::sAim1, isCurrentlyFiring) && isCurrentlyFiring)
                        //        lastFireTime = std::chrono::steady_clock::now();
                        //    bool isFiring = (std::chrono::duration_cast<std::chrono::milliseconds>(
                        //        std::chrono::steady_clock::now() - lastFireTime).count() < fireCooldownMs360);
                        //    if (isFiring)
                        //    {
                        //        uint32_t bestEntity = 0;
                        //        float closestCrosshairDist = FLT_MAX;
                        //        ImVec2 screenCenter(width / 2.0f, height / 2.0f);
                        //        uint32_t targetBoneOffsett;
                        //        //if (SelectedPullBone == 0) targetBoneOffsett = Offsets::Bones::Head;
                        //        //else if (SelectedPullBone == 1) targetBoneOffsett = Offsets::Bones::Spine;
                        //        //else targetBoneOffsett = Offsets::Bones::Root;
                        //        for (uint32_t i = 0; i < entitiesCount; ++i)
                        //        {
                        //            uint32_t entityAddr = 0;
                        //            if (!ReadZ((uintptr_t)(entities + (i * 0x10) + 0xC), entityAddr) || entityAddr == 0 || entityAddr == localPlayer) continue;
                        //            bool isDead = false, isTeam = false;
                        //            if (!ReadZ(entity + Offsets::Player_IsDead, isDead) || isDead) continue;
                        //            uint32_t avatarManager, avatar, avatarData;
                        //            if (!ReadZ(entity + Offsets::AvatarManager, avatarManager) ||
                        //                !ReadZ(avatarManager + Offsets::Avatar, avatar) ||
                        //                !ReadZ(avatar + Offsets::Avatar_Data, avatarData)) continue;
                        //            if (!ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam) || isTeam) continue;
                        //            bool isKnocked = false;
                        //            uint32_t shadowBase = 0;
                        //            if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase) && shadowBase != 0) {
                        //                int pose;
                        //                if (ReadZ(shadowBase + Offsets::XPose, pose) && pose == 8) isKnocked = true;
                        //            }
                        //            
                        //        }

                        //        if (bestEntity)
                        //        {
                        //            currentPullTarget = bestEntity;
                        //            uint32_t boneToPull = 0, rootBone = 0;
                        //            if (ReadZ(entity + targetBoneOffsett, boneToPull) && ReadZ(entity + Offsets::Bones::Root, rootBone))
                        //            {
                        //                Vector3 targetBonePos = {}, rootPos = {};
                        //                if (GetNodePosition(boneToPull, targetBonePos) && GetNodePosition(rootBone, rootPos))
                        //                {
                        //                    uint32_t trans = 0, obj = 0, matrix = 0;
                        //                    if (ReadZ(rootBone + 0x8, trans) && ReadZ(trans + 0x8, obj) && ReadZ(obj + 0x20, matrix))
                        //                    {
                        //                        if (originalPositions.find(bestEntity) == originalPositions.end())
                        //                            originalPositions[bestEntity] = rootPos;

                        //                        Vector3 fireDir(viewMatrix.m02, viewMatrix.m12, viewMatrix.m22);
                        //                        Vector3 toTarget = targetBonePos - mainPos; // bestTargetPos වෙනුවට targetBonePos
                        //                        float projLength = Vector3::Dot(toTarget, fireDir);
                        //                        Vector3 linePoint = mainPos + fireDir * projLength;

                        //                        Vector3 offset = linePoint - targetBonePos; // bestTargetPos වෙනුවට targetBonePos

                        //                        // 🎯 උඩට සහ දෙපැත්තට ඇදෙන ප්‍රමාණයන් සීමා කිරීම:
                        //                        if (offset.X > 0.01f)
                        //                            offset.Z = 0.01f;

                        //                        if (offset.Y > 0.0f)
                        //                            offset.Y = 0.0f;

                        //                        Vector3 pulledPos = rootPos + offset; // bestRootPos වෙනුවට rootPos
                        //                        WriteZ<Vector3>(matrix + 0x60, pulledPos);
                        //                    }
                        //                }
                        //            }
                        //        }
                        //    }
                        //    else if (!originalPositions.empty())
                        //    {
                        //        for (auto const& [entity, pos] : originalPositions)
                        //        {
                        //            uint32_t rootBone = 0;
                        //            if (ReadZ(entity + Offsets::Bones::Root, rootBone))
                        //            {
                        //                uint32_t trans = 0, obj = 0, matrix = 0;
                        //                if (ReadZ(rootBone + 0x8, trans) && ReadZ(trans + 0x8, obj) && ReadZ(obj + 0x20, matrix))
                        //                    WriteZ<Vector3>(matrix + 0x60, pos);
                        //            }
                        //        }
                        //        originalPositions.clear();
                        //        //pullTime = 0.0f;
                        //        currentPullTarget = 0;
                        //    }
                        //}

if (pullene)
{
    // -------------------------------------------------------------
    // ⌨️ Key Toggle Logic (උදා: CAPS LOCK Key එකෙන් Head/Chest මාරු කිරීමට)
    // වෙනත් Key එකක් (උදා: 'T' Key එක නම් 'T' ලෙස) යොදාගත හැක.
    // -------------------------------------------------------------
    bool isKeyPressedToggle = (GetAsyncKeyState(VK_END) & 0x8000) != 0;

    if (isKeyPressedToggle && !isToggleKeyPressed)
    {
        // Head (0) නම් Chest (1) වලටත්, Chest (1) නම් Head (0) වලටත් මාරු වේ.
        selectedTargetBone = (selectedTargetBone == 0) ? 1 : 0;
        isToggleKeyPressed = true; // Key එක Press කරගෙන සිටින විට දිගටම Toggle වීම වලකයි
    }
    else if (!isKeyPressedToggle)
    {
        isToggleKeyPressed = false; // Key එක Release කළ පසු ආපසු Toggle කිරීමට සූදානම් වේ
    }

    int EnemyPullBind = 0;
    int EnemyPullStrength = 1; // 0 = Hip, 1 = Head
    int EnemyPullMaxDistance = 150; // Max distance in meters
    float PullHeightOffset = 0.0f; // Height offset
    float verticalPullFactor = 0.1f; // 0.0f - 1.0f

    // Target එක වෙනස් නොවී Lock කර තබා ගැනීමට Dynamic Lock Variable එකක්
    static uint32_t lockedTargetEntity = 0;

    bool isKeyPressed = selectedKey == AimKey::LeftMouseButton
        ? (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 : false;

    if (isKeyPressed)
    {
        bool isCurrentlyFiring = false;
        if (ReadZ(localPlayer + Offsets::sAim1, isCurrentlyFiring) && isCurrentlyFiring)
        {
            lastFireTime = std::chrono::steady_clock::now();
        }

        bool isFiring = (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - lastFireTime).count() < fireCooldownMs360);

        if (isFiring)
        {
            uint32_t bestEntity = 0;
            float closestDistance = FLT_MAX; // maxAimFOV වෙනුවට FOV සීමාවක් නොමැතිව ළඟම Target එක තෝරාගැනීමට FLT_MAX යොදා ඇත
            Vector3 bestTargetPos = {};
            Vector3 bestRootPos = {};
            uint32_t bestMatrix = 0;

            ImVec2 screenCenter(width / 2.0f, height / 2.0f);

            // 🎯 1. මුලින්ම Aim Crosshair එක ළඟම ඉන්න Target එක විතරක් Lock කරගන්නවා
            if (lockedTargetEntity == 0)
            {
                for (uint32_t i = 0; i < entitiesCount; ++i)
                {
                    uint32_t currentEntity = entity + i * 0x5;

                    uint32_t entityAddr = 0;
                    if (!ReadZ(currentEntity, entityAddr) || entityAddr == 0 || entityAddr == localPlayer)
                        continue;

                    uint32_t avatarManager = 0, avatar = 0, avatarData = 0;
                    if (!ReadZ(currentEntity + Offsets::AvatarManager, avatarManager) ||
                        !ReadZ(avatarManager + Offsets::Avatar, avatar) ||
                        !ReadZ(avatar + Offsets::Avatar_Data, avatarData))
                        continue;

                    // Dead check
                    bool entityIsDead = false;
                    ReadZ(currentEntity + Offsets::Player_IsDead, entityIsDead);
                    if (entityIsDead) continue;

                    // Knocked check
                    bool entityIsKnocked = false;
                    uint32_t shadowBase = 0;
                    if (ReadZ(currentEntity + Offsets::Player_ShadowBase, shadowBase)) {
                        int xpose = 0;
                        ReadZ(shadowBase + Offsets::XPose, xpose);
                        if (xpose == 8) entityIsKnocked = true;
                    }
                    if (entityIsKnocked) continue;

                    // Team check
                    bool isTeam = false;
                    if (!ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam) || isTeam)
                        continue;

                    // 1. Target Offset එක තෝරාගැනීම
                    uint32_t targetBoneOffset = (selectedTargetBone == 0)
                        ? Offsets::Bones::Head
                        : Offsets::Bones::Hip; // 0 = Head, 1 = Chest

                    // 2. Variable එක Declare කර Memory Read කරගැනීම
                    uint32_t targetBone = 0;
                    if (!ReadZ(currentEntity + targetBoneOffset, targetBone) || targetBone == 0)
                        continue;

                    // 3. Bone එක Valid ද බලන්න
                    if (targetBone == 0) continue;

                    Vector3 dynamicTargetPos = {};
                    if (!GetNodePosition(targetBone, dynamicTargetPos)) continue;

                    ImVec2 screenPos = WorldToScreenImVec2(viewMatrix, dynamicTargetPos, width, height);

                    // Off-screen check
                    if (screenPos.x <= 0 || screenPos.y <= 0 || screenPos.x >= width || screenPos.y >= height)
                        continue;

                    float dx = screenPos.x - screenCenter.x;
                    float dy = screenPos.y - screenCenter.y;
                    float distToCenter = sqrtf(dx * dx + dy * dy);

                    if (distToCenter < closestDistance)
                    {
                        closestDistance = distToCenter;
                        bestEntity = currentEntity;
                    }
                }

                // Lock the target
                if (bestEntity != 0)
                {
                    lockedTargetEntity = bestEntity;
                }
            }

            // 🎯 2. Lock වුණු Target එක dynamically pull කිරීම
            if (lockedTargetEntity != 0)
            {
                // 💥 Lock වෙලා තිබුණත් Real-time වෙනස් වන selectedTargetBone එක Read කිරීම
                uint32_t currentBoneOffset = (selectedTargetBone == 0)
                    ? Offsets::Bones::Head
                    : Offsets::Bones::Hip;

                uint32_t targetBone = 0, rootBone = 0;
                if (ReadZ(lockedTargetEntity + currentBoneOffset, targetBone) &&
                    ReadZ(lockedTargetEntity + Offsets::Bones::Root, rootBone))
                {
                    Vector3 dynamicTargetPos = {}, rootPos = {};
                    if (GetNodePosition(targetBone, dynamicTargetPos) &&
                        GetNodePosition(rootBone, rootPos))
                    {
                        bestTargetPos = dynamicTargetPos;
                        bestRootPos = rootPos;

                        uint32_t trans = 0, obj = 0, matrix = 0;
                        if (ReadZ(rootBone + 0x8, trans) && ReadZ(trans + 0x8, obj) && ReadZ(obj + 0x20, matrix))
                        {
                            bestMatrix = matrix;
                        }
                    }
                }
                else
                {
                    lockedTargetEntity = 0;
                }

                // Dynamic Position Update (Pull calculation)
                if (bestMatrix != 0)
                {
                    currentPullTarget = lockedTargetEntity;

                    if (originalPositions.find(lockedTargetEntity) == originalPositions.end())
                        originalPositions[lockedTargetEntity] = bestRootPos;

                    Vector3 fireDir = { viewMatrix.m02, viewMatrix.m12, viewMatrix.m22 };
                    fireDir = Vector3::Normalized(fireDir);

                    Vector3 toTarget = bestTargetPos - mainPos;
                    float projLength = Vector3::Dot(toTarget, fireDir);
                    Vector3 linePoint = mainPos + fireDir * projLength;

                    Vector3 offset = linePoint - bestTargetPos;

                    if (offset.X > 9.0f);

                    if (offset.Y > 0.0f)
                        offset.Y = 0.1f;

                    Vector3 pulledPos = bestRootPos + offset;

                    WriteZ<Vector3>(bestMatrix + 0x60, pulledPos);
                }
            }
        }
        else
        {
            // Position Restore on Fire Stop
            if (!originalPositions.empty())
            {
                for (auto& entry : originalPositions)
                {
                    uint32_t entityAddr = entry.first;
                    uint32_t rootBone = 0;
                    if (!ReadZ(entityAddr + Offsets::Bones::Root, rootBone)) continue;

                    uint32_t trans = 0, obj = 0, matrix = 0;
                    if (!ReadZ(rootBone + 0x8, trans)) continue;
                    if (!ReadZ(trans + 0x8, obj)) continue;
                    if (!ReadZ(obj + 0x20, matrix)) continue;

                    WriteZ<Vector3>(matrix + 0x60, entry.second);
                }
                originalPositions.clear();
            }

            lockedTargetEntity = 0;
        }
    }
    else
    {
        // Key release reset
        if (!originalPositions.empty())
        {
            for (auto& entry : originalPositions)
            {
                uint32_t entityAddr = entry.first;
                uint32_t rootBone = 0;
                if (!ReadZ(entityAddr + Offsets::Bones::Root, rootBone)) continue;

                uint32_t trans = 0, obj = 0, matrix = 0;
                if (!ReadZ(rootBone + 0x8, trans)) continue;
                if (!ReadZ(trans + 0x8, obj)) continue;
                if (!ReadZ(obj + 0x20, matrix)) continue;

                WriteZ<Vector3>(matrix + 0x60, entry.second);
            }
            originalPositions.clear();
        }

        lockedTargetEntity = 0;
    }
}
                        
// Dynamic variable එකක් static ලෙස තබා ගැනීමෙන් Original Y position එක save කරගත හැක
static float originalY = 0.0f;
static bool isLockedUnderground = false;

// 1. Global / File scope එකේ:
static std::unordered_map<uint32_t, float> originalYMap;


// 2. Down Player Function / Logic එක:
if (DownPlayerEnable)
{
    // localPlayer එක 0 නෙමේ නම් Process කිරීම
    if (localPlayer != 0)
    {
        uint32_t targetPlayerPtr = localPlayer;
        uint32_t rootBonePtr = 0;
        float DownPlayerSpeed = 0.8f; // පොළොව යටට බැසිය යුතු ගැඹුර

        if (ReadZ(targetPlayerPtr + Offsets::Bones::Root, rootBonePtr) && rootBonePtr != 0)
        {
            uint32_t t1 = 0, t2 = 0, mat = 0;
            if (ReadZ(rootBonePtr + 0x8, t1) && t1 != 0 &&
                ReadZ(t1 + 0x8, t2) && t2 != 0 &&
                ReadZ(t2 + 0x20, mat) && mat != 0)
            {
                Vector3 cur;
                if (ReadZ<Vector3>(mat + 0x60, cur))
                {
                    // Original Y Position එක Save කරගැනීම
                    if (originalYMap.find(targetPlayerPtr) == originalYMap.end()) {
                        originalYMap[targetPlayerPtr] = cur.Y;
                    }

                    // Y position එක පොළොව යටට Set කිරීම
                    cur.Y = originalYMap[targetPlayerPtr] - DownPlayerSpeed;
                    WriteZ<Vector3>(mat + 0x60, cur);
                }
            }
        }
    }
}
else
{
    // Feature එක OFF කළ විට නැවත උඩට ගැනීම
    if (!originalYMap.empty())
    {
        for (auto const& [playerPtr, savedY] : originalYMap)
        {
            if (playerPtr != 0)
            {
                uint32_t rootBonePtr = 0;
                if (ReadZ(playerPtr + Offsets::Bones::Root, rootBonePtr) && rootBonePtr != 0)
                {
                    uint32_t t1 = 0, t2 = 0, mat = 0;
                    if (ReadZ(rootBonePtr + 0x8, t1) && t1 != 0 &&
                        ReadZ(t1 + 0x8, t2) && t2 != 0 &&
                        ReadZ(t2 + 0x20, mat) && mat != 0)
                    {
                        Vector3 cur;
                        if (ReadZ<Vector3>(mat + 0x60, cur))
                        {
                            cur.Y = savedY;
                            WriteZ<Vector3>(mat + 0x60, cur);
                        }
                    }
                }
            }
        }
        originalYMap.clear();
    }
}
                        //if (Aimlock && !IsTeam)
                        //{
                        //    uint32_t weaponProcessor;
                        //    if (!ReadZ(localPlayer + Offsets::Weapon, weaponProcessor) || weaponProcessor == 0)
                        //        ; // bos geï¿½

                        //    else {
                        //        uint32_t itemComponent;
                        //        if (ReadZ(weaponProcessor + Offsets::WeaponData, itemComponent) && itemComponent != 0)
                        //        {
                        //            float spreadValue;
                        //            if (ReadZ(itemComponent + Offsets::HeadCollider, spreadValue) && spreadValue != -1.0f)
                        //            {
                        //                WriteZ(itemComponent + Offsets::HeadCollider, -1.0f);
                        //            }
                        //        }
                        //    }
                        //}
                        //static float flywallOffset = 100.0f;
                        //static int flywallTickDelay = 10;
                        //static Vector3 flywallPosition = { 0, 0, 0 };
                        //static bool isFlywallActive = false;

                        //if (FlyWall) {
                        //    // Variable Declarations
                        //    static bool isFlywallActive = false;
                        //    static Vector3 flywallPosition = { 0, 0, 0 };

                        //    // M / Distance Control
                        //    float flywallOffset = 50.0f; // ඉදිරියට යන දුර (Unreal Engine මීටර් 50ක් සඳහා අවශ්‍ය පරිදි 50.0f හෝ 5000.0f ලෙස වෙනස් කරන්න)
                        //    int flywallTickDelay = 10;   // ms Delay එක

                        //    uint32_t rootPtr = 0;
                        //    if (ReadZ<uint32_t>(localPlayer + (uint32_t)Offsets::Bones::Root, rootPtr) && rootPtr) {

                        //        uint32_t t1 = 0, t2 = 0, mat = 0;
                        //        ReadZ<uint32_t>(rootPtr + 0x8, t1);
                        //        ReadZ<uint32_t>(t1 + 0x8, t2);
                        //        ReadZ<uint32_t>(t2 + 0x20, mat);

                        //        Vector3 cur;
                        //        if (ReadZ<Vector3>(mat + 0x60, cur)) {
                        //            if (!isFlywallActive) {
                        //                Vector3 newPos = cur;

                        //                // Y (Side) සහ Z (Up/Down) අගයන් වෙනස් නොකර X (Forward) එක පමණක් මීටර් 50ක් ඉදිරියට තබයි
                        //                newPos.X += flywallOffset;

                        //                // Y සහ Z වෙනස් වීම වැළැක්වීම
                        //                newPos.Y = 0.0f;
                        //                newPos.Z = 1.0f;

                        //                for (int fi = 0; fi < 50; fi++) {
                        //                    WriteZ<Vector3>(mat + 0x60, newPos);
                        //                    std::this_thread::sleep_for(std::chrono::milliseconds(flywallTickDelay));
                        //                }

                        //                flywallPosition = newPos;
                        //                isFlywallActive = true;
                        //            }
                        //            else {
                        //                Vector3 posNow;
                        //                if (ReadZ<Vector3>(mat + 0x60, posNow)) {
                        //                    // Pos එක වෙනස් වුවහොත් Lock එක Reset වේ
                        //                    if (Vector3::Distance(posNow, flywallPosition) > 0.3f) {
                        //                        isFlywallActive = false;
                        //                    }
                        //                    else {
                        //                        WriteZ<Vector3>(mat + 0x60, flywallPosition);
                        //                    }
                        //                }
                        //            }
                        //        }
                        //    }
                        //}
                        //else {
                        //    isFlywallActive = false;
                        //}

                        static uint32_t staticGameFacadeCache = 0;

                        if (TeleportMarkEnable)
                        {
                            try {
                                // Cache staticGameFacade for performance (like C# version)
                                if (staticGameFacadeCache == 0)
                                {
                                    uint32_t baseGameFacade = 0, gameFacade = 0;
                                    if (Offsets::Il2Cpp != 0 &&
                                        ReadZ(Offsets::Il2Cpp + Offsets::InitBase, baseGameFacade) && baseGameFacade != 0 &&
                                        ReadZ(baseGameFacade, gameFacade) && gameFacade != 0 &&
                                        ReadZ(gameFacade + Offsets::StaticClass, staticGameFacadeCache) && staticGameFacadeCache != 0)
                                    {
                                        // Cached successfully
                                    }
                                }

                                if (staticGameFacadeCache != 0)
                                {
                                    uint32_t currentGame = 0;
                                    if (ReadZ(staticGameFacadeCache + 0x0, currentGame) && currentGame != 0)
                                    {
                                        // Get marked position from map UI
                                        uint32_t UIInGameScene = 0, m_BigMapCtrl = 0, m_MapContentCtrl = 0, m_LocalMapMarkController = 0;
                                        Vector3 markedPos{};

                                        if (ReadZ(currentGame + 0x8, UIInGameScene) && UIInGameScene != 0 &&
                                            ReadZ(UIInGameScene + 0x1F4, m_BigMapCtrl) && m_BigMapCtrl != 0 &&
                                            ReadZ(m_BigMapCtrl + 0x218, m_MapContentCtrl) && m_MapContentCtrl != 0 &&
                                            ReadZ(m_MapContentCtrl + 0x54, m_LocalMapMarkController) && m_LocalMapMarkController != 0 &&
                                            ReadZ<Vector3>(m_LocalMapMarkController + 0x58, markedPos))
                                        {
                                            // Only teleport if position is valid (not zero)
                                            if (markedPos.X != 0.0f || markedPos.Z != 0.0f)
                                            {
                                                // Get local player from currentMatch
                                                uint32_t currentMatch = 0, localPlayer = 0;
                                                if (ReadZ(currentGame + Offsets::CurrentMatch, currentMatch) && currentMatch != 0 &&
                                                    ReadZ(currentMatch + Offsets::LocalPlayer, localPlayer) && localPlayer != 0)
                                                {
                                                    // Teleport to marked position (like C# TeleportLoop)
                                                    uint32_t root = 0, transform = 0, obj = 0, matrix = 0;
                                                    if (ReadZ(localPlayer + Offsets::Bones::Root, root) && root != 0 &&
                                                        ReadZ(root + 0x8, transform) && transform != 0 &&
                                                        ReadZ(transform + 0x8, obj) && obj != 0 &&
                                                        ReadZ(obj + 0x20, matrix) && matrix != 0)
                                                    {
                                                        WriteZ<Vector3>(matrix + 0x60, markedPos);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            catch (...) {
                                // Silently catch exceptions
                            }
                        }
                        else
                        {
                            // Reset cache when disabled
                            staticGameFacadeCache = 0;
                        }



                        //// 1. Condition verification & Typo fix
                        //if (frwardPlayer && !IsTeam)
                        //{
                        //    float closestDistance = FLT_MAX;
                        //    uint32_t bestEnemy = 0;

                        //    uint32_t localRootBonePtr = 0;
                        //    if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr) && localRootBonePtr != 0)
                        //    {
                        //        Vector3 localRootPos{};
                        //        if (GetNodePosition(localRootBonePtr, localRootPos))
                        //        {
                        //            // Entity List base address ekatama pointer reading eka harida bala ganna
                        //            for (int i = 0; i < 18; i++)
                        //            {
                        //                uint32_t entity = 0;

                        //                // Entity pointer eka read kiriema
                        //                if (!ReadZ(entities + (i * 0x4), entity) || entity == 0)
                        //                    continue;

                        //                // Local player wa skip kiriema
                        //                if (entity == localPlayer)
                        //                    continue;

                        //                // Dead check (Read boundary success veema saha value eka check kiriema)
                        //                bool isDead = false;
                        //                if (ReadZ(entity + Offsets::Player_IsDead, isDead) && isDead)
                        //                    continue;

                        //                // Knocked check
                        //                bool isKnocked = false;
                        //                uint32_t shadowBase = 0;
                        //                if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase) && shadowBase != 0)
                        //                {
                        //                    int xpose = 0;
                        //                    if (ReadZ(shadowBase + Offsets::XPose, xpose) && xpose == 8)
                        //                        isKnocked = true;
                        //                }
                        //                if (isKnocked)
                        //                    continue;

                        //                // Enemy root bone position eka ganeema
                        //                uint32_t enemyRootBonePtr = 0;
                        //                if (!ReadZ(entity + Offsets::Bones::Root, enemyRootBonePtr) || enemyRootBonePtr == 0)
                        //                    continue;

                        //                Vector3 enemyPos{};
                        //                if (!GetNodePosition(enemyRootBonePtr, enemyPos))
                        //                    continue;

                        //                // Distance calculation
                        //                float playerDistance = Vector3::Distance(localRootPos, enemyPos);

                        //                // Game unit wisin distance eka marnaya wena nisa 100.0f adu da kiyala pariksha kiriema
                        //                if (playerDistance < closestDistance)
                        //                {
                        //                    closestDistance = playerDistance;
                        //                    bestEnemy = entity;
                        //                }
                        //            }
                        //        }
                        //    }

                        //    // Target ekak labune thibeth pamani kriyathmaka wenne
                        //    if (bestEnemy != 0)
                        //    {
                        //        // ----------------------------------------------------
                        //        // Ithurukota execution code eka mehi liyanna:
                        //        // Ex: Teleporting, Aiming, Teleporting Player Pos
                        //        // ----------------------------------------------------
                        //    }
                        //}





                        float TpDistance = 50000.0f; // Max range infinity setup for any distance

                        if (TeleportBase && !IsTeam) {
                            uint32_t localRootBonePtr = 0;
                            if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr)) {
                                Vector3 localRootPos;
                                if (GetNodePosition(localRootBonePtr, localRootPos)) {
                                    uint32_t enemyRootBonePtr = 0;
                                    if (ReadZ(entity + Offsets::Bones::Root, enemyRootBonePtr)) {
                                        Vector3 enemyPos;
                                        if (GetNodePosition(enemyRootBonePtr, enemyPos)) {

                                            // Distance check uses TpDistance
                                            float currentDist = Vector3::Distance(localRootPos, enemyPos);
                                            if (currentDist <= TpDistance) {

                                                uint32_t t1 = 0, t2 = 0, mat = 0;
                                                if (ReadZ(localRootBonePtr + 0x8, t1) &&
                                                    ReadZ(t1 + 0x8, t2) &&
                                                    ReadZ(t2 + 0x20, mat)) {

                                                    Vector3 targetPos = enemyPos;

                                                    // Local player ge sita enemy dikata thiyena direction vector eka
                                                    Vector3 dir = (enemyPos - localRootPos);
                                                    float length = sqrt(dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z);

                                                    if (length > 0.001f) {
                                                        dir.X /= length;
                                                        dir.Y /= length;
                                                        dir.Z /= length;

                                                        // Enemy ge pitipassata 15.0f units ekathu kireema:
                                                        // Vector direction eka local -> enemy nisai mehi '+' baavitha karanne
                                                        targetPos.X = enemyPos.X + (dir.X * 15.0f);
                                                        targetPos.Y = enemyPos.Y + (dir.Y * 15.0f);
                                                        targetPos.Z = enemyPos.Z + 0.1f; // Ground clipping prevent kireema sandaha
                                                    }

                                                    // Write teleport position directly to matrix
                                                    WriteZ<Vector3>(mat + 0x60, targetPos);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (TpBaseCheck && !IsTeam) {
                            uint32_t localRootBonePtr = 0;
                            if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr)) {
                                Vector3 localRootPos;
                                if (GetNodePosition(localRootBonePtr, localRootPos)) {
                                    uint32_t enemyRootBonePtr = 0;
                                    if (ReadZ(entity + Offsets::Bones::Root, enemyRootBonePtr)) {
                                        Vector3 enemyPos;
                                        if (GetNodePosition(enemyRootBonePtr, enemyPos)) {
                                            if (Vector3::Distance(localRootPos, enemyPos) <= TpDistance) {

                                                // --- Teleport Position Offset Calculation ---
                                                // Enemy ge angle / direction ekata galapena widihata offset position ekak hadaganna
                                                // Enemy igan issarahama naha wall/front side eka offset karanna space ekak ekatu karamu:

                                                // Enemy ge rotation / direction eka ganna natham local player view direction eka shape karaganna:
                                                Vector3 targetTeleportPos = enemyPos;

                                                // Distance offset (e.g., enemy ege indan meter 1.5 - 2.0 k issarahin thiyanna)
                                                float offsetDistance = 1.8f;

                                                // Direction Vector calculation (Enemy ge idan poddak offset karanna)
                                                Vector3 dir = enemyPos - localRootPos;
                                                dir.Y = 0; // Height eka eka samana mattedhi thiyanna

                                                float length = sqrt(dir.X * dir.X + dir.Z * dir.Z);
                                                if (length > 0.01f) {
                                                    dir.X /= length;
                                                    dir.Z /= length;

                                                    // Enemy agata yanne nathuwa poddak issarahin/patten teleport wena target point eka:
                                                    targetTeleportPos.X = enemyPos.X - (dir.X * offsetDistance);
                                                    targetTeleportPos.Z = enemyPos.Z - (dir.Z * offsetDistance);
                                                    // Ground level eka match karanna Y axis eka ehemama thiyanna:
                                                    targetTeleportPos.Y = enemyPos.Y;
                                                }

                                                // --- Memory Write ---
                                                uint32_t t1 = 0, t2 = 0, mat = 0;
                                                if (ReadZ(localRootBonePtr + 0x8, t1) &&
                                                    ReadZ(t1 + 0x8, t2) &&
                                                    ReadZ(t2 + 0x20, mat)) {

                                                    // Enemy ege kelinma postion eka wenuwata calculated `targetTeleportPos` eka liyanawa
                                                    WriteZ<Vector3>(mat + 0x60, targetTeleportPos);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        //if (Tptawore && !IsTeam) {
                        //    uint32_t localRootBonePtr = 0;
                        //    if (ReadZ(localPlayer + Offsets::Bones::Root, localRootBonePtr)) {
                        //        Vector3 localRootPos;
                        //        if (GetNodePosition(localRootBonePtr, localRootPos)) {

                        //            // Tower Root Bone Pointer eka read karaganima
                        //            uint32_t towerRootBonePtr = 0;
                        //            // entity dynamic loop eke thiyena current tower entity pointer eka methanata pass karanna
                        //            if (ReadZ(entity + Offsets::Bones::Head, towerRootBonePtr)) {
                        //                Vector3 towerPos;

                        //                // GetTowerPosition wenuwata project eke already thiyena GetNodePosition use karanna
                        //                if (GetNodePosition(towerRootBonePtr, towerPos)) {

                        //                    if (Vector3::Distance(localRootPos, towerPos) <= TpDistance) {
                        //                        uint32_t t1 = 0, t2 = 0, mat = 0;
                        //                        ReadZ(localRootBonePtr + 0x8, t1);
                        //                        ReadZ(t1 + 0x8, t2);
                        //                        ReadZ(t2 + 0x20, mat);

                        //                        // Matrix position eka overwrite kirima
                        //                        WriteZ<Vector3>(mat + 0x60, towerPos);
                        //                    }
                        //                }
                        //            }
                        //        }
                        //    }
                        //}


                        if (SpinBotEnable) {
                            uint32_t rootBone = 0;
                            if (!ReadZ(localPlayer + Offsets::Bones::Root, rootBone)) continue;

                            uint32_t trans = 0, obj = 0, matrix = 0;
                            if (!ReadZ(rootBone + 0x8, trans)) continue;
                            if (!ReadZ(trans + 0x8, obj)) continue;
                            if (!ReadZ(obj + 0x20, matrix)) continue;

                            // Angle incremental update (Yaw spin around Y-axis)
                            static float angle = 0.0f;
                            angle += SpinBotSpeed;

                            // Normalize angle within 0 to 2*PI (6.2831853f)
                            if (angle >= 6.2831853f) {
                                angle -= 6.2831853f;
                            }

                            // Convert Yaw Angle (Y-axis) to Quaternion
                            // Q = [X: 0, Y: sin(angle/2), Z: 0, W: cos(angle/2)]
                            Quaternion spinRot{};
                            spinRot.X = 0.0f;
                            spinRot.Y = sinf(angle * 0.5f);
                            spinRot.Z = 0.0f;
                            spinRot.W = cosf(angle * 0.5f);

                            // Overwrite the Transform Matrix Quaternion
                            WriteZ<Quaternion>(matrix + 0x70, spinRot);
                        }



                        if (EnemyPullEnabledHeadV2 && !IsTeam && localPlayer != 0) {
                            static std::unordered_map<uint32_t, Vector3> originalPositions;
                            static std::chrono::steady_clock::time_point lastPullTime;
                            static uint32_t lastPulledEnemy = 0;
                            static int safetyCounter = 0;

                            bool isFiring = false;
                            if (ReadZ(localPlayer + Offsets::sAim1, isFiring) && isFiring)
                            {
                                auto now = std::chrono::steady_clock::now();
                                auto timeSinceLastPull = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPullTime).count();

                                // Safeguard: Prevent rapid pulling (at least 400ms)
                                if (timeSinceLastPull > 400 + (rand() % 200))
                                {
                                    safetyCounter++;
                                    if (safetyCounter % 20 == 0) {
                                        originalPositions.clear();
                                    }

                                    float closestDistance = FLT_MAX;
                                    uint32_t bestEnemy = 0;
                                    Vector3 enemyOriginalHeadPos;

                                    for (int j = 0; j < entitiesCount; j++)
                                    {
                                        uint32_t targetEntity = 0;
                                        if (!ReadZ((uintptr_t)(j * 0x10 + entities), targetEntity) || targetEntity == 0 || targetEntity == localPlayer) continue;

                                        bool isDead = false;
                                        if (!ReadZ(targetEntity + Offsets::Player_IsDead, isDead) || isDead) continue;

                                        bool isKnocked = false;
                                        uint32_t shadowBase;
                                        if (ReadZ(targetEntity + Offsets::Player_ShadowBase, shadowBase) && shadowBase)
                                        {
                                            int xpose;
                                            if (ReadZ(shadowBase + Offsets::XPose, xpose) && xpose == 8) isKnocked = true;
                                        }
                                        if (isKnocked) continue;

                                        bool isTeamMate = false;
                                        uint32_t avatarManager = 0;
                                        if (ReadZ(targetEntity + Offsets::AvatarManager, avatarManager) && avatarManager != 0)
                                        {
                                            uint32_t avatar = 0;
                                            if (ReadZ(avatarManager + Offsets::Avatar, avatar) && avatar != 0)
                                            {
                                                uint32_t avatarData = 0;
                                                if (ReadZ(avatar + Offsets::Avatar_Data, avatarData) && avatarData != 0)
                                                {
                                                    ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeamMate);
                                                }
                                            }
                                        }
                                        if (isTeamMate) continue;

                                        uint32_t enemyHeadBonePtr;
                                        Vector3 enemyHeadPos = Vector3::Zero();
                                        if (ReadZ(targetEntity + Offsets::Bones::Head, enemyHeadBonePtr))
                                        {
                                            if (GetNodePosition(enemyHeadBonePtr, enemyHeadPos))
                                            {
                                                ImVec2 screenPos = WorldToScreenImVec2(viewMatrix, enemyHeadPos, width, height);

                                                if (screenPos.x >= -500 && screenPos.x <= width + 500 &&
                                                    screenPos.y >= -500 && screenPos.y <= height + 500)
                                                {
                                                    float dx = screenPos.x - (width / 2.0f);
                                                    float dy = screenPos.y - (height / 2.0f);
                                                    float distanceToCenter = sqrt(dx * dx + dy * dy);

                                                    // Safeguard: Random weighted selection
                                                    float randomFactor = 1.0f + (rand() % 100) * 0.01f;
                                                    float weightedDistance = distanceToCenter * randomFactor;

                                                    if (weightedDistance < closestDistance)
                                                    {
                                                        closestDistance = weightedDistance;
                                                        bestEnemy = targetEntity;
                                                        enemyOriginalHeadPos = enemyHeadPos;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    if (bestEnemy != 0 && closestDistance < 1000.0f)
                                    {
                                        // Safeguard: Don't pull same enemy twice too quickly
                                        if (!(bestEnemy == lastPulledEnemy && timeSinceLastPull < 1000)) {
                                            lastPulledEnemy = bestEnemy;
                                            lastPullTime = now;

                                            uint32_t enemyRootBonePtr;
                                            if (ReadZ(bestEnemy + Offsets::Bones::Root, enemyRootBonePtr))
                                            {
                                                uint32_t enemyTransformValue;
                                                if (ReadZ(enemyRootBonePtr + 0x8, enemyTransformValue))
                                                {
                                                    uint32_t enemyTransformObjPtr;
                                                    if (ReadZ(enemyTransformValue + 0x8, enemyTransformObjPtr))
                                                    {
                                                        uint32_t enemyMatrixValue;
                                                        if (ReadZ(enemyTransformObjPtr + 0x20, enemyMatrixValue))
                                                        {
                                                            uintptr_t positionOffset = (rand() % 5 == 0) ? 0x90 : 0x80;

                                                            Vector3 currentRootPos;
                                                            if (ReadZ<Vector3>(enemyMatrixValue + positionOffset, currentRootPos))
                                                            {
                                                                float currentDistance = Vector3::Distance(mainPos, enemyOriginalHeadPos);
                                                                float pullPercentage = 0.3f + (rand() % 40) * 0.01f;

                                                                Vector3 forwardDir = Vector3(
                                                                    viewMatrix.m02 + (rand() % 100 - 50) * 0.001f,
                                                                    viewMatrix.m12 + (rand() % 100 - 50) * 0.001f,
                                                                    viewMatrix.m22 + (rand() % 100 - 50) * 0.001f
                                                                );

                                                                Vector3 newHeadPos = mainPos + (forwardDir * currentDistance * pullPercentage);
                                                                Vector3 offset = newHeadPos - enemyOriginalHeadPos;

                                                                float lerpFactor = 0.4f + (rand() % 30) * 0.01f;
                                                                Vector3 newRootPos;
                                                                newRootPos.X = currentRootPos.X + (offset.X * lerpFactor);
                                                                newRootPos.Y = currentRootPos.Y + (offset.Y * lerpFactor * 0.5f);
                                                                newRootPos.Z = currentRootPos.Z + (offset.Z * lerpFactor);

                                                                std::this_thread::sleep_for(std::chrono::microseconds(50 + rand() % 100));
                                                                WriteZ<Vector3>(enemyMatrixValue + positionOffset, newRootPos);

                                                                if (originalPositions.find(bestEnemy) == originalPositions.end()) {
                                                                    originalPositions[bestEnemy] = currentRootPos;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else if (!originalPositions.empty())
                            {
                                for (const auto& entry : originalPositions)
                                {
                                    uint32_t enemyId = entry.first;
                                    Vector3 originalPos = entry.second;
                                    uint32_t enemyRootBonePtr;
                                    if (ReadZ(enemyId + Offsets::Bones::Root, enemyRootBonePtr))
                                    {
                                        uint32_t enemyTransformValue, clientTransformObjPtr, enemyMatrixValue;
                                        if (ReadZ(enemyRootBonePtr + 0x8, enemyTransformValue) &&
                                            ReadZ(enemyTransformValue + 0x8, clientTransformObjPtr) &&
                                            ReadZ(clientTransformObjPtr + 0x20, enemyMatrixValue))
                                        {
                                            WriteZ<Vector3>(enemyMatrixValue + 0x0, originalPos);
                                        }
                                    }
                                }
                                originalPositions.clear();
                                lastPulledEnemy = 0;
                            }
                        }


















                        if (FovEnable)
                        {
                            ImGuiIO& io = ImGui::GetIO();
                            ImVec2 center(io.DisplaySize.x / 2.0f, io.DisplaySize.y / 2.0f);
                            DrawSmoothCircle(center, fov, 1.0f);
                        }





                        if (TeleKill == true && !IsTeam)
                        {
                            float closestDistance = FLT_MAX;
                            uint32_t bestEnemy = 0;
                            Vector3 localHeadPos;

                            uint32_t localHeadBonePtr;

                            if (ReadZ(localPlayer + Offsets::Bones::Head, localHeadBonePtr))
                            {
                                if (GetNodePosition(localHeadBonePtr, localHeadPos))
                                {

                                    uint32_t entity = 0;
                                    if (!ReadZ((uintptr_t)(i * 0x4 + entities), entity)) continue;

                                    bool isDead = false;
                                    if (!ReadZ(entity + Offsets::Player_IsDead, isDead) || isDead) continue;

                                    uint32_t enemyHeadBonePtr;
                                    if (ReadZ(entity + Offsets::Bones::Head, enemyHeadBonePtr))
                                    {
                                        Vector3 enemyHeadPos;
                                        if (GetNodePosition(enemyHeadBonePtr, enemyHeadPos))
                                        {

                                            float playerDistance = Vector3::Distance(localHeadPos, enemyHeadPos);
                                            if (playerDistance > enemyplayerdistance) continue;

                                            if (playerDistance < closestDistance)
                                            {
                                                closestDistance = playerDistance;
                                                bestEnemy = entity;
                                            }
                                        }
                                    }


                                    if (bestEnemy != 0)
                                    {
                                        uint32_t enemyHeadBonePtr2;
                                        if (ReadZ(bestEnemy + Offsets::Bones::Head, enemyHeadBonePtr2))
                                        {
                                            Vector3 enemyHeadPosNow;
                                            if (!GetNodePosition(enemyHeadBonePtr2, enemyHeadPosNow)) continue;


                                            uint32_t enemyTransformValue;
                                            if (!ReadZ(enemyHeadBonePtr2 + 0x8, enemyTransformValue)) continue;

                                            uint32_t enemyTransformObjPtr;
                                            if (!ReadZ(enemyTransformValue + 0x8, enemyTransformObjPtr)) continue;

                                            uint32_t enemyMatrixValue;
                                            if (!ReadZ(enemyTransformObjPtr + 0x20, enemyMatrixValue)) continue;

                                            // Mevcut root pozisyonunu oku
                                            Vector3 enemyRootPos;
                                            if (!ReadZ<Vector3>(enemyMatrixValue + 0x80, enemyRootPos)) {

                                            }


                                            Vector3 offset;
                                            offset.X = localHeadPos.X - enemyHeadPosNow.X;
                                            offset.Y = localHeadPos.Y - enemyHeadPosNow.Y;
                                            offset.Z = localHeadPos.Z - enemyHeadPosNow.Z;

                                            Vector3 newRootPos;
                                            newRootPos.X = enemyRootPos.X + offset.X;
                                            newRootPos.Y = enemyRootPos.Y + offset.Y;
                                            newRootPos.Z = enemyRootPos.Z + offset.Z;

                                            WriteZ<float>(enemyMatrixValue + 0x80, newRootPos.X);
                                            WriteZ<float>(enemyMatrixValue + 0x84, newRootPos.Y);
                                            WriteZ<float>(enemyMatrixValue + 0x88, newRootPos.Z);
                                        }
                                    }
                                }
                            }
                        }



                        if (headtraking == true && !IsTeam) {

                            ImVec2 screenCenter(g_windowWidth / 2, g_windowHeight / 2);
                            POINT middlePos;



                            bool isKeyPressed = false;

                            bool isRightButtonPressed = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
                            bool isLeftButtonPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

                            switch (selectedKey) {
                            case AimKey::LeftMouseButton:
                                isKeyPressed = isRightButtonPressed || isLeftButtonPressed;
                                break;
                            }

                            if (isKeyPressed) {
                                if (isKnocked) continue;
                                if (isDead) continue;
                                if (DistanceA > AimBotDis) continue;

                                ImVec2 targetScreenPos = WorldToScreenImVec2(viewMatrix, bonePositions.HeadV3, g_windowWidth, g_windowHeight);

                                float distanceToCenter = std::sqrt(std::pow(targetScreenPos.x - screenCenter.x, 2) + std::pow(targetScreenPos.y - screenCenter.y, 2));

                                if (distanceToCenter <= fov) {
                                    ImVec2 targetHeadScreenPos = WorldToScreenImVec2(viewMatrix, bonePositions.HeadV3, g_windowWidth, g_windowHeight);

                                    float deltaX = targetHeadScreenPos.x - screenCenter.x;
                                    float deltaY = targetHeadScreenPos.y - screenCenter.y;

                                    deltaX /= smoothFactor;
                                    deltaY /= smoothFactor;

                                    mouse_event(MOUSEEVENTF_MOVE, static_cast<int>(deltaX), static_cast<int>(deltaY), 0, 0);

                                    std::this_thread::sleep_for(std::chrono::milliseconds(30));
                                }
                            }
                        }

                        /*if (SilentAim && !IsTeam) {
                            ImVec2 screenCtr(g_windowWidth / 2.0f, g_windowHeight / 2.0f);

                             1. කලින් පැවති Arguments 4 සහිත ක්‍රමය
                            ImVec2 targetPos = WorldToScreenImVec2(viewMatrix, bonePositions.HeadV3, g_windowWidth, g_windowHeight);

                            float dx = targetPos.x - screenCtr.x;
                            float dy = targetPos.y - screenCtr.y;
                            float dist = std::sqrt(dx * dx + dy * dy);

                            if (dist <= fov) {
                                bool isFiring = false;
                                if (ReadZ<bool>(localPlayer + Offsets::IS_FIRING, isFiring) && isFiring) {
                                    uint32_t weaponPtr = 0;
                                    if (ReadZ<uint32_t>(localPlayer + Offsets::sAim1, weaponPtr) && weaponPtr) {
                                        Vector3 startPos{};
                                        if (ReadZ<Vector3>(weaponPtr + Offsets::sAim2, startPos)) {

                                            Vector3 targetHead = bonePositions.HeadV3;
                                             Vector3 struct එකේ Capital (X, Y, Z) හෝ Simple (x, y, z) ඇත්දැයි බලන්න
                                            targetHead.Z += 0.1f;

                                            Vector3 dir;
                                            dir.X = targetHead.X - startPos.X;
                                            dir.Y = targetHead.Y - startPos.Y;
                                            dir.Z = targetHead.Z - startPos.Z;

                                             Vector Normalization
                                            float length = std::sqrt(dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z);
                                            if (length > 0.0001f) {
                                                dir.X /= length;
                                                dir.Y /= length;
                                                dir.Z /= length;
                                            }

                                            WriteZ<Vector3>(weaponPtr + Offsets::sAim3, dir);
                                        }
                                    }
                                }
                            }
                        }*/

                        if (Sniper_aim) {

                            // --- Sniper check ---
                            uint32_t weapon = 0;
                            if (!ReadZ(localPlayer + Offsets::Weapon, weapon) || weapon == 0)
                                goto skip_sniper_aimbot;

                            // 1. Must be scoped
                            bool isSighting = false;
                            if (!ReadZ(weapon + Offsets::Weapon_IsSighting, isSighting))
                                isSighting = false;
                            if (!isSighting)
                                goto skip_sniper_aimbot;

                            // 2. Must be a sniper weapon (by reading weapon data)
                            uint32_t weaponData = 0;
                            if (!ReadZ(weapon + Offsets::WeaponData, weaponData) || weaponData == 0)
                                goto skip_sniper_aimbot;

                            // --- FILL IN THE CORRECT OFFSET AND VALUE ---
                            // For example: weapon type might be at weaponData + 0x14
                            // Replace 0x?? with the actual offset and SNIPER_TYPE_ID with the enum/ID for sniper
                            int weaponType = 0;
                            if (!ReadZ(weaponData + 0x14, weaponType))
                                goto skip_sniper_aimbot;
                            const int SNIPER_TYPE_ID = 0x8;  // replace with actual value
                            if (weaponType != SNIPER_TYPE_ID)
                                goto skip_sniper_aimbot;
                            // -------------------------------------------

                            uint32_t bestEntity = 0;
                            Vector3 bestHeadPos;
                            float closestCrosshairDistance = FLT_MAX;
                            Vector3 cameraPosition;
                            Vector2 screenCenter(g_windowWidth / 2.0f, g_windowHeight / 2.0f);

                            bool keyPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
                            if (!keyPressed) goto skip_sniper_aimbot;

                            uint32_t mainCameraTransform;
                            if (!ReadZ(localPlayer + Offsets::MainCameraTransform, mainCameraTransform) || mainCameraTransform == 0)
                                goto skip_sniper_aimbot;

                            if (!GetPosition(mainCameraTransform, cameraPosition))
                                goto skip_sniper_aimbot;

                            for (int i = 0; i < entitiesCount; i++) {
                                // ... (entity loop remains unchanged) ...
                            }

                            if (bestEntity != 0) {
                                auto targetRotation = AimBZ::GetRotationToLocation(bestHeadPos, 0.1f, cameraPosition);
                                WriteZ(localPlayer + Offsets::AimRotation, targetRotation);
                            }

                        skip_sniper_aimbot:;
                        }

                        




                        bool isd;
                        if (ReadZ(entity + Offsets::Player_IsDead, isDead))
                        {
                            if (isDead)
                            {
                                continue;
                            }
                        }



                        //// Global/Static Variables
                        //bool RapidFireXX = false;        // Checkbox එකෙන් control වෙන්නේ මේක
                        //bool RapidFireActiveXX = false;  // Memory එක වෙනස් වුනාද නැද්ද බලන state එක
                        //float SpeedValueX = 2.0f;

                        //uint32_t playerAttrRF = 0;

                        //// 1. Read player attributes pointer safely
                        //if (ReadZ(localPlayer + Offsets::PlayerAttributes, playerAttrRF) && playerAttrRF != 0)
                        //{
                        //    // 2. Additional check: Address eka readable/valid Range ekaka thiyenawada balanna (e.g. > 0x10000)
                        //    if (playerAttrRF > 0x10000)
                        //    {
                        //        if (RapidFireXX)
                        //        {
                        //            // 3. Zero eken divide wima nawathwanna (Divide by zero protection)
                        //            float speed = (SpeedValueX > 0.0f) ? SpeedValueX : 1.0f;
                        //            float fireInterval = 1.0f / speed;

                        //            WriteZ<float>(playerAttrRF + Offsets::m_FireIntervalScale, fireInterval);
                        //            WriteZ<float>(playerAttrRF + Offsets::m_FireIntervalScaleSkill, fireInterval);
                        //            WriteZ<float>(playerAttrRF + Offsets::m_FireIntervalScaleTwo, fireInterval);

                        //            RapidFireActiveXX = true;
                        //        }
                        //        else if (RapidFireActiveXX) // (Methane RapidFireActivekey wenuwata RapidFireActiveXX wenna oni)
                        //        {
                        //            // Reset to default
                        //            WriteZ<float>(playerAttrRF + Offsets::m_FireIntervalScale, 1.0f);
                        //            WriteZ<float>(playerAttrRF + Offsets::m_FireIntervalScaleSkill, 1.0f);
                        //            WriteZ<float>(playerAttrRF + Offsets::m_FireIntervalScaleTwo, 1.0f);

                        //            RapidFireActiveXX = false;
                        //        }
                        //    }
                        //}








                    }
                    
                        if (GetAsyncKeyState(FlyHackinkey) & 0x1)
                        {
                            FlyHackin = !FlyHackin;
                            Beep(FlyHackin ? 1500 : 800, 100);

                        }

                        if (GetAsyncKeyState(dwkey) & 0x1)
                        {
                            DownPlayerEnable = !DownPlayerEnable;
                            Beep(DownPlayerEnable ? 1500 : 800, 100);
                        }
                   
                    if (GetAsyncKeyState(FlyHackinkey) & 0x1)
                    {
                        FlyHackin = !FlyHackin;
                        Beep(FlyHackin ? 1500 : 800, 100);

                    }
                    if (GetAsyncKeyState(tpkey) & 0x1)
                    {
                        TpBaseCheck = !TpBaseCheck;
                        Beep(TpBaseCheck ? 1500 : 800, 100);
                    }
                    if (GetAsyncKeyState(Tptaworekey) & 0x1)
                    {
                        Tptawore = !Tptawore;
                        Beep(Tptawore ? 1500 : 800, 100);

                    }
                    if (GetAsyncKeyState(flykey1) & 0x1)
                    {
                        FlyWall = !FlyWall;
                        Beep(FlyWall ? 1500 : 800, 100);
                    }

                    if (GetAsyncKeyState(TeleportMarkEnablekey) & 0x1)
                    {
                        TeleportMarkEnable = !TeleportMarkEnable;
                        Beep(TeleportMarkEnable ? 1500 : 800, 100);
                    }

                    if (GetAsyncKeyState(TeleportKey) & 0x1)
                    {
                        TeleportBase = !TeleportBase;
                        Beep(TeleportBase ? 1500 : 800, 100);
                    }
                }
            }
            ImGuiStyle* style = &ImGui::GetStyle();

            style->WindowPadding = ImVec2(0, 0);
            style->ItemSpacing = ImVec2(10, 10);
            style->WindowBorderSize = 0;
            style->ScrollbarSize = 8.f;

            static float color[4] = {
                1.00f, // R
                0.00f, // G
                0.00f, // B
                1.00f  // A
            };

            // Bright Cyan / Blue Accent (#00D2FF)
            c::accent = { color[0], color[1], color[2], color[3] };

            if (!hide)
            {
                // Static variables persistence සදහා (Crash වීම වැළැක්වීමට)
                static bool is_authenticating = false;
                static float loading_start_time = 0.0f;
                static bool login_page = true;
                static float login_page_offset = 40.f;
                static float animation_speed = 0.1f;

                // Login කරදර (Error) පණිවිඩය පෙන්වීම සඳහා variables
                static bool login_error = false;
                static float error_time = 0.0f;

                // Password පෙන්වීමට/සැඟවීමට variable එකක්
                static bool show_password = false;

                if (!authed)
                {
                    // ==========================================
                    //  1. CUSTOM ANIMATION (KENZO REGZ - SLOW TYPE)
                    // ==========================================
                    if (is_authenticating)
                    {
                        float elapsed = (float)(ImGui::GetTime() - loading_start_time);

                        ImDrawList* fg_draw = ImGui::GetForegroundDrawList();
                        ImVec2 screen_size = ImGui::GetIO().DisplaySize;

                        // Dark Background Overlay Fade-in
                        float bg_alpha = ImMin(elapsed / 0.8f, 0.85f);
                        fg_draw->AddRectFilled(
                            ImVec2(0, 0),
                            screen_size,
                            ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, bg_alpha))
                        );

                        if (font::hoverfront) ImGui::PushFont(font::hoverfront);
                        ImGui::SetWindowFontScale(2.2f);

                        // Stage 1: "K" Letter Pulse (0.0s to 1.5s)
                        if (elapsed < 1.5f)
                        {
                            float pulse_alpha = fabsf(sinf(elapsed * 4.188f));
                            std::string j_text = "K";
                            ImVec2 j_size = ImGui::CalcTextSize(j_text.c_str());
                            ImVec2 j_pos = ImVec2((screen_size.x - j_size.x) / 2.0f, (screen_size.y - j_size.y) / 2.0f);

                            // Glow Shadow Effect
                            ImU32 j_shadow_color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, pulse_alpha * 0.3f));
                            for (float x = -2.0f; x <= 2.0f; x += 2.0f) {
                                for (float y = -2.0f; y <= 2.0f; y += 2.0f) {
                                    fg_draw->AddText(ImVec2(j_pos.x + x, j_pos.y + y), j_shadow_color, j_text.c_str());
                                }
                            }

                            ImU32 j_color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, pulse_alpha));
                            fg_draw->AddText(j_pos, j_color, j_text.c_str());
                        }
                        // Stage 2: Full Text Reveal "KENZO REGZ !" (1.5s to 4.5s)
                        else
                        {
                            float text_elapsed = elapsed - 1.5f;
                            std::string full_kenzo = "KENZO ";
                            std::string full_regz = "REGZ ";

                            float progress = ImMin(text_elapsed / 3.0f, 1.0f);
                            int total_chars = (int)(progress * (full_kenzo.length() + full_regz.length()));

                            int kenzo_chars = ImMin(total_chars, (int)full_kenzo.length());
                            int Regz_chars = ImClamp(total_chars - (int)full_kenzo.length(), 0, (int)full_regz.length());

                            std::string visible_kenzo = full_kenzo.substr(0, kenzo_chars);
                            std::string visible_regz = full_regz.substr(0,Regz_chars);

                            ImVec2 kenzo_size = ImGui::CalcTextSize(full_kenzo.c_str());
                            ImVec2 regz_size = ImGui::CalcTextSize(full_regz.c_str());
                            float total_width = kenzo_size.x + regz_size.x;

                            ImVec2 start_pos = ImVec2((screen_size.x - total_width) / 2.0f, (screen_size.y - kenzo_size.y) / 2.0f);

                            // "KENZO" Text Glow
                            if (kenzo_chars > 0)
                            {
                                ImU32 kenzo_shadow = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 0.25f));
                                for (float x = -2.0f; x <= 2.0f; x += 1.0f) {
                                    for (float y = -2.0f; y <= 2.0f; y += 1.0f) {
                                        fg_draw->AddText(ImVec2(start_pos.x + x, start_pos.y + y), kenzo_shadow, visible_kenzo.c_str());
                                    }
                                }
                                fg_draw->AddText(start_pos, ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), visible_kenzo.c_str());
                            }

                            // "REGZ" Blue Accent Glow
                            if (Regz_chars > 0)
                            {
                                ImVec2 regz_pos = ImVec2(start_pos.x + kenzo_size.x, start_pos.y);
                                ImU32 regz_accent = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                                ImU32 regz_shadow = ImGui::ColorConvertFloat4ToU32(ImVec4(0.28f, 0.56f, 0.85f, 0.35f));

                                for (float x = -2.0f; x <= 2.0f; x += 1.0f) {
                                    for (float y = -2.0f; y <= 2.0f; y += 1.0f) {
                                        fg_draw->AddText(ImVec2(regz_pos.x + x, regz_pos.y + y), regz_shadow, visible_regz.c_str());
                                    }
                                }
                                fg_draw->AddText(regz_pos, regz_accent, visible_regz.c_str());
                            }

                            if (elapsed >= 5.0f)
                            {
                                is_authenticating = false;
                                authed = true;
                            }
                        }

                        ImGui::SetWindowFontScale(1.0f);
                        if (font::hoverfront) ImGui::PopFont();
                    }
                    // ==========================================
                    //  2. NORMAL LOGIN FORM (PHOTO MATCHED THEME)
                    // ==========================================
                    else
                    {
                        ImGui::SetNextWindowSize(c::background::size2);

                        // Dark Clean Background Styles
                        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 0.0f, 0.0f, 0.98f));
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

                        ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
                        {
                            LoadCredentials();

                            ImVec2 pos = ImGui::GetWindowPos();
                            ImVec2 size = c::background::size2;
                            ImDrawList* draw = ImGui::GetWindowDrawList();

                            // Clear Background Fill
                            draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.01f, 0.02f, 0.04f, 1.0f)), 12.0f);

                            // Particles Effect
                            ParticlesV();

                            // ----------------------------------------------------
                            // TOP RIGHT CLOSE BUTTON (X)
                            // ----------------------------------------------------
                            ImGui::SetCursorPos(ImVec2(size.x - 30, 10));
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
                            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.20f, 0.85f, 0.45f, 1.0f));
                            if (ImGui::Button("X", ImVec2(20, 20)))
                            {
                                hide = true;
                            }
                            ImGui::PopStyleColor(4);

                            // ----------------------------------------------------
                            // TITLE HEADER: "KENZO REGZ"
                            // ----------------------------------------------------
                            if (font::Kenzofront) ImGui::PushFont(font::Kenzofront);

                            std::string title_main = "KENZO ";
                            std::string title_accent = "REGZ";
                            ImVec2 main_size = ImGui::CalcTextSize(title_main.c_str());
                            ImVec2 accent_size = ImGui::CalcTextSize(title_accent.c_str());

                            float total_title_width = main_size.x + accent_size.x;
                            ImVec2 title_pos = ImVec2(pos.x + (size.x - total_title_width) / 2.0f, pos.y + 40.0f);

                            // Cyan / Light Blue for "KENZO"
                            draw->AddText(title_pos, ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f)), title_main.c_str());

                            // White with Glow effect for "REGZ"
                            ImVec2 accent_pos = ImVec2(title_pos.x + main_size.x, title_pos.y);
                            draw->AddText(ImVec2(accent_pos.x + 1, accent_pos.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 0.3f)), title_accent.c_str());
                            draw->AddText(accent_pos, ImGui::ColorConvertFloat4ToU32(ImVec4(0.9f, 0.9f, 0.95f, 1.0f)), title_accent.c_str());

                            if (font::Kenzofront) ImGui::PopFont();

                            // ----------------------------------------------------
                            // FORM INPUTS AREA
                            // ----------------------------------------------------
                            login_page_offset = ImLerp(login_page_offset, login_page ? (size.x - 240.0f) / 2.0f : -100.f, animation_speed);

                            ImGui::SetCursorPos(ImVec2(login_page_offset, 110));
                            ImGui::BeginChild("Inputs", ImVec2(260, 210), false, ImGuiWindowFlags_NoBackground);
                            {
                                ImGuiInputTextFlags password_flags = show_password ? 0 : ImGuiInputTextFlags_Password;

                                // Frame Styling for Inputs
                                ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.01f, 0.07f, 0.035f, 0.95f));
                                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.10f, 0.45f, 0.22f, 0.9f));
                                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
                                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

                                // 1. Username Field
                                ImGui::SetNextItemWidth(210);
                                ImGui::InputTextExNew("v", "Username", username, IM_ARRAYSIZE(username), ImVec2(210, 36), 0, 0, 0);
                                ImGui::SameLine();
                                ImGui::SetCursorPosX(222);
                                ImGui::GetWindowDrawList()->AddCircleFilled(
                                    ImVec2(ImGui::GetCursorScreenPos().x + 8, ImGui::GetCursorScreenPos().y + 18),
                                    6.0f,
                                    ImGui::ColorConvertFloat4ToU32(ImVec4(0.3f, 0.35f, 0.4f, 1.0f))
                                );
                                ImGui::Dummy(ImVec2(16, 36));

                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);

                                // 2. Password Field
                                ImGui::SetNextItemWidth(210);
                                ImGui::InputTextExNew("x", "Password", password, IM_ARRAYSIZE(password), ImVec2(210, 36), password_flags, 0, 0);
                                ImGui::SameLine();
                                ImGui::SetCursorPosX(222);
                                ImGui::GetWindowDrawList()->AddCircleFilled(
                                    ImVec2(ImGui::GetCursorScreenPos().x + 8, ImGui::GetCursorScreenPos().y + 18),
                                    6.0f,
                                    ImGui::ColorConvertFloat4ToU32(ImVec4(0.3f, 0.35f, 0.4f, 1.0f))
                                );
                                ImGui::Dummy(ImVec2(16, 36));

                                ImGui::PopStyleVar(2);
                                ImGui::PopStyleColor(2);

                                // 3. Show Password Toggle (Circle Switch)
                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Show Password");
                                ImGui::SameLine();
                                ImGui::SetCursorPosX(222);

                                ImVec2 p_pos = ImGui::GetCursorScreenPos();
                                bool clicked = ImGui::InvisibleButton("##show_pwd_toggle", ImVec2(16, 16));
                                if (clicked) show_password = !show_password;

                                ImU32 circle_col = show_password ?
                                    ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f)) :
                                    ImGui::ColorConvertFloat4ToU32(ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

                                ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(p_pos.x + 8, p_pos.y + 8), 6.0f, circle_col);

                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);

                                // 4. Blue Rounded Login Button ("Login >")
                                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.15f, 0.15f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.0f, 0.0f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.05f, 0.08f, 0.12f, 1.0f));
                                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

                                if (ImGui::Button("Login >", ImVec2(240, 36)))
                                {
                                    // Validation logic
                                    if (std::string(username) == "knzz" && std::string(password) == "1")
                                    {
                                        login_error = false;
                                        is_authenticating = true;
                                        loading_start_time = (float)ImGui::GetTime();
                                    }
                                    else
                                    {
                                        login_error = true;
                                        error_time = (float)ImGui::GetTime();
                                    }

                                    // Validation logic
                                    if (std::string(username) == "guild" && std::string(password) == "1")
                                    {
                                        login_error = false;
                                        is_authenticating = true;
                                        loading_start_time = (float)ImGui::GetTime();
                                    }
                                    else
                                    {
                                        login_error = true;
                                        error_time = (float)ImGui::GetTime();
                                    }

                                    // Validation logic
                                    if (std::string(username) == "k" && std::string(password) == "1")
                                    {
                                        login_error = false;
                                        is_authenticating = true;
                                        loading_start_time = (float)ImGui::GetTime();
                                    }
                                    else
                                    {
                                        login_error = true;
                                        error_time = (float)ImGui::GetTime();
                                    }

                                    // Validation logic
                                    if (std::string(username) == "induu" && std::string(password) == "1")
                                    {
                                        login_error = false;
                                        is_authenticating = true;
                                        loading_start_time = (float)ImGui::GetTime();
                                    }
                                    else
                                    {
                                        login_error = true;
                                        error_time = (float)ImGui::GetTime();
                                    }
                                }


                                ImGui::PopStyleVar();
                                ImGui::PopStyleColor(4);
                            }
                            ImGui::EndChild();

                            // ----------------------------------------------------
                            // FOOTER SECTION: REGISTER LINK & COPYRIGHT
                            // ----------------------------------------------------
                            ImGui::SetCursorPos(ImVec2(0, size.y - 75));
                            ImGui::BeginGroup();
                            {
                                float footer_width = ImGui::CalcTextSize("Don't have an account?  Register").x;
                                ImGui::SetCursorPosX((size.x - footer_width) / 2.0f);

                                ImGui::TextColored(ImVec4(0.6f, 0.65f, 0.7f, 1.0f), "Don't have an account?");
                                ImGui::SameLine();

                                // Blue Register Link
                                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                                if (ImGui::Selectable("Register", false, ImGuiSelectableFlags_DontClosePopups, ImGui::CalcTextSize("Register")))
                                {
                                    ShellExecuteA(NULL, "open", "https://discord.gg/swN9e4XJ3", NULL, NULL, SW_SHOW);
                                }
                                ImGui::PopStyleColor();
                            }
                            ImGui::EndGroup();

                            // Copyright Text
                            std::string copyright_text = "kenzoregzprem \xC2\xA9 copyright 2026";
                            float copy_width = ImGui::CalcTextSize(copyright_text.c_str()).x;
                            ImGui::SetCursorPos(ImVec2((size.x - copy_width) / 2.0f, size.y - 30));
                            ImGui::TextColored(ImVec4(0.35f, 0.4f, 0.45f, 0.8f), "%s", copyright_text.c_str());

                            // ----------------------------------------------------
                            // ERROR MESSAGE DISPLAY
                            // ----------------------------------------------------
                            if (login_error)
                            {
                                draw->AddText(
                                    ImVec2(pos.x + 10, pos.y + size.y - 15),
                                    ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.2f, 0.2f, 1.0f)),
                                    "Invalid Username or Password!Contact KENZO"
                                );

                                if (ImGui::GetTime() - error_time > 3.0f)
                                {
                                    login_error = false;
                                }
                            }

                            ImGui::End();
                        }
                        ImGui::PopStyleVar(2);
                        ImGui::PopStyleColor();
                    }
                }
            
            
            
            
            
            
            
            


                
                if (authed == true)
                {
                    // Persistent window position (saved between frames)
                    static ImVec2 menuPos = ImVec2(0, 0);

                    // Main UI Window corner rounding
                    float windowCornerRounding = 18.0f;

                    // Set position only on first use; then allow dragging
                    ImGui::SetNextWindowPos(menuPos, ImGuiCond_FirstUseEver);
                    ImGui::SetNextWindowSize(c::background::size);

                    // Begin the window once
                    if (ImGui::Begin("Menu", nullptr,
                        ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoCollapse |
                        ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoBackground |
                        ImGuiWindowFlags_NoBringToFrontOnFocus |
                        ImGuiWindowFlags_NoScrollWithMouse))
                    {
                        // ─── Particle Network / Constellation Overlay Effect ───
                        struct Particle {
                            ImVec2 pos;
                            ImVec2 vel;
                            float radius;
                        };

                        const int MAX_PARTICLES = 45;
                        static std::vector<Particle> particles;
                        static bool particlesInitialized = false;

                        ImVec2 displaySize = ImGui::GetIO().DisplaySize;

                        if (!particlesInitialized) {
                            particles.resize(MAX_PARTICLES);
                            for (int i = 0; i < MAX_PARTICLES; i++) {
                                particles[i].pos = ImVec2((float)(rand() % (int)displaySize.x), (float)(rand() % (int)displaySize.y));
                                particles[i].vel = ImVec2(((float)(rand() % 100) / 100.0f - 0.5f) * 0.8f, ((float)(rand() % 100) / 100.0f - 0.5f) * 0.8f);
                                particles[i].radius = 1.5f + (float)(rand() % 20) / 10.0f;
                            }
                            particlesInitialized = true;
                        }

                        ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();

                        // Particle Movement & Screen Boundary Check
                        for (int i = 0; i < MAX_PARTICLES; i++) {
                            particles[i].pos.x += particles[i].vel.x;
                            particles[i].pos.y += particles[i].vel.y;

                            if (particles[i].pos.x < 0 || particles[i].pos.x > displaySize.x) particles[i].vel.x *= -1;
                            if (particles[i].pos.y < 0 || particles[i].pos.y > displaySize.y) particles[i].vel.y *= -1;

                            // Simple Minimal Particle Glow
                            bgDrawList->AddCircleFilled(particles[i].pos, particles[i].radius, ImGui::GetColorU32(c::accent, 0.80f), 16);
                        }

                        // Connecting lines between close particles
                        const float connectionDistance = 140.0f;
                        for (int i = 0; i < MAX_PARTICLES; i++) {
                            for (int j = i + 1; j < MAX_PARTICLES; j++) {
                                float dx = particles[i].pos.x - particles[j].pos.x;
                                float dy = particles[i].pos.y - particles[j].pos.y;
                                float dist = sqrtf(dx * dx + dy * dy);

                                if (dist < connectionDistance) {
                                    float alpha = (1.0f - (dist / connectionDistance)) * 0.35f;
                                    bgDrawList->AddLine(particles[i].pos, particles[j].pos, ImGui::GetColorU32(c::accent, alpha), 1.0f);
                                }
                            }
                        }

                        // ─── Window Coordinates ───
                        const ImVec2 pos = ImGui::GetWindowPos();
                        const ImVec2 winSize = ImGui::GetWindowSize();

                        ImDrawList* draw = ImGui::GetForegroundDrawList();
                        ImDrawList* windowDraw = ImGui::GetWindowDrawList();

                        // ─── Pitch Dark Base Window Background ───
                        ImU32 deepDarkBg = IM_COL32(10, 10, 14, 255);
                        windowDraw->AddRectFilled(pos, pos + winSize, deepDarkBg, windowCornerRounding);

                        // ─── INTERNAL INNER GLOW SHADOW (Top-Right & Bottom-Left) ───
                        // 1. Top-Right Corner Inner Glow Shadow
                        ImVec2 trGlowCenter = ImVec2(pos.x + winSize.x - 20.0f, pos.y + 20.0f);
                        for (int i = 12; i >= 1; i--) {
                            float radius = 40.0f + (i * 9.0f);
                            float alpha = 0.06f * (1.0f - ((float)i / 13.0f));
                            windowDraw->AddCircleFilled(trGlowCenter, radius, ImGui::GetColorU32(c::accent, alpha), 36);
                        }

                        // 2. Bottom-Left Corner Inner Glow Shadow
                        ImVec2 blGlowCenter = ImVec2(pos.x + 20.0f, pos.y + winSize.y - 20.0f);
                        for (int i = 12; i >= 1; i--) {
                            float radius = 40.0f + (i * 9.0f);
                            float alpha = 0.06f * (1.0f - ((float)i / 13.0f));
                            windowDraw->AddCircleFilled(blGlowCenter, radius, ImGui::GetColorU32(c::accent, alpha), 36);
                        }

                        // ─── ADJUSTED INNER CONTAINER & BORDER LINE ───
                        float innerMarginLeft = 58.0f;
                        float innerMarginTop = 54.0f;
                        float innerMarginRight = 2.0f;
                        float innerMarginBottom = 2.0f;

                        ImVec2 innerMin = ImVec2(pos.x + innerMarginLeft, pos.y + innerMarginTop);
                        ImVec2 innerMax = ImVec2(pos.x + winSize.x - innerMarginRight, pos.y + winSize.y - innerMarginBottom);
                        float innerRounding = 12.0f;

                        // Inner Content Container Background
                        windowDraw->AddRectFilled(innerMin, innerMax, IM_COL32(16, 17, 23, 255), innerRounding);

                        // Border Line for Inner Container
                        windowDraw->AddRect(innerMin, innerMax, IM_COL32(40, 44, 58, 255), innerRounding, 0, 1.5f);

                        // ─── Top Notification Banner Attached to Window ───
                        const char* bannerText = "This is Only REGED!Tz MEMBERS PREMIUM PANAL Don't Share It others.";
                        ImVec2 bannerTextSize = ImGui::CalcTextSize(bannerText);

                        float bannerPaddingY = 5.0f;
                        float bannerPaddingX = 18.0f;
                        float bannerHeight = bannerTextSize.y + (bannerPaddingY * 2.0f);
                        float bannerWidth = bannerTextSize.x + (bannerPaddingX * 2.0f);

                        ImVec2 bannerPos = ImVec2(pos.x + (winSize.x - bannerWidth) * 0.5f, pos.y - bannerHeight - 12.0f);

                        ImU32 bannerBgColor = IM_COL32(235, 40, 55, 225);
                        ImU32 bannerBorderColor = IM_COL32(255, 100, 110, 255);
                        float bannerRounding = 5.0f;

                        draw->AddRectFilled(bannerPos, ImVec2(bannerPos.x + bannerWidth, bannerPos.y + bannerHeight), bannerBgColor, bannerRounding);
                        draw->AddRect(bannerPos, ImVec2(bannerPos.x + bannerWidth, bannerPos.y + bannerHeight), bannerBorderColor, bannerRounding, 0, 1.2f);
                        draw->AddText(ImVec2(bannerPos.x + bannerPaddingX, bannerPos.y + bannerPaddingY), IM_COL32(255, 255, 255, 255), bannerText);

                        // ─── Clean Ninja + Serpent Logo Renderer ───
                        auto DrawNinjaLogo = [](ImDrawList* draw, ImVec2 pos, float size, ImU32 mainColor, ImU32 eyeColor, ImU32 bgColor)
                            {
                                float s = size / 40.0f;

                                draw->AddCircleFilled(ImVec2(pos.x + 16 * s, pos.y + 16 * s), 11.5f * s, mainColor, 24);

                                draw->PathClear();
                                draw->PathLineTo(ImVec2(pos.x + 4 * s, pos.y + 20 * s));
                                draw->PathBezierCubicCurveTo(
                                    ImVec2(pos.x - 2 * s, pos.y + 8 * s),
                                    ImVec2(pos.x + 10 * s, pos.y - 2 * s),
                                    ImVec2(pos.x + 24 * s, pos.y + 2 * s)
                                );
                                draw->PathBezierCubicCurveTo(
                                    ImVec2(pos.x + 18 * s, pos.y + 6 * s),
                                    ImVec2(pos.x + 6 * s, pos.y + 12 * s),
                                    ImVec2(pos.x + 8 * s, pos.y + 22 * s)
                                );
                                draw->PathFillConvex(mainColor);

                                draw->PathClear();
                                draw->PathLineTo(ImVec2(pos.x + 16 * s, pos.y + 6 * s));
                                draw->PathBezierCubicCurveTo(
                                    ImVec2(pos.x + 28 * s, pos.y + 1 * s),
                                    ImVec2(pos.x + 36 * s, pos.y + 7 * s),
                                    ImVec2(pos.x + 39 * s, pos.y + 14 * s)
                                );
                                draw->PathBezierCubicCurveTo(
                                    ImVec2(pos.x + 30 * s, pos.y + 17 * s),
                                    ImVec2(pos.x + 22 * s, pos.y + 14 * s),
                                    ImVec2(pos.x + 19 * s, pos.y + 18 * s)
                                );
                                draw->PathFillConvex(mainColor);

                                draw->PathClear();
                                draw->PathLineTo(ImVec2(pos.x + 22 * s, pos.y + 19 * s));
                                draw->PathBezierCubicCurveTo(
                                    ImVec2(pos.x + 38 * s, pos.y + 20 * s),
                                    ImVec2(pos.x + 40 * s, pos.y + 35 * s),
                                    ImVec2(pos.x + 20 * s, pos.y + 39 * s)
                                );
                                draw->PathBezierCubicCurveTo(
                                    ImVec2(pos.x + 32 * s, pos.y + 32 * s),
                                    ImVec2(pos.x + 31 * s, pos.y + 23 * s),
                                    ImVec2(pos.x + 21 * s, pos.y + 23 * s)
                                );
                                draw->PathFillConvex(mainColor);

                                ImVec2 maskCenter = ImVec2(pos.x + 15.5f * s, pos.y + 14.0f * s);
                                draw->AddEllipseFilled(maskCenter, 7.0f * s, 3.8f * s, bgColor, 0.0f, 16);

                                draw->AddCircleFilled(maskCenter, 3.8f * s, ImGui::GetColorU32(c::accent, 0.35f), 16);
                                draw->AddCircleFilled(maskCenter, 2.5f * s, eyeColor, 16);

                                draw->AddLine(ImVec2(pos.x + 22 * s, pos.y + 14 * s), ImVec2(pos.x + 27 * s, pos.y + 12 * s), eyeColor, 1.5f * s);
                                draw->AddLine(ImVec2(pos.x + 27 * s, pos.y + 12 * s), ImVec2(pos.x + 30 * s, pos.y + 10 * s), eyeColor, 1.2f * s);
                                draw->AddLine(ImVec2(pos.x + 27 * s, pos.y + 12 * s), ImVec2(pos.x + 30 * s, pos.y + 14 * s), eyeColor, 1.2f * s);
                            };

                        // ─── Watermark Loop ───
                        static float wmProgress = 0.0f;
                        wmProgress += ImGui::GetIO().DeltaTime * 130.0f;

                        const char* wmText = "</> Kenzo";
                        ImVec2 wmSize = ImGui::CalcTextSize(wmText);

                        float pad = 10.0f;
                        float leftX = pos.x + pad;
                        float rightX = pos.x + winSize.x - wmSize.x - pad;
                        float topY = pos.y + pad;
                        float bottomY = pos.y + winSize.y - wmSize.y - pad;

                        float widthLimit = rightX - leftX;
                        float heightLimit = bottomY - topY;
                        float totalPerimeter = (widthLimit + heightLimit) * 2.0f;

                        float currentProgress = fmodf(wmProgress, totalPerimeter);
                        ImVec2 curPos;

                        if (currentProgress < widthLimit) {
                            curPos = ImVec2(leftX + currentProgress, topY);
                        }
                        else if (currentProgress < widthLimit + heightLimit) {
                            curPos = ImVec2(rightX, topY + (currentProgress - widthLimit));
                        }
                        else if (currentProgress < (widthLimit * 2.0f) + heightLimit) {
                            curPos = ImVec2(rightX - (currentProgress - (widthLimit + heightLimit)), bottomY);
                        }
                        else {
                            curPos = ImVec2(leftX, bottomY - (currentProgress - ((widthLimit * 2.0f) + heightLimit)));
                        }

                        ImU32 whiteGlowColor = IM_COL32(255, 255, 255, 120);
                        ImU32 softOuterWhiteGlow = IM_COL32(255, 255, 255, 40);

                        for (float r = 1.5f; r <= 4.5f; r += 1.5f) {
                            windowDraw->AddText(curPos + ImVec2(-r, 0), softOuterWhiteGlow, wmText);
                            windowDraw->AddText(curPos + ImVec2(r, 0), softOuterWhiteGlow, wmText);
                            windowDraw->AddText(curPos + ImVec2(0, -r), softOuterWhiteGlow, wmText);
                            windowDraw->AddText(curPos + ImVec2(0, r), softOuterWhiteGlow, wmText);
                        }

                        windowDraw->AddText(curPos + ImVec2(-1, -1), whiteGlowColor, wmText);
                        windowDraw->AddText(curPos + ImVec2(1, -1), whiteGlowColor, wmText);
                        windowDraw->AddText(curPos + ImVec2(-1, 1), whiteGlowColor, wmText);
                        windowDraw->AddText(curPos + ImVec2(1, 1), whiteGlowColor, wmText);

                        windowDraw->AddText(curPos, IM_COL32(255, 255, 255, 245), wmText);

                        // Main Window Outer Stroke Line
                        windowDraw->AddRect(pos, pos + winSize,
                            ImGui::GetColorU32(c::background::stroke), windowCornerRounding);

                        // ─── TOP HEADER (MATCHED TO REFERENCE IMAGE) ───
                        float logoSize = 42.0f;
                        float start_x = 18.0f;
                        float headerTopY = pos.y + 12.0f;

                        // Render Ninja Logo
                        ImVec2 logoPos = ImVec2(pos.x + start_x, headerTopY);
                        DrawNinjaLogo(draw, logoPos, logoSize, ImGui::GetColorU32(c::accent), ImGui::GetColorU32(c::accent), deepDarkBg);

                        // Calculate Text Alignment & Positions
                        float textStartX = logoPos.x + logoSize + 12.0f;

                        ImGui::PushFont(font::Kenzofront);
                        const char* title1 = "KENZO";
                        const char* title2 = " REGZ";
                        ImVec2 sz1 = ImGui::CalcTextSize(title1);
                        ImVec2 sz2 = ImGui::CalcTextSize(title2);

                        // Render Title Text ("KENZO REGZ")
                        float titleY = headerTopY + (logoSize - sz1.y) * 0.5f - 2.0f;
                        draw->AddText(ImVec2(textStartX, titleY), IM_COL32(255, 255, 255, 255), title1);
                        draw->AddText(ImVec2(textStartX + sz1.x, titleY), ImGui::GetColorU32(c::accent), title2);
                        ImGui::PopFont();

                        // Render Sub-Text (".Premium")
                        float subTextStartX = textStartX + sz1.x + sz2.x + 6.0f;
                        ImGui::PushFont(font::lexend_bold);
                        const char* subText = ".Premium";
                        ImVec2 subSz = ImGui::CalcTextSize(subText);
                        float subTextY = titleY + (sz1.y - subSz.y) * 0.5f + 1.0f;

                        draw->AddText(ImVec2(subTextStartX, subTextY), IM_COL32(140, 145, 160, 200), subText);
                        ImGui::PopFont();

                        // ─── Invisible Drag Area ───
                        float totalHeaderWidth = (subTextStartX + subSz.x) - pos.x;
                        ImGui::SetCursorPos(ImVec2(start_x, 10));
                        ImGui::InvisibleButton("##drag_title", ImVec2(totalHeaderWidth + 40.0f, 55));
                        if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
                        {
                            menuPos = menuPos + ImGui::GetIO().MouseDelta;
                            ImGui::SetWindowPos(menuPos);
                        }

                        // ─── Bottom-Left Profile Avatar Logo ("K" Icon) With Soft Glow Shadow ───
                        float bLogoSize = 42.0f;
                        float bMargin = 15.0f;
                        ImVec2 profileLogoPos = ImVec2(pos.x + bMargin, pos.y + winSize.y - bLogoSize - bMargin);
                        ImVec2 profileCenter = ImVec2(profileLogoPos.x + bLogoSize * 0.5f, profileLogoPos.y + bLogoSize * 0.5f);

                        // J Icon Soft Glow Layers
                        draw->AddCircleFilled(profileCenter, (bLogoSize * 0.5f) + 8.0f, ImGui::GetColorU32(c::accent, 0.15f), 32);
                        draw->AddCircleFilled(profileCenter, (bLogoSize * 0.5f) + 4.0f, ImGui::GetColorU32(c::accent, 0.30f), 32);
                        draw->AddCircleFilled(profileCenter, (bLogoSize * 0.5f) + 1.5f, ImGui::GetColorU32(c::accent, 0.50f), 32);

                        // Base Profile Circle
                        draw->AddCircleFilled(profileCenter, (bLogoSize * 0.5f), ImGui::GetColorU32(c::accent), 32);

                        float jScale = 0.40f;
                        ImFont* jFont = font::hoverfront;
                        float jFontSize = jFont->FontSize * jScale;
                        const char* jChar = "K";
                        ImVec2 jSize = jFont->CalcTextSizeA(jFontSize, FLT_MAX, 0.0f, jChar);

                        draw->AddText(
                            jFont,
                            jFontSize,
                            ImVec2(profileCenter.x - jSize.x * 0.5f, profileCenter.y - jSize.y * 0.5f),
                            IM_COL32_WHITE,
                            jChar
                        );

                        // Green Online Status Dot
                        float dotRadius = 5.0f;
                        ImVec2 dotPos = ImVec2(profileLogoPos.x + bLogoSize - 3.5f, profileLogoPos.y + bLogoSize - 3.5f);
                        draw->AddCircleFilled(dotPos, dotRadius + 1.5f, deepDarkBg, 16);
                        draw->AddCircleFilled(dotPos, dotRadius, IM_COL32(46, 204, 113, 255), 16);
                    
                   
                   
                   
                    
                        

                            
                   
                
                    
                    
                

                    
                    
                    
                    
                
               

                        // ─── Particles (optional) ───
                        if (LineRunning)
                        {
                            LineRunning = true;
                            dot_draw();
                           // DrawBubblesParticles();
                            DrawMouseDot();



                        }
                        else
                        {
                            LineRunning = false;
                            dot_destroy();
                            DrawMouseDot();


                           //  DrawBubblesParticles();


                        }
                        if (DotRunning)
                        {
                            DotRunning = true;
                            ParticlesV();
                            DrawMouseDot();

                           // DrawBubblesParticles();


                        }
                        else
                        {
                            DotRunning = false;
                            Destroy_ParticlesV();
                            DrawMouseDot();

                           // DrawBubblesParticles();


                        }
                        

                        // ─── Sidebar Tabs ───

                    // Sidebar - Vertical at left
                        float tab_size = 40.f;
                        float tab_spacing = 10.f;

                        ImGui::SetCursorPos(ImVec2(10, 80));

                        ImGui::BeginGroup();

                        if (edited::Tab(page == 0, "a", "Aimbot", ImVec2(tab_size, tab_size))) {
                            page = 0;
                        }

                        ImGui::SetCursorPosX(10);

                        if (edited::Tab(page == 1, "q", "ESP", ImVec2(tab_size, tab_size))) {
                            page = 1;
                        }

                        ImGui::SetCursorPosX(10);

                        if (edited::Tab(page == 2, "i", "Fake Lag", ImVec2(tab_size, tab_size))) {
                            page = 2;
                        }

                        ImGui::SetCursorPosX(10);

                        if (edited::Tab(page == 3, "d", "Key Binds", ImVec2(tab_size, tab_size))) {
                            page = 3;
                        }

                        ImGui::SetCursorPosX(10);

                        if (edited::Tab(page == 4, "g", "Settings", ImVec2(tab_size, tab_size))) {
                            page = 4;
                        }

                        ImGui::EndGroup();


                        tab_alpha = ImLerp(tab_alpha, (page == active_tab) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);
                        if (tab_alpha < 0.01f && tab_add < 0.01f) active_tab = page;

                        float content_x = 65.f;
                        float content_width = c::background::size.x - content_x - 15.f;

                        ImGui::SetCursorPos(ImVec2(content_x, 65));

                        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);

                        if (active_tab == 0)
                        {
                            // Aimbot Functions
                            edited::BeginChild("a", "Aimbot Functions", ImVec2((content_width - 10) / 2, c::background::size.y - 108), ImGuiChildFlags_None);

                            {
                                //static int selected = 0;
                                //static int previousSelect = -1;
                                //const char* items[] = { "None", "Safe Forze","Cover Hit"};

                                //edited::Combo("Forze Aim Type", "In Game", &selected, items, IM_ARRAYSIZE(items));

                                //if (selected != previousSelect) {

                                //   

                                //    switch (selected) {
                                //    case 0: // None
                                //        break;
                                //    case 1: pullene = false; break;

                                //    case 2: coverhit = false; break;

                                //    case 3: pullenesiper = false; break;

                                //    }

                                //    previousSelect = selected;
                                //}

                                //

                                //if (selected == 2)
                                //{
                                //    edited::Checkbox("Cover Hit", "Enable", &coverhit);
                                //    if (coverhit)
                                //    {
                                //       

                                //    }  
                                //}
                                //if (selected == 1)
                                //{
                                    //edited::Checkbox("Safe Forze Aim", "Enable", &pullene);
                                    //if (pullene)
                                    //{
                                    //    
                                    //    const char* targetBones[] = {"Head", "Chest"};

                                    //    // Global int variable එක direct pass කරන්න
                                    //    ImGui::Combo("Target Bone", &selectedTargetBone, targetBones, IM_ARRAYSIZE(targetBones));
                                    //    

                                    //}
                                    edited::Checkbox("Cover Hit", "full safe", &coverhit);
                                        if (coverhit)
                                        {
                                           

                                        }  

                                
                                    //edited::Checkbox("Aimbot Rege", "Dont use mine id", &AimbotRage);
                                    if (AimbotRage)
                                    {

                                    }
                                
                              //  if (edited::Checkbox("Aimbot Visible", "Dont use mine id", &AimbotAI))
                                {


                                }

                               // if (edited::Checkbox("No Recoil", "In Game", &norecoilpro))
                                {
                                    if (norecoilpro)
                                    {

                                        //notificationSystem.AddNotification("No Recoil Enabled !", 2500);
                                    }
                                    else
                                    {
                                        //notificationSystem.AddNotification("No Recoil Desabled !", 2500);
                                    }
                                }




                              //  if (edited::Checkbox("Fast Reload", "In Game", &FastReload))
                                {
                                    if (FastReload)
                                    {

                                        //notificationSystem.AddNotification("Fast Reload Enabled !", 2500);
                                    }
                                    else
                                    {
                                        //notificationSystem.AddNotification("Fast Reload Desabled !", 2500);
                                    }
                                }
                               // edited::Checkbox("Auto Fire ", "Auto fire", &AutoFire);


                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(65);

                            // Sniper Functions
                            edited::BeginChild("f", "Fucking Functions", ImVec2((content_width - 10) / 2, 132), NULL);
                            {
                               // edited::Checkbox("Spin Bot", "Spin Player", &SpinBotEnable);

                                
                                



                                
                            }
                            edited::EndChild();

                            ImGui::SetCursorPos(ImVec2(content_x + (content_width + 10) / 2, 248));

                            // General Functions
                            edited::BeginChild("m", "General Functions", ImVec2((content_width - 10) / 2, 205), NULL);
                            {

                                edited::Checkbox("Ignore Knocked Entity", "Ignores Knocked Entity", &ingerknocked);
                               

                                edited::Checkbox("Show Fov", "", &FovEnable);
                                if (FovEnable) {
                                    edited::SliderInt("Fov Size", "", &fov, 1, 1000);
                                }

                               

                            }
                            edited::EndChild();
                        }
                    
                        else if (active_tab == 1)
                        {
                            
                            edited::BeginChild("q", "Visual Functions", ImVec2((content_width - 10) / 2, 377), NULL);
                            {

                                

                                /*if (edited::Checkbox("Activar Esp", "Go To Memory - Initialize", &ActiveADB))
                                {
                                    if (ActiveADB == 1)
                                    {
                                        std::thread([]() { hdPlayerWindow = InjectADB(); }).detach();
                                    }
                                }*/

                                if (NEXUSV1)
                                {
                                    edited::Checkbox("Esp Line", "", &EspLineZ);
                                    edited::Checkbox("Esp Box", "", &ESPBox);
                                    edited::Checkbox("Esp Filled", "", &ESPBoxFILLED);
                                    edited::Checkbox("Esp Name", "", &ESPNameZ);
                                    edited::Checkbox("Esp Health", "", &ESPHealth);
                                    edited::Checkbox("Esp Distance", "", &ESPDistance);
                                    edited::Checkbox("Esp Bones", "", &ESPBones);
                                    edited::Checkbox("Esp Radar", "", &EspRadar360);
                                    edited::Checkbox("Esp Aim", "", &CustomCrosshair);
                                    edited::Checkbox("Esp Wukong", "", &SHowVis);
                                    edited::Checkbox("Esp Timer", "", &EspTimerEnabled);

                                  //  if (edited::Checkbox("Auto Refresh", "Auto Refresh For ESP", &RefreshEsp))
                                    {
                                        if (RefreshEsp)
                                            std::thread([]() { std::thread(AutoRefreshLoop).detach(); }).detach();
                                    }
                                    if (RefreshEsp) {
                                       // edited::SliderFloat("Refresh Delay", "Delay For Refresh", &cacheClearInterval, 1.0f, 250.0f, "%.0f");
                                    }
                                }

                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(65);

                            edited::BeginChild("q", "Visual Settings", ImVec2((content_width - 10) / 2, 376), NULL);
                            {

                                if (EspLineZ) {

                                    const char* items[3]{ "Top", "Centre", "Bottom" };
                                    edited::Combo("ESP Type", "", &lineType, items, IM_ARRAYSIZE(items), 3);

                                    const char* items1[3]{ "Line", "Curved", "Stairs" };
                                    edited::Combo("ESP Point", "", &lineType1, items1, IM_ARRAYSIZE(items1), 3);

                                    edited::SliderFloat("Esp Thickness", "", &EsplineWidth, 0.5f, 10.0f, "%.1f");

                                    edited::SliderFloat("Esp Distance", "", &maxDistance, 150.f, 500.f, "%.0f");
                                }

                                if (ESPBox) {
                                    const char* items2[3]{ "3D Box", "Full Box", "Shadow", };
                                    edited::Combo("Box Type", "", &ESPBoxType, items2, IM_ARRAYSIZE(items2), 3);
                                }

                                if (ESPHealth) {
                                    const char* items2[4]{ "Left", "Right", "Top", "Bottom" };
                                    edited::Combo("Health Type", "", &selectedHealthBarPos, items2, IM_ARRAYSIZE(items2), 3);
                                }

                                if (ESPBones) {
                                    edited::SliderFloat("Bones Thickness", "", &boneThickness, 0.5f, 4.0f, "%.1f");
                                }

                                if (ESPNameZ) {
                                    ImGui::InputTextEx("##2", "Enter bot name...", defaultName, sizeof(defaultName), ImVec2(250, 50), ImGuiInputTextFlags_None);
                                }

                                /*if (NEXUSV1)
                                {
                                    edited::ColorEdit4("Line Color", "", (float*)&lineColorEnemy, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                                    edited::ColorEdit4("Filled Color", "", (float*)&boxColorFilled, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                                    edited::ColorEdit4("Box Color", "", (float*)&boxColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                                    edited::ColorEdit4("Name Color", "", (float*)&nameColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                                    edited::ColorEdit4("Bones Color", "", (float*)&bonesColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                                }*/

                            }
                            edited::EndChild();
                        }
                        else if (active_tab == 2)
                        {
                            edited::BeginChild("i", "Fake Lag & Freeze Functions", ImVec2((content_width - 10) / 2, 190), NULL);
                            {
                                if (edited::Checkbox("Fake Lag - Enable", "Active Anywhere", &fake_lag))
                                    notificationSystem.AddNotification("Notification", "Fake Lag On", ImGui::GetColorU32(c::accent));

                                static int select1 = 0;
                                static int previousSelect4 = -1;
                                const char* items1[2]{ "Automatic", "Manual" };
                                ImGui::Combo("Mode", &select1, items1, IM_ARRAYSIZE(items1), 2);
                                if (select1 != previousSelect4) { previousSelect4 = select1; }
                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 40);
                            edited::BeginChild("d", "Fake Lag - Key Bind", ImVec2((c::background::size.x - 220) / 2, 70), NULL);
                            {
                                edited::Keybind("Freeze Lag", "", &FreezeLagKey);

                                edited::Keybind("Ghost Hack", "", &GhostHackKey);

                                edited::Keybind("Aim Lag", "", &AimLagkey);
                            }
                            edited::EndChild();
                        }
                        else if (active_tab == 3)
                        {
                            edited::BeginChild("d", "Tele Key", ImVec2((content_width - 10) / 2, 190), NULL);
                            {
                                edited::Keybind("Teliport Enemy", "", &tpkey);
                                edited::Keybind("Teleport Enemy M.70", "Choose Your key", &TeleportKey);

                                edited::Keybind("Dawon Kill", "", &dwkey);
                                //if (dwkey) {
                                //    //ImGui::SliderFloat("Underground Depth", &DownPlayerSpeed, 0.0f, 20.0f);
                                //}
                                //edited::Keybind("Fl", "", &frwardPlayerkey);
                                //edited::Keybind("Fly Hack v1", "", &FlyHackinkey);

                                //edited::Keybind("Teleport Mark ","", &TeleportMarkEnablekey);
                               // edited::Keybind("Speed Internal X33", "Dont use mine id", &SpeedKey);

                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 40);
                            edited::BeginChild("i", "Streamer Key Binds", ImVec2((c::background::size.x - 100) / 2, 370), NULL);
                            {}
                            edited::EndChild();
                        }
                        else if (active_tab == 4)
                        {
                            edited::BeginChild("g", "Settings", ImVec2((content_width - 10) / 2, 380), NULL);
                            {
                               // edited::ColorEdit4("Main Color", "Set the main color of the menu.", color, picker_flags);
                                edited::Keybind("Show | Hide Menu", "", &show_hide_menu_key);
                                //edited::Checkbox("KENZO REGZ", "ESP RGB Colors", &beginmark);
                                static int selected = 0;
                                static int previousSelectParticle = -1;
                                const char* Particleitems[3]{ "Line", "Dot", "None" };

                                ImGui::Combo("Particle Type", &selected, Particleitems, IM_ARRAYSIZE(Particleitems), 3);
                                if (selected != previousSelectParticle) {

                                    if (selected == 0)
                                    {
                                        LineRunning = true;
                                        DotRunning = false;
                                        TriangleRunning = false;
                                    }
                                    else if (selected == 1)
                                    {
                                        LineRunning = false;
                                        DotRunning = true;
                                        TriangleRunning = false;
                                    }
                                    else if (selected == 2)
                                    {
                                        LineRunning = false;
                                        DotRunning = false;
                                        TriangleRunning = true;
                                    }
                                }

                                if (edited::Checkbox("Streamer Mode", "Hides panel and cheats in stream", &streammode))
                                {
                                    stream = !stream;
                                    if (stream)
                                    {
                                        notificationSystem.AddNotification("Done", "Stream Mode Enabled!", ImGui::GetColorU32(c::accent));
                                        SetWindowDisplayAffinity(GetActiveWindow(), WDA_EXCLUDEFROMCAPTURE);
                                        ITaskbarList* pTaskList = NULL;
                                        CoInitialize(NULL);
                                        if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList)))
                                        {
                                            pTaskList->DeleteTab(GetActiveWindow());
                                            pTaskList->Release();
                                        }
                                        CoUninitialize();
                                    }
                                    else
                                    {
                                        notificationSystem.AddNotification("Done", "Stream Mode Disabled!", ImGui::GetColorU32(c::accent));
                                        SetWindowDisplayAffinity(GetActiveWindow(), WDA_NONE);
                                        ITaskbarList* pTaskList = NULL;
                                        CoInitialize(NULL);
                                        if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList)))
                                        {
                                            pTaskList->AddTab(GetActiveWindow());
                                            pTaskList->Release();
                                        }
                                        CoUninitialize();
                                    }
                                }

                                //edited::Checkbox("KEY BIND MENU", "", &LOGSPANEL);
                                ImGui::Spacing();
                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 30);
                            edited::BeginChild("m", "Memory", ImVec2((c::background::size.x - 100) / 2, 160), NULL);
                            {
                                const char* gameList[] = { "FF Max", "FF Max X86", "FF V7A", "FF India" };



                                if (edited::Combo("Select FF", "FF Versions", &SelectedGame, gameList, IM_ARRAYSIZE(gameList)))

                                {

                                    if (SelectedGame == 0) LoadFFMax();

                                    else if (SelectedGame == 1) LoadFFmaxX86();

                                    else if (SelectedGame == 2) LoadNormalFF();

                                    else if (SelectedGame == 3) LoadFFIndia();

                                }



                                // Selected Version එක කොළ පාටින් (Green) පෙන්වීම

                                if (SelectedGame >= 0 && SelectedGame < IM_ARRAYSIZE(gameList))

                                {

                                    ImGui::Text("Selected:");

                                    ImGui::SameLine();

                                    ImGui::TextColored(ImVec4(0.00f, 1.00f, 0.00f, 1.00f), "%s", gameList[SelectedGame]);

                                }



                                // ----------------------------------------------------

                                // UI display section (Memory Status Text)

                                // ----------------------------------------------------

                                static bool isConnected = false;

                                static bool isConnecting = false;



                                const char* statusText = isConnected ? "Ready" : (isConnecting ? "Connecting..." : "Not Ready");

                                ImVec4 statusColor = isConnected ? ImVec4(0.00f, 1.00f, 0.00f, 1.00f) :

                                    (isConnecting ? ImVec4(1.00f, 1.00f, 0.00f, 1.00f) : ImVec4(1.00f, 0.00f, 0.00f, 1.00f));



                                ImGui::Text("Memory status :");

                                float targetX = ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize(statusText).x - ImGui::GetStyle().ItemSpacing.x;

                                ImGui::SameLine(targetX);

                                ImGui::TextColored(statusColor, "%s", statusText);



                                ImGui::Spacing();



                                // ----------------------------------------------------

                                // Button and Thread Section

                                // ----------------------------------------------------

                                if (ImGui::Button("Memory - Initialize", ImVec2(ImGui::GetContentRegionAvail().x, 37)))

                                {

                                    Beep(800, 150);



                                    isConnecting = true;

                                    isConnected = false;



                                    std::thread([]() {

                                        hdPlayerWindow = InjectADB();



                                        isConnected = true;

                                        isConnecting = false;



                                        Beep(1200, 200);

                                        }).detach();

                                }



                                // ----------------------------------------------------

                                // Vertical Loading Bars Animation (Image Style)

                                // ----------------------------------------------------

                                if (isConnecting)

                                {

                                    ImDrawList* drawList = ImGui::GetForegroundDrawList(); // Full screen එක උඩින් පෙනීමට foreground drawlist එක භාවිතා කරයි

                                    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

                                    ImVec2 center = ImVec2(displaySize.x * 0.5f, displaySize.y * 0.5f);



                                    static float animTime = 0.0f;

                                    animTime += ImGui::GetIO().DeltaTime * 6.0f; // Speed එක වෙනස් කරගත හැක



                                    float barWidth = 12.0f; // Bar එකක පලල

                                    float barSpacing = 8.0f; // Bars අතර පරතරය

                                    float maxBarHeight = 45.0f; // උපරිම උස

                                    float minBarHeight = 15.0f; // අවම උස

                                    float totalWidth = (3 * barWidth) + (2 * barSpacing);

                                    float startX = center.x - (totalWidth * 0.5f);



                                    for (int i = 0; i < 3; i++)

                                    {

                                        // Wave animation එක සඳහා sine wave භාවිතා වේ

                                        float t = animTime - (i * 0.4f);

                                        float heightFactor = (sinf(t) + 1.0f) * 0.5f; // 0.0 සිට 1.0 දක්වා

                                        float currentHeight = minBarHeight + (maxBarHeight - minBarHeight) * heightFactor;



                                        ImVec2 barMin = ImVec2(startX + i * (barWidth + barSpacing), center.y - (currentHeight * 0.5f));

                                        ImVec2 barMax = ImVec2(barMin.x + barWidth, center.y + (currentHeight * 0.5f));



                                        // Accent color එක හෝ තද නිල්/Cyan පාට ලබාදීම

                                        drawList->AddRectFilled(barMin, barMax, ImGui::GetColorU32(c::accent, 0.9f), 3.0f);

                                    }

                                }



                                edited::EndChild();

                            }
                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPos(ImVec2(content_x + (content_width + 10) / 2, 258));
                            edited::BeginChild("m", "Others", ImVec2((c::background::size.x - 100) / 2, 196), NULL);
                            {
                                if (ImGui::Button("Emulator", ImVec2(255, 35))) {
                                    ShellExecuteA(0, "open", "https://www.mediafire.com/file/31qx67e6self2c/BlueStacksInstaller_5.22.110.1028.exe/file", 0, 0, SW_SHOWNORMAL);
                                }
                                ImGui::Spacing();
                                if (ImGui::Button("Free Fire V7A", ImVec2(255, 35))) {
                                    ShellExecuteA(0, "open", "https://www.mediafire.com/file/w019lsmxdguoyl4/FREE+FIRE+V7A+OB55.xapk/file", 0, 0, SW_SHOWNORMAL);
                                }
                                // 2. Button එකේ පාට සහ corner rounding සකස් කිරීම
                                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.65f, 1.0f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.35f, 0.75f, 1.0f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.55f, 0.9f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.15f, 0.4f, 1.0f));
                                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

                                // 3. "Kill Emulator" button එක નિર્මාණය (ImVec2 භාවිතා කරන්න)
                                if (ImGui::Button("Kill Emulator", ImVec2(255, 35)))
                                {
                                    exit(0);
                                }

                                // 4. Style වෙනස්කම් නැවත මුල් තත්වයට පත් කිරීම
                                ImGui::PopStyleVar();
                                ImGui::PopStyleColor(4);
                            }
                            edited::EndChild();
                        }

                            ImGui::PopStyleVar();
            }
            ImGui::End();   // only one End() for the single Begin()
        }
    }
    notificationSystem.DrawNotifications();
}


        ImGui::Render();

        const float clear_color_with_alpha[4] = { 0.f };

        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }


    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return;
}




bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK) return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam);
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}







HMODULE hCurrentModule = nullptr;
HANDLE hCurrentUIThread = nullptr;
HANDLE hCurrentBgThread = nullptr;

#ifdef _WINDLL


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved, HMODULE hMod, DWORD reason)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        hCurrentModule = hinstDLL;
        hCurrentUIThread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)MANAS, nullptr, NULL, nullptr);

    }

    if (fdwReason == DLL_PROCESS_DETACH)
        TerminateThread(hCurrentUIThread, 0);

    return TRUE;
}

#else

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    MANAS();

    return 0;
}

#endif


