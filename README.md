# Fuzzy Library for Arduino

Library built to embeded Fuzzy Logic Models on Arduino.

## Getting Started

### Instalation

* Clone this project inside your arduino /library folder

```
git clone git@github.com:Amimaro/FuzzyLibrary.git
```

* Or, download the .zip file and extract it


### Documentation

* Fuzzy  

Main class. Creates an object to start using the other functions.
```
Fuzzy fz;
```
 
 
* uint8_t createVariable(uint8_t INPUT/OUPUT)


Creates a variable that can be set as INPUT or OUTPUT. Example: speed, temperature...



* uint8_t addTerm(uint8_t variable);


Adds terms to the variable by setting these variable as parameter. Example: for speed, fast, slow; for temperature, hot, cold...



* void addPointsTo(uint8_t term, float p1, float p2, float p3, float p4);	


Adds four points to the term. The points are set based on the X axis, **p1** and **p4** they are pulled to 0 at the Y axis and **p2** and **p3** are pulled to 1 at the Y axis.

Example: 0, 1, 1, 2 makes a triangle starting at 0 at X and Y axis, the 1's make the vertex of the triangle at 1 on the X and Y axis and the line goes down to 2 at the X axis and 0 at the Y axis.



* uint8_t createRule(uint8_t input_variable, uint8_t input_term, uint8_t output_variable, uint8_t output_term);


Creates the rule of inference for the fuzzy logic. This function works like this: "if *input variable* is *input_term* then *output_variable* is *output_term*".



* uint8_t setVariableValue(uint8_t, float);	


Sets a value to the term of the variable. This value is set based on the X axis.



* float getVariableValue(uint8_t);	


Returns the value of the term of the variable.



* float calculate();	


Calculate the defuzzified value of the OUTPUT variable based on the rules of inference and the setted values.



***

Feel free to check the example at the library. :)
