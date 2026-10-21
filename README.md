# Fractaler

Rendering beautiful fractals (**Julia**, **Mandelbrot** and **Burning Ship**) in C [zoom, pan, color controls].

<table>
  <tr>
    <td align="center" width="33%"><img src="images/julia.png" alt="Julia"><br>Julia</td>
    <td align="center" width="33%"><img src="images/mandelbrot.png" alt="Mandelbrot"><br>Mandelbrot</td>
    <td align="center" width="33%"><img src="images/burning_ship.png" alt="Burning Ship"><br>Burning Ship</td>
  </tr>
</table>

<div align="center">
  <img src="images/fractal-zooms.gif" width="300" alt="Julia zoom followed by Mandelbrot zoom">
  <br>
  Julia and Mandelbrot infinite zoom demo. <a href="images">Check images</a>
</div>

## Usage

```sh
gcl https://github.com/0xseljarida/fractaler.git && cd fractaler # clone and enter
make # compile
./fractol M
```

Run `./fractol` for usage details.

## Libraries

- [MiniLibX](https://github.com/42paris/minilibx-linux) (Linux/X11)
