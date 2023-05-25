#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <tuple>
#include <algorithm>

#include "lib.h"

int version();

std::vector<int> split(const std::string &str, char d);