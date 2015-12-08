//
//  inputException.cpp
//  MipsPipelinedSimulator
//
//  Created by Alia Hassan  on 12/8/15.
//  Copyright (c) 2015 Alia Hassan . All rights reserved.
//
#include <stdexcept>
#include <iostream>
#include "inputException.h"



inputException::inputException(std::string k ):std::runtime_error(k)
{
//    std::cout << k;
}