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

var MyLayer = cc.Layer.extend({
    isMouseDown:false,
    helloImg:null,
    helloLabel:null,
    circle:null,
    sprite:null,

    init:function () {

        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask director the window size
        var size = cc.Director.getInstance().getWinSize();

        // add a "close" icon to exit the progress. it's an autorelease object
        var closeItem = cc.MenuItemImage.create(
            "../Resources/CloseNormal.png",
            "../Resources/CloseSelected.png",
            this,
            function () {
                history.go(-1);
            });
        closeItem.setAnchorPoint(cc.p(0.5, 0.5));

        var menu = cc.Menu.create(closeItem, null);
        menu.setPosition(cc.PointZero());
        this.addChild(menu, 1);
        closeItem.setPosition(cc.p(size.width - 20, 20));

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        this.helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38);
        // position the label on the center of the screen
        this.helloLabel.setPosition(cc.p(size.width / 2, size.height - 40));
        // add the label as a child to this layer
        this.addChild(this.helloLabel, 5);

        var lazyLayer = new cc.LazyLayer();
        this.addChild(lazyLayer);

        // add "Helloworld" splash screen"
        this.sprite = cc.Sprite.create("../Resources/HelloWorld.png");
        this.sprite.setAnchorPoint(cc.p(0.5, 0.5));
        this.sprite.setPosition(cc.p(size.width / 2, size.height / 2));

        lazyLayer.addChild(this.sprite, 0);

        var url = "http://192.168.0.51:22222/game/pk/getPKList/";
        var parameter = "{\"header\":{\"token\": \"3\", \"index\": 1}, \"meta\":{\"mod\": \"pk\", \"do\": \"getPKList\", \"ver\":1, \"in\":{}}}"
        sendAsynchronRequest(url,parameter,loadCallBack);

        return true;
    }

});

var xmlHttp;
function createXMLHttpRequest(){
    //Mozilla 浏览器（将XMLHttpRequest对象作为本地浏览器对象来创建）
    if(window.XMLHttpRequest){ //Mozilla 浏览器
        xmlHttp = new XMLHttpRequest();
    }else if(window.ActiveXObject) { //IE浏览器
        //IE浏览器（将XMLHttpRequest对象作为ActiveX对象来创建）
        try{
            xmlHttp = new ActiveXObject("Msxml2.XMLHTTP");
        }catch(e){
            try {
                xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
            }catch(e){}
        }
    }
    if(xmlHttp == null){
        alert("不能创建XMLHttpRequest对象");
        return false;
    }
}
//用于发出异步请求的方法
function sendAsynchronRequest(url,parameter,callback){
    createXMLHttpRequest();
    if(parameter == null){
        //设置一个事件处理器，当XMLHttp状态发生变化，就会出发该事件处理器，由他调用
        //callback指定的javascript函数
        xmlHttp.onreadystatechange = callback;
        //设置对拂去其调用的参数（提交的方式，请求的的url，请求的类型（异步请求））
        xmlHttp.open("GET",url,true);//true表示发出一个异步的请求。
        xmlHttp.send(null);
    }else{
        xmlHttp.onreadystatechange = callback;
        xmlHttp.open("POST",url,true);
        xmlHttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
        //xmlHttp.setRequestHeader("Access-Control-Allow-Origin","*");
        xmlHttp.send(parameter);
    }
}

// 指定回调方法
function loadCallBack(){
    try
    {
        if (xmlHttp.readyState == 4) {
            if (xmlHttp.status == 200) {
                if(xmlHttp.responseText != null && xmlHttp.responseText != ""){
                    var divProid = document.getElementById('videolist');
                    divProid.innerHTML = xmlHttp.responseText;
                    for(i=0;i<len;i++)
                    {
                        var video_url = document.getElementById("videolist"+i+"").href;
                        if(video_url != undefined && video_url != null && video_url != ""){
                            window.location.href = video_url;
                        }
                    }
                }
            }
        }
        if (xmlHttp.readyState == 1)
        {
            alert("正在加载连接对象......");
        }
        if (xmlHttp.readyState == 2)
        {
            alert("连接对象加载完毕。");
        }
        if (xmlHttp.readyState == 3)
        {
            alert("数据获取中......");
        }
    }
    catch (e)
    {
        //alert(e);
    }
}

var MyScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new MyLayer();
        this.addChild(layer);
        layer.init();
    }
});
