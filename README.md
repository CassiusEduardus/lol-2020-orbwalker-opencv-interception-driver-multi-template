# lol-2020-orbwalker-opencv-interception-driver-multi-template

> **Historical 2020 League of Legends orbwalker using OpenCV (multi-template targeting, OCR), DXGI Desktop Duplication capture, and Interception driver for input. External only—no game memory injection. Published as-is; educational only. No build/support. Not affiliated with Riot Games. Explicitly posted as a “personal capability test” and not intended to violate any terms, rights, or policies.**

## What this is (and why it’s public)
This repository preserves a **functional 2020 demo** of an external orbwalker prototype. It is shared **as an archival study case**: computer-vision targeting (template matching + HUD OCR), fast desktop screen capture via **DXGI Desktop Duplication**, and **keyboard/mouse** events through the **Interception** driver.  
There is **no memory reading/writing** of the game. The code is provided **as-is** for educational/reference purposes only.

> **No build or usage support.** This code is not a product and should not be used to target live services. It exists to document historical techniques and architecture.

## Language & naming note
Some variable names, comments, and messages remain in **Portuguese** on purpose to keep the code **as-it-is** and historically faithful. Only documentation was standardized to US English.

## High-level pipeline
```
[capture]  -->  [vision]  -->  [core]  -->  [input]
 DXGI/GDI       OpenCV/OCR     timings      Interception
  frames      templates & HUD  (cast/walk)    mouse/keys
```

- **capture**: grabs frames from the desktop (DXGI Desktop Duplication, with GDI fallback).
- **vision**: finds enemies via **multi-template matching**, thresholds by color, and (optionally) reads stats via OCR.
- **core**: computes attack windup & cooldown windows (per champion/attack speed) and decides cast vs walk.
- **input**: tracks the cursor and sends mouse/keyboard events (Space key state, absolute pointer moves).

## Directory layout (20 official files)
```
src/
├─ core/
│  ├─ main.cpp
│  ├─ Globais.cpp
│  ├─ Estruturas.h
│  ├─ GetCastWalkSleep.cpp
│  ├─ GetCastWalkSleep.h
│  ├─ GetScreenSize.cpp
│  └─ GetScreenSize.h
├─ capture/
│  ├─ ScreenCaptureFast.cpp
│  └─ ScreenCaptureFast.h
├─ vision/
│  ├─ GetClosestEnemy.cpp
│  ├─ GetClosestEnemy.h
│  ├─ GetStatsInRealtime.cpp
│  ├─ GetStatsInRealtime.h
│  └─ avir.h
└─ input/
   ├─ GetMousePosInRealTime.cpp
   ├─ GetMousePosInRealTime.h
   ├─ GetSpaceState.cpp
   ├─ GetSpaceState.h
   ├─ interception.c
   └─ interception.h
```

## File-by-file overview
- **core/main.cpp** — Orchestrates threads/loops and module interaction (demo entry point).
- **core/Globais.cpp** — Defines global state (cursor positions, timings, champion ID, attack speed, screen size).
- **core/Estruturas.h** — Basic structs/enums for points, offsets, Interception contexts, etc.
- **core/GetCastWalkSleep.[h|cpp]** — Computes **cast/walk sleep windows** from attack speed & champion profiles.
- **core/GetScreenSize.[h|cpp]** — Detects and exposes supported screen resolutions.
- **capture/ScreenCaptureFast.[h|cpp]** — DXGI/D3D11 Desktop Duplication for high-FPS capture, with GDI fallback.
- **vision/GetClosestEnemy.[h|cpp]** — OpenCV color thresholding + **multi-template matching** to select nearest enemy.
- **vision/GetStatsInRealtime.[h|cpp]** — HUD parsing; OCR of attack speed/HP (intended for **Tesseract/Leptonica**).
- **vision/avir.h** — Header-only image resampler (third-party; used for fast/high-quality resizing).
- **input/GetMousePosInRealTime.[h|cpp]** — Tracks cursor position (absolute/relative), clamps to screen bounds.
- **input/GetSpaceState.[h|cpp]** — Polls/holds **Space** key state via Interception.
- **input/interception.[h|c]** — Embedded **Interception** driver user-mode interface (third-party source snapshot).

## Historical dependencies (not included)
- **Windows 10** (Win32 API).
- **DirectX 11 / DXGI 1.2** (Desktop Duplication).
- **OpenCV** (3.x/4.x) for CV and template matching.
- **Tesseract OCR + Leptonica** (optional HUD OCR).
- **Interception** driver for input capture/injection.

> This repo does **not** provide build instructions or binaries. The code is frozen as a historical reference.

## Assets & templates (not included)
Some modules expect UI templates such as:
```
Interface Templates\CHAMPS\ALLY TEMPLATE.png
Interface Templates\CHAMPS\ENEMY TEMPLATE.png
Interface Templates\STATS\*.png
```
These are **not** part of the repository and are referenced only to document how the pipeline worked in 2020.

## Scope & limitations
- **External only** (desktop capture + input). **No game memory injection.**
- **No anti-cheat claims** are made. This code is not maintained, tested, or intended for live use.
- Timing heuristics, thresholds, template assets, and OCR tuning reflect **2020** experiments.

## Ethics & legal
- **Educational/archive only**. Not affiliated with or endorsed by **Riot Games**.  
- Do **not** use this to violate **ToS**, EULAs, anti-cheat policies, or any law.  
- Shared explicitly as a **“personal capability test”** and study case.  
- Third-party components remain under their respective licenses (see `THIRD_PARTY_NOTICES.md`).

## Repository housekeeping
- A curated `.gitignore` is included to keep builds and intermediates out of version control.
- Documentation lives under `docs/` (architecture overview, module map, asset references).
- No CI, no issue support, no feature requests.

## License
No open-source license is granted for this repository by default (archival release).

![Alt](https://repobeats.axiom.co/api/embed/e3012718351228252e51df2ae3db72cfd51caf28.svg "Repobeats analytics image")
