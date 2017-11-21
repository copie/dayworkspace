log = console.log
window.onload = init;
function check_num(fun) {
    return function wapp(value) {
        if (100 <= value && value <= 999) {
            log(value)
            return fun(value)
        }
        else {
            alert("傻逼")
        }
    }
}
function check_none(fun) {
    return function wapp(site,ul) {
        if (ul.childElementCount == 0) {
            alert("没有了还删 傻逼")
        } else {
            fun(site,ul)
        }
    }
}
function create_li(value) {
    ch = document.createElement("li")
    ch.innerText = value
    return ch
}
create_li = check_num(create_li)
// 装饰 create_li 判断 输入数据

function insert_li(site, ul) {
    ch = create_li(document.getElementById('text').value)
    if (ch) {
        if (site == "right") {
            ul.appendChild(ch)
        } else {
            log(ul.firstChild)
            ul.insertBefore(ch,ul.firstChild)
        }
    }
}
function del_li(site, ul) {
    if (site == 'right') {
        ul.removeChild(ul.lastChild) 
    } else {
        ul.removeChild(ul.firstChild)
    }
}
del_li = check_none(del_li)
// 装饰li
function init() {
    var ul = document.getElementById('num_list')
    log(ul)
    document.getElementById('right_in').onclick = function () {
        insert_li("right", ul)
    }
    document.getElementById('left_in').onclick = function () {
        insert_li('left', ul)
    }
    document.getElementById("right_out").onclick = function () {
        del_li('right',ul)
    }
    document.getElementById('left_out').onclick = function () {
        del_li('left', ul)
    }
    
}

