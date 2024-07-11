# dusk

Dusk is an interpreted programming language written in C++. Compared to other interpreted languages, Dusk doesn't use tokens, all command being parsed.
For the time being, I haven't implemented functions, classes or arrays!!!

Syntax:
print -> prints text, variables or operations (print Hello World!)
var -> declares a variable (var a=1)
put -> input for variable (put a)
if -> decision branch (if 3>2)
stopif -> if statement end
Note: There is no else statement yet!
while -> loop (while 3>2)
stoploop -> while loop end
newline -> Jump to the next line
exit -> stops the program

<u>Examples</u>
1) Print simple message
print Hello World!
exit
   
2) Sum
var a=1
var b=1
  
put a Enter first number:
put b Enter second number:
  
print a+b
exit

3) Even or odd
var i=1

while i<10
if i%2=0
print Even
stopif
if i%2=1
print Odd
stopif
i=i+1
newline
stoploop
exit

Note: While using print, sometimes, the space at the end of a word isn't parsed, so you can use 'print @spc' for a more aesthetic look. 

In the coming days, I'll make tutorials on my Youtube Channel.
