/**
 * ApiReference path format: /<namespace>/<mod>/<do>
 * ApiReference structure look like this:
 *  ApiReference._reference = {
 *      game:{  // namespace for game server
 *          actor{  // actor module
 *              getBasicInfo:{  // do action: getBasicInfo
 *                  1:{             // version 1
 *                      in:{            // input parameters
 *                      },
 *                      out:{           // output data
 *                      },
 *                      result: []
 *                  },
 *                  2:{             // version 2
 *                      ... ...
 *                  },
 *                  ... ...
 *              },
 *              getEquipmentInfo:{// do action: getEquipmentInfo
 *                  ... ...
 *              },
 *              ... ...
 *          },
 *          battle:{// battle module
 *              ... ...
 *          },
 *          ... ...
 *      },
 *      admin:{ // namespace for admin server
 *          ... ...
 *      },
 *      ... ...
 *  }
 */

ApiReference = {
    _reference: {},
    /**
     * 在ApiReference._reference中查找路径对应的节点
     * @param path  要查找的的节点(eg. /a/b/c)， 不能为空、""、"/"等
     * @private
     * @return      返回路径中每个目录名对应的节点，如果某个目录还没有节点，则为空节点
     *              (eg. {$(path): [a, b, c], a: objectA, b: objectB, c: {}})
     */
    locate: function(path) {
        var dirs = path.split("/");
        // 去掉path首尾的'/'导致的split出的空元素
        if (dirs[0] == "") {
            dirs.shift();
        }
        if (dirs[dirs.length - 1] == "") {
            dirs.pop();
        }
        var nodes = {};
        nodes[path] = dirs;
        var root = ApiReference._reference;
        for (var i = 0; i < dirs.length; ++i) {
            var dir = dirs[i];
            // 如果节点不存在，则插入空节点
            if (! root[dir]) {
                root[dir] = {};
            }
            root = root[dir];
            nodes[dir] = root;
        }
        return nodes;
    },

    setReference: function(path, reference) {
        if (! path || ! path.length || path == "/" || ! reference) {
            return;
        }
        var nodes = ApiReference.locate(path);
        var dirs = nodes[path];
        // 把reference添加到最后的节点上
        nodes[dirs[dirs.length - 2]][dirs[dirs.length - 1]] = reference;
    },

    getReference: function(path) {
        if (! path || ! path.length || path == "/") {
            return ApiReference._reference;
        }
        var nodes = ApiReference.locate(path);
        var dirs = nodes[path];
        return nodes[dirs[dirs.length - 1]];
    }
};

module.exports = ApiReference;