# Architecture & Organization

This is an **archival/educational** repository (no build support). The 20 official files are organized into subfolders for readability.

```
src/
├── capture
│   ├── ScreenCaptureFast.cpp
│   └── ScreenCaptureFast.h
├── core
│   ├── Estruturas.h
│   ├── GetCastWalkSleep.cpp
│   ├── GetCastWalkSleep.h
│   ├── GetScreenSize.cpp
│   ├── GetScreenSize.h
│   ├── Globais.cpp
│   └── main.cpp
├── input
│   ├── GetMousePosInRealTime.cpp
│   ├── GetMousePosInRealTime.h
│   ├── GetSpaceState.cpp
│   ├── GetSpaceState.h
│   ├── interception.c
│   └── interception.h
└── vision
    ├── avir.h
    ├── GetClosestEnemy.cpp
    ├── GetClosestEnemy.h
    ├── GetStatsInRealtime.cpp
    └── GetStatsInRealtime.h
```

## Folders
- `core/` — entry point, globals/utilities, cast/walk timing.
- `capture/` — Desktop Duplication (DXGI/D3D11) screen capture.
- `vision/` — CV (OpenCV/OCR) and resampling (AVIR).
- `input/` — input capture/control (Interception), mouse position, Space key.

> Some identifiers/comments remain in Portuguese on purpose to keep the code **as-it-is** (historical).

## Data flow
```
[ capture ] -> [ vision ] -> [ core ] -> [ input ]
ScreenCap      OCR/Match      Timings     Send/Track
```
