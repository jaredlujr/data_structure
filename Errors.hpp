
/* ERROR type definition*/

class OutOfBound : public std::exception {
  const char *what(void) const throw() {// what is the common method of exception class, it return the cause of error
    return "[ERROR]Your visit is out of the maximum size of list!\n";
  }
};

class IllegalSize: public std::exception {
  const char *what(void) const throw() {
    return "[ERROR]Allocating memory failed.Illegal Size arises!\n";
  }
};