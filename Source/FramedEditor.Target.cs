// Fill out your copyright notice in the Description page of Project Settings.

using System.Collections.Generic;
using UnrealBuildTool;

public class FramedEditorTarget : TargetRules
{
    public FramedEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange(new string[] { "Framed" });
    }
}
