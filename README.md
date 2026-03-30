# fract-ol

A fractal explorer written in C using the MiniLibX graphics library. Renders Mandelbrot, Julia, and Burning Ship fractals with real-time zoom, pan, and color controls.

---

## Preview


| Mandelbrot | Julia | Burning Ship |
|:---:|:---:|:---:|
| ![Mandelbrot](images/mandelbrot.png) | ![Julia](images/julia.png) | ![Burning Ship](images/burning_ship.png) |

---

## Features

- Three fractal types: **Mandelbrot**, **Julia**, **Burning Ship**
- Real-time zoom (mouse wheel or keyboard)
- Pan with arrow keys
- Adjustable iteration depth for more detail
- Dynamic color shifting

---

## Requirements

- Linux with X11
- MiniLibX (`mlx_linux`)
- GCC / cc

---

## Build

```sh
make
```

---

## Usage

```sh
./fractol M                          # Mandelbrot
./fractol J                          # Julia (default params)
./fractol J <real> <imag>            # Julia with custom seed (values between -2.0 and 2.0)
./fractol B                          # Burning Ship
```

**Example:**
```sh
./fractol J -0.7 0.27
```

---

## Controls

| Key / Input | Action |
|---|---|
| Arrow keys | Pan |
| Mouse wheel | Zoom in / out |
| `i` / `o` | Zoom in / out (keyboard) |
| `j` / `f` | Increase / decrease iterations |
| `z` / `x` | Shift colors |
| `ESC` | Quit |

---

## Project Structure

```
fract-ol/
├── fractol.h           # Structs and function prototypes
├── fractol.c           # Entry point and argument validation
├── fractol_render.c    # Fractal rendering logic
├── fractol_events.c    # Keyboard and mouse event handlers
├── fractol_utils.c     # Fractal init helpers
├── cal_utils.c         # Complex number math
├── extra_utils.c       # String/parsing utilities
├── ft_putstr_fd.c      # Output utility
└── Makefile
```

