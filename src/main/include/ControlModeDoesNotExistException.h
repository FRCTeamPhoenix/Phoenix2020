#include <iostream>
#include <exception>

class ControlModeDoesNotExistException : public std::exception {
    public:
        virtual const char* what() const throw() override {
            return "ControlModeDoesNotExistException: Control mode does not exist";
        }
};