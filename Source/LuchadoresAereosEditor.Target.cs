// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LuchadoresAereosEditorTarget : TargetRules
{
	public LuchadoresAereosEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("LuchadoresAereos");
	}
}
