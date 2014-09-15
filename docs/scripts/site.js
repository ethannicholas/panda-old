function applyToTree(node, f) {
    f(node)
    node = node.firstChild
    while (node) {
        applyToTree(node, f)
        node = node.nextSibling
    }
}

function supportsLocalStorage() {
    try {
        return 'localStorage' in window && window['localStorage'] !== null
    } 
    catch (e) {
        return false
    }
}

function prepareToC(imagePath) {
    if (supportsLocalStorage()) {
        applyToTree(document.body, function (node) {
            if (node.className === "collapse") {
                if (localStorage[node.id] === "open")
                    node.className = "open"
                else
                    node.className = "closed"
                node.innerHTML = '<img src="' + imagePath + "/" + 
                        node.className + '.png" class="bullet"/>' + 
                        node.innerHTML.trim()
                var img = node.firstChild
                img.onmousedown = function() {
                    if (node.className === "open")
                        node.className = "closed"
                    else
                        node.className = "open"
                    img.src = imagePath + "/" + node.className + ".png"
                    localStorage[node.id] = node.className
                }
            }
        })
    }
}
