/**
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE.txt
* file distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#include <QtCore/QCoreApplication>
#include "printpowerset.h"
#include <QVector>

#include "activelogs.h"
#ifdef MAIN
    #define ENABLE_LOG_MACROS
#endif
#include "logmacros.h"

int main(int argc, char *argv[])
{
    DEBUG("main ... ... beginning");
    PrintPowerSet printPowerSet;

    QVector<int> input;
    input.append(1);
    input.append(2);
    input.append(3);
    input.append(4);
    printPowerSet.setInputArray(input);
    DEBUG("input array created...");
    printPowerSet.calculatePowerSet();
    DEBUG("main ... ... done!.!.!.!");
    return 0;
}
