1. run server
    a. Install nodejs from www.nodejs.org.
    b. Install mysql from http://dev.mysql.com/downloads/ .
    d. Run server from console: node <LuckCat dir>/server/src/index.js .

2. development
    a. Install webstorm from http://www.jetbrains.com/webstorm/ for server development.
    b. Open Directory <LuckCat dir> from webstorm.
    c. Menu->Run->Edit configuration... then create nodejs config. set Path to node App JS file: <LuckCat dir>/server/src/index.js
    d. Run server.
    e. File->Setting...->JavaScript->Node.js->Configuration..., download nodejs src for code auto-complete.

3. hot reload
    a. Open console.
    b. cd <project dir>/server
    c. Run server like this: cmd\supervisor .\src\index.js
    d. When the js codes in .\src directory has changed, the server will reload automatically.

3. Unit test


4. API document
    Refer to server/doc/HowToBuildAPIDocument.txt.