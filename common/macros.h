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

/** Namespace Macro: begin. */
#define QTB_BEGIN_NAMESPACE namespace QTB {
/** Namespace Macro: end. */
#define QTB_END_NAMESPACE }

// TODO: This is temporary, while the proper debug macros part of this project gets submitted
#include <QDebug>
#define DEBUG(x) qDebug() << x;
#define DEBUG_TAG(tag, x) qDebug() << "[" << tag << "]" << x;
#define WARNING(x) qWarning() << x;
#define WARNING_TAG(tag, x) qWarning() << "[" << tag << "]" << x;
#define VERBOSE(x) qDebug() << x;
#define VERBOSE_TAG(tag, x) qDebug() << "[" << tag << "]" << "(verbose)" x;
