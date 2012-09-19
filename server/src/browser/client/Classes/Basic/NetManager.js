var lc = lc = lc || {};

g_sharedNetManager = null;

lc.NetManager = cc.Class.extend({
    m_iToken:3,
    m_strURL:"http://localhost:22222/game/",
    m_iIndex:1,
    _init:function(){

    },
    getPlatfrom:function(){
        //get current platfrom,return the platfrom of a string;
        return "desktop"
    },
    createRequest:function(){
        var request;
        var platfrom = this.getPlatfrom();
        if(platfrom == lc.g_platfromNames[lc.modePlatfromType.kModeDesktop]){
            request = new lc.CustomXMLHTTPRequest();
        }else{
            // new js binding object for ccnetwork;
        }

        return request;
    },
    //target指向回调的作用域
    sendRequest:function(modEnum,doEnum,requestData,target,responseCallback,errorCallback){
        var request = this.createRequest();
        var url = this.generatePostURL(modEnum,doEnum);
        var parameter = this.generatePostJsonData(modEnum,doEnum,requestData);
        if(parameter == null){
            //send a get request;
        }else{
            //send a post request;
            request.sendRequest(url,parameter,target,responseCallback,errorCallback);
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


