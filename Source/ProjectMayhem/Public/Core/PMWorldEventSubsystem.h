#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PMWorldEvent.h"
#include "PMWorldEventSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPMWorldEventPublished, const FPMWorldEvent&, WorldEvent);

/** Central event bus for cross-system world events. Not intended for per-frame messaging. */
UCLASS()
class PROJECTMAYHEM_API UPMWorldEventSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static constexpr int32 MaxRecentEvents = 256;

    UPROPERTY(BlueprintAssignable, Category = "Project Mayhem|World Events")
    FPMWorldEventPublished OnWorldEventPublished;

    UFUNCTION(BlueprintCallable, Category = "Project Mayhem|World Events")
    FGuid PublishWorldEvent(FName EventType, FGuid InstigatorId, FGuid SubjectId,
        FVector Location, float Severity = 0.0f, float Confidence = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Project Mayhem|World Events")
    void CopyRecentEvents(TArray<FPMWorldEvent>& OutEvents) const;

    UFUNCTION(BlueprintCallable, Category = "Project Mayhem|World Events")
    void ClearRecentEvents();

private:
    UPROPERTY()
    TArray<FPMWorldEvent> RecentEvents;
};
