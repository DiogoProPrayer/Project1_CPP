
# Programming project

## Group elements

- up202306461 Diogo Alexandre Morais Pinheiro
- up202305035 Ana Belém Meireles Bilhoto 
- up202305089 Bárbara Catarina Cerqueira Veloso Gomes


## Accomplished tasks

### SVGElements.hpp

- All classes used in the project are declared in this document as well as the functions related to each class, which are a constructor, a draw and a transform function.
- we created the classes needed to represent the geometrical shapes. Furthermore, we established a correlation between some of the classes, which in turn made our code better for others to read through and understand.


### SVGElements.cpp

- Contains the code of each class function,previously declared in the header file, wich are the draw function, the constructor specific to each class and a transform function.


### readSVG.cpp

- Created a new recursive function **readElements( )** to read all the elements of the **.svg** file, create an object for each element using dynamic memory, apply all the transformations using the **transform( )** method and store them in the **svg_elements** vector;
- Created a new (also recursive) function **use( )**, called when an **<use>** element is found by the **readElements( )** function, to read the entire file from the beggining and call the **readElements( )** function back when the **id** of the current element matches the **id** given as an argument to the function.
