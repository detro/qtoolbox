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

#ifndef LOGMACROS_H
#define LOGMACROS_H

//< Put "DEFINES += ENABLE_LOG_MACROS" in your .pro/.pri file to enable Logging.
#if defined(ENABLE_LOG_MACROS) && defined(ENABLE_FILE_LOG)
    #include <qDebug>
    #define DEBUG_TAG(tag, exp) qDebug() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                            "(" << tag << ")" << \
                                            "(" << exp << ")"

    #define DEBUG(exp)         qDebug() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                            "(" << exp << ")"

    #define CRITICAL_TAG(tag, exp) qCritical() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                                    "(" << tag << ")" << \
                                                    "(" << exp << ")"

    #define CRITICAL(exp) qCritical() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                            "(" << exp << ")"

    #define WARNING_TAG(tag, exp) qWarning() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                                    "(" << tag << ")" << \
                                                    "(" << exp << ")"

    #define WARNING(exp) qWarning() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                        "(" << exp << ")"

    // common debugs:
    #define DEBUG_ENTER_FN() qDebug() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                            "( enter )" << \
                                            "(" << __FUNCTION__ << ")"

    #define DEBUG_EXIT_FN() qDebug() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                            "( exit )" << \
                                            "(" << __FUNCTION__ << ")"
#else
    #define DEBUG_TAG(tag, exp)
    #define DEBUG(exp)

    #define CRITICAL_TAG(tag, exp)
    #define CRITICAL(exp)

    #define WARNING_TAG(tag, exp)
    #define WARNING(exp)

    // common debugs:
    #define DEBUG_ENTER_FN()
    #define DEBUG_EXIT_FN()
#endif // ENABLE_LOG_MACROS && ENABLE_FILE_LOG

#if defined(ENABLE_LOG_MACROS) && defined(ENABLE_FILE_LOG) && defined(ENABLE_LOG_MACROS_VERBOSE)
    #define VERBOSE_TAG(tag, exp) qDebug() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                                "(" << tag << ")" << \
                                                "(" << exp << ")"

    #define VERBOSE(exp) qDebug() << "("<< __FILE__ << ":" << __LINE__ << ")" << \
                                        "(" << exp << ")"
#else
    #define VERBOSE_TAG(tag, exp)
    #define VERBOSE(exp)
#endif // ENABLE_LOG_MACROS && ENABLE_FILE_LOG && ENABLE_LOG_MACROS_VERBOSE

#endif // LOGMACROS_H
