// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class TableTopGameTarget : TargetRules
{
	public TableTopGameTarget(TargetInfo Target): base(Target)
	{
		Type = TargetType.Game;
        ExtraModuleNames.Add("TableTopGame");
    }

	//
	// TargetRules interface.
	//

	//public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
	//	OutExtraModuleNames.AddRange( new string[] { "TableTopGame" } );
	//}
}
