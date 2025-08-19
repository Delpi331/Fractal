# Fract-ol (42) — Mandelbrot & Julia en C con MiniLibX

**Fractal visualization program in C (Mandelbrot & Julia) with interactive zooming and adjustable visual parameters.**

---

## 🌌 Resumen

* **Lenguaje:** C (C99)
* **Gráficos:** [MiniLibX](https://github.com/42Paris/minilibx-linux)
* **Fractales:** Mandelbrot y Julia
* **Interacción:** Zoom, pan, cambio de parámetros
* **Objetivo:** Comprender matemáticas complejas, eventos gráficos y renderizado 2D desde cero

---

## 🧠 ¿Por qué **MiniLibX**?

**MiniLibX (MLX)** es una librería gráfica ligera diseñada para 42. Permite:

* Crear **ventanas** y **buffers de imagen**
* Dibujar píxeles directamente en memoria
* Manejar **eventos** de teclado y ratón
* Mantener un **loop gráfico** sencillo

👉 Elegí MiniLibX porque es la librería permitida en 42 y obliga a trabajar a **bajo nivel**, entendiendo cómo se genera cada píxel del fractal. Esto me dio control total sobre el renderizado y una base sólida en gráficos.

---

## ⚙️ Funcionamiento del programa

1. Cada píxel de la ventana se **mapea** a un punto en el plano complejo.
2. Según el fractal elegido:

   * **Mandelbrot**: itera `z = z² + c` con `z0 = 0`.
   * **Julia**: itera `z = z² + c` donde `c` es fijo y viene por CLI.
3. Se cuentan las **iteraciones hasta escapar** (cuando `|z| > 2`).
4. Ese número define el **color** del píxel.
5. El buffer se dibuja en la ventana con `mlx_put_image_to_window`.

---

## ⌨️ Controles

* **Zoom**: rueda del ratón
* **Moverse**: flechas o WASD (pendiente en esta versión)
* **Salir**: tecla `ESC` o cerrar la ventana

---

## 🚀 Uso

```bash
# Compilar con Makefile
make

# Ejecutar Mandelbrot
./fractol mandelbrot

# Ejecutar Julia con parámetros
./fractol julia -0.8 0.156
```

---

## 🗂️ Explicación del código

### 📌 `Main.c`

Este archivo contiene el **punto de entrada**.

* `strcmp` → Implementación propia para comparar cadenas (evitando `strcmp` estándar).
* `fract()` → Inicializa la estructura `t_fractal`: ventana, imagen, rango complejo, zoom, offsets y máximo de iteraciones.
* `win()` → Encapsula la lógica de ventana: muestra la imagen y configura hooks de eventos (`close_window`, `key_hook`, `mouse_hook`).
* `main()` →

  1. Lee argumentos (`mandelbrot` o `julia a b`).
  2. Inicializa la estructura `t_fractal`.
  3. Llama a `render_fractal`.
  4. Inicia el bucle de eventos con `win()`.

📌 **Decisión clave:** el parseo CLI permite seleccionar entre Mandelbrot y Julia, pasando parámetros reales e imaginarios para personalizar la constante `c`.

---

### 📌 `fractal.c`

Contiene la lógica de renderizado.

* `render_fractal()` →

  * Recorre cada píxel `(x, y)`.
  * Lo traduce a coordenadas complejas `(re, im)` usando el rango `min/max_re/im`.
  * Evalúa el fractal:

    * Mandelbrot: `mandelbrot(re, im)`
    * Julia: `julia(re, im, cr, ci, max_iter)`
  * Obtiene un color en función de las iteraciones (`get_color`).
  * Escribe el píxel en el buffer (`my_mlx_pixel_put`).

* `my_mlx_pixel_put()` → Función auxiliar para dibujar un píxel en la dirección de memoria de la imagen.

📌 **Decisión clave:** se escribe en el buffer en lugar de dibujar píxel a píxel en ventana → esto mejora la eficiencia.

---

### 📌 `Makefile`

Reglas estándar de 42:D

* `all`: compila el binario `fractol`
* `clean`: elimina objetos `.o`
* `fclean`: elimina objetos y binario
* `re`: recompila desde cero

📌 **Decisión clave:** simplifica la compilación y asegura portabilidad.

---

## 🧵 Posibles mejoras

* Añadir **paletas de colores múltiples**
* Implementar **pan con teclado** y zoom suave
* Guardar capturas en PNG
* Incluir más fractales (Burning Ship, Multibrot)

---

## 🖼️ Ejemplo visual

(Mandelbrot)

<img width="812" height="630" alt="image" src="https://github.com/user-attachments/assets/52f61d6e-5aa7-4ffc-a872-d3c27f2f7db3" />

(Julia)
