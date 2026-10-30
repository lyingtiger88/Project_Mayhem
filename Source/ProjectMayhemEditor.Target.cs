using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectMayhemEditorTarget : TargetRules
{
    public ProjectMayhemEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("ProjectMayhem");
    }
}
