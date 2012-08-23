
require("../../system/Log");

var reference = require("../../system/ApiReference");

var reference_1 = {
    desc:
        "<p>代码中内嵌的协议文档编写示例</p>" +
        "<ul>" +
        "   <li>desc字段用来说明当前协议的功能</li>" +
        "   <li>in字段用来说明输入参数</li>" +
        "   <li>out字段用来说明返回结果</li>" +
        "</ul>",

    in: {
        field_1:
            "<p>第一个输入参数，用来示例</p>" +
                "<ul>" +
                "<li>整数</li>" +
                "<li>取值为1~3</li>" +
                "</ul>",
        field_2:
            "<p>第二个参数，用来示例</p>" +
                "<ul>" +
                "<li>字符串</li>" +
                "<li>不为空串</li>" +
                "</ul>"
    },

    out: {
        field_3:
            "<p>第一个输出参数</p>"
    },
    result: {
        0:
            "<p>操作成功</p>" +
                "可能还需要一个专门定义返回值的地方。",
        1:
            "<p>某个错误标识</p>"
    }
};

module.exports.initReference = function(ref) {
    // 添加一下api模块的说明，一般handler不需要这类代码
    // 添加模块的说明的代码建议在具体的模块初始化的时候做
    var mod = reference.getReference("/game/api_demo");
    mod.desc =
        "<h3>API模块</h3>" +
            "<p>这个模块的文档是用来示例的，演示如何添加API文档和显示表现，具体函数请点击左边函数名。</p>" +
            "<img src='/img/api_demo.png'/>";

    // 当前是版本1 所以填写文档到ref[1]
    ref[1] = reference_1;
};

module.exports.handler = function (req, res, next) {
    var log = new Log("game.ApiReference");
    var path = req._parsedUrl.pathname;
    var nodes = reference.locate(path);
    var dirs = nodes[path];
    var mods = nodes[dirs[0]];
    var api = nodes[dirs[dirs.length - 1]];
    log.d(JSON.stringify(api));
    res.render("./views/api_reference", {
        "namespace":dirs[0],
        "mod": dirs[1],
        "action": dirs[2],
        "mods": mods,
        "api":api});
};
