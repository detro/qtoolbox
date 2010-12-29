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

#define FILE_AND_LINE_INFO __FILE__ << ":" << __LINE__
#define TAG(tag) "[" << tag << "]"
#define EXP(exp) exp

#define ENTER_TAG TAG("enter")
#define EXIT_TAG TAG("exit")

#if defined(ENABLE_LOG_MACROS)
    #include <qDebug>
    #include <QThread>
    #define CURRENT_THREAD "Thread ("<< QThread::currentThreadId () << ")"

#if defined(DEBUG_LEVEL_ACTIVE)
    #define DEBUG_TAG(tag, exp) qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                            TAG("d") << \
                                            TAG(CURRENT_THREAD) << \
                                            TAG(tag) << \
                                            EXP(exp)

    #define DEBUG(exp)         qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                            TAG("d") << \
                                            TAG(CURRENT_THREAD) << \
                                            EXP(exp)
    // common debugs:
    #define DEBUG_ENTER_FN() qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                            TAG("d") << \
                                            TAG(CURRENT_THREAD) << \
                                            ENTER_TAG << \
                                            __FUNCTION__

    #define DEBUG_EXIT_FN() qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                            TAG("d") << \
                                            TAG(CURRENT_THREAD) << \
                                            EXIT_TAG << \
                                            __FUNCTION__

#else
    #define DEBUG_TAG(tag, exp)
    #define DEBUG(exp)
    #define DEBUG_ENTER_FN()
    #define DEBUG_EXIT_FN()
#endif

#if defined(CRITICAL_LEVEL_ACTIVE)
    #define CRITICAL_TAG(tag, exp) qCritical() << TAG(FILE_AND_LINE_INFO) << \
                                                    TAG("c") << \
                                                    TAG(CURRENT_THREAD) << \
                                                    TAG(tag) << \
                                                    EXP(exp)

    #define CRITICAL(exp) qCritical() << TAG(FILE_AND_LINE_INFO) << \
                                            TAG("c") << \
                                            TAG(CURRENT_THREAD) << \
                                            EXP(exp)
#else
    #define CRITICAL_TAG(tag, exp)
    #define CRITICAL(exp)
#endif

#if defined(WARNING_LEVEL_ACTIVE)
    #define WARNING_TAG(tag, exp) qWarning() << TAG(FILE_AND_LINE_INFO) << \
                                                    TAG("w") << \
                                                    TAG(CURRENT_THREAD) << \
                                                    TAG(tag) << \
                                                    EXP(exp)

    #define WARNING(exp) qWarning() << TAG(FILE_AND_LINE_INFO) << \
                                        TAG("w") << \
                                        TAG(CURRENT_THREAD) << \
                                        EXP(exp)
#else
    #define WARNING_TAG(tag, exp)
    #define WARNING(exp)
#endif

#else
    #define DEBUG_TAG(tag, exp)
    #define DEBUG(exp)
    #define CRITICAL_TAG(tag, exp)
    #define CRITICAL(exp)
    #define WARNING_TAG(tag, exp)
    #define WARNING(exp)
    #define DEBUG_ENTER_FN()
    #define DEBUG_EXIT_FN()
#endif // ENABLE_LOG_MACROS
#if defined(ENABLE_LOG_MACROS) && defined(ENABLE_LOGS_VERBOSE)
    #define VERBOSE_TAG(tag, exp) qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                                TAG("v") << \
                                                TAG(CURRENT_THREAD) << \
                                                TAG(tag) << \
                                                EXP(exp)

    #define VERBOSE(exp) qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                        TAG("v") << \
                                        TAG(CURRENT_THREAD) << \
                                        EXP(exp)
    // common debugs:
    #define VERBOSE_ENTER_FN() qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                            TAG("v") << \
                                            TAG(CURRENT_THREAD) << \
                                            ENTER_TAG << \
                                            __FUNCTION__

    #define VERBOSE_EXIT_FN() qDebug() << TAG(FILE_AND_LINE_INFO) << \
                                            TAG("v") << \
                                            TAG(CURRENT_THREAD) << \
                                            EXIT_TAG << \
                                            __FUNCTION__
#else
    #define VERBOSE_TAG(tag, exp)
    #define VERBOSE(exp)
    #define VERBOSE_ENTER_FN()
    #define VERBOSE_EXIT_FN()
#endif // ENABLE_LOG_MACROS && ENABLE_LOG_VERBOSE

#endif // LOGMACROS_H

