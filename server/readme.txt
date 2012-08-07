1. run server
    a. Install nodejs from www.nodejs.org , remember add node binary path to system path variable.
    b. Install mysql from http://dev.mysql.com/downloads/ for local development, or use public mysql server instead.
    d. Run server from console: node <LuckCat dir>/server/src/index.js .

2. development
    a. Install webstorm from http://www.jetbrains.com/webstorm/ for server development.
    b. Open Directory <LuckCat dir> from webstorm.
    c. Menu->Run->Edit configuration... then create nodejs config by click plus button in the top-left conner. set Path to node App JS file: <LuckCat dir>/server/src/index.js
    d. click run/debug button to run server.
    e. File->Setting...->JavaScript->Node.js->Configuration..., download nodejs src for code auto-complete.

3. hot reload
    a. Open console.
    b. cd <project dir>/server
    c. Run server like this: cmd\supervisor .\src\index.js , make sure give the right authority to the binary operation refered.
    d. When the js codes in .\src directory has changed, the server will reload automatically.

3. Unit test
    a. Open console.
    b. cd <project dir>/server
    c. Run server like this: cmd\mocha .\test\game\GameServer.test.js , make sure give the right authority to the binary operation refered.

4. API document
    Refer to server/doc/HowToBuildAPIDocument.txt.