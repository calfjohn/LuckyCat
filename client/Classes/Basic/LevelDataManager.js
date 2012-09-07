/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-9-6
 * Time: 下午4:33
 * To change this template use File | Settings | File Templates.
 */

var lc = lc = lc || {};

lc.LevelDataManager = cc.Class.extend({
    m_mapBible : [],
    m_mapActorLevelUpgrade : [],
    ctor:function () {
        this._super();
    },
    //在这里初始化数据,读取数据库
    init:function () {
        this._super();


        return true;
    },
    reload:function () {
        this.m_mapBible.length = 0;

        this.init();
    },
    changePageState:function (chapterId, pageId)
    {
        var pPage = null;
        for (var iterTemp = 0;
             iterTemp != this.m_mapBible[1].listChapter.length;
             iterTemp++)
        {
            var tChapter = this.m_mapBible[1].listChapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                for (var iterPage = 0;
                iterPage != tChapter.listPage.length;
                iterPage++)
                {
                    var tPage = tChapter.listPage[iterPage];
                    if (tPage.id == pageId)
                    {
                        pPage = tPage;
                        pPage.state = 1;
                        break;
                    }
                }
                break;
            }
        }

        return pPage != null;
    },
    getPage:function(chapterId, pageId)
    {
        var pPage = null;
        for (var iterTemp = 0;
             iterTemp != this.m_mapBible[1].listChapter.length;
             iterTemp++)
        {
            var tChapter = this.m_mapBible[1].listChapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                for (var iterPage = 0;
                iterPage != tChapter.listPage.length;
                iterPage++)
                {
                    pPage = tChapter.listPage[iterPage];
                    if (pPage.id == pageId)
                    {
                        break;
                    }
                }
                break;
            }
        }

        return pPage;
    },
    getNewPage:function (chapterId)
    {
        var pPage = null;
        for (var iterTemp = 0;
             iterTemp != this.m_mapBible[1].listChapter.length;
             iterTemp++)
        {
            var tChapter = this.m_mapBible[1].listChapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                for (var iterPage = 0;
                iterPage != tChapter.listPage.length;
                iterPage++)
                {
                    pPage = tChapter.listPage[iterPage];
                    if (pPage.state != 1)
                    {
                        break;
                    }
                }
                break;
            }
        }

        return pPage;
    },
    getChapter:function (chapterId)
    {
        var pRetValue = null;
        for (var iterTemp = 0;
             iterTemp != this.m_mapBible[1].listChapter.length;
             iterTemp++)
        {
            var tChapter = this.m_mapBible[1].listChapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                pRetValue = tChapter;
            }
        }

        return pRetValue;
    },
    isChapterEnd:function (chapterId)
    {
        var bRetValue = false;
        for (var iterTemp = 0;
             iterTemp != this.m_mapBible[1].listChapter.length;
             iterTemp++)
        {
            var tChapter = this.m_mapBible[1].listChapter[iterTemp];
            if (tChapter.id == chapterId && tChapter.listPage.length > 0)
            {
                var lastIndex = tChapter.listPage.length == 0 ? 0 : (tChapter.listPage.length - 1);
                if (tChapter.listPage[lastIndex].state == 1)
                {
                    bRetValue = true;
                    break;
                }
            }
        }

        return bRetValue;
    },
    isLastPageOfChapter:function (chapterId, pageId)
    {
        var bRetValue = false;

        for (var iterTemp = 0;
             iterTemp != this.m_mapBible[1].listChapter.length;
             iterTemp++)
        {
            var tChapter = this.m_mapBible.listChapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                var lastIndex = tChapter.listPage.length == 0 ? 0 : (tChapter.listPage.length - 1);
                if (tChapter.listPage[lastIndex].id == pageId)
                {
                    bRetValue = true;
                    break;
                }
            }
        }

        return bRetValue;
    },
    getBible:function ()
    {
        return this.m_mapBible[1];
    },
    setMapActorLevelUpgrade:function ( tmpList)
    {

    },
    deleteMapActorLevelUpgrade:function ()
    {
        this.m_mapActorLevelUpgrade.length = 0;
    },
    getMapActorLevelUpgrade:function (tLevel)
    {
        var pRetValue = null;
        var _iter = this.m_mapActorLevelUpgrade.find(tLevel);
        for (var _index = 0, _index < this.m_mapActorLevelUpgrade.length; _index++)
        {
            var tActorLevelUpgrade = this.m_mapActorLevelUpgrade[_index];
            if (tActorLevelUpgrade.level == tLevel)
            {
                pRetValue = tActorLevelUpgrade;
                break;
            }
        }

        return pRetValue;
    }
});

lc.fristLevelDataManager = true;
lc.s_SharedLevelDataManager = null;

lc.LevelDataManager.shareLevelDataManager = function (pOwner) {
    if (lc.s_SharedLevelDataManager) {
        lc.fristLevelDataManager = false;
        lc.s_SharedLevelDataManager = new lc.LevelDataManager();
        lc.s_SharedLevelDataManager.init();
    }
    return cc.s_SharedLevelDataManager;
};