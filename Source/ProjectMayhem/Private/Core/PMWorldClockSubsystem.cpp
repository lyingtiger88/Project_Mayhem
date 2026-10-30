#include "Core/PMWorldClockSubsystem.h"

TStatId UPMWorldClockSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UPMWorldClockSubsystem, STATGROUP_Tickables);
}

void UPMWorldClockSubsystem::Tick(const float DeltaTime)
{
    if (!bIsPaused && DeltaTime > 0.0f)
    {
        ElapsedGameSeconds += static_cast<double>(DeltaTime) * static_cast<double>(TimeScale);
    }
}

float UPMWorldClockSubsystem::GetDayProgress() const
{
    if (GameDayLengthSeconds <= 0.0f)
    {
        return 0.0f;
    }

    const double DaySeconds = FMath::Fmod(ElapsedGameSeconds, static_cast<double>(GameDayLengthSeconds));
    return static_cast<float>(DaySeconds / static_cast<double>(GameDayLengthSeconds));
}

void UPMWorldClockSubsystem::SetTimeScale(const float NewTimeScale)
{
    TimeScale = FMath::Clamp(NewTimeScale, 0.0f, 100.0f);
}
