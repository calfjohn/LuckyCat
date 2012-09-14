/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

var CCB_VERSION = 2;

var CCB_PROPTYPE_POSITION = 0;
var CCB_PROPTYPE_SIZE = 1;
var CCB_PROPTYPE_POINT = 2;
var CCB_PROPTYPE_POINTLOCK = 3;
var CCB_PROPTYPE_SCALELOCK = 4;
var CCB_PROPTYPE_DEGREES = 5;
var CCB_PROTYPE_INTEGER = 6;
var CCB_PROTYPE_FLOAT = 7;
var CCB_PROTYPE_FLOATVAR = 8;
var CCB_PROTYPE_CHECK = 9;
var CCB_PROTYPE_SPRITEFRAME = 10;
var CCB_PROTYPE_TEXTURE = 11;
var CCB_PROTYPE_BYTE = 12;
var CCB_PROTYPE_COLOR3 = 13;
var CCB_PROTYPE_COLOR4VAR = 14;
var CCB_PROTYPE_FLIP = 15;
var CCB_PROTYPE_BLENDFUNC = 16;
var CCB_PROTYPE_FNTFILE = 17;
var CCB_PROTYPE_TEXT = 18;
var CCB_PROTYPE_FONTTTF = 19;
var CCB_PROTYPE_INTEGERLABELED = 20;
var CCB_PROTYPE_BLOCK = 21;
var CCB_PROTYPE_ANIMATION = 22;
var CCB_PROTYPE_CCBFILE = 23;
var CCB_PROTYPE_STRING = 24;
var CCB_PROTYPE_BLOCKCCCONTROL = 25;
var CCB_PROTYPE_FLOATSCALE = 26;

var CCB_FLOAT0 = 0;
var CCB_FLOAT1 = 1;
var CCB_FLOAT_MINUS1 = 2;
var CCB_FLOAT05 = 3;
var CCB_FLOAT_INTEGER = 4;
var CCB_FLOAT_FULL = 5;

var CCB_PLATFORM_ALL = 0;
var CCB_PLATFORM_IOS = 1;
var CCB_PLATFORM_MAC = 2;

var CCB_TARGETTYPE_NONE = 0;
var CCB_TARGETTYPE_DOCUMENTROOT = 1;
var CCB_TARGETTYPE_OWNER = 2;

var CCB_POSITIONTYPE_RELATIVE_BOTTOM_LEFT = 0;
var CCB_POSITIONTYPE_RELATIVE_TOP_LEFT = 1;
var CCB_POSITIONTYPE_RELATIVE_TOP_RIGHT = 2;
var CCB_POSITIONTYPE_RELATIVE_BOTTOM_RIGHT = 3;
var CCB_POSITIONTYPE_PERCENT = 4;

var CCB_SIZETYPE_ABSOLUTE = 0;
var CCB_SIZETYPE_PERCENT = 1;
var CCB_SIZETYPE_RELATIVE_CONTAINER = 2;
var CCB_SIZETYPE_HORIZONTAL_PERCENT = 3;
var CCB_SIZETYPE_VERTICAL_PERCENT = 4;

var CCB_SCALETYPE_ABSOLUTE = 0;
var CCB_SCALETYPE_MULTIPLY_RESOLUTION = 1;

/**
 * Parse CCBI file which is generated by CocosBuilder
 */
cc.CCBReader = cc.Class.extend({
    _ccbRootPath:null,
    _rootCCBReader:false,

    _bytes:0,
    _currentByte:0,
    _currentBit:0,
    _owner:null,
    _rootNode:null,
    _rootContainerSize:null,
    _resolutionScale:0,

    _ccNodeLoaderLibrary:null,
    _ccNodeLoaderListener:null,
    _ccbMemberVariableAssigner:null,
    _ccbSelectorResolver:null,

    _stringCache:null,
    _loadedSpriteSheets:null,

    ctor:function (ccNodeLoaderLibrary, ccbMemberVariableAssigner, ccbSelectorResolver, ccNodeLoaderListener) {
        this._stringCache = [];
        this._loadedSpriteSheets = [];

        if (ccNodeLoaderLibrary instanceof cc.CCBReader) {
            var ccbReader = ccNodeLoaderLibrary;
            this._rootNode = null;
            this._rootCCBReader = false;

            /* Borrow data from the 'parent' CCBReader. */
            this._resolutionScale = ccbReader._resolutionScale;
            this._loadedSpriteSheets = ccbReader._loadedSpriteSheets;
            this._ccNodeLoaderLibrary = ccbReader._ccNodeLoaderLibrary;

            this._ccbMemberVariableAssigner = ccbReader._ccbMemberVariableAssigner;
            this._ccbSelectorResolver = ccbReader._ccbSelectorResolver;
            this._ccNodeLoaderListener = ccbReader._ccNodeLoaderListener;
        } else {
            this._rootNode = null;
            this._rootCCBReader = true;

            this._ccNodeLoaderLibrary = ccNodeLoaderLibrary;
            this._ccbMemberVariableAssigner = ccbMemberVariableAssigner;
            this._ccbSelectorResolver = ccbSelectorResolver;
            this._ccNodeLoaderListener = ccNodeLoaderListener;

            this._resolutionScale = 1;
        }
    },

    readNodeGraphFromFile:function (ccbRootPath, ccbFileName, owner, rootContainerSize) {
        rootContainerSize = rootContainerSize || cc.Director.getInstance().getWinSize();

        this._ccbRootPath = ccbRootPath;

        var path = cc.FileUtils.getInstance().fullPathFromRelativePath(ccbRootPath + ccbFileName);

        this._bytes = cc.FileUtils.getInstance().getFileData(path);

        this._currentByte = 0;
        this._currentBit = 0;

        this._owner = owner;
        this._rootContainerSize = rootContainerSize;

        var node = null;
        if (this._readHeader() && this._readStringCache()) {
            node = this._readNodeGraph();
        }
        return node;
    },

    getCCBMemberVariableAssigner:function () {
        return this._ccbMemberVariableAssigner;
    },

    getCCBSelectorResolver:function () {
        return this._ccbSelectorResolver;
    },

    getCCBRootPath:function () {
        return this._ccbRootPath;
    },

    getOwner:function () {
        return this._owner;
    },

    getRootNode:function () {
        return this._rootNode;
    },

    getContainerSize:function (node) {
        if (node) {
            return node.getContentSize();
        } else {
            return this._rootContainerSize;
        }
    },

    getResolutionScale:function () {
        return this._resolutionScale;
    },

    isSpriteSheetLoaded:function (spriteSheet) {
        return this._loadedSpriteSheets.indexOf(spriteSheet) > -1;
    },

    addLoadedSpriteSheet:function (spriteSheet) {
        // Since std::set<string> will copy the string from pSpriteSheet, we needn't to retain 'pSpriteSheet'.
        //    pSpriteSheet.retain();
        this._loadedSpriteSheets.push(spriteSheet);
    },

    readInt:function (signed) {
        var numBits = 0;
        while (!this._getBit()) {
            numBits++;
        }

        var current = 0;
        for (var a = numBits - 1; a >= 0; a--) {
            if (this._getBit()) {
                current |= 1 << a;
            }
        }
        current |= 1 << numBits;

        var num;
        if (signed) {
            var s = current % 2;
            if (s) {
                num = 0|(current / 2);
            } else {
                num = 0|(-current / 2);
            }
        } else {
            num = current - 1;
        }

        this._alignBits();

        return num;
    },

    readByte:function () {
        var byteValue = this._bytes[this._currentByte];
        this._currentByte++;
        return byteValue;
    },

    readBool:function () {
        return (0 != this.readByte());
    },

    readFloat:function () {
        var type = this.readByte();

        switch (type) {
            case CCB_FLOAT0:
                return 0;
            case CCB_FLOAT1:
                return 1;
            case CCB_FLOAT_MINUS1:
                return -1;
            case CCB_FLOAT05:
                return 0.5;
            case CCB_FLOAT_INTEGER:
                return this.readInt(true);
            default:
                /* using a memcpy since the compiler isn't
                 * doing the float ptr math correctly on device.
                 */
                var pF =  this._decodeFloat(23,8); //this._bytes + this._currentByte;
                //this._currentByte += 4;
                return pF;
        }
    },

    _decodeFloat: function(precisionBits, exponentBits){
        var length = precisionBits + exponentBits + 1;
        var size = length >> 3;
        this._checkSize(length);

        var bias = Math.pow(2, exponentBits - 1) - 1;
        var signal = this._readBitsOnly(precisionBits + exponentBits, 1, size);
        var exponent = this._readBitsOnly(precisionBits, exponentBits, size);
        var significand = 0;
        var divisor = 2;
        var curByte = 0; //length + (-precisionBits >> 3) - 1;
        do {
            var byteValue = this._readByteOnly(++curByte, size);
            var startBit = precisionBits % 8 || 8;
            var mask = 1 << startBit;
            while (mask >>= 1) {
                if (byteValue & mask) {
                    significand += 1 / divisor;
                }
                divisor *= 2;
            }
        } while (precisionBits -= startBit);

        this._currentByte += size;

        return exponent == (bias << 1) + 1 ? significand ? NaN : signal ? -Infinity : +Infinity
            : (1 + signal * -2) * (exponent || significand ? !exponent ? Math.pow(2, -bias + 1) * significand
            : Math.pow(2, exponent - bias) * (1 + significand) : 0);
    },

    _readBitsOnly: function (start, length, size) {
        var offsetLeft = (start + length) % 8;
        var offsetRight = start % 8;
        var curByte = size - (start >> 3) - 1;
        var lastByte = size + (-(start + length) >> 3);
        var diff = curByte - lastByte;

        var sum = (this._readByteOnly(curByte, size) >> offsetRight) & ((1 << (diff ? 8 - offsetRight : length)) - 1);

        if (diff && offsetLeft) {
            sum += (this._readByteOnly(lastByte++, size) & ((1 << offsetLeft) - 1)) << (diff-- << 3) - offsetRight;
        }

        while (diff) {
            sum += this._shl(this._readByteOnly(lastByte++, size), (diff-- << 3) - offsetRight);
        }

        return sum;
    },

    _readByteOnly: function (i, size) {
        return this._bytes[this._currentByte + size -i -1];
    },

    _shl: function (a, b){
        for (++b; --b; a = ((a %= 0x7fffffff + 1) & 0x40000000) == 0x40000000 ? a * 2 : (a - 0x40000000) * 2 + 0x7fffffff + 1);
        return a;
    },

    _checkSize: function (neededBits) {
        if (!(this._currentByte + Math.ceil(neededBits / 8) < this._bytes.length)) {
            throw new Error("Index out of bound");
        }
    },

    readCachedString:function () {
        var i = this.readInt(false);
        return this._stringCache[i];
    },

    _readHeader:function () {
        /* If no bytes loaded, don't crash about it. */
        if (this._bytes == null) {
            return false;
        }

        /* Read magic bytes */
        var magicBytes = this._readStringFromBytes(this._currentByte, 4, true);
        this._currentByte += 4;

        if (magicBytes != 'ccbi') {
            return false;
        }

        /* Read version. */
        var version = this.readInt(false);
        if (version != CCB_VERSION) {
            cc.log("WARNING! Incompatible ccbi file version (file: " + version + " reader: " + CCB_VERSION + ")");
            return false;
        }

        return true;
    },

    _readStringFromBytes:function (startIndex, strLen, reverse) {
        reverse = reverse || false;
        var strValue = "";
        var i;
        if (reverse) {
            for (i = strLen - 1; i >= 0; i--) {
                strValue += String.fromCharCode(this._bytes[this._currentByte + i]);
            }
        } else {
            for (i = 0; i < strLen; i++) {
                strValue += String.fromCharCode(this._bytes[this._currentByte + i]);
            }
        }
        return strValue;
    },

    _readStringCache:function () {
        var numStrings = this.readInt(false);
        for (var i = 0; i < numStrings; i++) {
            this._readStringCacheEntry();
        }
        return true;
    },

    _readStringCacheEntry:function () {
        var b0 = this.readByte();
        var b1 = this.readByte();

        var numBytes = b0 << 8 | b1;

        var str = "";
        for (var i = 0; i < numBytes; i++) {
            var hexChar = this._bytes[this._currentByte + i].toString("16").toUpperCase();
            hexChar = hexChar.length > 1?hexChar : "0" + hexChar;
            str += "%" + hexChar;
        }
        str = decodeURIComponent(str);

        this._currentByte += numBytes;
        this._stringCache.push(str);
    },

    _readNodeGraph:function (parent) {
        /* Read class name. */
        var className = this.readCachedString();

        var memberVarAssignmentType = this.readInt(false);
        var memberVarAssignmentName;
        if (memberVarAssignmentType != CCB_TARGETTYPE_NONE) {
            memberVarAssignmentName = this.readCachedString();
        }

        var ccNodeLoader = this._ccNodeLoaderLibrary.getCCNodeLoader(className);
        var node = ccNodeLoader.loadCCNode(parent, this);

        /* Set root node, if not set yet. */
        if (this._rootNode == null) {
            this._rootNode = node;
        }

        if (memberVarAssignmentType != CCB_TARGETTYPE_NONE) {
            var target = null;
            if (memberVarAssignmentType == CCB_TARGETTYPE_DOCUMENTROOT) {
                target = this._rootNode;
            } else if (memberVarAssignmentType == CCB_TARGETTYPE_OWNER) {
                target = this._owner;
            }

            if (target != null) {
                var assigned = false;

                if (target != null && (target.onAssignCCBMemberVariable)) {
                    assigned = target.onAssignCCBMemberVariable(target, memberVarAssignmentName, node);
                }

                if (!assigned && this._ccbMemberVariableAssigner != null && this._ccbMemberVariableAssigner.onAssignCCBMemberVariable) {
                    this._ccbMemberVariableAssigner.onAssignCCBMemberVariable(target, memberVarAssignmentName, node);
                }
            }
        }

        /* Read and add children. */
        var numChildren = this.readInt(false);
        for (var i = 0; i < numChildren; i++) {
            var child = this._readNodeGraph(node);
            node.addChild(child);
        }

        //var nodeAsCCNodeLoaderListener = node;
        if (node != null && node.onNodeLoaded) {
            node.onNodeLoaded(node, ccNodeLoader);
        } else if (this._ccNodeLoaderListener != null) {
            this._ccNodeLoaderListener.onNodeLoaded(node, ccNodeLoader);
        }

        return node;
    },

    _getBit:function () {
        var bit = (this._bytes[this._currentByte] & (1 << this._currentBit)) != 0 ;

        this._currentBit++;

        if (this._currentBit >= 8) {
            this._currentBit = 0;
            this._currentByte++;
        }

        return bit;
    },

    _alignBits:function () {
        if (this._currentBit) {
            this._currentBit = 0;
            this._currentByte++;
        }
    },

    _readUTF8:function () {
    }
});

cc.CCBReader.lastPathComponent = function (pathStr) {
    var slashPos = pathStr.lastIndexOf("/");
    if (slashPos != -1) {
        return pathStr.substring(slashPos + 1, pathStr.length - slashPos);
    }
    return pathStr;
};

cc.CCBReader.deletePathExtension = function (pathStr) {
    var dotPos = pathStr.lastIndexOf(".");
    if (dotPos != -1) {
        return pathStr.substring(0, dotPos);
    }
    return pathStr;
};

cc.CCBReader.toLowerCase = function (sourceStr) {
    return sourceStr.toLowerCase();
};

cc.CCBReader.endsWith = function (sourceStr, ending) {
    if (sourceStr.length >= ending.length)
        return (sourceStr.lastIndexOf(ending) == 0);
    else
        return false;
};

cc.CCBReader.concat = function (stringA, stringB) {
    return stringA + stringB;
};

