# GraFX

GraFX is a header-only libraries set based on glfw3 and providing the same set of features as exact glfw3 and additional features (planned) such as loading graphics from files and OpenGl-based GUI (probably based on Nuklear). The main difference between glfw3 and GraFX is that GraFX is OOP-designed and mostly uses Modern C++ (11, 14, 17, and going to 20) features in opposite to the pure C-styled library glfw3.

Dependencies for the latest version are:

ACTUAL DEPENDENCIES:
 - C++ 11, 14, 17 features
 - glfw3 (because GraFX is at most an object oriented addon over glfw3, see original glfw dependencies - https://www.glfw.org/)
 - gsl - Guideline support library (currently used gsl-lite, but ms-gsl is also welcome, just change <gsl-lite> to <ms-gsl>
 - STL (just standard library, - see the C++ features the library uses)
  
PLANNED DEPENDENCIES (PROBABLY, NOT USED FOR THE MOMENT, BUT PROBABLY WOULD BE IN THE FUTURE):  
 - (???)  Nuklear (https://github.com/vurtun/nuklear) 
 - (???)  OpenImageIO (https://sites.google.com/site/openimageio/home)
 - (???)  Glbinding (https://github.com/cginternals/glbinding)
 - (???)  Globjects (https://github.com/cginternals/globjects)
 
Sign "(???)" - means that the decision isn't made yet. Amount of question signs ("?") says, how far the decision from being made.

WARNING: The project is under active development and is in a pre-alpha version, therefore it has uncomplete functionality, and (somewhere) it's organized in unstructured order and there is a lack of tests, documentation and examples. Please notice, that all those problems are temporary and will be fixed in fututre versions.

For this moment it uses uncomplete but working CMakeLists.txt, therefore you can test it.

License: MIT/BSD depending on your choice. 
Notice, that libraries, GraFX based on have their own licence agreements.
