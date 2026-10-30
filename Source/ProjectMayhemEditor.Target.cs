using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectMayhemEditorTarget : TargetRules
{
    public ProjectMayhemEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V7;
        ExtraModuleNames.Add("ProjectMayhem");
    }
}
