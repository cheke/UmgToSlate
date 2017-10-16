// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.


#include "MultiPackerCommands.h"

#define LOCTEXT_NAMESPACE "FMultiPackerModule"

void FMultiPackerCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MultiPacker", "Bring up MultiPacker window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
