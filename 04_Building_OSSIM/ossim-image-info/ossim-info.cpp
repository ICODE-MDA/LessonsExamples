//*******************************************************************
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  Garrett Potts
//
//*******************************************************************
//  $Id: ossim-info.cpp 18619 2011-01-03 10:33:51Z dburken $

#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimException.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/init/ossimInit.h>
#include <ossim/util/ossimInfo.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
   
   // Initialize ossim stuff, factories, plugin, etc.
   ossimInit::instance()->initialize(ap);

   
   return 0;
   
} // End of main...
