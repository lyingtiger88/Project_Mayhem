#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PMEntityIdentityComponent.generated.h"

/**
 * Stable Actor identity for cross-system references.
 * SaveGame marks the field for serialization; the future Save system must explicitly
 * serialize and restore the owning Actor/component for persistence across loads.
 */
UCLASS(ClassGroup = (ProjectMayhem), meta = (BlueprintSpawnableComponent))
class PROJECTMAYHEM_API UPMEntityIdentityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPMEntityIdentityComponent();
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure, Category = "Project Mayhem|Identity")
    FGuid GetPersistentId() const { return PersistentId; }

    /** Intended for controlled restore/import workflows, not routine gameplay. */
    void SetPersistentId(const FGuid& InPersistentId);

private:
    UPROPERTY(VisibleAnywhere, SaveGame, Category = "Project Mayhem|Identity")
    FGuid PersistentId;
};
