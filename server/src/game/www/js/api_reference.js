$(function(){
    $("#module_list").accordion({
        header: "h3",
        fillSpace: true,
        changestart: function(event, ui) {
            var meta = document.getElementById("meta");
            var namespace = meta.getAttribute("namespace");
            var url = "/" + namespace + "/" + ui.newContent.context.outerText.replace(/[\r\n]/g, "");
            document.getElementById("content").setAttribute("src", url);
        }
    });
});