# ASCII-Art
Creates a text file that looks like a specified image. You can choose the font with which the program makes the calculations.

## Usage
- Compile with ./build.sh
- Compiles two executables, ./readfont and ./convert.
- Use ./readfont to create new .fontinfo files and ./convert to convert images.
- Syntax
  + ./readfont [path-to-ttf] [font-size]
  + ./convert [path-to-image] [result width] [result height] [path-to-.fontinfo]
- If no .fontinfo file is specified, the program will use default.fontinfo, which represents Arial Black, size 32.
