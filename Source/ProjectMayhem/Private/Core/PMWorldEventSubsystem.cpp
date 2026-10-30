#include "Core/PMWorldEventSubsystem.h"
#include "Engine/World.h"

FGuid UPMWorldEventSubsystem::PublishWorldEvent(
    const FName EventType, const FGuid InstigatorId, const FGuid SubjectId,
    const FVector Location, const float Severity, const float Confidence)
{
    check(IsInGameThread());

    if (EventType.IsNone())
    {
        UE_LOG(LogTemp, Warning, TEXT("Project Mayhem: ignored a world event with no EventType."));
        return FGuid();
    }

    FPMWorldEvent Event;
    Event.EventId = FGuid::NewGuid();
    Event.EventType = EventType;
    Event.InstigatorId = InstigatorId;
    Event.SubjectId = SubjectId;
    Event.Location = Location;
    Event.Severity = FMath::Clamp(Severity, 0.0f, 1.0f);
    Event.Confidence = FMath::Clamp(Confidence, 0.0f, 1.0f);

    if (const UWorld* World = GetWorld())
    {
        Event.WorldTimestamp = World->GetTimeSeconds();
    }

    RecentEvents.Add(Event);
    if (RecentEvents.Num() > MaxRecentEvents)
    {
        RecentEvents.RemoveAt(0, RecentEvents.Num() - MaxRecentEvents, EAllowShrinking::No);
    }

    OnWorldEventPublished.Broadcast(Event);
    return Event.EventId;
}

void UPMWorldEventSubsystem::CopyRecentEvents(TArray<FPMWorldEvent>& OutEvents) const
{
    OutEvents = RecentEvents;
}

void UPMWorldEventSubsystem::ClearRecentEvents()
{
    RecentEvents.Reset();
}
