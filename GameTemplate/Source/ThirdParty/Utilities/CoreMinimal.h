#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

#define CONCAT(a, b) a b
#define FINDASSET(FilePath) CONCAT(CONTENTPATH, FilePath)
//#define FINDASSET(FilePath) CONTENTPATH FilePath

using std::string;

#include "raylib.h"
#include "LogSystem/LogSystem.h"