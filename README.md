# Dusk

Dusk is an interpreted programming language written in C++. Compared to other interpreted languages, Dusk doesn't use tokens, all commands being parsed.
For the time being, I haven't implemented functions, classes or arrays!!!

Syntax: </br>
print -> prints text, variables or operations (print Hello World!) </br>
var -> declares a variable (var a=1) </br>
put -> input for variable (put a) </br>
if -> decision branch (if 3>2) </br>
stopif -> if statement end </br>
Note: There is no else statement yet! </br>
while -> loop (while 3>2) </br>
stoploop -> while loop end </br>
newline -> Jump to the next line </br>
exit -> stops the program </br>

Examples </br>
1. Print simple message</br>
print Hello World!</br>
exit</br>
2. Sum
var a=1</br>
var b=1</br>
</br>
put a Enter first number:</br>
put b Enter second number:</br>
</br>
print a+b</br>
exit</br>
3. Even or odd</br>
var i=1</br>
</br>
while i<10</br>
if i%2=0</br>
print Even</br>
stopif</br>
if i%2=1</br>
print Odd</br>
stopif</br>
i=i+1</br>
newline</br>
stoploop</br>
exit</br>
</br>
Note: While using print, sometimes, the space at the end of a word isn't parsed, so you can use 'print @spc' for a more aesthetic look. </br>
</br>
In the coming days, I'll make tutorials on my Youtube Channel.</br>
