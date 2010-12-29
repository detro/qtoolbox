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

#include "printpowerset.h"
#include <QString>

#include "activelogs.h"
#ifdef PRINT_POWER_SET
    #define ENABLE_LOG_MACROS
#endif
#include "logmacros.h"

PrintPowerSet::PrintPowerSet() : m_currentIndex(0) {
    DEBUG_ENTER_FN();
    DEBUG("debug test");
    DEBUG_TAG("debug tag" , "debug text");

    WARNING("warning test");
    WARNING_TAG("warning test" , "warning text");

    CRITICAL("critical tag");
    CRITICAL_TAG("critical test" , "critical text");
    DEBUG_EXIT_FN();
}

void PrintPowerSet::printSet() {
    QString solution;
    foreach(int n, m_currentSolution) {
        solution.append(QString().setNum(n));
    }
    CRITICAL("set element:" << solution );
}

void PrintPowerSet::setInputArray(const QVector<int>& aArray) {
    DEBUG_ENTER_FN();
    m_inputArray = aArray;
    m_currentSolution.reserve( m_inputArray.count() );
    DEBUG_EXIT_FN();
}

void PrintPowerSet::calculatePowerSet() {
    if( m_currentIndex == m_inputArray.count() ) {
        VERBOSE_TAG("tagged", "found set element");
        VERBOSE("found set element");
        //it's a set element
        printSet();
        return;
    }

    // calculate all sets which include element at m_currentIndex
    m_currentSolution.append( m_inputArray.at(m_currentIndex) );
    ++m_currentIndex;
    calculatePowerSet();

    // calculate all sets which DO NOT include element at m_currentIndex
    m_currentSolution.pop_back();
    calculatePowerSet();
    --m_currentIndex;
}

