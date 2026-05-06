"""Bridge-first client for M27 persistent editor bridge.

When the editor is running with the BlueprintExporter plugin loaded, the C++
bridge listens on `ws://127.0.0.1:<BPX_BRIDGE_PORT>` (default 1337) and speaks
JSON-RPC 2.0. `try_bridge_call` tries to reach it; on connect-refused or
handshake-timeout it returns `None` so the caller can fall through to today's
subprocess-shell path. On any other outcome — success OR server-side error —
the bridge response is authoritative and returned as-is.

Two design rules:
  1. No import-time side effects. `websockets` is imported lazily so colleagues
     on an older MCP install without the dep still fall through cleanly.
  2. Connection failure is the ONLY signal that routes to subprocess. If we
     got a JSON-RPC response back (even an error object), the editor handled
     the request and further subprocess retries would duplicate state mutations.
"""

from __future__ import annotations

import json
import os
from typing import Any


DEFAULT_BRIDGE_PORT = 1337
DEFAULT_CONNECT_TIMEOUT = 2.0
DEFAULT_RECV_TIMEOUT_VALIDATE = 600.0
DEFAULT_RECV_TIMEOUT_APPLY = 900.0


class BridgeUnavailable(Exception):
    """Raised when the bridge transport itself is not reachable.

    Signals that the caller should fall through to the subprocess path.
    Distinct from bridge-returned JSON-RPC errors, which are real results
    and must not trigger a fallback.
    """


def resolve_bridge_port() -> int:
    raw = os.environ.get("BPX_BRIDGE_PORT", "").strip()
    if not raw:
        return DEFAULT_BRIDGE_PORT
    try:
        parsed = int(raw)
    except ValueError:
        return DEFAULT_BRIDGE_PORT
    if not 1 <= parsed <= 65535:
        return DEFAULT_BRIDGE_PORT
    return parsed


def try_bridge_call(
    method: str,
    params: dict[str, Any],
    *,
    recv_timeout: float,
    connect_timeout: float = DEFAULT_CONNECT_TIMEOUT,
    port: int | None = None,
) -> dict[str, Any]:
    """Connect to the editor bridge and invoke a method.

    Raises `BridgeUnavailable` if the transport itself is unreachable
    (connection refused, DNS fail, handshake timeout, websockets not installed).
    Returns the parsed JSON-RPC response dict for any server-delivered outcome,
    including error objects — the caller should inspect `.get("error")` to
    distinguish.
    """
    try:
        import asyncio
        import websockets
        from websockets.exceptions import InvalidHandshake, WebSocketException
    except ImportError as exc:
        raise BridgeUnavailable(f"websockets import failed: {exc}") from exc

    if port is None:
        port = resolve_bridge_port()
    uri = f"ws://127.0.0.1:{port}"

    async def _call() -> dict[str, Any]:
        try:
            ws_ctx = websockets.connect(uri, open_timeout=connect_timeout)
        except Exception as exc:
            raise BridgeUnavailable(f"connect setup failed: {exc}") from exc

        async with ws_ctx as ws:
            request = {
                "jsonrpc": "2.0",
                "id": 1,
                "method": method,
                "params": params,
            }
            await ws.send(json.dumps(request))
            raw = await asyncio.wait_for(ws.recv(), timeout=recv_timeout)
            if isinstance(raw, bytes):
                raw = raw.decode("utf-8", errors="replace")
            return json.loads(raw)

    try:
        return asyncio.run(_call())
    except (ConnectionRefusedError, OSError, TimeoutError, asyncio.TimeoutError) as exc:
        raise BridgeUnavailable(f"bridge transport error: {exc}") from exc
    except WebSocketException as exc:
        # websockets raises subclasses for handshake / protocol errors at connect time.
        if isinstance(exc, InvalidHandshake):
            raise BridgeUnavailable(f"bridge handshake failed: {exc}") from exc
        # Once connected, protocol errors during the exchange are authoritative —
        # don't fall back to subprocess mid-conversation.
        raise
