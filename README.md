# MPinCPP
Exercises and snippets of code in CPP template metaprogramming

0. you should ignore the <tt>.cpp</tt> files, their content is mainly a
   commented <tt>main</tt> function. They've been useful to me in the 
   development of the templates, may contain some snippets of code exercising
   the templates, definitely do NOT include them in your project (I didn't pay
   too much attention to the global variables I might have declared and not
   commented out).
1. <tt>arg_pack_trn.hpp</tt> - apply a transformation on each (typename)
   elements of a [template parameter pack](http://en.cppreference.com/w/cpp/language/parameter_pack)
  one by one and "store" the result as the parameter pack of another
  template.
2. <tt>replace_type.hpp</tt> - the modern solution of the exercise 2.1 of the
  ["C++ Template Metaprogramming"](http://www.barnesandnoble.com/w/c-template-metaprogramming-david-abrahams/1100834384?type=eBook) - the <tt>replace_type</tt> one.
  (the text of the exercise in comments at the top of the file). 
 
