/**
 * Created with JetBrains WebStorm.
 * User: zhuxiaozhong
 * Date: 12-9-6
 * Time: 下午4:33
 * To change this template use File | Settings | File Templates.
 */

var lc = lc = lc || {};

lc.LevelDataManager = cc.Class.extend({
    _m_mapBible : null,
    _m_mapChapter : null,
    _m_mapPage : null,
    m_mapActorLevelUpgrade : null,
    //在这里初始化数据,读取数据库
    init:function () {
        this._initBible();
        this._initActorLevelUpgrade();
        return true;
    },
    _initBible: function () {
        this._m_mapPage = JSON.parse(cc.SAXParser.shareParser().getList(s_dictPage));

        this._m_mapChapter = JSON.parse(cc.SAXParser.shareParser().getList(s_dictChapter));

        for ( var key in this._m_mapChapter)
        {
            var tChapter = this._m_mapChapter[key];
            tChapter.list_page = [];
            for ( var key_page in this._m_mapPage )
            {
                var tPage = this._m_mapPage[key_page];
                if (tChapter.id == tPage.chapter_id)
                {
                    tChapter.list_page.push(tPage);
                }
            }
            tChapter.list_page.sort(lc.sortById);
        }

        this._m_mapBible = JSON.parse(cc.SAXParser.shareParser().getList(s_dictBible));

        for ( var key in this._m_mapBible )
        {
            var tempBibe = this._m_mapBible[key];
            tempBibe.list_chapter = [];
            for (var key_chapter in this._m_mapChapter )
            {
                var tChapter = this._m_mapChapter[key];
                if (tempBibe.id == tChapter.bible_id)
                {
                    tempBibe.list_chapter.push(tChapter);
                }
            }
            tempBibe.list_chapter.sort(lc.sortById);
        }
    },
    _initActorLevelUpgrade : function () {
        this.m_mapActorLevelUpgrade = JSON.parse(cc.SAXParser.shareParser().getList(s_dictActorLevelUpgrade));
        for (var key in this.m_mapActorLevelUpgrade )
        {
            var temp = this.m_mapActorLevelUpgrade[key];
            if (temp.bonus)
                temp.bonus = JSON.parse(temp.bonus);
        }
    },
    reload:function () {
        this._m_mapBible.length = 0;

        this.init();
    },
    changePageState:function (chapterId, pageId)
    {
        var pPage = null;
        for (var iterTemp = 0;
             iterTemp != this._m_mapBible["" + 1].list_chapter.length;
             iterTemp++)
        {
            var tChapter = this._m_mapBible["" + 1].list_chapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                for (var iterPage = 0;
                iterPage != tChapter.list_page.length;
                iterPage++)
                {
                    var tPage = tChapter.list_page[iterPage];
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
             iterTemp != this._m_mapBible[""+1].list_chapter.length;
             iterTemp++)
        {
            var tChapter = this._m_mapBible[""+1].list_chapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                for (var iterPage = 0;
                iterPage != tChapter.list_page.length;
                iterPage++)
                {
                    pPage = tChapter.list_page[iterPage];
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
             iterTemp != this._m_mapBible[""+1].list_chapter.length;
             iterTemp++)
        {
            var tChapter = this._m_mapBible[""+1].list_chapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                for (var iterPage = 0;
                iterPage != tChapter.list_page.length;
                iterPage++)
                {
                    pPage = tChapter.list_page[iterPage];
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
             iterTemp != this._m_mapBible[""+1].list_chapter.length;
             iterTemp++)
        {
            var tChapter = this._m_mapBible[""+1].list_chapter[iterTemp];
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
             iterTemp != this._m_mapBible[""+1].list_chapter.length;
             iterTemp++)
        {
            var tChapter = this._m_mapBible[""+1].list_chapter[iterTemp];
            if (tChapter.id == chapterId && tChapter.list_page.length > 0)
            {
                var lastIndex = tChapter.list_page.length == 0 ? 0 : (tChapter.list_page.length - 1);
                if (tChapter.list_page[lastIndex].state == 1)
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
             iterTemp != this._m_mapBible[""+1].list_chapter.length;
             iterTemp++)
        {
            var tChapter = this._m_mapBible.list_chapter[iterTemp];
            if (tChapter.id == chapterId)
            {
                var lastIndex = tChapter.list_page.length == 0 ? 0 : (tChapter.list_page.length - 1);
                if (tChapter.list_page[lastIndex].id == pageId)
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
        return this._m_mapBible[""+1];
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
        for (var _index = 0; _index < this.m_mapActorLevelUpgrade.length; _index++)
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

lc.LevelDataManager.getInstance = function (pOwner) {
    if (lc.fristLevelDataManager) {
        lc.fristLevelDataManager = false;
        lc.s_SharedLevelDataManager = new lc.LevelDataManager();
        lc.s_SharedLevelDataManager.init();
    }
    return lc.s_SharedLevelDataManager;
};