var lc = lc = lc || {};

g_sharedNetManager = null;

lc.NetManager = cc.Class.extend({
    m_iToken:3,
    m_strURL:"http://localhost:22222/game/",
    m_iIndex:1,
    _init:function(){

    },
    createXMLHttpRequest:function(){
        var xmlhttp;
        //Mozilla 浏览器（将XMLHttpRequest对象作为本地浏览器对象来创建）
        if(window.XMLHttpRequest){ //Mozilla 浏览器
            xmlhttp = new XMLHttpRequest();
        }else if(window.ActiveXObject) { //IE浏览器
            //IE浏览器（将XMLHttpRequest对象作为ActiveX对象来创建）
            try{
                xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
            }catch(e){
                try {
                    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                }catch(e){}
            }
        }
        if(xmlhttp == null){
            //alert("不能创建XMLHttpRequest对象");
            return false;
        }
        return xmlhttp;
    },
    sendRequest:function(modEnum,doEnum,requestData,responseCallback,errorCallback){
        var xhr = this.createXMLHttpRequest();
        var url = this.generatePostURL(modEnum,doEnum);
        var parameter = this.generatePostJsonData(modEnum,doEnum,requestData);
        if(parameter == null){
            //设置一个事件处理器，当XMLHttp状态发生变化，就会出发该事件处理器，由他调用
            //callback指定的javascript函数
            xhr.onreadystatechange = function(){
                if(xhr.readyState == 4){
                    if(xhr.status == 200){
                        responseCallback(xhr.responseText);
                    }
                }
            };
            //设置对其调用的参数（提交的方式，请求的的url，请求的类型（异步请求））
            xhr.open("GET",url,true);//true表示发出一个异步的请求。
            xhr.send(null);
        }else{
            xhr.onreadystatechange = function(){
                if(xhr.readyState == 4){
                    if(xhr.status == 200){
                        responseCallback(xhr.responseText);
                    }
                }
            };
            xhr.open("POST",url,true);
            xhr.setRequestHeader("Content-Type","application/x-www-form-urlencoded;");
            cc.log(parameter);
            xhr.send(parameter);
        }
    },
    generatePostJsonData:function(modEnum,doEnum,requestData){
        var jsonText;
        if(requestData == null || requestData == ""){
            jsonText = "{\"header\":{\"token\": \"" + this.m_iToken + "\", \"index\": " + (this.m_iIndex++) + "}, \"meta\":{\"mod\": \"" + g_modNames[modEnum] + "\", \"do\": \"" + g_doNames[doEnum] + "\", \"ver\":" + g_doVersion[doEnum] + ", \"in\":{}}}";
        }else{
            jsonText = "{\"header\":{\"token\": \"" + this.m_iToken + "\", \"index\": " + (this.m_iIndex++) + "}, \"meta\":{\"mod\": \"" + g_modNames[modEnum] + "\", \"do\": \"" + g_doNames[doEnum] + "\", \"ver\":" + g_doVersion[doEnum] + ", \"in\":{" + requestData + "}}}";
        }
        return jsonText;
    },
    generatePostURL:function(modEnum,doEnum){
        return this.m_strURL + g_modNames[modEnum]+"/"+g_doNames[doEnum]+"/";
    }
});

lc.NetManager.sharedNetManager = function(){
    if(g_sharedNetManager == null){
        g_sharedNetManager = new lc.NetManager();
        g_sharedNetManager._init();
    }
    return g_sharedNetManager;
};


