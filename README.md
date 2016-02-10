# ASCII-Art
Turns images into text files that look like them.

## Usage
- Compile with ./build.sh
- Compiles two executables, ./readfont and ./convert.
- Use ./readfont to create new .fontinfo files and ./convert to convert images.
- Syntax
  + ./readfont [path-to-ttf] [font-size]
  + ./convert [path-to-image] [result width] [result height] [path-to-.fontinfo]
- If no .fontinfo file is specified, the program will use default.fontinfo, which represents Arial Black, size 32.
