#pragma once

#include "EngineUtils.h"
#include <type_traits>

namespace FramedUtils
{
    template <typename T>
    FORCEINLINE TArray<T*> FindAllActors(UWorld* World)
    {
        static_assert(std::is_base_of<AActor, T>::value, "Type must be derived from AActor");

        TArray<T*> Out{};

        for (TActorIterator<T> It(World); It; ++It) {
            Out.Add(*It);
        }

        return Out;
    }
} // namespace FramedUtils