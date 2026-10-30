#pragma once

#include "CoreMinimal.h"
#include "PMWorldEvent.generated.h"

/** A compact, serializable description of a meaningful event in the game world. */
USTRUCT(BlueprintType)
struct PROJECTMAYHEM_API FPMWorldEvent
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World Event")
    FGuid EventId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FName EventType = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FGuid InstigatorId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FGuid SubjectId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FVector Location = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Severity = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Confidence = 1.0f;

    /** World-relative seconds when the event was published. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World Event")
    double WorldTimestamp = 0.0;
};
