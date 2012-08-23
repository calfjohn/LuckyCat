
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
        desc: "这里说明输入的参数",
        type: "输入的类型或什么类型的数组， eg. Null/Int/LongLong/Float/String/Map or Array(Int/...)",
        field:{ // 如果返回的是Map或Map的数组，此处用来说明对象或数组的key-value对
            field_1:
                "第一个输入参数，用来示例",
            field_2:
                "第二个参数，用来示例"
        }
    },

    out: {
        desc: "这里说明返回的结果",
        type: "返回什么类型，如果不是对象或对象数组，可以没有field字段",
        field: {
            field_1:
                "<p>第一个输出参数</p>"
        }
    },
    result: {
        0:
            "操作成功",
        1:
            "某个错误标识"
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

    var data = {
        namespace: dirs[0],
        mod: dirs[1],
        mod_do: dirs[2]
    };
    switch (dirs.length) {
        case 3: // dirs包含 namespace module action
            data.api_content = nodes[dirs[2]];
            res.render("./views/api_content", data);
            break;
        case 2: // dirs包含 namespace module
            data.module_content = nodes[dirs[1]];
            res.render("./views/module_content", data);
            break;
        default:
            data.namespace_content = nodes[dirs[0]];
            res.render("./views/api_reference", data);
            break;
    }
};
