/*chrome.webRequest.onBeforeRequest.addListener(
	function(details)
	{
		//window.alert(details.url);
	},
	{urls: ["<all_urls>"]}
)       */

var SID = "";
var f = 0
chrome.webNavigation.onCommitted.addListener(function(details) {
		var re = /.*(\?SID=.*)/
		f = 1
//		alert(re.exec(details.url)[1]);
		SID = re.exec(details.url)[1];
	//chrome.tabs.update(details.tabId, {
//				url:"http://" + to
//		});                       
	

},
	{url : [{hostSuffix:"ejudge.lksh.ru", pathContains: "cgi-bin/serve-control"}]}	
//	{urls : ["<all_urls>"]}	
)


chrome.webNavigation.onCommitted.addListener(function(details) {
//		alert(SID);
		if (f > 0){
			f = -1;
			chrome.tabs.update(details.tabId, {
					url:details.url + SID 
			});
		}              
	

},
	{url : [{hostSuffix:"ejudge.lksh.ru", urlSuffix: "stand.php"}]}	
//	{urls : ["<all_urls>"]}	
)

chrome.webNavigation.onCommitted.addListener(function(details) {
//		alert(SID);
		if (f == 1){
			f = 2;
			chrome.tabs.update(details.tabId, {
					url:details.url.split("?")[0] + SID 
			});
		}
		if (f == -1)
			f = 2;       
	

},
	{url : [{hostSuffix:"ejudge.lksh.ru", urlContains: "stand.php?"}]}	
//	{urls : ["<all_urls>"]}	
)