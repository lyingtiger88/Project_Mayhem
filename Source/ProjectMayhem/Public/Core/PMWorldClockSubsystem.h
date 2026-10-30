#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PMWorldClockSubsystem.generated.h"

/** World-local clock for schedules and time-dependent simulation. */
UCLASS()
class PROJECTMAYHEM_API UPMWorldClockSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override;
    virtual bool IsTickable() const override { return !IsTemplate(); }

    UFUNCTION(BlueprintPure, Category = "Project Mayhem|World Time")
    double GetElapsedGameSeconds() const { return ElapsedGameSeconds; }

    UFUNCTION(BlueprintPure, Category = "Project Mayhem|World Time")
    float GetDayProgress() const;

    UFUNCTION(BlueprintCallable, Category = "Project Mayhem|World Time")
    void SetTimeScale(float NewTimeScale);

    UFUNCTION(BlueprintCallable, Category = "Project Mayhem|World Time")
    void SetPaused(bool bNewPaused) { bIsPaused = bNewPaused; }

    UFUNCTION(BlueprintPure, Category = "Project Mayhem|World Time")
    bool IsPaused() const { return bIsPaused; }

    UPROPERTY(EditDefaultsOnly, Category = "Project Mayhem|World Time", meta = (ClampMin = "60.0"))
    float GameDayLengthSeconds = 1440.0f;

private:
    UPROPERTY()
    double ElapsedGameSeconds = 0.0;

    UPROPERTY()
    float TimeScale = 1.0f;

    UPROPERTY()
    bool bIsPaused = false;
};
