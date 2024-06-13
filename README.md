# 系统架构
```plaintext
+--------------------------------------------------------+
|                      Frontend                          |
|                     (Vue.js 3.0)                       |
|                                                        |
|  +-----------------------------------------------+     |
|  |                User Interface                 |     |
|  |  - Login Form                                 |     |
|  |  - Registration Form                          |     |
|  |  - Route Planner                              |     |
|  |  - Diary Management                           |     |
|  +-----------------------------------------------+     |
|                                                        |
|  Sends HTTP requests to the backend via Axios          |
+----------------------|---------------------------------+
                       |
                       v
+----------------------|---------------------------------+
|                  Backend (Node.js/Express)             |
|                                                        |
|  +-----------------------------------------------+     |
|  |            HTTP Request Handlers              |     |
|  |  - /api/login                                 |     |
|  |  - /api/register                              |     |
|  |  - /api/recommendation                        |     |
|  |  - /api/route-plan                            |     |
|  |  - /api/diary-* (various endpoints)           |     |
|  +-----------------------------------------------+     |
|                                                        |
|  Uses child_process.spawn to execute C++ programs      |
|  and handle their output and errors.                   |
+----------------------|---------------------------------+
                       |
                       v
+----------------------|--------------------------------------------------+
|                       C++ Programs                                      |
|                                                                         |
|  +--------------------------+   +-----------------------------------+   |
|  |     Login Program        |   |      Register Program             |   |
|  |     - login              |   |      - register                   |   |
|  +--------------------------+   +-----------------------------------+   |
|                                                                         |
|  +--------------------------+   +-----------------------------------+   |
|  |  Route Planner Program   |   |    Diary Management Programs      |   |
|  |  - routePlanner          |   |    - diaryWrite                   |   |
|  |  - routePlannerSc        |   |    - diaryRead                    |   |
|  +--------------------------+   |    - diarySearch                  |   |
|                                 |    - diaryDownload                |   |
|  C++ programs perform specific  +-----------------------------------+   |
|  tasks and return results or errors to the backend.                     |
+----------------------|--------------------------------------------------+
                       |
                       |
                       |
                       v
+----------------------|--------------------------------------------------+
|                      Database (MySQL 8.0)                               |
|                                                                         |
|  +----------------+   +-----------------+   +-------------------+       |
|  |  User Data     |   |  Diary Entries  |   |  Route Info       |       |
|  |  - Users       |   |  - Diaries      |   |  - Routes         |       |
|  +----------------+   +-----------------+   +-------------------+       |
|                                                                         |
|  Stores and retrieves user, diary, and route data.                      |
+-------------------------------------------------------------------------+
```

