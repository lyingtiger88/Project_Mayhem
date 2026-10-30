using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectMayhemTarget : TargetRules
{
    public ProjectMayhemTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("ProjectMayhem");
    }
}
