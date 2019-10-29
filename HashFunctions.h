// Copyright Andra Serban
#ifndef HASHFUNCTIONS_H_
#define HASHFUNCTIONS_H_
#include <iostream>
#include <string>

int char_hash(std::string str) {
  return str.length() + 8497;
}

#endif  // HASHFUNCTIONS_H_

