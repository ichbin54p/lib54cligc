# lib54cligc

`lib54cligc` is a library for terminal graphics, for linux machines, developed in C. lib 54 cli(command line interface) g(graphics) c(programming language)

**NOTE**: This library is meant for linux machines so it will **not work on windows**.

## Documentation

### Tutorial

First of all, you will need to initialize `lib54cligc` using `lib54cligc_init();` and make sure you run the quit function when your program ends using `lib54cligc_quit();`

Now, when you execute your program, first of all, it will tell you how many bytes it's allocating for pm (pixel map) e.g: Allocating *n* bytes for pm.

Then it should print enough new lines to move the text above it off-screen from the terminal.

Lastly, it will print the quit message, it should be successful. If there are any errors during the initialization or exit, please make an issue on [github](https://github.com/ichbin54p/lib54cligc)

Now, you are ready print pixels on your terminal. You can use the `lib54cligc_pixel_add(x, y, r, g, b)` function to print pixels on your screen. The arguements are:

- x: The X position of the pixel (0 is the first pixel on left of the terminal) Should be an integer.

- y: The Y position of the pixel (0 is the first pixel on top of the terminal) Should be an integer.

- r, g, b: These are to color your pixels, for example: `255, 0, 0` would be red.

Code example:

```c
int main(){    
    lib54cligc_init(); // Initialize

    lib54cligc_pixel_add(2, 2, 255, 25, 25); // Adding a pixel at 2, 2 with a red color.
    sleep(1);

    lib54cligc_quit(); // Quit
    return 0;
}
```

Alright, now that you've placed a pixel on the screen, you probably want to know how to clear it, as well. There are several ways to clear a pixel or multiple.

You could simply use `lib54cligc_pixel_clear();` to clear every pixel on the terminal.

However, if you wanted to clear only 1 pixel specifically, you could use `lib54cligc_pixel_remove(x, y)` to remove it. Arguements:

- x: The X position of the pixel (0 is the first pixel on left of the terminal) Should be an integer.

- y: The Y position of the pixel (0 is the first pixel on top of the terminal) Should be an integer.

You could also use `lib54cligc_pixel_remove_fast(i)` but then you have to use an index to remove a certain pixel. Pixels are stored in the `lib54cligc_pixels` structure, every time you add a new pixel it will increment `lib54cligc_pixels.idx`,

unless you use the `lib54cligc_pixel_add_advanced(x, y, e)` function, it is basically the same as `lib54cligc_pixel_add` except instead of using rgb you have to input your own escape codes, as well as adding the pixel characters and end escape code which is normally `\033[0m`.

Now, try making a bouncey ball program.

### Reference

#### `lib54cligc_pixelmap`

This is a structure used for plotting pixels. A use case example would be:

```c
int main(){
    struct lib54cligc_pixelmap pm;

    pm.x = malloc(4);
    pm.y = malloc(4);

    // Allocate 8 bytes for enough space to plot 4 pixels
}
```

#### `TERMINAL_FLAGS`

This is a structure, it contains the old terminal flags.

#### `TERMINAL_FLAGS_NEW`

This is also a structure, it contains the new terminal flags which were applied during the initialization.

#### `TERMINAL_SIZE`

This structure contains your terminal size during the initialization

#### `lib54cligc_pixels`

This is a structure which contains the pixel map from `lib54cligc`.

#### `lib54cligc_init()`

This function initializes `lib54cligc`. You must execute this function before you do anything else with `lib54cligc`.

#### `lib54cligc_pixel_add(int x, int y, int r, int g, int b)`

You can place pixels on the terminal using this function. The first 2 arguements are for the position of the pixel and the last 3 are the color.

#### `lib54cligc_pixel_add_advanced(int x, int y, char* e)`

The same as `lib54cligc_pixel_add` except instead of having rgb arguements, you input your own escape codes at arguement e.

#### `lib54cligc_pixel_remove_fast(int i)`

Remove a pixel via it's index on `lib54cligc_pixels`.

#### `lib54cligc_pixel_remove(int x, int y)`

Remove a pixel via it's position.

#### `lib54cligc_pixel_clear()`

Removes all pixels from the terminal.

#### `lib54cligc_quit()`

Quits `lib54cligc`, make sure to execute this program when your program is finished running.

## Credits

`lib54cligc` was programmed by 54p (ichbin54p)