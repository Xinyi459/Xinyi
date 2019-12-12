//
//  getData.h
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#ifndef getData_h
#define getData_h

#include <stdio.h>
///put the data we need into an array
///it will get all the data in your file
///so you need fetch the data you need via below two function
double *ReadCSV(const char *filename);

///get each triangle's apex data store in an array
double *getApex(const char *filename);

///get each sphere's center data
double *getCenter(const char *filename);


#endif /* getData_h */
