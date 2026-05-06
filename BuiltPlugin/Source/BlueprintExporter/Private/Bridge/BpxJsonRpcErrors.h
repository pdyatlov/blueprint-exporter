// Copyright Ten Chambers. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// JSON-RPC 2.0 spec-defined error codes, shared by every bridge-side
// handler module. Kept out of the per-file anon namespaces so unity
// (jumbo) builds don't collide identical `ErrInternal` / `ErrInvalidParams`
// definitions across `BpxBridgeServer.cpp` + `BpxPlanHandlers.cpp`.
//
// Custom server-range codes (-32000..-32099) stay file-local next to
// the handler that owns them.
namespace BlueprintExporter::Bridge
{
	inline constexpr int32 ErrParse           = -32700;
	inline constexpr int32 ErrInvalidRequest  = -32600;
	inline constexpr int32 ErrMethodNotFound  = -32601;
	inline constexpr int32 ErrInvalidParams   = -32602;
	inline constexpr int32 ErrInternal        = -32603;
}
