# Implementation Plan - Device Lock Command Handling

Implement a server-side logic to monitor lock/unlock commands from Firebase Realtime Database and execute them via MQTT with a two-stage retry mechanism.

## User Review Required

> [!IMPORTANT]
> Based on your feedback, I've updated the logic:
> 1. **Command Topic**: `Son/{imei}/lock` (imei from RTDB).
> 2. **Payload**: Plain string `"lock"` or `"unlock"`.
> 3. **Logic Flow**: 
>    - **Stage 1 (Immediate)**: Send command as soon as Firebase status is `pending`.
>    - **Stage 2 (Wake-up Retry)**: If the device doesn't respond, wait indefinitely until the device reports any data/status (meaning it has woken up). At that moment, send the command again.
>    - **Stage 3 (Final Timeout)**: After the **2nd attempt**, if there is no response within **60 seconds**, update status to `error`.
>    - **Success**: If the device responds to either attempt, update status to `done`.
> 4. **Detection**: Any message received on `Son/{imei}/data` or `Son/{imei}/status` will trigger the 2nd attempt.`.

## Proposed Changes

### [Component] Firebase Command Listener

#### [NEW] `device_command_listener_task`
- Listen to `device_commands/{imei}/lock` nodes.
- If `status == "pending"`, call `send_lock_command(imei, cmd)`.

### [Component] Command State Management

#### Tracking Logic
- Use a `pending_locks` dict: `{imei: {"cmd": str, "attempt": int, "timer": Timer}}`.
- **Attempt 1**: Sent immediately.
- **Attempt 2**: Triggered by incoming MQTT message from device if `attempt == 1`.
- **Timeout**: A 60-second timer starts *only after* Attempt 2.

## Open Questions

1. **Confirmation Topic**: I will implement handling for `Son/{imei}/lock/res` with `{"status": "done"}`. Is this correct?
2. **Activity Trigger**: I will assume any message on `Son/{imei}/data` or `Son/{imei}/status` counts as "device reporting state/ready".

## Verification Plan

### Automated Tests
- Use `device_simulator_send_sms.py` (modified) to simulate a device receiving a lock command and responding.
- Verify Firebase status updates from `pending` -> `done`.
- Simulate device offline (no response) -> wait for `data` message -> verify retry -> verify `error` if still no response.

### Manual Verification
- Manually update Firebase `status` to `pending` and observe terminal logs for MQTT publication.
- Check MQTT broker (HiveMQ) for outgoing messages.
