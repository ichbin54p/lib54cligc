# Compiling

To compile `54cligc`, run:

```sh
sudo make install
```
```sh
make clean
```
Then you should be able to include it like this:
```c
#include <lib54cligc/lib54cligc.h> // Base library
#include <lib54cligc/lib54cligc-widgets.h> // Widget addon
```

To compile a program with `54cligc`, run:

```sh
gcc your_program.c -L/usr/local/lib -l54cligc -o output
```

# lib54cligc

`lib54cligc` is a library for terminal graphics, for linux machines, developed in C. lib 54 cli(command line interface) g(graphics) c(programming language)

![alt text](https://github.com/ichbin54p/lib54cligc/blob/main/Content/snake.gif?raw=true)

**NOTE**: This library is meant for linux machines so it will **not work on windows** unless you use WSL.

## Documentation

### Tutorial

First of all, you will need to initialize `lib54cligc` using `lib54cligc_init();` and make sure you run the quit function when your program ends using `lib54cligc_quit();`

Now, when you execute your program, you should have a log file containing all important information about the program while it's running.

Then it should print enough new lines to move the text above it off-screen from the terminal.

If there are any errors during the initialization or exit, please make an issue on [github](https://github.com/ichbin54p/lib54cligc)

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

There is also a `lib54cligc_rect` function, play around with it.


Now try making a bouncy ball program
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

#### `lib54cligc_text`

This structure is basically the same as `lib54cligc_pixels` except it's for the characters on the terminal, not the pixels.

#### `pms`

Stands for pixel map size, in bytes.

#### `tms`

Stands for text map size, in bytes.

#### `lib54cligc_init()`

This function initializes `lib54cligc`. You must execute this function before you do anything else with `lib54cligc`.

#### `lib54cligc_pixel_add(int x, int y, int r, int g, int b)`

You can place pixels on the terminal using this function. The first 2 arguements are for the position of the pixel and the last 3 are the color.

#### `lib54cligc_pixel_add_advanced(int x, int y, char* e)`

The same as `lib54cligc_pixel_add` except instead of having rgb arguements, you input your own escape codes at arguement e.

#### `lib54cligc_pixel_text_advanced(int x, int y, char* text)`

The same as `lib54cligc_pixel_text` except instead of having rgb arguements for the foreground and background, you input your own escape codes at arguement e. 

#### `lib54cligc_pixel_rect(int x, int y, int w, int h, int r, int g, int b)`

Almost the same as `lib54cligc_pixel_add` except you have 2 extra arguements: `w` and `h`.

#### `lib54cligc_pixel_text(int x, int y, char* text, int fr, int fg, int fb, int br, int bg, int bb)`

You can place characters on the terminal using this function. The first 2 arguements are for the position of the text and the next 3 are for the text color and the last 3 are for the background color.

#### `lib54cligc_pixel_remove_fast(int i)`

Remove a pixel via it's index on `lib54cligc_pixels`.

#### `lib54cligc_pixel_remove(int x, int y)`

Remove a pixel via it's position.

#### `lib54cligc_pixel_clear()`

Removes all pixels from the terminal.

#### `lib54cligc_quit()`

Quits `lib54cligc`, make sure to execute this program when your program is finished running.

# lib54cligc-widgets

`lib54cligc-widgets` is an addon for `lib54cligc` which adds widgets such as buttons and input fields.

![alt text](https://github.com/ichbin54p/lib54cligc/blob/main/Content/widget.gif?raw=true)

## Tutorial

So you've probably already read the `lib54cligc` tutorial, if not, go read [`lib54cligc` Tutorial](#tutorial) before reading this one.

So, let's start off with a simple button. First of all, if you haven't already, you need to include `lib54cligc/lib54cligc-widgets.h`, then you must define your button with the struct `lib54cligc_widget_button`

There are quite a few values you have to fill in:

- index: The index of the button, later on when we display it and the cursor value is the same as the button index, it will be hovered and then you can use it.

- fg1: This is an array with 3 integers in it for the foreground color of the button when it's not hovered

- bg1: This is the same as fg1, except it's the background color.

- fg2, bg2: This is for when the button is hovered, the data type is exactly the same as fg1 and bg1.

- onclick: When the button is actived, this onclick will trigger, it should be a `void` function with `(void)` arguements.

Now that we have defined our button, we need to display it. The function `lib54cligc_widget_button_display(x, y, label, index, activate, button)` will display your button and execute a function when it's activated, let's break down the arguements and explain it in detail:

- x: The x display position of the button
- y: The y display position of the button
- label: The buttons label
- index: The cursor's position
- activate: Whether the button should be activated or not
- button: Your button structure goes here, the one you defined earlier.

Let's check out a code example

```c
char out[24];

void onclick(void){
    strcpy(out, "You clicked the button!");
} // Our onclick which we will use later in the program

int main(){
    if (lib54cligc_init() != 0){
        return -1;
    } // Init

    int run = 1; // Run variable for our while loop
    int active = 0; // We will use this variable later
    int cursor = 0; // The cursor is the current index, which we will compare to our button
    char lk = 0; // Will be used later for key detection

    struct lib54cligc_widget_button button = {0, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}, onclick};

    // Create a button at index 0 which will execute our onclick function if activated

    while (run){
        if (active == 1){
            active = 0;
        } // If active was triggered, reset it to 0 at the beginning of the loop

        char key = 0;
        size_t kl = read(STDIN_FILENO, &key, 1);

        // For our input detection

        if (key != lk){
            if (kl > 0){
                switch (key){
                    case 'q':
                        run = 0; // Handle exit
                        break;
                    case '\n':
                        active = 1;
                        break;
                    case 'a':
                        cursor -= 1;
                        break;
                    case 'd':
                        cursor += 1;
                        break;
                }
            }

            lk = key;
        }

        // This is just some key detection code, you don't have to understand it

        lib54cligc_widget_button_display(2, 5, "click me!", cursor, active, button);

        lib54cligc_pixel_text(1, 2, out, 255, 255, 255, 0, 0, 0);

        fflush(stdout);

        // Display the button and it will execute if active is 1 and cursor is index

        usleep(10000);
        lib54cligc_pixel_clear();

        // Clearing the pixel map, can prevent core dumps
    }

    lib54cligc_quit(); // Quit
}
```

Now, let's make an input box. The input box will only capture text when it's active. Inputs are a little more complex then buttons, you have to initialize them and destroy them.

Let's start by creating our input with the struct `lib54cligc_widget_input`, if you thought the button had many values... The input field has even more!

- active: Whether the input should be active or inactive, when the input is active, you can enter text into it.

- index: The same as a button, the index of the input which we will use later in our program with our cursor.

- fg1, bg1, fg2, bg2: The exact same as a button.

- max_chars: The maximum amount of characters the input can hold. **Note:** the input's size is also equal to the maximum amount of characters so, if you were to set it to a number which is bigger than your terminal, it will not dispaly.

- chars: counts the amount of characters in the input field, set this to 0.

- content, placeholder: You can leave these values as we will be setting them up with `lib54cligc_widget_input_create`

Now, let's create aka initialize our input, we can use the function `lib54cligc_widget_input_create(placeholder, input)`, arguements:

- placeholder: The placeholder of the input, it will display when `chars` is equal to 0. **Note:** the placeholder is not allowed to be larger than max_chars.

- input: A pointer of your input structure

Then, we'll want to display it in the loop with `lib54cligc_widget_input_display(x, y, index, active, k, pactive, input)`, arguements:

- x: The position of the widget.
- y: The position of the widget.
- index: The cursor's position.
- active: Whether to activate the widget or not.
- k: The current key that is being pressed. **Note:** make sure you reset the key to `0` otherwise it will input whatever the key was before.
- pactive: This needs to be pointing to an integer so that it can modify if active.
- input: This needs to be pointing to your input so that it can modify it

Afterwards, you must destroy it with `lib54cligc_widget_input_destroy(input);` where `input` is the same as `lib54cligc_widget_input_display`. The reason we are destroying the widget is so that you can free the memory.

Now, let's check out another code example! Actually, this code example was used to test the library widget. You can find the gif at [lib54cligc-widgets](#lib54cligc-widgets)

```c
struct lib54cligc_widget_input input = {0, 0, {255, 255, 255}, {50, 50, 40}, {0, 0, 0}, {255, 255, 255}, 11, 0};

// Define the input at index 0 with an 11 character limit

char text[11];

// Text which we will modify later on

void onclick(void){
    strcpy(text, input.content);
} // Onclick function to modify the text when clicked

int main(){
    if (lib54cligc_init() != 0){
        return -1;
    } // Init

    int run = 1;
    int active = 0; 
    int cursor = 0;
    int pactive = 0;

    // We will use pactive to disable keybinds while in the input

    char lk = 0;

    struct lib54cligc_widget_button submit = {1, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}, onclick};
    
    // Our submit button

    lib54cligc_widget_input_create("type...", &input);

    // Create the input with the placeholder "type..."

    while (run){
        if (active == 1){
            active = 0;
        }

        char key = 0;
        size_t kl = read(STDIN_FILENO, &key, 1);

        if (key != lk){
            if (kl > 0){
                switch (key){
                    case 'q':
                        run = 0;
                        break;
                    case '\n':
                        active = 1;
                        break;
                    case 'a':
                        if (!pactive){
                            cursor -= 1;
                        }
                        break;
                    case 'd':
                        if (!pactive){
                            cursor += 1;
                        } // Only move the cursor if pactive is 0
                        break;
                }
            }

            lk = key;
        }

        lib54cligc_pixel_text(1, 5, text, 255, 255, 255, 0, 0, 0);

        // Display the text

        lib54cligc_widget_input_display(1, 10, cursor, active, key, &pactive, &input);
        lib54cligc_widget_button_display(16, 10, "submit", cursor, active, submit);

        // Display the widgets

        fflush(stdout);
        usleep(30000);
        lib54cligc_pixel_clear();
    }

    lib54cligc_widget_input_destroy(&input);

    // Destroy the input when we're finished with it

    lib54cligc_quit(); // Quit
}
```

## Reference

### `lib54cligc_widget_button`

A button struct used to define a button

### `lib54cligc_widget_input`

An input struct used to define an input field.

### `lib54cligc_widget_input_create(char* placeholder, struct lib54cligc_widget_input* input)`

Create (initialize) an input widget, you have to use this function before you can actually start displaying your input widget.

### `lib54cligc_widget_input_destroy(struct lib54cligc_widget_input* input)`

Destroy an input widget, frees all the memory used up by the widget. Useful when you don't need to use the input widget anymore.

### `lib54cligc_widget_input_display(int x, int y, int index, int active, char k, int* pactive, struct lib54cligc_widget_input* input)`

Display an input widget

### `lib54cligc_widget_button_display(int x, int y, char* label, int index, int activate, struct lib54cligc_widget_button button)`

Display a button widget

# Credits

`lib54cligc` was programmed by `54p` (`ichbin54p`)

Thanks to `Riverspace` for testing
Thanks to **everyone** who gave feedback, as well.

# Extra

Make sure to check out `tests` for some fun silly programs