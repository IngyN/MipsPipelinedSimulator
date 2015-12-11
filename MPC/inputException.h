//
//  inputException.h
//  MipsPipelinedSimulator
//
//  Created by Alia Hassan  on 12/8/15.
//  Copyright (c) 2015 Alia Hassan . All rights reserved.
//

#ifndef __MipsPipelinedSimulator__inputException__
#define __MipsPipelinedSimulator__inputException__

#include <stdio.h>
#include <stdexcept>
#include <QString>

class inputException: public std::runtime_error
{
public:
    inputException(std::string k );
};


#endif /* defined(__MipsPipelinedSimulator__inputException__) */
