#include "Core/PMEntityIdentityComponent.h"

UPMEntityIdentityComponent::UPMEntityIdentityComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPMEntityIdentityComponent::BeginPlay()
{
    Super::BeginPlay();
    if (!PersistentId.IsValid())
    {
        PersistentId = FGuid::NewGuid();
    }
}

void UPMEntityIdentityComponent::SetPersistentId(const FGuid& InPersistentId)
{
    if (InPersistentId.IsValid())
    {
        PersistentId = InPersistentId;
    }
}
