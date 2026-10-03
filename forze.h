#pragma oa#pragma once

#include <cmath>
#include <cfloat>
#include <cstdint>
#include <chrono>
#include <unordered_map>

// Requires Offset.hpp, Unity.hh and Complementos.h included before this header.

namespace AimForce
{
    constexpr uintptr_t kMatrixPositionOffset = 0x60;

    inline std::unordered_map<uint32_t, Vector3> originalPositions;
    inline uint32_t currentTargetId = 0;

    inline bool WriteRootPosition(uint32_t rootBone, const Vector3& pos)
    {
        uint32_t transformValue = 0;
        uint32_t transformObj = 0;
        uint32_t matrixPtr = 0;

        if (!ReadZ(rootBone + 0x8, transformValue) || transformValue == 0)
            return false;
        if (!ReadZ(transformValue + 0x8, transformObj) || transformObj == 0)
            return false;
        if (!ReadZ(transformObj + 0x20, matrixPtr) || matrixPtr == 0)
            return false;

        WriteZ<Vector3>(matrixPtr + kMatrixPositionOffset, pos);
        return true;
    }

    inline void RestoreAll()
    {
        for (const auto& entry : originalPositions)
        {
            uint32_t rootBone = 0;
            if (!ReadZ(entry.first + Offsets::Bones::Root, rootBone) || rootBone == 0)
                continue;

            WriteRootPosition(rootBone, entry.second);
        }

        originalPositions.clear();
        currentTargetId = 0;
    }

    inline float GetCrosshairDistance(const Vector2& a, const Vector2& b)
    {
        const float dx = a.X - b.X;
        const float dy = a.Y - b.Y;
        return std::sqrt(dx * dx + dy * dy);
    }

    inline bool GetBonePosition(uint32_t bone, Vector3& out)
    {
        return GetNodePosition(bone, out) && out != Vector3::Zero();
    }

    inline uint32_t GetNeckBoneOffset(bool useFFMax)
    {
        if (useFFMax && Offsets::Bones::Spine != 0)
            return Offsets::Bones::Spine;

        if (Offsets::Bones::Neck != 0)
            return Offsets::Bones::Neck;

        return Offsets::Bones::Spine;
    }

    inline uint32_t FindBestTarget(
        uint32_t entities,
        uint32_t entityListCount,
        uint32_t localPlayer,
        const Matrix4x4& viewMatrix,
        const Vector3& cameraPos,
        int screenW,
        int screenH,
        float fovPx,
        float maxDistance,
        bool ignoreKnocked)
    {
        if (screenW <= 0 || screenH <= 0)
            return 0;

        const Vector2 screenCenter(screenW * 0.5f, screenH * 0.5f);
        uint32_t bestEntity = 0;
        float closestDist = FLT_MAX;

        for (uint32_t i = 0; i < entityListCount; i++)
        {
            uint32_t entity = 0;
            if (!ReadZ(entities + i * 0x10, entity) || entity == 0 || entity == localPlayer)
                continue;

            bool isDead = false;
            if (ReadZ(entity + Offsets::Player_IsDead, isDead) && isDead)
                continue;

            if (ignoreKnocked)
            {
                bool isKnocked = false;
                uint32_t shadowBase = 0;
                if (ReadZ(entity + Offsets::Player_ShadowBase, shadowBase) && shadowBase)
                {
                    int xpose = 0;
                    if (ReadZ(shadowBase + Offsets::XPose, xpose) && xpose == 8)
                        isKnocked = true;
                }
                if (isKnocked)
                    continue;
            }

            uint32_t avatarManager = 0;
            if (!ReadZ(entity + Offsets::AvatarManager, avatarManager) || avatarManager == 0)
                continue;

            uint32_t avatar = 0;
            if (!ReadZ(avatarManager + Offsets::Avatar, avatar) || avatar == 0)
                continue;

            uint32_t avatarData = 0;
            if (!ReadZ(avatar + Offsets::Avatar_Data, avatarData) || avatarData == 0)
                continue;

            bool isTeam = false;
            if (ReadZ(avatarData + Offsets::Avatar_Data_IsTeam, isTeam) && isTeam)
                continue;

            uint32_t headBone = 0;
            if (!ReadZ(entity + Offsets::Bones::Head, headBone) || headBone == 0)
                continue;

            Vector3 headPos;
            if (!GetBonePosition(headBone, headPos))
                continue;

            const Vector2 head2D = WorldToScreen(viewMatrix, headPos, screenW, screenH);
            if (head2D.X < 1.f || head2D.Y < 1.f)
                continue;

            const float dist3D = Vector3::Distance(cameraPos, headPos);
            if (dist3D > maxDistance)
                continue;

            const float crosshairDist = GetCrosshairDistance(head2D, screenCenter);
            if (fovPx > 0.f && crosshairDist > fovPx)
                continue;

            if (crosshairDist < closestDist)
            {
                closestDist = crosshairDist;
                bestEntity = entity;
            }
        }

        return bestEntity;
    }

    inline void Tick(
        uint32_t entities,
        uint32_t entityListCount,
        uint32_t localPlayer,
        const Matrix4x4& viewMatrix,
        const Vector3& cameraPos,
        int screenW,
        int screenH,
        bool ignoreKnocked,
        bool useFFMax = true)
    {
        static std::chrono::steady_clock::time_point lastFireTime{};

        if (!AimForceEnabled || localPlayer == 0)
        {
            if (!originalPositions.empty())
                RestoreAll();
            return;
        }

        if (screenW <= 0 || screenH <= 0)
            return;

        bool isCurrentlyFiring = false;
        if (ReadZ(localPlayer + Offsets::sAim1, isCurrentlyFiring) && isCurrentlyFiring)
            lastFireTime = std::chrono::steady_clock::now();

        const int fireCooldownMs = AimForceFireCooldownMs;
        const bool isFiring = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - lastFireTime).count() < fireCooldownMs;

        if (!isFiring)
        {
            if (!originalPositions.empty())
                RestoreAll();
            return;
        }

        const float fovPx = (static_cast<float>(fov) / 360.0f) * static_cast<float>(screenW);
        const float maxDistance = static_cast<float>(AimBotDis);

        const uint32_t bestEntity = FindBestTarget(
            entities,
            entityListCount,
            localPlayer,
            viewMatrix,
            cameraPos,
            screenW,
            screenH,
            fovPx,
            maxDistance,
            ignoreKnocked
        );

        if (bestEntity == 0)
            return;

        currentTargetId = bestEntity;

        uint32_t headBone = 0;
        uint32_t neckBone = 0;
        uint32_t chestBone = 0;
        uint32_t rootBone = 0;

        if (!ReadZ(bestEntity + Offsets::Bones::Head, headBone) || headBone == 0)
            return;
        if (!ReadZ(bestEntity + GetNeckBoneOffset(useFFMax), neckBone) || neckBone == 0)
            return;
        if (!ReadZ(bestEntity + Offsets::Bones::Hip, chestBone) || chestBone == 0)
            return;
        if (!ReadZ(bestEntity + Offsets::Bones::Root, rootBone) || rootBone == 0)
            return;

        Vector3 headPos;
        Vector3 neckPos;
        Vector3 chestPos;
        Vector3 rootPos;

        if (!GetBonePosition(headBone, headPos))
            return;
        if (!GetBonePosition(neckBone, neckPos))
            return;
        if (!GetBonePosition(chestBone, chestPos))
            return;
        if (!GetBonePosition(rootBone, rootPos))
            return;

        Vector3 targetPos = headPos;
        switch (AimForceType)
        {
        case 1: targetPos = neckPos; break;
        case 2: targetPos = chestPos; break;
        default: targetPos = headPos; break;
        }

        if (originalPositions.find(bestEntity) == originalPositions.end())
            originalPositions[bestEntity] = rootPos;

        Vector3 fireDir(viewMatrix.m02, viewMatrix.m12, viewMatrix.m22);
        fireDir = Vector3::Normalized(fireDir);

        const Vector3 toTarget(
            targetPos.X - cameraPos.X,
            targetPos.Y - cameraPos.Y,
            targetPos.Z - cameraPos.Z
        );
        const float projLength = Vector3::Dot(toTarget, fireDir);
        const Vector3 linePoint(
            cameraPos.X + fireDir.X * projLength,
            cameraPos.Y + fireDir.Y * projLength,
            cameraPos.Z + fireDir.Z * projLength
        );

        Vector3 offset(
            linePoint.X - targetPos.X,
            linePoint.Y - targetPos.Y,
            linePoint.Z - targetPos.Z
        );

        // Horizontal pull only (left, right, down) — no upward pull.
        if (offset.Y > 0.0f)
            offset.Y = 0.0f;

        const Vector3 pulledPos(
            rootPos.X + offset.X,
            rootPos.Y + offset.Y,
            rootPos.Z + offset.Z
        );

        WriteRootPosition(rootBone, pulledPos);
    }
}
nce
