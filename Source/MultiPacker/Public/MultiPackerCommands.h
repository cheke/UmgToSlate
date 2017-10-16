// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MultiPackerStyle.h"

class FMultiPackerCommands : public TCommands<FMultiPackerCommands>
{
public:

	FMultiPackerCommands()
		: TCommands<FMultiPackerCommands>(TEXT("MultiPacker"), NSLOCTEXT("Contexts", "MultiPacker", "MultiPacker Plugin"), NAME_None, FMultiPackerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};