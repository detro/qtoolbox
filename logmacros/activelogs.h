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

#ifndef ACTIVE_LOGS_H
#define ACTIVE_LOGS_H

// comment/uncomment these to disable/enable the logs
#define ENABLE_LOGS
#define ENABLE_LOGS_VERBOSE

#ifdef ENABLE_LOGS
        // comment/uncomment these to disable/enable debug/warning/critical level logs
        #define DEBUG_LEVEL_ACTIVE
        #define WARNING_LEVEL_ACTIVE
        #define CRITICAL_LEVEL_ACTIVE
		
		// put here the defines relevant to your cpp files
		
#endif // ENABLE_LOGS
#endif // ACTIVE_LOGS_H
