window.onload = init;
function init()
{
	var button = document.getElementById("addButton");
	button.onclick = handleButtonClick;	
}

function handleButtonClick()
{
	var textInput = document.getElementById("songTextInput");
	var songName = textInput.value;
    /*if (songName.length != 0)
		alert("我按下了按钮 呵呵！ 添加了一个歌曲 他的名字是：" + songName);	
	else
		alert("按下按钮为什么什么都不输入啊 你是不是傻");-*/
	var li = document.createElement("li");
	li.innerHTML = songName;
	var ul = document.getElementById("playlist");
	ul.appendChild(li)
}



