#!/bin/bash

# Check if a class name is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <ClassName>"
    exit 1
fi

# Class name
CLASS_NAME=$1
HEADER_FILE="${CLASS_NAME}.hpp"
SOURCE_FILE="${CLASS_NAME}.cpp"

# Create .hpp file
cat <<EOL > $HEADER_FILE
#pragma once

#include <iostream>
#include <string>

class $CLASS_NAME {
protected:
    std::string _type;

public:
    $CLASS_NAME(std::string const & type);
    $CLASS_NAME(const $CLASS_NAME &copy);
    $CLASS_NAME &operator =(const $CLASS_NAME &source);
    ~$CLASS_NAME();

    std::string const &getType() const;
};
EOL

echo "$HEADER_FILE generated."

# Create .cpp file
cat <<EOL > $SOURCE_FILE
#include "${CLASS_NAME}.hpp"

$CLASS_NAME::$CLASS_NAME(std::string const &type) : _type(type) {
    std::cout << "Class $CLASS_NAME constructed" << std::endl;
}

$CLASS_NAME::$CLASS_NAME(const $CLASS_NAME &copy) {
    *this = copy;
}

$CLASS_NAME &$CLASS_NAME::operator=(const $CLASS_NAME &source) {
    if (this != &source) {
        _type = source._type;
        std::cout << "Operator = called for $CLASS_NAME class" << std::endl;
    }
    return *this;
}

$CLASS_NAME::~$CLASS_NAME() {
    std::cout << "Destructor for $CLASS_NAME is called" << std::endl;
}

std::string const &$CLASS_NAME::getType() const {
    return _type;
}
EOL

echo "$SOURCE_FILE generated."

# Done
echo "Files for class $CLASS_NAME have been created."
