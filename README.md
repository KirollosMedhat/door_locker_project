# Two-MCU Door Locker System

Final project for an embedded systems course: a password-protected electronic door lock built on two AVR **ATmega16** microcontrollers communicating over UART, with a Proteus circuit simulation. Written from scratch in bare-metal C (direct register access, no HAL/Arduino libraries).

## System overview

```
┌─────────────────────┐         UART (9600, 8N1)        ┌──────────────────────────┐
│   MC1 — HMI Unit     │ ───────────────────────────────▶ │  MC2 — Control Unit      │
│  (mc1_hmi_unit/)     │ ◀─────────────────────────────── │  (mc2_control_unit/)     │
│                      │                                  │                          │
│  • 4x4 Keypad        │                                  │  • I2C EEPROM (password  │
│  • 16x2 LCD          │                                  │    storage, persists     │
│  • Password entry    │                                  │    across power cycles)  │
│  • Menu display      │                                  │  • DC motor (lock/unlock │
│                      │                                  │    drive, timer-timed)   │
│                      │                                  │  • 3-strike lockout +    │
│                      │                                  │    buzzer alarm          │
└─────────────────────┘                                  └──────────────────────────┘
```

MC2 is the decision-maker: it owns the stored password (in external EEPROM over I2C) and drives the physical lock motor. MC1 is a dumb terminal by comparison — it only collects keypad input and displays status, and does nothing without MC2 requesting it first. The two communicate over a small byte-code protocol (`GET_PASSWORD`, `CORRECT_PASSWORD`, `LOCK_THE_DOOR`, `ALARM`, etc. — see the `#define`s at the top of each `Main.c`) that has to match exactly on both sides, since it's the only thing keeping them synchronized.

## Behavior

- **First power-up**: MC2 detects an uninitialized EEPROM and asks MC1 to prompt the user to set a password, which gets written to EEPROM.
- **Normal use**: MC2 asks MC1 for the keypad-entered password, compares it against EEPROM, and either unlocks (drives the motor clockwise/counter-clockwise via `timerRoutine`, timed by Timer1) or rejects it.
- **Lockout**: three wrong attempts in a row trigger `buzzerFor1Min()` — an audible alarm on both MCUs, and MC2 refuses further input until it completes.
- **Menu**: once unlocked, MC1 displays a 2-option menu (lock the door / reset password) and relays the choice back to MC2.

## Repository structure

```
.
├── mc1_hmi_unit/          # ATmega16 firmware — keypad, LCD, UART (the "front desk")
├── mc2_control_unit/      # ATmega16 firmware — I2C/EEPROM, motor control, UART (the "brain")
└── proteus_simulation/
    └── Door Locker.pdsprj # Proteus 8 circuit schematic + simulation
```

Each firmware folder is a standalone AVR-Eclipse / Atmel Studio project (`.cproject` + `.project`) targeting **ATmega16 @ 8 MHz**, built with **WinAVR/AVR-GCC**. They are separate projects because they're separate physical chips — there's no shared build here, each gets flashed independently.


## Building

Open each of `mc1_hmi_unit/` and `mc2_control_unit/` as a separate project in Eclipse with the AVR plugin (or Atmel Studio, which can usually import AVR-Eclipse projects). Both target ATmega16 at 8 MHz — set the fuse bits accordingly if flashing to real hardware, since the internal RC oscillator default doesn't match `F_CPU=8000000UL` in the source. Flash `mc1_hmi_unit` and `mc2_control_unit` to two separate ATmega16 chips wired together via UART (TX↔RX crossed, common ground).

## Simulation

`proteus_simulation/Door Locker.pdsprj` is a Proteus 8 project. Open it in Proteus to see the full circuit (both ATmega16s, keypad, LCD, motor, EEPROM, buzzer) and run the simulation without physical hardware.
